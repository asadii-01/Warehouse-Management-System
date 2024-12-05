#pragma once

#include "person.h"

#include <vector>
#include <fstream>
#include <string>
#include <sstream>

enum ROLE{
	NONE, MANAGER, INVENTORY_CLERK, SHIPPING_CLERK, STAFF_SUPERVISOR, OPERATOR, SECURITY_GAURD
};

class Staff : public Person{
private:
	ROLE role;
	int pin;

public:

	// Consturctors
	Staff();
	Staff(int id, string n, ROLE r, string info, int p);

	// Destructor
	~Staff() = default;
	
	// Getters
	ROLE getRole();

	string roleToString(ROLE role);

	ROLE stringToRole(string r);

	int getPin();


	// Setters
	void setRole(int r);

	void setPin(int p); 


	
	// Read from file
	void setDetails(string read);

	// Write to file
	void WriteToFile(ofstream& w) const;

	// Operator overloading
	friend ostream& operator<<(ostream& cout, Staff* s);
	friend istream& operator>>(istream& cin, Staff* s);
};
