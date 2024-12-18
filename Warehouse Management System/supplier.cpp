#include "supplier.h"
#include "utility.h"

Supplier::Supplier()
    :Person(0, "NOBODY", "NOTHING"), itemsSupplied({}) {}

Supplier::Supplier(int id, string name, string Info, vector<string> itSupplied)
    : Person(id, name, Info), itemsSupplied(itSupplied) {}

Supplier::~Supplier() {}


vector<string> Supplier::getItemsSupplied() {
    return itemsSupplied;
}



void Supplier::addItem(string item) {
    itemsSupplied.push_back(item);
}

void Supplier::addItem(ItemCollection& inventory)
{
    string input;
    int quantity;
    do
    {
        cout << "\n\n\t\tEnter Name of the item ordered : ";
        input = getStringFromUser(20);

        if (!inventory.nameExists(input)) {
            throw runtime_error("Item does not exists in the invetory!!\t Enter correct item name");
        }

        addItem(input);

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

bool Supplier::removeItem(string item) {
    auto it = find(itemsSupplied.begin(), itemsSupplied.end(), item);
    if (it != itemsSupplied.end()) {
        itemsSupplied.erase(it);
        return true;
    }
    return false;
}


void Supplier::WriteToFile(ofstream& w) const {
    w << ID << "," << name << "," << contactInfo;
    for (const auto& item : itemsSupplied) {
        w << "," << item;
    }
    w << endl;
}


void Supplier::setDetails(string read) {
    stringstream ss(read);
    vector<string> data;
    
    while (getline(ss, read, ',')) {
        data.push_back(read);
    }
    
    ID = stoi(data[0]);
    name = data[1];
    contactInfo = data[2];

    for (int i = 3; i < data.size(); i++) {
        addItem(data[i]);
    }

}