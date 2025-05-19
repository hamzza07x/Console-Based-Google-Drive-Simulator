#ifndef USER_H
#define USER_H
#include<iostream>
#include<String>
using namespace std;

class User {
public:
	string username;
	string password;
	string securityQuestion;
	string securityAnswer;
	string lastLogIn;
	string lastLogOut;
	User* nextUser;
	User();
	User(string u, string p, string sq, string sa);
	class SharedFiles {
	public:
		string fileName;
		SharedFiles* nextFile;
		SharedFiles();
		SharedFiles(string fn);
	};
	SharedFiles* sharedFiles;
	void addSharedFile(string fileName);
	void showShareFiles();
	void ListRecentFiles();
	~User();
};

class UserNode {
public:
	User* user;
	UserNode* nextUser;
	UserNode();
	UserNode(User* u);
	~UserNode();
};
#endif