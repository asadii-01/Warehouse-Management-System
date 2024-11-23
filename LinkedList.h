#pragma once
#include "stockitem.h"
struct node
{
    StockItem* item;
    node* adrs;

    node(StockItem* item)
    {
        this->item = item;
    }

    node() {}
};

class LinkedList
{
private:
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

    void nodeInBetween(int p, StockItem* item);

    void saveToFile(ofstream& W);

    void deleteNode(StockItem* item);

    void display();

};

