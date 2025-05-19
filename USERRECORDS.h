#ifndef USERRECORDS_H
#define USERRECORDS_H
#include<iostream>
#include<fstream>
#include<string>
#include"USER.h"
#include"COLOR.h"
using namespace std;

class UserRecords {
private:
	string recordFile;
public:
	UserRecords();
	void clearRecords();
	~UserRecords();
};
#endif