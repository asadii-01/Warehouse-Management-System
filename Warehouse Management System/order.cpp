#include "order.h"

#include "utility.h"

Order::Order() :orderId(0), items({}) {}
Order::Order(int id, vector <pair<string, int>> it) :orderId(id), items(it) {}
Order::~Order(){}

int Order::getOrderId() {
	return orderId;
}

vector<pair<string, int>> Order::getItemsFromOrder() {
	return items;
}

pair<string, int> Order::getItem(string item) {
	for (const auto& i : items) {
		if ((i.first) == item) {
			return i;
		}
	}
	return make_pair("",0);
}

// setters
void Order::addItemToOrder(string stock, int quantity) {
	items.push_back(make_pair(stock, quantity));
}

void Order::addItems(){
	string input;
	int quantity;
	do
	{
		cout << "\n\n\t\tEnter Name of the item ordered : ";
		input = getStringFromUser(20);

		cout << "\n\n\t\tEnter Quantity of item ordered : ";
		quantity = getNumberFromUser(5);

		addItemToOrder(input,quantity);

		cout << "\n\n\t\t\033[33mWant to add another item to the order? <Y/N> : \033[0m ";
		input = getStringFromUser(1);

		if (input == "N") {
			break;
		}
		else if (input == "Y") {
			continue;
		}
		else {
			cerr << "\033[31mInvalid choice !! choose between Y or N\033[0m";
		}

	} while (true);

}

void Order::removeItemFromOrder(string i) {
	pair<string, int> item = getItem(i);
	auto it = find(items.begin(), items.end(), item);
	if (it != items.end()) {
		items.erase(it);
	}
}

// Check Item in order
bool Order::itemExistsInOrder(string item) {
	for (const auto& i : items) {
		if ((i.first) == item) {
			return true;
		}
	}

	return false;
}

// Load order information from a file
void Order::getOrderFromFile(string read) {
	stringstream ss(read);
	string token, item;
	int quantity = 0;

	if (getline(ss, token, ',')) {
		orderId = stoi(token);
	}
	else {
		throw runtime_error("Failed to get orderId");
	}
	while (getline(ss, token, ',')) {
		size_t pos = token.find(':');
		if (pos == string::npos) {
			return;
		}
		item = token.substr(0, pos);
		quantity = stoi(token.substr(pos + 1));
		items.push_back(make_pair(item, quantity));
	}
}

// Save order information to a file
void Order::WriteToFile(ofstream& w) const {
	w << orderId;
	for (auto& i : items) {
		w << "," << i.first << ":" << i.second;
	}
	w << endl;
}