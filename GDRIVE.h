#ifndef GDRIVE_H
#define GDRIVE_H
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include"USER.h"
#include"USERRECORDS.h"
#include"FOLDER.h"
#include"RECYCLEBIN.h"
#include"FILE.h"
#include"COLOR.h"
using namespace std;

class UserNode;

class GDrive {
private:
	UserNode* users;
	Folder* rootFolder;
	Folder* currentFolder;
	RecycleBin trashBin;
	UserRecords userAuthentications;
	string currentUser;
	UserNode* findUser(string userName);
public:
	GDrive();
	string getCurrentUser();
	void addUser(string userName, string password);
	string getCurrentTime();
	void signUp(string n, string p, string sq, string sa);
	bool logIn(string userName, string password);
	void logOut();
	void forgotPassword(string userName);
	void createFolder(string folderName);
	void changeDirectory(string folderName);
	void createFile(string fn, string ft, string o, int fs, string dc, string c);
	void listContentOfCurrentDirectory();
	void deleteFolder(string folderName);
	void deleteFile(string fileName);
	void viewRecycleBin();
	void restoreFile();
	void checkLogInStatus();
	void authentications();
	void recentFiles(string userName);
	void shareFile(string senderName, string recieverName, string fileName);
	void showSharedFiles(string userName);
	~GDrive();
};

#endif