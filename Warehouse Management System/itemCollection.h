#pragma once
#include "collection.h"
#include "LinkedList.h"

class ItemCollection : public StockItem, public Collection {

private:

    LinkedList itemList;

public:

    // Default constructor
    ItemCollection();

    // Destructor
    ~ItemCollection() = default;

    // Add a stock item to inventory
    void addToList(StockItem item);

    // Remove a stock item from the inventory
    void removeFromList(string name) override;

    // Modify details of a stock item
    void modifyDetails(string name) override;

    // Find a stock item by its id
    StockItem* findStockById(int itemId);

    // Find a stock by its name
    StockItem* findStockByName(string name);

    // To check existing values
    bool idExists(int id) override;
    bool nameExists(string name) override;
    bool itemExists(StockItem item);

    // Low Stock Level alert
    vector<StockItem*> lowStockAlert(bool& lowStock);

    // Read Data from file
    void loadFromFile(string filename) override;

    // Write data to files
    void saveToFile(string filename) override;

    //Display items
    void displayList() override;
};