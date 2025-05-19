#ifndef FOLDER_H
#define FOLDER_H
#include<iostream>
#include<string>
#include"FILE.h"
using namespace std;

class FolderNode;
class File;

class Folder {
public:
	string folderName;
	Folder* parent;
	FolderNode* subFolders;
	FileNode* files;
	Folder();
	Folder(string fn, Folder* p);
	void addSubFolder(string folderName);
	Folder* getSubFolder(string folderName);
	Folder* removeFolder(string folderName);
	void addFile(File* file);
	File* removeFile(string fileName);
	void listContent();
	~Folder();
};

class FolderNode {
public:
	Folder* folder;
	FolderNode* nextFolder;
	FolderNode();
	FolderNode(Folder* f);
	~FolderNode();
};
#endif 