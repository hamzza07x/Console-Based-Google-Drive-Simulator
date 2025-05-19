#include<iostream>
#include<string>
#include"COLOR.h"
#include"USER.h"
using namespace std;

// User default constructor
User::User()
	: username(""), password(""), securityQuestion(""), securityAnswer(""),
	lastLogIn(""), lastLogOut(""), nextUser(nullptr), sharedFiles(nullptr) {

}

// User parameterized constructor
User::User(string u, string p, string sq, string sa)
	: username(u), password(p), securityQuestion(sq), securityAnswer(sa),
	lastLogIn(""), lastLogOut(""), nextUser(nullptr), sharedFiles(nullptr) {

}

// SharedFiles default constructor
User::SharedFiles::SharedFiles()
	: fileName(""), nextFile(nullptr) {

}

// SharedFiles parameterized constructor
User::SharedFiles::SharedFiles(string fn)
	: fileName(fn), nextFile(nullptr) {

}

// Add a new file to the shared files list
void User::addSharedFile(string fileName) {
	SharedFiles* newFile = new SharedFiles(fileName);
	newFile->nextFile = this->sharedFiles;
	this->sharedFiles = newFile;
}

// Display all shared files of the user
void User::showShareFiles() {
	if (this->sharedFiles == nullptr) {
		cout << RED << "No files shared by " << this->username << RESET << endl;
		return;
	}
	cout << "Files shared by " << this->username << endl;
	SharedFiles* currentFile = this->sharedFiles;
	while (currentFile != nullptr) {
		cout << "..." << currentFile->fileName << endl;
		currentFile = currentFile->nextFile;
	}
	cout << endl;
}

// List recent files shared by the user
void User::ListRecentFiles() {
	if (this->sharedFiles == nullptr) {
		cout << RED << "No files for this " << this->username << RESET << endl;
		return;
	}
	cout << "Recent files for " << this->username << endl;
	SharedFiles* currentFile = this->sharedFiles;
	while (currentFile != nullptr) {
		cout << "..." << currentFile->fileName << endl;
		currentFile = currentFile->nextFile;
	}
	cout << endl;
}

// User destructor to clean up shared files
User::~User() {
	SharedFiles* currentFile = this->sharedFiles;
	while (currentFile != nullptr) {
		SharedFiles* toDestroy = currentFile;
		currentFile = currentFile->nextFile;
		delete toDestroy;
	}
}

// UserNode default constructor
UserNode::UserNode() {
	this->user = nullptr;
	this->nextUser = nullptr;
}

// UserNode parameterized constructor
UserNode::UserNode(User* u) {
	this->user = u;
	this->nextUser = nullptr;
}

// UserNode destructor to delete user and next user node
UserNode::~UserNode() {
	if (this->user != nullptr) {
		delete this->user;
		this->user = nullptr;
	}
	if (this->nextUser != nullptr) {
		delete this->nextUser;
		this->nextUser = nullptr;
	}
}