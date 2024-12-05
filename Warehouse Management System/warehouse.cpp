#include "warehouse.h"
#include "utility.h"

void Warehouse::Run(){
    bool loggedIn = false;
    int loggerId = 0;
    bool exit = false;

    try {
        Employees.loadFromFile("staff.txt");
        report.loadFromFile("record.txt");
        do {
            logInPage(loggedIn, loggerId, exit);


            if (loggedIn) {
                LoadingScreen("\033[34mlogging In");
                Staff* user = Employees.findStaffById(loggerId);

                report.logActivity("Staff with Id : " + to_string(loggerId) + " and name : " + user->getName() + " - " + user->roleToString(user->getRole()) + " logged in successfully.");

                switch (user->getRole()) {
                case MANAGER:
                    mainPage_M(user);
                    break;

                case INVENTORY_CLERK:
                    mainPage_Ic(user);
                    break;

                case SHIPPING_CLERK:
                    mainPage_Sc(user);
                    break;

                case STAFF_SUPERVISOR:
                    mainPage_Ss(user);
                    break;

                case OPERATOR:
                    mainPage_Others(user);
                    break;

                case SECURITY_GAURD:
                    mainPage_Others(user);
                    break;

                default:
                    throw runtime_error("You don't access to this system !!!");
                    break;
                }
            }
            
            loggedIn = false;

        } while (exit == false);
        Employees.saveToFile("staff.txt");
        
        report.saveToFile("record.txt");
        report.logActivity("Staff logged out successfully.");
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void Warehouse::fullfillOrder(int orderId) {
    bool orderFound = false;
    try {
        for (int i = 0; i < (Orders.getOrders()).size(); i++) {
            if (orderId == Orders[i].getOrderId()) {
                orderFound = true;

                //for (auto& it : Orders[i].getItemsFromOrder()) {
                //    StockItem* stock = Inventory.findStockByName(it.first);
                //    if (stock->getQuantity() < it.second) {
                //        throw runtime_error("Low on Stock !!!\nUpdate Stock !!!");
                //    }
                //    else if (stock->getQuantity() >= it.second) {
                //        stock->removeQuantity(it.second);
                //    }
                //}
                cout << "\n\n\t\033[32mItems dispatched!!\t\tOrder Completed Successfully!!\033[0m";
                report.logActivity("Order of id " + to_string(orderId) + " was marked completed.");
                Orders.removeFromList(to_string(orderId));

                break;
            }
        }

        if (!orderFound) {
            throw runtime_error("Order not Found !!!");
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void Warehouse::contactSupplier(StockItem* stock, int quantity) {
    try {
        bool supplierFound = false;
        for (auto& s : Suppliers.getSupplierList()) {
            for (auto& item : s->getItemsSupplied()) {
                if (item == stock->getName()) {
                    stock->addQuantity(quantity);
                    cout << "\n\t\t\033[32mSupplier contacted, New stock is being added.\033[0m";
                    report.logInteraction("Item " + stock->getName() + " restocked by supplier: " + s->getName());
                    supplierFound = true;
                }
            }
        }

        if (!supplierFound) {
            throw runtime_error("Supplier for item " + stock->getName() + "not found!!");
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void Warehouse::notification() {
    bool lowStock = false;
    int quantity = 0;

    LoadingScreen("Loading");
    cout << "\n\n\t\t\t\t    \033[32m:: WAREHOUSE MANAGMENT SYSTEM ::\033[0m\n\t\t\t\t    ";
    DrawGreenLine(32, '-');

    vector<StockItem*> stock = Inventory.lowStockAlert(lowStock);

    if (lowStock) {

        report.logActivity("Low stock alert was given.");
        while (true) {
            cout << "\n\n\t\t\033[33mDo you want to restock the items? <Y/N> : \033[0m";
            string choice = getStringFromUser(1);

            if (choice == "Y") {
                for (auto& i : stock) {
                    cout << "\n\n\t\tEnter quantity to add for item " << i->getName() << " : ";
                    quantity = getNumberFromUser(8);
                    contactSupplier(i, quantity);
                    break;
                }
                lowStock = true;
                break;
            }
            else if (choice == "N") {
                cout << "\n\n\t\t\033[33mKeep in mind to restock as soon as possible.\033[0m";
                report.logActivity("Inventory was not restocked.");
                break;
            }
            else {
                cerr << "\n\n\t\033[31mInvalid choice !! choose between Y or N\033[0m";
            }
        }

        Pause();
    }

}


void Warehouse::logInPage(bool& bLI, int& lID, bool& exit) {
    try {
        string tempmail = "";
        bool staffFound = false;
        int wrongPin = 0, choice = 0;
        
        LoadingScreen("Loading");
        cout << "\n\n\n\t\t\t\t\t    \033[32m:: LOG-IN PAGE ::\033[0m\n\t\t\t\t\t    ";
        DrawGreenLine(17, '-');

        cout << "\n\n\t\t01. LOG IN";
        cout << "\n\n\t\t02. EXIT PROGRAM";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-2) : \033[0m";
        choice = getChoiceFromUser(2);
        
        switch (choice) {
        case 1:
            LoadingScreen("Loading");
            cout << "\n\n\n\t\t\t\t\t    \033[32m:: LOG-IN PAGE ::\033[0m\n\t\t\t\t\t    ";
            DrawGreenLine(17, '-');

            cout << "\n\n\t\tEnter email:  ";
            cin >> tempmail;


            for (auto& s : Employees.getStaffList()) {


                if (tempmail == s->getContactInfo()) {
                    staffFound = true;

                    if (s->getPin() == 0) {
                        Employees.newLogIn(s);
                        cout << "\n\n\t\t\033[32mPin saved successfully!!\tRemeber it for future login\033[0m";
                        bLI = true;

                        lID = s->getID();
                    }
                    else {
                        while (wrongPin != 5) {
                            cout << "\n\t\tEnter your pin:  ";
                            int pin = getPinFromUser();
                            if (s->getPin() == pin) {
                                cout << "\n\n\t\t\033[32mLogged In successfully!!\033[0m\n"; //(only 5 tries to input correct pin)
                                bLI = true;

                                lID = s->getID();

                                Sleep(1000);
                                return;
                            }
                            else {
                                cerr << "\n\t\t\033[31mIncorrect pin try again\033[0m\n\n";
                                wrongPin++;
                                if (wrongPin == 5) {
                                    report.logActivity("Failed log in attempt by staff - " + s->getName());
                                    throw runtime_error("Entered wrong pin too many times !!!");
                                    return;
                                }
                            }
                        }
                    }
                }

            }

            if (!staffFound) {
                report.logActivity("Failed attempt to log in recorded.");
                throw runtime_error("Mail not found !!!\n\t\tPlease enter a valid username.");
            }

            break;
        case 2:
            exit = true;
            return;

        default:
            break;
        }

    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void Warehouse::inventoryMenu() {
    int choice = 0;
    string input = "";
    while (true) {
        StockItem* item = new StockItem();

        LoadingScreen("loading");

        cout << "\t\t\t\t\t\033[34m:: INVENTORY MANAGMENT ::\033[0m\n\t\t\t\t\t";
        DrawBlueLine(24, '-');

        cout << "\n\n\t\t01. DISPALY INVENTORY";
        cout << "\n\n\t\t02. SEARCH AN ITEM IN INVENTORY";
        cout << "\n\n\t\t03. ADD NEW ITEM TO INVENTORY";
        cout << "\n\n\t\t04. REMOVE ITEM FROM INVENTORY";
        cout << "\n\n\t\t05. MODIFY ITEM DETAILS";
        cout << "\n\n\t\t06. GO BACK TO MAIN MENU";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-6) : \033[0m";
        choice = getChoiceFromUser(6);

        try {
            switch (choice) {

            case 1:
                system("cls");
                cout << "\t\t\t\t\t\033[34m:: INVENTORY MANAGMENT ::\033[0m\n\t\t\t\t\t";
                DrawBlueLine(24, '-');

                Inventory.displayList();
                break;

            case 2:
                system("cls");
                cout << "\t\t\t\t\t\033[34m:: INVENTORY MANAGMENT ::\033[0m\n\t\t\t\t\t";
                DrawBlueLine(24, '-');

                cout << "\n\n\t\tEnter item name : ";
                input = getStringFromUser(20);

                if (!Inventory.nameExists(input)) {
                    throw invalid_argument("Item not found !!!");
                    break;
                }

                item = Inventory.findStockByName(input);

                cout << "\n\n\t\t\033[32m" << setw(8) << left << "Stock Id";
                cout << "\t\t" << setw(20) << left << "Name";
                cout << "\t\t" << setw(8) << left << "Price";
                cout << "\t\t" << setw(20) << left << "Category";
                cout << "\t\t" << setw(8) << left << "Quantity\033[0m" << endl << endl;
                cout << item;

                item = NULL;
                Pause();
                break;

            case 3:
                system("cls");
                cout << "\t\t\t\t\t\033[34m:: INVENTORY MANAGMENT ::\033[0m\n\t\t\t\t\t";
                DrawBlueLine(24, '-');
                while (true) {
                    cin >> item;
                    if (Inventory.itemExists(*item)) {
                        throw runtime_error("Item with this name or id already exists !!\t Try Again with different values.");
                    }
                    else {
                        Inventory.addToList(*item);
                        cout << "\n\n\t\033[32mItem successfully added in the inventory!!\033[0m";
                        break;
                    }
                }

                report.logActivity("New item " + item->getName() + " was added to the inventory.");
                Pause();

                item = NULL;
                break;

            case 4:
                system("cls");
                cout << "\t\t\t\t\t\033[34m:: INVENTORY MANAGMENT ::\033[0m\n\t\t\t\t\t";
                DrawBlueLine(24, '-');

                cout << "\n\n\t\tEnter Name of the item to be removed: ";
                input = getStringFromUser(20);

                if (!Inventory.nameExists(input)) {
                    throw invalid_argument("Item not found !!!");
                    break;
                }
                else {
                    Inventory.removeFromList(input);
                    cout << "\n\n\t\033[32mItem successfully removed from the inventory!!\033[0m";

                    report.logActivity("Item " + item->getName() + " was removed from the inventory.");
                    Pause();

                    item = NULL;
                    break;
                }

            case 5:
                system("cls");
                cout << "\t\t\t\t\t\033[34m:: INVENTORY MANAGMENT ::\033[0m\n\t\t\t\t\t";
                DrawBlueLine(24, '-');

                cout << "\n\n\t\tEnter item name to be modified : ";
                input = getStringFromUser(20);

                if (!Inventory.nameExists(input)) {
                    throw invalid_argument("Item not found !!!");
                    break;
                }

                item = Inventory.findStockByName(input);

                cout << "\n\t\t\t\t\t\033[32m----PREVIOUS DETAILS----\033[0m\n\n";
                cout << "\t\t\033[32m" << setw(8) << left << "Stock Id";
                cout << "\t\t" << setw(20) << left << "Name";
                cout << "\t\t" << setw(8) << left << "Price";
                cout << "\t\t" << setw(20) << left << "Category";
                cout << "\t\t" << setw(8) << left << "Quantity\033[0m" << endl;
                cout << item;

                Inventory.modifyDetails(input);

                item = Inventory.findStockById(item->getStockId());
                cout << "\n\t\t\t\t\t\033[32m----NEW DETAILS----\033[0m\n\n";
                cout << "\t\t\033[32m" << setw(8) << left << "Stock Id";
                cout << "\t\t" << setw(20) << left << "Name";
                cout << "\t\t" << setw(8) << left << "Price";
                cout << "\t\t" << setw(20) << left << "Category";
                cout << "\t\t" << setw(8) << left << "Quantity\033[0m" << endl;
                cout << item;

                report.logActivity("Item " + item->getName() + " details's were updated.");
                Pause();

                item = NULL;
                break;

            case 6:
                //Inventory.saveToFile("inventory.txt");
                delete item;
                item = NULL;
                return;

            default:
                cout << "\n\n\t\t\033[31mInvalid Choice!!\033[0m";
                break;
            }
        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    }
}

void Warehouse::orderMenu() {
    int choice = 0, id = 0;
    Order* order = new Order();

    while (true) {
        system("cls");

        cout << "\t\t\t\t\t\033[34m:: ORDER MANAGMENT ::\033[0m\n\t\t\t\t\t";
        DrawBlueLine(21, '-');
        cout << endl;
            
        Orders.displayList();

        cout << "\n\n\t\t01. FULFILL AN ORDER";
        cout << "\n\n\t\t02. MODIFY ORDER DETAILS";
        cout << "\n\n\t\t03. ADD AN ORDER TO THE LIST";
        cout << "\n\n\t\t04. REMOVE AN ORDER FROM THE LIST";
        cout << "\n\n\t\t05. GO BACK TO MAIN MENU";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-5) : \033[0m";
        choice = getChoiceFromUser(5);
        try {
            switch (choice)
            {
            case 1:
                cout << "\n\n\t\tEnter the id of the order to be fulfilled : ";
                id = getNumberFromUser(4);
                if (Orders.idExists(id)) {
                    fullfillOrder(id);

                    Pause();
                    order = NULL;
                    break;
                }
                else {
                    throw invalid_argument("Order with particular id not found !!!");
                    break;
                }

            case 2:
                cout << "\n\n\t\tEnter id of the order to be modified : ";
                id = getNumberFromUser(4);

                if (!Orders.idExists(id)) {
                    throw invalid_argument("Order with particular id not found !!!");
                    break;
                }

                order = Orders.findOrderById(id);

                cout << "\n\t\t\t\t\t\033[32m----PREVIOUS DETAILS----\033[0m\n\n";
                cout << "\t\t\033[32m" << setw(9) << left << "Order Id" << "\t\t\t" << setw(30) << left << "Items" << endl;
                cout << "\t\t\t\t\t" << setw(25) << left << "Item Name" << setw(5) << left << "Quantity\033[0m" << endl << "\t";
                cout << order;

                Orders.modifyDetails(to_string(id));

                order = Orders.findOrderById(id);

                cout << "\n\t\t\t\t\t\033[32m----NEW DETAILS----\033[0m\n\n";
                cout << "\t\t\033[32m" << setw(9) << left << "Order Id" << "\t\t\t" << setw(30) << left << "Items" << endl;
                cout << "\t\t\t\t\t" << setw(25) << left << "Item Name" << setw(5) << left << "Quantity\033[0m" << endl << "\t";
                cout << order;

                report.logActivity("Order of id " + to_string(id) + " was updated.");
                Pause();
                order = NULL;
                break;

            case 3:
                cin >> order;
                if (Orders.orderExists(*order)) {
                    throw runtime_error("Order with this id already exists !!\t try different id !!");
                }
                else {
                    Orders.addToList(*order);
                    cout << "\n\n\t\033[32mOrder successfully added to the List!!\033[0m";
                    report.logActivity("New Order of id " + to_string(order->getOrderId()) + " was added to the list.");
                }

                Pause();
                order = NULL;
                break;

            case 4:
                cout << "\n\n\t\tEnter id of the order to be removed : ";
                id = getNumberFromUser(5);

                if (Orders.idExists(id)) {
                    Orders.removeFromList(to_string(id));
                    cout << "\n\n\t\033[32mOrder Removed from the List!!\033[0m";

                    report.logActivity("Order of id " + to_string(id) + " was removed from the list.");
                    Pause();
                    break;
                }
                else {
                    throw invalid_argument("Order with particular id not found !!!");
                    break;
                }

            case 5:
                //Orders.saveToFile("orders.txt");
                delete order;
                order = NULL;
                return;

            default:
                cout << "\n\n\t\t\033[31mInvalid Choice!!\033[0m";
                break;
            }
        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    }

}

void Warehouse::staffMenu() {
    int choice = 0;
    Staff* staff = new Staff();
    string input = "";
    while (true) {
        LoadingScreen("Loading");

        cout << "\t\t\t\t\t\033[34m:: STAFF MANAGMENT ::\033[0m\n\t\t\t\t\t";
        DrawBlueLine(21, '-');

        cout << "\n\n\t\t01. ADD NEW STAFF MEMBER";
        cout << "\n\n\t\t02. REMOVE A STAFF MEMBER";
        cout << "\n\n\t\t03. MODIFY A STAFF MEMBER'S DETAILS";
        cout << "\n\n\t\t04. DISPLAY ALL STAFF MEMBERS";
        cout << "\n\n\t\t05. GO BACK TO MAIN MENU";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-5) : \033[0m";
        choice = getChoiceFromUser(5);

        try {
            switch (choice) {
            case 1:
                while (true) {
                    LoadingScreen("Loading");

                    cout << "\t\t\t\t\t\033[34m:: STAFF MANAGMENT ::\033[0m\n\t\t\t\t\t";
                    DrawBlueLine(21, '-');
                    try {
                        cin >> staff;
                        if (Employees.staffExists(*staff)) {
                            cerr << "\033[31mStaff with this name or id already exists !!\t Try Again with different values.\033[0m";
                        }
                        else {
                            Employees.addToList(*staff);
                            cout << "\n\n\t\033[32mNew staff successfully added!!\033[0m";
                            report.logActivity("Staff of id " + to_string(staff->getID()) + " was added to the list.");
                            break;
                        }
                    }
                    catch (exception& e) {
                        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
                        Pause();
                    }

                }

                Pause();
                staff = NULL;
                break;

            case 2:
                LoadingScreen("Loading");
                cout << "\t\t\t\t\t\033[34m:: STAFF MANAGMENT ::\033[0m\n\t\t\t\t\t";
                DrawBlueLine(21, '-');

                cout << "\n\n\t\tEnter Name of the staff to be removed: ";
                input = getStringFromUser(20);

                if (Employees.nameExists(input)) {
                    Employees.removeFromList(input);
                    cout << "\n\n\t\033[32mStaff successfully removed !!\033[0m";

                    report.logActivity("Staff of id " + input + " was removed from the list.");
                    Pause();
                    break;
                }
                else {
                    throw invalid_argument("Staff not found !!!");
                    break;
                }

            case 3:
                LoadingScreen("Loading");
                cout << "\t\t\t\t\t\033[34m:: STAFF MANAGMENT ::\033[0m\n\t\t\t\t\t";
                DrawBlueLine(21, '-');

                cout << "\n\n\t\tEnter Name of the Staff Member to be modified : ";
                input = getStringFromUser(20);

                if (!Employees.nameExists(input)) {
                    throw invalid_argument("Staff not found !!!");
                    break;
                }

                staff = Employees.findStaffByName(input);

                cout << "\n\t\t\t\t\t\033[32m----PREVIOUS DETAILS----\033[0m\n\n";
                cout << "\t\t\033[32m" << setw(8) << left << "Staff Id";
                cout << "\t\t" << setw(17) << left << "Name";
                cout << "\t\t" << setw(17) << left << "Role";
                cout << "\t\t" << setw(25) << left << "E-mail\033[0m" << endl;
                cout << staff << endl;

                Employees.modifyDetails(input);

                staff = Employees.findStaffById(staff->getID());

                cout << "\n\t\t\t\t\t\033[32m----NEW DETAILS----\033[0m\n\n";
                cout << "\t\t\033[32m" << setw(8) << left << "Staff Id";
                cout << "\t\t" << setw(17) << left << "Name";
                cout << "\t\t" << setw(17) << left << "Role";
                cout << "\t\t" << setw(25) << left << "E-mail\033[0m" << endl;
                cout << staff << endl;

                report.logActivity("Staff of id " + to_string(staff->getID()) + " was updated.");
                Pause();
                staff = NULL;
                break;

            case 4:
                LoadingScreen("Loading");
                Employees.displayList();

                Pause();
                break;

            case 5:
                //Employees.saveToFile("staff.txt");
                delete staff;
                staff = NULL;
                return;

            default:
                throw invalid_argument("Invalid Choice !!");
                break;
            }
        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    }
}

void Warehouse::supplyMenu() {
    int choice = 0;
    Supplier* supplier = new Supplier();
    string input = "";

    while (true) {
        LoadingScreen("loading");

        cout << "\t\t\t\t\t\033[34m:: SUPPLY MANAGMENT ::\033[0m\n\t\t\t\t\t";
        DrawBlueLine(22, '-');

        cout << "\n\n\t\t01. DISPLAY ALL SUPPLIERS";
        cout << "\n\n\t\t02. DISPLAY SUPPLIER INTERACTIONS";
        cout << "\n\n\t\t03. ADD NEW SUPPLIER";
        cout << "\n\n\t\t04. REMOVE A SUPPLIER";
        cout << "\n\n\t\t05. MODIFY A SUPPLIER'S DETAILS";
        cout << "\n\n\t\t06. GO BACK TO MAIN MENU";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-6) : \033[0m";
        choice = getChoiceFromUser(6);

        try {
            switch (choice)
            {
            case 1:
                LoadingScreen("Loading");
                cout << "\t\t\t\t\t\t\033[34m:: SUPPLY MANAGMENT ::\033[0m\n\t\t\t\t\t\t";
                DrawBlueLine(22, '-');
                cout << "\n\n";
                Suppliers.displayList();
                Pause();
                break;

            case 2:
                report.displaySupplierInteractionsLog();
                break;

            case 3:
                LoadingScreen("Loading");
                cout << "\t\t\t\t\t\033[34m:: SUPPLY MANAGMENT ::\033[0m\n\t\t\t\t\t";
                DrawBlueLine(22, '-');
                while (true) {
                    cin >> supplier;
                    if (Suppliers.supplierExists(*supplier)) {
                        throw runtime_error("Supplier with this name or id already exists !!\t Try Again with different values.");
                    }
                    else {
                        Suppliers.addToList(*supplier);
                        cout << "\n\n\t\033[32mNew supplier successfully added!!\033[0m";
                        report.logActivity("Supplier of id " + to_string(supplier->getID()) + " was added to the list.");
                        break;
                    }
                }
                Pause();
                break;

            case 4:
                LoadingScreen("Loading");
                cout << "\t\t\t\t\t\033[34m:: SUPPLY MANAGMENT ::\033[0m\n\t\t\t\t\t";
                DrawBlueLine(22, '-');
                cout << "\n\n\t\tEnter Name of the supplier to be removed: ";
                input = getStringFromUser(20);

                if (!Suppliers.nameExists(input)) {
                    throw invalid_argument("Supplier not found !!!");
                    break;
                }
                else {
                    Suppliers.removeFromList(input);
                    cout << "\n\n\t\033[32mSupplier successfully removed !!\033[0m";

                    report.logActivity("Supplier of id " + to_string(supplier->getID()) + " was removed to the list.");
                    Pause();
                    break;
                }

            case 5:
                LoadingScreen("Loading");
                cout << "\t\t\t\t\t\033[34m:: SUPPLY MANAGMENT ::\033[0m\n\t\t\t\t\t";
                DrawBlueLine(22, '-');

                cout << "\n\n\t\tEnter Name of the Supplier to be modified : ";
                input = getStringFromUser(20);

                if (!Suppliers.nameExists(input)) {
                    throw invalid_argument("Supplier not found !!!");
                    break;
                }

                supplier = Suppliers.findSupplierByName(input);

                cout << "\n\t\t\t\t\t\033[32m----PREVIOUS DETAILS----\033[0m\n\n";
                cout << "\t\t\033[32m" << setw(8) << left << "Supplier Id";
                cout << "\t\t" << setw(17) << left << "Name";
                cout << "\t\t" << setw(20) << left << "Contact Info";
                cout << "\t\t" << setw(15) << left << "Items Supplied\033[0m" << endl;
                cout << supplier;

                Suppliers.modifyDetails(input);

                supplier = Suppliers.findSupplierById(supplier->getID());

                cout << "\n\t\t\t\t\t\033[32m----NEW DETAILS----\033[0m\n\n";
                cout << "\t\t\033[32m" << setw(8) << left << "Supplier Id";
                cout << "\t\t" << setw(17) << left << "Name";
                cout << "\t\t" << setw(20) << left << "Contact Info";
                cout << "\t\t" << setw(15) << left << "Items Supplied\033[0m" << endl;
                cout << supplier;


                report.logActivity("Supplier of id " + to_string(supplier->getID()) + " was updated.");
                Pause();
                break;

            case 6:
                //Suppliers.saveToFile("suppliers.txt");
                delete supplier;
                supplier = NULL;
                return;

            default:
                throw invalid_argument("Invalid Choice !!");
                break;
            }
        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    }
}


void Warehouse::mainPage_M(Staff* user) {
    int ch = 0, choice = 0;
    bool back = false;

    Inventory.loadFromFile("inventory.txt");
    Orders.loadFromFile("orders.txt");
    Suppliers.loadFromFile("suppliers.txt");

    notification();

    while (true) {
        back = false, ch = 0;
        LoadingScreen("Loading");
        cout << "\n\n\t\t\t\t    \033[32m:: WAREHOUSE MANAGMENT SYSTEM ::\033[0m\n\t\t\t\t    ";
        DrawGreenLine(32, '-');


        cout << "\n\n\t\t\033[94mWelcome Mr/Ms " << user->getName() << "\n\t\t\t\t\t" << user->roleToString(user->getRole()) << "\033[0m";

        cout << "\n\n\t\t01. WAREHOUSE MANAGMENT";
        cout << "\n\n\t\t02. PERSONAL PROFILE MANAGMENT";
        cout << "\n\n\t\t03. CHECK RECORD";
        cout << "\n\n\t\t04. LOG OUT";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-4) : \033[0m";
        choice = getChoiceFromUser(4);

        try {
            switch (choice) {
            case 1:
                while (!back) {
                    LoadingScreen("Loading");
                    showMainMenu();
                    ch = getChoiceFromUser(5);
                    try {
                        switch (ch) {
                        case 1:
                            inventoryMenu();
                            break;
                        case 2:
                            orderMenu();
                            break;
                        case 3:
                            staffMenu();
                            break;
                        case 4:
                            supplyMenu();
                            break;
                        case 5:
                            back = true;
                            break;
                        default:
                            throw runtime_error("Invalid Choice !!");
                            break;
                        }
                    }
                    catch (exception& e) {
                        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
                        Pause();
                    }
                }
                break;

            case 2:
                Employees.personalProfile(user);
                report.logActivity("Personal details were updated.");
                break;

            case 3:
                while (!back) {
                    LoadingScreen("loading");
                    cout << "\t\t\t\t\t\t\t\033[34m:: RECORD ::\033[0m\n\t\t\t\t\t\t\t";
                    DrawBlueLine(12, '-');
                    cout << endl << endl;

                    cout << "\n\n\t\t01. CHECK ACTIVITY REPORT";
                    cout << "\n\n\t\t02. CHECK ATTENDANCE REPORT";
                    cout << "\n\n\t\t03. BACK";
                    cout << "\n\n\t\t\033[33mChoose what you want to do (1-3) : \033[0m";
                    ch = getChoiceFromUser(3);

                    try {
                        switch (ch) {
                        case 1:
                            report.displayActivityLog();
                            break;

                        case 2:
                            report.displayAttendanceLog();
                            break;

                        case 3:
                            back = true;
                            break;

                        default:
                            throw runtime_error("Invalid Choice !!");
                            break;
                        }
                    }
                    catch (exception& e) {
                        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
                        Pause();
                    }
                }
                report.saveToFile("record.txt");
                break;

            case 4:
                Inventory.saveToFile("inventory.txt");
                Orders.saveToFile("orders.txt");
                Suppliers.saveToFile("suppliers.txt");

                LoadingScreen("\033[31m Logging Out");
                return;

            default:
                break;
            }
        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    }
}

void Warehouse::mainPage_Ic(Staff* user) {
    int choice = 0;
    bool back = false;

    Inventory.loadFromFile("inventory.txt");
    Suppliers.loadFromFile("suppliers.txt");

    report.logAttendance("Staff : " + user->getName() + " - " + user->roleToString(user->getRole()) + " Marked Entry.");

    notification();

    while (true) {
        LoadingScreen("Loading");
        cout << "\n\n\n\t\t\t\t\t    \033[32m:: WAREHOUSE MANAGMENT SYSTEM ::\033[0m\n\t\t\t\t\t    ";
        DrawGreenLine(32, '-');


        cout << "\n\n\t\t\033[94mWelcome Mr/Ms " << user->getName() << "\n\t\t\t\t\t" << user->roleToString(user->getRole()) << "\033[0m";


        cout << "\n\n\t\t01. INVENTORY MANAGMENT";
        cout << "\n\n\t\t02. SUPPLY MANAGMENT";
        cout << "\n\n\t\t03. PERSONAL PROFILE MANAGMENT";
        cout << "\n\n\t\t04. LOG OUT";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-4) : \033[0m";
        choice = getChoiceFromUser(4);

        switch (choice) {
        case 1:
            inventoryMenu();
            break;

        case 2:
            supplyMenu();
            break;

        case 3:
            Employees.personalProfile(user);
            report.logActivity("Personal details were updated.");
            break;

        case 4:
            Inventory.saveToFile("inventory.txt");
            Suppliers.saveToFile("suppliers.txt");
            report.logAttendance("Staff : " + user->getName() + " - " + " Marked Exit.");

            LoadingScreen("\033[31m Logging Out");
            return;

        default:
            break;
        }
    }
}

void Warehouse::mainPage_Sc(Staff* user) {
    int choice = 0;
    bool back = false;

    Inventory.loadFromFile("inventory.txt");
    Orders.loadFromFile("orders.txt");
    
    report.logAttendance("Staff : " + user->getName() + " - " + user->roleToString(user->getRole()) + " Marked Entry.");

    while (true) {
        LoadingScreen("Loading");
        cout << "\n\n\n\t\t\t\t\t    \033[32m:: WAREHOUSE MANAGMENT SYSTEM ::\033[0m\n\t\t\t\t\t    ";
        DrawGreenLine(32, '-');

        cout << "\n\n\t\t\033[94mWelcome Mr/Ms " << user->getName() << "\n\t\t\t\t\t" << user->roleToString(user->getRole()) << "\033[0m";

        cout << "\n\n\t\t01. ORDER MANAGMENT";
        cout << "\n\n\t\t02. PERSONAL PROFILE MANAGMENT";
        cout << "\n\n\t\t03. LOG OUT";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-3) : \033[0m";
        choice = getChoiceFromUser(3);

        switch (choice) {
        case 1:
            orderMenu();
            break;

        case 2:
            Employees.personalProfile(user);
            report.logActivity("Personal details were updated.");
            break;

        case 3:
            Inventory.saveToFile("inventory.txt");
            Orders.saveToFile("orders.txt");
            report.logAttendance("Staff : " + user->getName() + " - " + " Marked Exit.");
            
            LoadingScreen("\033[31m Logging Out");
            return;

        default:
            break;
        }
    }
}

void Warehouse::mainPage_Ss(Staff* user) {
    int choice = 0;

    report.logAttendance("Staff : " + user->getName() + " - " + user->roleToString(user->getRole()) + " Marked Entry.");

    while (true) {
        LoadingScreen("Loading");
        cout << "\n\n\n\t\t\t\t\t    \033[32m:: WAREHOUSE MANAGMENT SYSTEM ::\033[0m\n\t\t\t\t\t    ";
        DrawGreenLine(32, '-');

        cout << "\n\n\t\t\033[94mWelcome Mr/Ms " << user->getName() << "\n\t\t\t\t\t" << user->roleToString(user->getRole()) << "\033[0m";

        cout << "\n\n\t\t01. STAFF MANAGMENT";
        cout << "\n\n\t\t02. PERSONAL PROFILE MANAGMENT";
        cout << "\n\n\t\t03. LOG OUT";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-3) : \033[0m";
        choice = getChoiceFromUser(3);

        switch (choice) {
        case 1:
            staffMenu();
            break;

        case 2:
            Employees.personalProfile(user);
            report.logActivity("Personal details were updated.");
            break;

        case 3:
            report.logAttendance("Staff : " + user->getName() + " - " + " Marked Exit.");

            LoadingScreen("\033[31m Logging Out");
            return;

        default:
            break;
        }
    }
}

void Warehouse::mainPage_Others(Staff* user){
    int choice = 0;


    while (true) {
        LoadingScreen("Loading");
        cout << "\n\n\n\t\t\t\t\t    \033[32m:: WAREHOUSE MANAGMENT SYSTEM ::\033[0m\n\t\t\t\t\t    ";
        DrawGreenLine(32, '-');

        cout << "\n\n\t\t\033[94mWelcome Mr/Ms " << user->getName() << "\n\t\t\t\t\t" << user->roleToString(user->getRole()) << "\033[0m";

        cout << "\n\n\t\t01. MARK ENTRY";
        cout << "\n\n\t\t02. MARK EXIT";
        cout << "\n\n\t\t03. PERSONAL PROFILE MANAGMENT";
        cout << "\n\n\t\t04. LOG OUT";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-4) : \033[0m";
        choice = getChoiceFromUser(4);

        switch (choice) {
        case 1:
            report.logAttendance("Staff : " + user->getName() + " - " + user->roleToString(user->getRole()) + " Marked Entry.");
            cout << "\n\n\t\t\033[32mAttenance marked !!\033[0m";
            Pause();
            break;

        case 2:
            report.logAttendance("Staff : " + user->getName() + " - " + user->roleToString(user->getRole()) + " Marked Exit.");
            cout << "\n\n\t\t\033[32mAttenance marked !!\033[0m";
            Pause();
            break;

        case 3:
            Employees.personalProfile(user);
            report.logActivity("Personal details were updated.");
            break;

        case 4:
            LoadingScreen("\033[31m Logging Out");
            return;

        default:
            break;
        }
    }
}
