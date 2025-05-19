#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<ctime>
#include"USER.h"
#include"USERRECORDS.h"
#include"FOLDER.h"
#include"RECYCLEBIN.h"
#include"FILE.h"
#include"GDRIVE.h"
#include"COLOR.h"
using namespace std;

// Finds and returns a user node by username
UserNode* GDrive::findUser(string userName) {
	UserNode* currentUser = this->users;
	while (currentUser != nullptr) {
		if (currentUser->user->username == userName) {
			return currentUser;
		}
		currentUser = currentUser->nextUser;
	}
	return nullptr;
}

// Initializes the GDrive system with default root and folder
GDrive::GDrive() {
	this->users = nullptr;
	this->rootFolder = new Folder("root", nullptr);
	this->currentFolder = this->rootFolder;
}

// Returns the currently logged-in user's username
string GDrive::getCurrentUser() {
	return this->currentUser;
}

// Adds a new user if the username does not already exist
void GDrive::addUser(string userName, string password) {
	UserNode* currentUser = this->users;
	while (currentUser != nullptr) {
		if (currentUser->user->username == userName) {
			cout << RED << "User with " << userName << " name already exists" << RESET << endl;
			return;
		}
		currentUser = currentUser->nextUser;
	}
	User* newUser = new User(userName, password, "", "");
	UserNode* newUserNode = new UserNode(newUser);
	newUserNode->nextUser = this->users;
	this->users = newUserNode;
	cout << GREEN << "User with " << userName << " name added successfully" << RESET << endl;
}

// Returns the current date and time as a string
string GDrive::getCurrentTime() {
	time_t now = time(0);
	char buffer[26];
	ctime_s(buffer, sizeof(buffer), &now);
	string timeString(buffer);
	timeString.pop_back();
	return timeString;
}

// Registers a new user and stores their data in a text file
void GDrive::signUp(string n, string p, string sq, string sa) {
	if (findUser(n) != nullptr) {
		cout << RED << "UserName already exists" << endl;
		return;
	}

	User* newUser = new User(n, p, sq, sa);
	UserNode* newUserNode = new UserNode(newUser);
	newUserNode->nextUser = this->users;
	this->users = newUserNode;

	string filename = n + ".txt";
	ofstream outFile(filename);
	if (outFile.is_open()) {
		outFile << "Username: " << n << endl;
		outFile << "Password: " << p << endl;
		outFile << "Security Question: " << sq << endl;
		outFile << "Security Answer: " << sa << endl;
		outFile << "Last login: " << getCurrentTime()<<endl;
		outFile << "Last log out: Never" << endl;
		outFile.close();
		cout << GREEN << "Sign up successful and data saved to file: " << filename << endl;
	}
	else {
		cout << RED << "Error saving user data to file." << endl;
	}
}

// Authenticates a user and updates their login time
bool GDrive::logIn(string userName, string password) {
	string filename = userName + ".txt";
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cout << RED << "User with name \"" << userName << "\" not found." << RESET << endl;
		return false;
	}

	string line, storedPassword, securityQuestion, securityAnswer, lastLogin, lastLogout;
	int lineNum = 0;

	while (getline(inFile, line)) {
		if (line.find("Password:") == 0)
			storedPassword = line.substr(line.find(": ") + 2);
		else if (line.find("Security Question:") == 0)
			securityQuestion = line.substr(line.find(": ") + 2);
		else if (line.find("Security Answer:") == 0)
			securityAnswer = line.substr(line.find(": ") + 2);
		else if (line.find("Last login:") == 0)
			lastLogin = line.substr(line.find(": ") + 2);
		else if (line.find("Last log out:") == 0)
			lastLogout = line.substr(line.find(": ") + 2);
	}
	inFile.close();

	if (storedPassword != password) {
		cout << RED << "Password is incorrect." << RESET << endl;
		return false;
	}

	// ? Check if user already exists in memory
	UserNode* foundUser = findUser(userName);
	if (foundUser == nullptr) {
		User* newUser = new User(userName, storedPassword, securityQuestion, securityAnswer);
		newUser->lastLogIn = getCurrentTime();
		newUser->lastLogOut = lastLogout;

		UserNode* newNode = new UserNode(newUser);
		newNode->nextUser = users;
		users = newNode;
	}
	else {
		foundUser->user->lastLogIn = getCurrentTime();
	}

	this->currentUser = userName;
	cout << GREEN << "Log in successful." << RESET << endl;
	return true;
}

