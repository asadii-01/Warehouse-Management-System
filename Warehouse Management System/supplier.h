#pragma once

#include "person.h"

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include "itemCollection.h"


class Supplier : public Person {
private:
    vector<string> itemsSupplied;

public:

    // Constructors
    Supplier();
    Supplier(int id, string name, string Info, vector<string> itSupplied);

    // Destructor
    ~Supplier();

    // Getter
    vector<string> getItemsSupplied();

    // Setters
    // Add an item to the list of supplied items
    void addItem(string item);
    void addItem(ItemCollection& inventory);
    // Remove an item from the list of supplied items
    bool removeItem(string item);

    // Save supplier information to a file
    void WriteToFile(ofstream& w) const;

    // Load supplier information from a file
    void setDetails(string read);

    // Operator Overloading
    friend ostream& operator<<(ostream& cout, Supplier* s);
    friend istream& operator>>(istream& cin, Supplier* s);

};