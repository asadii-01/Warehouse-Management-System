#pragma once

#include "itemCollection.h"
#include "orderCollection.h"
#include "staffCollection.h"
#include "SupplierCollection.h"
#include "record.h"

class Warehouse{

private:
    ItemCollection Inventory;
    OrderCollection Orders;
    StaffCollection Employees;
    SupplierCollection Suppliers;
    Record report;
   
public:
    // Default Constructor
    Warehouse() = default;

    // Destructor
    ~Warehouse() = default;

    // Runs the System
    void Run();

    // Process an order (update inventory and mark order as completed)
    void fullfillOrder(int orderId);

    // Contact supplier to add stock
    void contactSupplier(StockItem* stock, int quantity);

    // Gives notification on start about low stock
    void notification();

    // Interface
    void logInPage(bool& bLI, int& lID, bool& exit);

    void mainPage_M(Staff* user);
    void mainPage_Ic(Staff* user);
    void mainPage_Sc(Staff* user);
    void mainPage_Ss(Staff* user);
    void mainPage_Others(Staff* user);
    
    void inventoryMenu();
    void orderMenu();
    void staffMenu();
    void supplyMenu();
};