#include "itemCollection.h"
#include "utility.h"

ItemCollection::ItemCollection() { itemList = {}; }

void ItemCollection::addToList(StockItem item) {
    StockItem* s = new StockItem(item.getStockId(),item.getName(),item.getPrice(),item.getQuantity(),item.getCategory());
    //itemList.push_back(s);
    itemList.createNode(s);
    itemList.insertionSort(); // To sort with stock ID.
}

void ItemCollection::removeFromList(string name) {
    bool itemFound = false;
    try {
        /*for (int i = 0; i <= itemList.size(); i++) {
            if (itemList[i]->getName() == name) {
                itemList.erase(itemList.begin() + i);
                itemFound = true;
                break;
            }
        }*/
        itemList.deleteNode(name, itemFound);
        if (!itemFound) {
            throw runtime_error("Product with name " + name + " not found.\n");
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void ItemCollection::modifyDetails(string name) {
    
    StockItem* item = findStockByName(name);

    bool back = false;

    cout << "\n\n\t\t01. Change Name of the item ";
    cout << "\n\n\t\t02. Change Price of the item";
    cout << "\n\n\t\t03. Add more stock";
    cout << "\n\n\t\t04. Remove stock";
    cout << "\n\n\t\t05. Change Category of the item";
    cout << "\n\n\t\t06. Go Back";
    
    while (!back) {
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-6) : \033[0m";
        int opt = getChoiceFromUser(6);

        string newInput = "";
        int newInt = 0;
        float newPrice = 0;
        try {
            switch (opt) {

            case 1:
                while (true) {
                    cout << "\n\n\t\tEnter new name: ";
                    newInput = getStringFromUser(20);

                    if (nameExists(newInput)) {
                        cerr << "\n\t\t\033[31mItem with this name already exists !!\t Try Again with different value.\033[0m";
                    }
                    else {
                        item->setName(newInput);
                        cout << "\n\t\033[32mName updated!!\033[0m";
                        break;
                    }
                }
                break;

            case 2:
                cout << "\n\n\t\tEnter new price : ";
                newPrice = getfloatFromUser(6);
                item->setPrice(newPrice);
                cout << "\n\t\033[32mPrice updated!!\033[0m";
                break;

            case 3:
                cout << "\n\n\t\tEnter amount of stock being added : ";
                newInt = getNumberFromUser(10);
                item->addQuantity(newInt);
                cout << "\n\t\033[32mStock updated!!\033[0m";
                break;

            case 4:
                cout << "\n\n\t\tEnter amount of stock being removed : ";
                newInt = getNumberFromUser(10);
                item->removeQuantity(newInt);
                cout << "\n\t\033[32mStock updated!!\033[0m";
                break;

            case 5:
                cout << "\n\n\t\tEnter category to change to : ";
                newInput = getStringFromUser(20);

                if (stringToCategory(newInput) == NON) {
                    throw runtime_error("Category not found!!!");
                    break;
                }
                else {
                    item->setCategory(stringToCategory(newInput));
                    cout << "\n\t\033[32mCategory updated!!\033[0m";
                    break;
                }

            case 6:
                back = true;
                break;

            default:
                throw invalid_argument("Invalid Choice Entered !!");
                break;
            }
        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    }
}

StockItem* ItemCollection::findStockById(int itemId) {
    try {
        if (!idExists(itemId)) {
            throw runtime_error("Product with id " + to_string(itemId) + " not found.\n");
        }
        else {
            /*for (StockItem* i : itemList) {
                if (i->getStockId() == itemId) {
                    return i;
                }
            }*/
            return itemList.findById(itemId);
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
    return NULL;
}

StockItem* ItemCollection::findStockByName(string name) {
    try {
        if (!nameExists(name)) {
            throw runtime_error("Product with name " + name + " not found.\n");
        }
        else {
            /*for (StockItem* i : itemList) {
                if (i->getName() == name) {
                    return i;
                }
            }*/
            return itemList.findByName(name);
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
    return NULL;
}

bool ItemCollection::idExists(int id){
    /*for (auto i : itemList) {
        if (i->getStockId() == id) {
            return true;
        }
    }
    return false;*/
    return itemList.idExists(id);
}
bool ItemCollection::nameExists(string name){
    /*for (auto i : itemList) {
        if (i->getName() == name) {
            return true;
        }
    }
    return false;*/
    return itemList.nameExists(name);
}
bool ItemCollection::itemExists(StockItem item){
    /*for (auto i : itemList) {
        if (i->getName() == item.getName()) {
            return true;
        }
        else if (i->getStockId() == item.getStockId()) {
            return true;
        }
    }
    return false;*/

    return itemList.itemExists(&item);
}


vector<StockItem*> ItemCollection::lowStockAlert(bool& lowStock) {
    vector<StockItem*> stock = {};
    /*for (StockItem* i : itemList) {
        
        if (i->getQuantity() <= 5 && i->getQuantity() != 0) {
            cout << "\n\n\t\t\033[31m ALERT !!!\033[0m\n\n\t\tLow on stock for item " << i->getName() << endl;
            lowStock = true;
            stock.push_back(i);
        }else if (i->getQuantity() == 0) {
            cout << "\n\n\t\t\033[31m ALERT !!!\033[0m\n\n\t\tStock level empty for item " << i->getName() << endl;
            lowStock = true;
            stock.push_back(i);
        }
    }*/

    itemList.lowStockCheck(lowStock, stock);

    return stock;
}

void ItemCollection::loadFromFile(string filename) {
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
            throw runtime_error("Inventory not Found!!!");
        }

        getline(reader, read); //for ignoring title line
        while (getline(reader, read)) {
            StockItem s;
            s.ReadStockFromFile(read);
            addToList(s);
        }

        reader.close();
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void ItemCollection::saveToFile(string filename) {
    ofstream Writer;
    Writer.open(filename);
    try {
        if (!Writer) {
            throw runtime_error("File failed to open!!");
        }

        Writer << "stockId,name,price,quantity,category\n";

        /*for (const auto& i : itemList) {
            i->StockItem::WriteToFile(Writer);
            delete i;
        }
        itemList.clear();*/

        itemList.saveToFile(Writer);
        itemList.clearList();
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
    Writer.close();
}

void ItemCollection::displayList() {
    do {
        cout << "\n\n\tCategories: ";
        cout << "\n\n\t\t01. ELECTRONICS";
        cout << "\n\n\t\t02. COMPUTER";
        cout << "\n\n\t\t03. AUTOMOTIVE";
        cout << "\n\n\t\t04. SPORTS";
        cout << "\n\n\t\t05. CLOTHING";
        cout << "\n\n\t\t06. FURNITURE";
        cout << "\n\n\t\t07. Back";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-7) : \033[0m";
        int choice = getChoiceFromUser(7);

        try {
            system("cls");
            cout << "\t\t\t\t\t\t\t\033[34m---INVENTORY---\033[0m\n\t\t\t\t\t\t\t";
            DrawBlueLine(15, '-');
            cout << endl << endl << "\t";

            DrawBlueLine(140, '=');
            cout << endl;
            cout << "\n\t\t\033[34m" << setw(8) << left << "Stock Id";
            cout << "\t\t" << setw(20) << left << "Name";
            cout << "\t\t" << setw(8) << left << "Price";
            cout << "\t\t" << setw(20) << left << "Category";
            cout << "\t\t" << setw(8) << left << "Quantity\033[0m" << endl << "\t";
            DrawBlueLine(140, '=');
            cout << endl;

            /*switch (choice)
            {
            case 1:
                for (StockItem* i : itemList) {
                    if ((i->getCategory()) == ELECTRONICS) {
                        cout << i;
                    }
                }
                break;

            case 2:
                for (StockItem* i : itemList) {
                    if (i->getCategory() == COMPUTER) {
                        cout << i;
                    }
                }
                break;

            case 3:
                for (StockItem* i : itemList) {
                    if (i->getCategory() == AUTOMOTIVE) {
                        cout << i;
                    }
                }
                break;

            case 4:
                for (StockItem* i : itemList) {
                    if (i->getCategory() == SPORTS) {
                        cout << i;
                    }
                }
                break;

            case 5:
                for (StockItem* i : itemList) {
                    if (i->getCategory() == CLOTHING) {
                        cout << i;
                    }
                }
                break;

            case 6:
                for (StockItem* i : itemList) {
                    if (i->getCategory() == FURNITURE) {
                        cout << i;
                    }
                }
                break;

            case 7:
                return;

            default:
                throw invalid_argument("Entered an invalid choice !!!");
                break;
            }*/

            bool exit = itemList.display(choice);
            if (exit)
                return;

        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    } while (true);
}