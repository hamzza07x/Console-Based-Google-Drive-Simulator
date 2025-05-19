#ifndef FILE_H
#define FILE_H
#include<iostream>
#include<string>
using namespace std;

class File {
public:
	string fileName;
	string owner;
	string fileType;
	int fileSize;
	string dateCreated;
	string content;
	File();
	File(string fn, string o, string ft, int fs, string dc, string c);
	~File();
};

class FileNode {
public:
	File* file;
	FileNode* nextFile;
	FileNode();
	FileNode(File* f);
	~FileNode();
};

#endif 