#pragma once
#include <iostream>

using namespace std;

class Person{
protected:
	int ID;
	string name;
	string contactInfo;

public:
	// Constructor
	Person(): ID(0), name("NOONE"), contactInfo("") {}
	Person(int id, string n, string info) : ID(id), name(n), contactInfo(info) {}

	// Destructor
	~Person() = default;

	// Getters
    string getName() {
		return name;
	}
    int getID() {
		return ID;
	}
    string getContactInfo() {
		return contactInfo;
	}

	// Setters
	void setName(string n) {
		name = n;
	}
	void setContactInfo(string info) {
		contactInfo = info;
	}

	// Save supplier information to a file
	virtual void WriteToFile(ofstream& w) const = 0;

	// Load supplier information from a file
	virtual void setDetails(string read) = 0;
};

