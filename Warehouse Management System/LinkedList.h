#pragma once
#include "stockitem.h"

class LinkedList
{
private:
    struct node
    {
        StockItem* item;
        node* adrs;

        node(StockItem* item)
        {
            this->item = item;
            this->adrs = nullptr;
        }

        node() {
            this->item = new StockItem();
            this->adrs = nullptr;
        }
    };

    node* start, * current, * next;

public:

    LinkedList();

    ~LinkedList();

    void createNode(StockItem* item);

    bool find(StockItem* item);

    StockItem* findById(int itemId);

    StockItem* findByName(string name);

    bool idExists(int id);

    bool nameExists(string name);

    bool itemExists(StockItem* item);

    void nodeInBetween(int p, StockItem* item);

    void lowStockCheck(bool& lowStock, vector<StockItem*>& stock);

    void saveToFile(ofstream& W);

    void deleteNode(string name, bool& itemFound);

    void clearList();

    bool display(int choice);

    void insertionSort();

    // Helper function
    bool isSorted();
};

