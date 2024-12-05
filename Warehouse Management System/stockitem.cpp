#include "stockitem.h"

StockItem::StockItem() : stockId(0), name("NOTHING"), price(0.00), quantity(0), category(NON) {} // Intializing with default values

StockItem::StockItem(int sId, string n, float p, int q, CATEGORY c) : stockId(sId), name(n), price(p), quantity(q), category(c) {}

StockItem::~StockItem() {}

int StockItem::getStockId() {
    return stockId;
}

string StockItem::getName() {
    return name;
}

float StockItem::getPrice() {
    return price;
}

int StockItem::getQuantity() {
    return quantity;
}

CATEGORY StockItem::getCategory() {
    return category;
}

string StockItem::categoryToString(CATEGORY category) {
    switch (category) {
    case ELECTRONICS:
        return "ELECTRONICS";
    case COMPUTER:
        return "COMPUTER";
    case AUTOMOTIVE:
        return "AUTOMOTIVE";
    case SPORTS:
        return "SPORTS";
    case CLOTHING:
        return "CLOTHING";
    case FURNITURE:
        return "FURNITURE";
    default:
        return "NON";
    }
}

CATEGORY StockItem::stringToCategory(string c) {
    if (c == "ELECTRONICS") {
        return ELECTRONICS;
    }
    else if (c == "COMPUTER") {
        return COMPUTER;
    }
    else if(c == "AUTOMOTIVE") {
        return AUTOMOTIVE;
    }
    else if (c == "SPORTS") {
        return SPORTS;
    }
    else if (c == "CLOTHING") {
        return CLOTHING;
    }
    else if (c == "FURNITURE") {
        return FURNITURE;
    }
    else {
        return NON;
    }
}

// setters
void StockItem::setCategory(CATEGORY newCategory) {
    category = newCategory;
}

void StockItem::setName(string newName) {
    name = newName;
}

void StockItem::setId(int newId) {
    stockId = newId;
}

void StockItem::setPrice(float newPrice){
    price = newPrice;
}

void StockItem::addQuantity(int newStock) {
    quantity += newStock;
}

void StockItem::removeQuantity(int n) {
    if (quantity < n) {
        quantity = 0;   // Prevent negative quantity
        throw runtime_error("Quantity not available in Stock !!!");
    }
    else
        quantity -= n;
}

// load stock information from a file
void StockItem::ReadStockFromFile(string read) {

    int i = 0;
    string data[5];
    stringstream ss(read);

    while (getline(ss, read, ',')) {
        data[i++] = read;
    }
    i = 0;

    stockId = stoi(data[0]);
    name = data[1];
    price = stod(data[2]);
    quantity = stoi(data[3]);
    category = (CATEGORY)stoi(data[4]);
}


// Save stock information to a file
void StockItem::WriteToFile(ofstream& w) const {
    w << stockId << "," << name << "," << price << "," << quantity << "," << category << endl;
}