// Logs out the current user and updates the logout time in the file
void GDrive::logOut() {
	if (currentUser.empty()) {
		cout << RED << "No user is currently logged in" << RESET << endl;
		return;
	}

	UserNode* foundUser = findUser(currentUser);
	if (foundUser != nullptr) {
		foundUser->user->lastLogOut = getCurrentTime();

		string filename = currentUser + ".txt";
		ifstream inFile(filename);
		if (!inFile.is_open()) {
			cout << RED << "Error opening user file for logout update." << RESET << endl;
			return;
		}

		stringstream buffer;
		string line;
		while (getline(inFile, line)) {
			if (line.find("Last log out:") != string::npos) {
				line = "Last log out: " + getCurrentTime();
			}
			buffer << line << endl;
		}
		inFile.close();

		// Write back to file
		ofstream outFile(filename);
		if (outFile.is_open()) {
			outFile << buffer.str();
			outFile.close();
		}
		else {
			cout << RED << "Error saving updated logout time." << RESET << endl;
			return;
		}

		cout << GREEN << "Log out successful" << RESET << endl;
		userAuthentications.clearRecords();
		currentUser.clear();
	}
}

// Allows a user to reset their password using a security question
void GDrive::forgotPassword(string userName) {
	string filename = userName + ".txt";
	ifstream inFile(filename);
	if (!inFile.is_open()) {
		cout << RED << "User with name \"" << userName << "\" not found." << RESET << endl;
		return;
	}

	string line;
	string securityQuestion = "", securityAnswer = "";
	string fileContent = "";

	while (getline(inFile, line)) {
		fileContent += line + "\n";
		if (line.find("Security Question:") == 0)
			securityQuestion = line.substr(line.find(": ") + 2);
		else if (line.find("Security Answer:") == 0)
			securityAnswer = line.substr(line.find(": ") + 2);
	}
	inFile.close();

	cout << "Security Question: " << securityQuestion << endl;
	string answer;
	cout << "Enter your answer: ";
	getline(cin >> ws, answer);

	if (answer != securityAnswer) {
		cout << RED << "Security answer is incorrect." << RESET << endl;
		return;
	}

	cout << "Enter new password: ";
	string newPass;
	getline(cin >> ws, newPass);
	cout << "Enter confirm new password: ";
	string confirmPass;
	getline(cin >> ws, confirmPass);

	if (newPass != confirmPass) {
		cout << RED << "Password mismatch." << RESET << endl;
		return;
	}
	ifstream inFileAgain(filename);
	ofstream tempFile("temp.txt");
	while (getline(inFileAgain, line)) {
		if (line.find("Password:") == 0)
			tempFile << "Password: " << newPass << endl;
		else
			tempFile << line << endl;
	}
	inFileAgain.close();
	tempFile.close();

	if (remove(filename.c_str()) != 0) {
		cout << RED << "Error deleting old file." << RESET << endl;
		return;
	}

	if (rename("temp.txt", filename.c_str()) != 0) {
		cout << RED << "Error renaming temp file to user file." << RESET << endl;
		return;
	}
	cout << GREEN << "Password updated successfully." << RESET << endl;
}

// Creates a new subfolder in the current directory
void GDrive::createFolder(string folderName) {
	this->currentFolder->addSubFolder(folderName);
}

// Navigates to a specified subfolder, root, or parent folder
void GDrive::changeDirectory(string folderName) {
	if (folderName == "root") {
		currentFolder = rootFolder;
		cout << GREEN << "Changed to root directory." << RESET << endl;
	}
	else if (folderName == "..") {
		if (currentFolder->parent != nullptr) {
			currentFolder = currentFolder->parent;
			cout << GREEN << "Moved up one directory." << RESET << endl;
		}
		else {
			cout << RED << "Already at the root directory." << RESET << endl;
		}
	}
	else {
		Folder* nextFolder = currentFolder->getSubFolder(folderName);
		if (nextFolder != nullptr) {
			currentFolder = nextFolder;
			cout << GREEN << "Entered folder: " << folderName << RESET << endl;
		}
		else {
			cout << RED << "No such folder named '" << folderName << "' in the current directory." << RESET << endl;
		}
	}
}

// Creates and adds a file in the current folder
void GDrive::createFile(string fn, string ft, string o, int fs, string dc, string c) {
	string data = getCurrentTime();
	File* newFile = new File(fn, ft, o, fs, data, c);
	currentFolder->addFile(newFile);
}

// Lists all contents (files/folders) of the current folder
void GDrive::listContentOfCurrentDirectory() {
	cout << "Curretn directory " << currentFolder->folderName << endl;
	currentFolder->listContent();
}

