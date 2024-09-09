#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

enum CATEGORY
{
   NON, ELECTRONICS, COMPUTER, AUTOMOTIVE, SPORTS, CLOTHING, FURNITURE
};

class StockItem {

private:
    int stockId;
    string name;
    float price;
    int quantity;
    CATEGORY category;

public:

    // Constructor
    StockItem();
    StockItem(int sId, string n, float p, int q, CATEGORY c);

    // Destructor
    ~StockItem();

    // Getters
    int getStockId();

    string getName();

    float getPrice();

    int getQuantity();

    CATEGORY getCategory();

    string categoryToString(CATEGORY category);

    CATEGORY stringToCategory(string c);

    // Setters
    void setCategory(CATEGORY newCategory);

    void setId(int newId);

    void setName(string newName);

    void setPrice(float newPrice);

    void addQuantity(int newStock);

    void removeQuantity(int n);

    // Read 
    void ReadStockFromFile(string read);

    // Write
    void WriteToFile(ofstream& w) const;

    // Operator Overloading
    friend istream& operator>>(istream& cin, StockItem* s);
    friend ostream& operator<<(ostream& cout, StockItem* s);
};
