#include<iostream>
#include<string>
#include"FOLDER.h"
#include"COLOR.h"
using namespace std;

// Constructor: Default Folder
Folder::Folder() {
	this->folderName = "";
	this->parent = nullptr;
	this->subFolders = nullptr;
	this->files = nullptr;
}

// Constructor: Parameterized Folder
Folder::Folder(string fn, Folder* p) {
	this->folderName = fn;
	this->parent = p;
	this->subFolders = nullptr;
	this->files = nullptr;
}

// Function: Add a subfolder to the current folder
void Folder::addSubFolder(string folderName) {
	FolderNode* currentFolder = this->subFolders;
	while (currentFolder != nullptr) {
		if (currentFolder->folder->folderName == folderName) {
			cout << RED << "Folder with " << folderName << " name already exists" << RESET << endl;
			return;
		}
		currentFolder = currentFolder->nextFolder;
	}
	Folder* newFolder = new Folder(folderName, this);
	FolderNode* newFolderNode = new FolderNode(newFolder);
	newFolderNode->nextFolder = this->subFolders;
	this->subFolders = newFolderNode;
	cout << GREEN << "Folder with " << folderName << " name created successfully" << RESET << endl;
}

// Function: Get a pointer to a subfolder by name
Folder* Folder::getSubFolder(string folderName) {
	FolderNode* currentFolder = this->subFolders;
	while (currentFolder != nullptr) {
		if (currentFolder->folder->folderName == folderName) {
			return currentFolder->folder;
		}
		currentFolder = currentFolder->nextFolder;
	}
	cout << RED << "Folder with " << folderName << " name not found" << RESET << endl;
	return nullptr;
}

// Function: Remove a subfolder by name and return its pointer
Folder* Folder::removeFolder(string folderName) {
	FolderNode* currentFolder = this->subFolders;
	FolderNode* previousFolder = nullptr;
	while (currentFolder != nullptr) {
		if (currentFolder->folder->folderName == folderName) {
			if (previousFolder == nullptr) {
				this->subFolders = currentFolder->nextFolder;
			}
			else {
				previousFolder->nextFolder = currentFolder->nextFolder;
			}

			Folder* toRemove = currentFolder->folder;
			currentFolder->folder = nullptr;  // Avoid dangling pointer
			delete currentFolder;  // Delete the FolderNode
			cout << GREEN << "Folder with " << folderName << " name removed successfully" << RESET << endl;
			return toRemove;
		}
		previousFolder = currentFolder;
		currentFolder = currentFolder->nextFolder;
	}
	cout << RED << "Folder with " << folderName << " name not found" << RESET << endl;
	return nullptr;
}

// Function: Add a file to the current folder
void Folder::addFile(File* file) {
	FileNode* currentFile = files;
	while (currentFile != nullptr) {
		if (currentFile->file->fileName == file->fileName) {
			cout << RED << "File with " << file->fileName << " name already exists" << RESET << endl;
			return;
		}
		currentFile = currentFile->nextFile;
	}
	FileNode* newFileNode = new FileNode(file);
	newFileNode->nextFile = this->files;
	this->files = newFileNode;
	cout << GREEN << "File with " << file->fileName << " name added successfully" << RESET << endl;
}

// Function: Remove a file by name and return its pointer
File* Folder::removeFile(string fileName) {
	FileNode* currentFile = this->files;
	FileNode* previousFile = nullptr;
	while (currentFile != nullptr) {
		if (currentFile->file->fileName == fileName) {
			if (previousFile == nullptr) {
				this->files = currentFile->nextFile;
			}
			else {
				previousFile->nextFile = currentFile->nextFile;
			}

			File* toRemove = currentFile->file;
			currentFile->file = nullptr;  // Avoid dangling pointer
			delete currentFile;  // Delete the FileNode
			return toRemove;
		}
		previousFile = currentFile;
		currentFile = currentFile->nextFile;
	}
	cout << RED << "File with " << fileName << " name not found" << RESET << endl;
	return nullptr;
}

// Function: List all folders and files in the current folder
void Folder::listContent() {
	cout << "Folders" << endl;
	cout << "_____________________________________________" << endl;
	FolderNode* currentFolder = this->subFolders;
	while (currentFolder != nullptr) {
		cout << "..." << currentFolder->folder->folderName << "/" << endl;
		currentFolder = currentFolder->nextFolder;
	}
	cout << "_____________________________________________" << endl;
	cout << endl;
	cout << "Files" << endl;
	FileNode* currentFile = this->files;
	while (currentFile != nullptr) {
		cout << "..." << currentFile->file->fileName << endl;
		currentFile = currentFile->nextFile;
	}
	cout << "_____________________________________________" << endl;
}

// Destructor: Clean up memory by deleting subfolders and files
Folder::~Folder() {
	// Safely delete subfolders
	while (this->subFolders != nullptr) {
		FolderNode* toDestroy = this->subFolders;
		this->subFolders = this->subFolders->nextFolder;

		if (toDestroy->folder != nullptr) {
			delete toDestroy->folder;  // Delete the folder object
			toDestroy->folder = nullptr;  // Avoid dangling pointer
		}

		delete toDestroy;  // Delete the FolderNode
	}

	// Safely delete files
	while (this->files != nullptr) {
		FileNode* toDestroy = this->files;
		this->files = this->files->nextFile;

		if (toDestroy->file != nullptr) {
			delete toDestroy->file;  // Delete the file object
			toDestroy->file = nullptr;  // Avoid dangling pointer
		}

		delete toDestroy;  // Delete the FileNode
	}

	// Clear parent reference
	this->parent = nullptr;
}

// Constructor: Default FolderNode
FolderNode::FolderNode() {
	this->folder = nullptr;
	this->nextFolder = nullptr;
}

// Constructor: Parameterized FolderNode
FolderNode::FolderNode(Folder* f) {
	this->folder = f;
	this->nextFolder = nullptr;;
}

// Destructor: Reset pointers in FolderNode
FolderNode::~FolderNode() {
	this->folder = nullptr;
	this->nextFolder = nullptr;
}

