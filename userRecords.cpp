#include<iostream>
#include<fstream>
#include<string>
#include"USERRECORDS.h"
#include"COLOR.h"
using namespace std;

// Constructor: Initializes the record file name
UserRecords::UserRecords() {
	this->recordFile = "userRecords.txt";
}

// clearRecords(): Clears the contents of the user records file
void UserRecords::clearRecords() {
	ofstream outFile(this->recordFile, ofstream::trunc);
	if (!outFile) {
		cout << RED << "Error clearing file" << RESET << endl;
	}
	else {
		cout << GREEN << "File cleared successfully" << RESET << endl;
	}
}

// Destructor: Handles any cleanup (currently empty)
UserRecords::~UserRecords() {

}