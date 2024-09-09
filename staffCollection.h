#pragma once

#include "staff.h"
#include "collection.h"

class StaffCollection : public Staff, public Collection {
private: 
	vector<Staff*> staffList;

public:

	// Destructor
	~StaffCollection() = default;

	// Getter
	vector<Staff*> getStaffList();

	// Add staff to the list
	void addToList(Staff& s);

	// Remove staff from the list
	void removeFromList(string name) override;

	// Modify details
	void modifyDetails(string name) override;
	void modifyPersonalDetails(string name);
	void personalProfile(Staff* user);

	// Find a staff by its name
	Staff* findStaffByName(string name);
	Staff* findStaffById(int id);

	// Set pin for the first time
	void newLogIn(Staff* s);

	// Check if values already exists
	bool staffExists(Staff& s);
	bool idExists(int id) override;
	bool nameExists(string name) override;
	bool mailExists(string name);

	// Read Data from file
	void loadFromFile(string filename) override;

	// Write data to files
	void saveToFile(string filename) override;

	//DisplayData
	void displayList() override;
};

