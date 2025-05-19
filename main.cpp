#include<iostream>
#include<string>
#include<stdexcept>
#include"GDRIVE.h"
using namespace std;

void simulateGoogleDrive(GDrive& gd);

void displayAboutMenu() {
    cout << RED;
    cout << BLUE << "Project Description:" << RESET << endl;
    cout << "This is a console-based simulation of Google Drive, developed" << endl;
    cout << "in C++ using object-oriented programming and data structures." << endl;
    cout << "It allows users to register, log in, manage files and folders," << endl;
    cout << "share files, and recover deleted items through a recycle bin." << endl;
    cout << endl;

    cout << BLUE << "Key Features:" << RESET << endl;
    cout << "- User Authentication with File-Based Storage" << endl;
    cout << "- Folder and File Management using Linked Lists" << endl;
    cout << "- File Sharing Mechanism with Recent File Tracking" << endl;
    cout << "- Recycle Bin Functionality (Stack Implementation)" << endl;
    cout << "- Structured and Modular OOP Design" << endl;
    cout << endl;

    cout << BLUE << "Technologies Used:" << RESET << endl;
    cout << "- C++ and Visual Studio" << endl;
    cout << "- File Handling (Text Files for Records)" << endl;
    cout << "- Data Structures: Linked List, Stack,Queue,Tree and Graph" << endl;
    cout << endl;
    cout << GREEN << "Developed By:"<<RESET<<" Muhammad Hamza" << endl;
    cout << endl;
}

void introsc() {
    cout << RED;
    cout << "==========================================" << endl;
    cout << "=      GOOGLE DRIVE SIMULATOR            =" << endl;
    cout << "==========================================" << endl;
    cout << RESET;
    cout << endl;
}

// Function: loginMenu
// Purpose: Displays the main login menu with options for SignUp, Login, Forgot Password, and Exit.
void loginMenu() {
    cout << "1.SignUp" << endl;
    cout << "2.Login" << endl;
    cout << "3.Forgot password" << endl;
    cout << "4.About" << endl;
    cout << "0.Exit" << endl;
}

// Function: GDriveMenu
// Purpose: Displays the Google Drive operations menu after user logs in.
void GDriveMenu() {
    cout << "1.Create folder" << endl;
    cout << "2.Change Directory" << endl;
    cout << "3.Create file" << endl;
    cout << "4.Show folder content" << endl;
    cout << "5.Delete file" << endl;
    cout << "6.Delete folder" << endl;
    cout << "7.View recycle bin" << endl;
    cout << "8.Restore last deleted file" << endl;
    cout << "9.List Recent files" << endl;
    cout << "10.Share files" << endl;
    cout << "11.Show shared files" << endl;
    cout << "0.Log out" << endl;
}

// Function: googleDriveSimulator
// Purpose: Handles user authentication workflows (signup, login, password recovery) and launches GDrive simulation on successful login.
void googleDriveSimulator(GDrive& gd) {
    int choice;
    try {
        do {
            cout << "==========================================" << endl;
            loginMenu();
            cout << "Enter: ";
            cin >> choice;
            if (cin.fail()) {
                throw runtime_error("Error");
                cin.clear();
                cin.ignore();
            }
            switch (choice) {
            case 1: {
                system("cls");
                cin.ignore();
                string username;
                string password;
                string securityQuestion;
                string securityAnswer;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                cout << "Enter security Question: ";
                getline(cin, securityQuestion);
                cout << "Enter security Answer: ";
                getline(cin, securityAnswer);
                gd.signUp(username, password, securityQuestion, securityAnswer);
				cout << GREEN << "User " << username << " signed up successfully" << RESET << endl;
                break;
            }
            case 2: {
                system("cls");
                cin.ignore();
                string username;
                string password;
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                bool logInStatus = gd.logIn(username,password);
                if (logInStatus) {
                    simulateGoogleDrive(gd);
                }
                break;
            }
            case 3: {
                system("cls");
                cin.ignore();
                string username;
                cout << "Enter you Username: ";
                getline(cin, username);
                gd.forgotPassword(username);
                break;
            }
            case 4: {
                system("cls");
                displayAboutMenu();
                cin.ignore();
                cin.get();
                system("cls");
                break;
            }
            case 0: {
                cout << "Exiting............" << endl;
                break;
            }
            default: {
                cout << "Invalid choice" << endl;
            }
            }
        } while (choice != 0);
    }
    catch (exception& e) {
        cout << RED << e.what() << RESET << endl;
    }
}

