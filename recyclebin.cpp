#include<iostream>
#include<string>

#include"RECYCLEBIN.h"
using namespace std;

// RecyclebinStack::RecyclebinStack()
// Constructor to initialize an empty recycle bin stack node.
RecyclebinStack::RecyclebinStack() {
	this->file = nullptr;
	this->folder = nullptr;
	this->nextFile = nullptr;
}

// Constructor to initialize a recycle bin stack node with a folder.
RecyclebinStack::RecyclebinStack(Folder* f) {
	this->file = nullptr;
	this->folder = f;
	this->nextFile = nullptr;
}

// Constructor to initialize a recycle bin stack node with a file.
RecyclebinStack::RecyclebinStack(File* f) {
	this->file = f;
	this->folder = nullptr;
	this->nextFile = nullptr;
}

// Destructor to clean up dynamically allocated file or folder.
RecyclebinStack::~RecyclebinStack() {
	if (this->file) {
		delete this->file; 
	}
	if (this->folder) {
		delete this->folder; 
	}
	this->nextFile = nullptr;
}

// Constructor to initialize the recycle bin with an empty top.
RecycleBin::RecycleBin() {
	this->top = nullptr;
}

// Pushes a deleted folder onto the recycle bin stack.
void RecycleBin::deleteFolder(Folder* folder) {
	if (folder == nullptr) {
		cout << RED << "folder not found" << RESET << endl;
		return;
	}
	RecyclebinStack* newFolder = new RecyclebinStack(folder);
	newFolder->nextFile = this->top;
	this->top = newFolder;
	cout << GREEN << "Folder " << folder->folderName << " deleted successfully" << RESET << endl;
}

// Pushes a deleted file onto the recycle bin stack.
void RecycleBin::deleteFile(File*file) {
	if (file == nullptr) {
		cout << RED << "file not found" << RESET << endl;
		return;
	}
	RecyclebinStack* newFile = new RecyclebinStack(file);
	newFile->nextFile = this->top;
	this->top = newFile;
	cout << GREEN << "File " << file->fileName << " deleted successfully" << RESET << endl;
}

// Pops and restores the most recently deleted file from the recycle bin.
File* RecycleBin::restoreFile() {
	if (this->top == nullptr) {
		cout << RED << "Recycle bin is empty" << RESET << endl;
		return nullptr;
	}
	File* restoredFile = this->top->file;
	RecyclebinStack* toResstroe = this->top;
	this->top = this->top->nextFile;
	toResstroe->file = nullptr;
	delete toResstroe;
	cout << GREEN << "File " << restoredFile->fileName << " restored successfully" << RESET << endl;
	return restoredFile;
}

// Displays the list of files currently in the recycle bin.
void RecycleBin::viewRecycleBin() {
	if (this->top == nullptr) {
		cout << RED << "Recycle bin is empty" << RESET << endl;
		return;
	}
	cout << "Files in Recycle bin" << endl;
	cout << "__________________________________" << endl;
	RecyclebinStack* currentFile = this->top;
	while (currentFile != nullptr) {
		cout << "..." << currentFile->file->fileName << endl;
		currentFile = currentFile->nextFile;
	}
	cout << "__________________________________" << endl;
}

// Destructor to clean up all nodes in the recycle bin stack.
RecycleBin::~RecycleBin() {
	RecyclebinStack* currentFile = this->top;
	while (currentFile != nullptr) {
		RecyclebinStack* toDestroy = currentFile;
		currentFile = currentFile->nextFile;
		toDestroy->file = nullptr;
		delete toDestroy;
	}
	this->top = nullptr;
}