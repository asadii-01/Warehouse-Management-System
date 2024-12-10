#pragma once
#include "order.h"
#include "collection.h"
#include "Queue.h"

class OrderCollection : public Order, public Collection {

private:
    //vector<Order*> orderList;
    Queue orderList;

public: 

    // Constructor
    OrderCollection();

    // Destructor
    ~OrderCollection() = default;

    // Getter
    vector<Order*> getOrders();

    // Add order to orders list
    void addToList(Order& o);

    // Remove order from orders list
    void removeFromList(string orderId) override;

    // Modify order
    void modifyDetails(string id) override;

    // Find a order by its id
    Order* findOrderById(int orderId);
    
    // To check if value exists
    bool idExists(int id) override;
    bool nameExists(string name) override;
    bool orderExists(Order& order);

    // Read Data from file
    void loadFromFile(string filename) override;

    // Write data to file
    void saveToFile(string filename) override;

    //Display Data
    void displayList() override;

    //Operator overloading
    Order operator[](int i);
};
