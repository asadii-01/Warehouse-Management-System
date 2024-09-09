#include "supplier.h"

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