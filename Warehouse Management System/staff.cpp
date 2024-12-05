#include "staff.h"

Staff::Staff() : Person(), role(NONE), pin(0) {}

Staff::Staff(int id, string n, ROLE r, string info, int p) : Person(id, n, info), role(r), pin(p) {};


ROLE Staff::getRole() {
	return role;
}

string Staff::roleToString(ROLE role) {
	switch (role) {
	case MANAGER:
		return "MANAGER";
	case INVENTORY_CLERK:
		return "INVENTORY CLERK";
	case SHIPPING_CLERK:
		return "SHIPPING CLERK";
	case STAFF_SUPERVISOR:
		return "STAFF SUPERVISOR";
	case OPERATOR:
		return "OPERATOR";
	case SECURITY_GAURD:
		return "SECURITY GUARD";
	default:
		return "NONE";
	}
}

ROLE Staff::stringToRole(string r) {
	if (r == "MANAGER") {
		return MANAGER;
	}
	else if (r == "INVENTORY CLERK") {
		return INVENTORY_CLERK;
	}
	else if (r == "SHIPPING CLERK") {
		return SHIPPING_CLERK;
	}
	else if (r == "STAFF SUPERVISOR") {
		return STAFF_SUPERVISOR;
	}
	else if (r == "OPERATOR") {
		return OPERATOR;
	}
	else if (r == "SECURITY GAURD") {
		return SECURITY_GAURD;
	}
	else {
		return NONE;
	}
}

int Staff::getPin() {
	return pin;
}


void Staff::setRole(int r) {
	role = (ROLE)r;
}

void Staff::setPin(int p) {
	pin = p;
};


void Staff::setDetails(string read) {
	stringstream ss(read);
	string data[6];
	int i = 0;

	while (getline(ss, read, ',')) {
		data[i++] = read;
	}

	ID = stoi(data[0]);
	name = data[1];
	role = (ROLE)stoi(data[2]);
	contactInfo = data[3];
	pin = stoi(data[4]);
}


void Staff::WriteToFile(ofstream& w) const {
	w << ID << ',' << name << ',' << role << ',' << contactInfo << ',' << pin << endl;
}