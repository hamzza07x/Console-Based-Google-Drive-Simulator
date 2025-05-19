#include<iostream>
#include<string>
#include"FILE.h"
#include"COLOR.h"
using namespace std;

// Default constructor for the File class
// Initializes all member variables to default values
File::File() {
	this->fileName = "";
	this->owner = "";
	this->fileType = "";
	this->fileSize = 0;
	this->dateCreated = "";
	this->content = "";
}

// Parameterized constructor for the File class
// Initializes member variables with provided values
File::File(string fn, string o, string ft, int fs, string dc, string c) {
	this->fileName = fn;
	this->owner = o;
	this->fileType = ft;
	this->fileSize = fs;
	this->dateCreated = dc;
	this->content = c;
}

// Destructor for the File class
// Currently does nothing as no dynamic memory is managed directly in this class
File::~File() {

}

// Default constructor for the FileNode class
// Initializes pointers to nullptr
FileNode::FileNode() {
	this->file = nullptr;
	this->nextFile = nullptr;
}

// Parameterized constructor for the FileNode class
// Takes a File pointer and sets the file pointer, nextFile is set to nullptr
FileNode::FileNode(File* f) {
	this->file = f;
	this->nextFile = nullptr;
}

// Destructor for the FileNode class
// Deletes the associated File object to prevent memory leak
FileNode::~FileNode() {
	if (file != nullptr) {
		delete file;
		file = nullptr;
	}
	nextFile = nullptr;
}
