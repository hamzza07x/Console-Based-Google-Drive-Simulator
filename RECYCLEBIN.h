#ifndef RECYCLEBIN_H
#define RECYCLEBIN_H
#include<iostream>
#include<string>
#include"FILE.h"
#include"FOLDER.h"
#include"COLOR.h"
using namespace std;

class File;
class folder;

class RecyclebinStack {
public:
	File* file;
	Folder* folder;
	RecyclebinStack* nextFile;
	RecyclebinStack();
	RecyclebinStack(Folder* f);
	RecyclebinStack(File* f);
	~RecyclebinStack();
};

class RecycleBin {
private:
	RecyclebinStack* top;
public:
	RecycleBin();
	void deleteFile(File* file);
	void deleteFolder(Folder* folder);
	File* restoreFile();
	void viewRecycleBin();
	~RecycleBin();
};
#endif