// Deletes a folder and moves it to the recycle bin
void GDrive::deleteFolder(string folderName) {
	if (folderName == "root" || folderName == ".." || folderName == "." || folderName == "/") {
		cout << RED << "Cannot delete root folder" << RESET << endl;
		return;
	}
	Folder* folderToDelete = currentFolder->getSubFolder(folderName);
	if (folderToDelete == nullptr) {
		cout << RED << "No such folder named " << folderName << " in the directory" << endl;
		return;
	}
	Folder* removed = currentFolder->removeFolder(folderName);
	if (!removed) {
		cout << RED << "Failed to delete folder " << folderName << RESET << endl;
		return;
	}
	trashBin.deleteFolder(folderToDelete);
	cout << GREEN << "Folder " << folderName << " deleted successfully" << RESET << endl;
}

// Deletes a file and moves it to the recycle bin
void GDrive::deleteFile(string fileName) {
	File* fileToDelete = currentFolder->removeFile(fileName);
	if (fileToDelete != nullptr) {
		trashBin.deleteFile(fileToDelete);
	}
	else {
		cout << RED << "No such file named " << fileName << " in the directory" << RESET << endl;
		return;
	}
}

// Displays the contents of the recycle bin
void GDrive::viewRecycleBin() {
	trashBin.viewRecycleBin();
}

// Restores a file from the recycle bin to the current folder
void GDrive::restoreFile() {
	File* restored = trashBin.restoreFile();
	if (restored != nullptr) {
		currentFolder->addFile(restored);
	}
}

// Checks whether a user is currently logged in
void GDrive::checkLogInStatus() {
	if (this->currentUser.empty()) {
		cout << RED << "No user is currently logged in" << RESET << endl;
	}
	else {
		cout << GREEN << "User " << this->currentUser << " is currently logged in" << RESET << endl;
	}
}

// Handles login or signup process for a user
void GDrive::authentications() {
	string userName; 
	string password;
	if (currentUser.empty()) {
		cout << "Enter Username: ";
		getline(cin >> ws, userName);
		cout << "Enter Password: ";
		getline(cin >> ws, password);

		if (!logIn(userName, password)) {
			int choice;
			cout << RED << "User not found!" << RESET << endl;
			cout << "Would you like to sign up?" << endl;
			cout << "1. Yes" << endl;
			cout << "2. No (Exit)" << endl;
			cout << "Enter your choice: ";
			cin >> choice;
			cin.ignore(); 

			if (choice == 1) {
				string securityQuestion, securityAnswer;
				cout << "Enter Security Question: ";
				getline(cin, securityQuestion);
				cout << "Enter Security Answer: ";
				getline(cin, securityAnswer);
				signUp(userName, password, securityQuestion, securityAnswer);
			}
			else if (choice == 2) {
				cout << "Exiting..." << endl;
			}
			else {
				cout << RED << "Invalid choice!" << RESET << endl;
			}
		}
	}
	else {
		cout << GREEN << "User " << currentUser << " is already logged in." << RESET << endl;
	}
}

// Displays recent files accessed by a user
void GDrive::recentFiles(string userName) {
	UserNode* foundUser = findUser(userName);
	if (foundUser == nullptr) {
		cout << RED << "User not found" << endl;
		return;
	}
	cout << "Recent files for user " << userName << ":" << endl;
	foundUser->user->ListRecentFiles();
}

// Shares a file from one user to another
void GDrive::shareFile(string senderName, string recieverName, string fileName) {
	UserNode* sender = findUser(senderName);
	UserNode* reciever = findUser(recieverName);
	if (sender == nullptr || reciever == nullptr) {
		cout << RED << "Sender or receiver not found" << RESET << endl;
		return;
	}
	reciever->user->addSharedFile(fileName);
	sender->user->addSharedFile(fileName);
	cout << GREEN << "File " << fileName << " shared from " << senderName << " to " << recieverName << RESET << endl;
}

// Displays shared files for a specific user
void GDrive::showSharedFiles(string userName) {
	UserNode* foundUser = findUser(userName);
	if (foundUser == nullptr) {
		cout << RED << "User not found" << endl;
		return;
	}
	cout << "Shared files for user " << userName << ":" << endl;
	foundUser->user->showShareFiles();
}

// Cleans up dynamically allocated memory and objects
GDrive::~GDrive() {
	UserNode* currentUser = this->users;
	while (currentUser != nullptr) {
		UserNode* nextUser = currentUser->nextUser;
		delete currentUser->user;
		delete currentFolder;
		currentUser = nextUser;
	}
	users = nullptr;
	if (rootFolder != nullptr) {
		delete rootFolder;
		rootFolder = nullptr;
	}
	currentFolder = nullptr;
}