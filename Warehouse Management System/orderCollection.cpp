#include "orderCollection.h"

#include "utility.h"

OrderCollection::OrderCollection() { orderList = {}; }

vector<Order*> OrderCollection::getOrders() { 
    return orderList.allOrders();
}

void OrderCollection::addToList(Order& o) {
    Order* order = new Order(o.getOrderId(), o.getItemsFromOrder());
    orderList.enqueue(order);
    orderList.priortize();
}

void OrderCollection::removeFromList(string Id) {
    int orderId = stoi(Id);
    bool idFound = false;
    try {

        /*for (int i = 0; i <= orderList.size(); i++) {
            if (orderList[i]->getOrderId() == orderId) {
                orderList.erase(orderList.begin() + i);
                itemFound = true;
                break;
            }
        }*/

        orderList.dequeueByID(orderId, idFound);

        if (!idFound) {
            throw runtime_error("Order with ID " + Id + " not found.\n");
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void OrderCollection::modifyDetails(string id) {
    int orderId = stoi(id);
    Order* o = findOrderById(orderId);
    cout << "\n\n\t\t01. Add an item in the order";
    cout << "\n\n\t\t02. Remove an item from the order";
    cout << "\n\n\t\t03. Update item quantity";
    cout << "\n\n\t\t04. Go Back";
    while (true) {
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-4) : \033[0m";
        int opt = getChoiceFromUser(4);

        string newInput;

        try {
            switch (opt) {

            case 1:
                cout << "\n\n\t\tEnter name of the item to add: ";
                newInput = getStringFromUser(25);

                if (o->itemExistsInOrder(newInput)) {
                    throw runtime_error("Item already present in the order !!!");
                    break;
                }
                else {
                    cout << "\n\n\t\tEnter quantity : ";
                    int quantity = getNumberFromUser(5);

                    o->addItemToOrder(newInput, quantity);

                    cout << "\n\t\033[32mItem added!!\033[0m";
                    break;
                }

            case 2:
                cout << "\n\n\t\tEnter name of the item to be removed : ";
                newInput = getStringFromUser(25);
                if (o->itemExistsInOrder(newInput)) {
                    o->removeItemFromOrder(newInput);
                    cout << "\n\t\033[32mItem removed!!\033[0m";
                    break;
                }
                else {
                    throw runtime_error("Item does not exists in order !!!");
                }

            case 3:
                cout << "\n\n\t\tEnter name of the item to be updated : ";
                newInput = getStringFromUser(25);
                if (o->itemExistsInOrder(newInput)) {
                    cout << "\n\n\t\tEnter new amount : ";
                    int quantity = getNumberFromUser(10);

                    if (quantity <= 0) {
                        throw invalid_argument("Value can not be equal to zero or less !!!");
                        break;
                    }
                    else {
                        for (auto& i : o->getItemsFromOrder()) {
                            if (i.first == newInput) {
                                i.second = quantity;
                            }
                        }
                        cout << "\n\t\033[32mStock updated!!\033[0m";
                    }
                }
                else {
                    throw runtime_error("Item does not exists in order !!!");
                }

            case 4:
                return;

            default:
                cerr << "\n\t\033[31mInvalid Choice Entered!!\033[0m";
                break;
            }
        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    }
}

Order* OrderCollection::findOrderById(int orderId) {
    try {
        if (!idExists(orderId)) {
            throw runtime_error("Order with id " + to_string(orderId) + "not found");
        }
        else {
            /*for (Order* i : orderList) {
                if (i->getOrderId() == orderId) {
                    return i;
                }
            }*/

            return orderList.findById(orderId);
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
        return nullptr;
    }
}

bool OrderCollection::idExists(int id){
    /*for (Order* o : orderList) {
        if (o->getOrderId() == id) {
            return true;
        }
    }*/

    if (orderList.findById(id) != nullptr) {
        return true;
    }
    else {
        return false;
    }
}

bool OrderCollection::nameExists(string name){
    return false;
}

bool OrderCollection::orderExists(Order& order){
    /*for (Order* o : orderList) {
        if (o->getOrderId() == order.getOrderId()) {
            return true;
        }
    }*/

    if (orderList.find(&order)) {
        return true;
    }
    else
    {
        return false;
    }
}

void OrderCollection::loadFromFile(string filename) {
    // Makes a new file if no file is found
    ofstream file;
    file.open(filename, ios::in);
    if (!file) {
        file.open(filename);
        file << "stockId,name,price,quantity,category\n";
    }
    file.close();
    
    
    try {
        ifstream reader;
        string read;
        reader.open(filename);

        if (!reader) {
            throw runtime_error("Order List not Found!!!");
        }

        getline(reader, read);
        while (getline(reader, read)) {
            Order o;
            o.getOrderFromFile(read);
            addToList(o);
        }

        reader.close();
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void OrderCollection::saveToFile(string filename) {
    ofstream Writer;
    try {
        Writer.open(filename);
        if (!Writer) {
            throw runtime_error("File failed to open!!");
        }

        Writer << "orderId,Items...\n";

        for (const auto o : orderList.allOrders()) {
            o->WriteToFile(Writer);
        }

        Writer.close();
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void OrderCollection::displayList() {
    cout << "\n\n\t\t\t\t\t\033[34m---PENDING ORDERS---\033[0m\n\t\t\t\t\t";
    DrawBlueLine(21, '-');
    cout << endl << endl << "\t";

    DrawBlueLine(100, '=');
    cout << endl;
    cout << "\t\t\033[32m" << setw(9) << left << "Order Id" << "\t\t\t" << setw(30) << left << "Items" << endl;
    cout << "\t\t\t\t\t" << setw(25) << left << "Item Name" << setw(5) << left << "Quantity\033[0m" << endl << "\t";
    DrawBlueLine(100, '=');
    cout << endl;

    for (auto& o : orderList.allOrders()) {
        cout << o;
    }
}

Order OrderCollection::operator[](int i) {
    auto orders = orderList.allOrders();
    return *orders[i];
}