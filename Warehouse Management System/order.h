#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "itemCollection.h"

using namespace std;

class Order {
private:
	int orderId;
	vector <pair<string, int>> items;

public:

	// Constructors
	Order();
	Order(int id, vector <pair<string, int>> items);

	// Destructor
	~Order();

	// Getters
	int getOrderId();

	vector<pair<string, int>>& getItemsFromOrder();

	pair<string, int> getItem(string item);

	// Setters
	void addItemToOrder(string stock, int qunatity);

	void setOrderId(int id);

	void addItems(ItemCollection& inventory);

	void removeItemFromOrder(string item);

	// Check Item in order
	bool itemExistsInOrder(string item);

	// Read from file
	void getOrderFromFile(string read);

	// Write ti file
	void WriteToFile(ofstream& w) const;

	// Operator Overloading
	friend istream& operator>>(istream& cin, Order* o);
	friend ostream& operator<<(ostream& cout, Order* o);
};