// Function: simulateGoogleDrive
// Purpose: Provides the core functionalities of the Google Drive simulator like file/folder operations, sharing, recycle bin, etc., after login.
void simulateGoogleDrive(GDrive& gd) {
    int choice;
    try {
        do {
            cout << "==========================================" << endl;
            GDriveMenu();
            cout << "Enter: ";
            cin >> choice;
            if (cin.fail()) {
                throw runtime_error("Error");
                cin.clear();
                cin.ignore();
            }
            cin.ignore();
            switch (choice) {
            case 1: {
                system("cls");
                string folderName;
                cout << "Enter folder name: ";
                getline(cin, folderName);
                gd.createFolder(folderName);
                break;
            }
            case 2: {
                system("cls");
                string folderName;
                cout << "Enter folder name: ";
                getline(cin, folderName);
                gd.changeDirectory(folderName);
                break;
            }
            case 3: {
                system("cls");
                string fileName;
                string fileType;
                string owner;
                int fileSize;
                string dateCreated;
                string content;
                cout << "Enter file name: ";
                getline(cin, fileName);
                cout << "Enter file type: ";
                getline(cin, fileType);
                cout << "Enter owner: ";
                getline(cin, owner);
                cout << "Enter file size: ";
                cin >> fileSize;
                cin.ignore();
                dateCreated = gd.getCurrentTime();
                cout << "Enter content: ";
                getline(cin, content);
                gd.createFile(fileName, fileType, owner, fileSize, dateCreated, content);
                break;
            }
            case 4: {
                system("cls");
                gd.listContentOfCurrentDirectory();
                break;
            }
            case 5: {
                system("cls");
                string fileName;
                cout << "Enter fileName to delete: ";
                cin.ignore();
                getline(cin, fileName);
                gd.deleteFile(fileName);
                break;
            }
            case 6: {
                system("cls");
                string folderName;
                cout << "Enter folder name: ";
                getline(cin, folderName);
                gd.deleteFolder(folderName);
                cin.ignore();
                break;
            }
            case 7: {
                system("cls");
                gd.viewRecycleBin();
                break;
            }
            case 8: {
                system("cls");
                gd.restoreFile();
                break;
            }
            case 9: {
                system("cls");
                string username = gd.getCurrentUser();
                gd.recentFiles(username);
                break;
            }
            case 10: {
                system("cls");
                string userToShare;
                string fileName;
                cout << "Enter user name to share: ";
                getline(cin, userToShare);
                cout << "Enter file name: ";
                getline(cin, fileName);
                gd.shareFile(gd.getCurrentUser(), userToShare,fileName);
                break;
            }
            case 11: {
                system("cls");
                string username;
                cout << "Enter username: ";
                getline(cin, username);
                gd.showSharedFiles(username);
                break;
            }
            case 0: {
                cout << "Returning back" << endl;
                gd.logOut();
                return;
            }
            default: {
                cout << "Invalid" << endl;
                break;
            }
            }
        } while (choice != 0);
    }
    catch (exception& e) {
        cout << RED << e.what() << RESET << endl;
    }
}

// Function: main
// Purpose: Entry point of the program; initializes GDrive and starts the simulation.
int main() {
    introsc();
    GDrive googleDrive;
    googleDriveSimulator(googleDrive);
    cout << GREEN << "Thanks for using Google Drive Simulator. Goodbye!" << RESET << endl;
    cin.get();
    return 0;
}
