#pragma once

#include <iostream>

using namespace std;

class Collection{

public:
	//virtual void addToList() = 0;
	virtual void removeFromList(string name) = 0;
	
	virtual  void modifyDetails(string name) = 0;

	virtual bool idExists(int id) = 0;
	virtual bool nameExists(string name) = 0;

	virtual void loadFromFile(string filename) = 0;
	virtual void saveToFile(string filename) = 0;

	virtual void displayList() = 0;
};

