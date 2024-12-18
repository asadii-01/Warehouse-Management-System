#include "supplierCollection.h"
#include "utility.h"

vector<Supplier*> SupplierCollection::getSupplierList() {
    return supplierList;
}

void SupplierCollection::addToList(Supplier& s) {
    Supplier* supplier = new Supplier(s.getID(), s.getName(), s.getContactInfo(), s.getItemsSupplied());
    supplierList.push_back(supplier);
    this->sortItems();
}

void SupplierCollection::removeFromList(string name){
    bool supplierFound = false;
    try {
        for (int i = 0; i <= supplierList.size(); i++) {
            if (supplierList[i]->getName() == name) {
                supplierList.erase(supplierList.begin() + i);
                supplierFound = true;
                break;
            }
        }
        if (!supplierFound) {
            throw runtime_error("Supplier with name " + name + " not found !!!");
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void SupplierCollection::modifyDetails(string name){
    Supplier* supplier = findSupplierByName(name);

    cout << "\n\n\t\t01. Change Name";
    cout << "\n\n\t\t02. Change Contact Info";
    cout << "\n\n\t\t03. Add new item supplied";
    cout << "\n\n\t\t04. Remove any item supplied";
    cout << "\n\n\t\t05. Done";
    while (true) {
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-5) : \033[0m";
        int opt = getChoiceFromUser(6);

        string newInput;
        try {
            switch (opt) {

            case 1:
                while (true) {
                    cout << "\n\n\t\tEnter new name : ";
                    newInput = getStringFromUser(20);
                    try {
                        if (nameExists(newInput)) {
                            throw invalid_argument("Supplier with this name already exists !!\t Try Again with different value.");
                        }
                        else if (!isValidName(newInput)) {
                            throw invalid_argument("Supplier cannot have such name !!\t Try Again with different value.");
                        }
                        else {
                            supplier->setName(newInput);
                            cout << "\n\t\033[32mName updated!!\033[0m";
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
                cout << "\n\n\t\tEnter new email : ";
                cin >> newInput;
                if (!isValidEmail(newInput)) {
                    throw invalid_argument("Invalid Email !!\t Try Again with different value.");
                }
                supplier->setContactInfo(newInput);
                cout << "\n\t\033[32mContact Info updated!!\033[0m";
                break;

            case 3:
                cout << "\n\n\t\tEnter name of the new item : ";
                newInput = getStringFromUser(20);
                if (!isValidName(newInput)) {
                    throw invalid_argument("Invalid item name !!\t Try Again with different value.");
                }
                supplier->addItem(newInput);
                cout << "\n\t\033[32mNew item added!!\033[0m";
                break;

            case 4:
                cout << "\n\n\t\tEnter name of the item to be removed : ";
                newInput = getStringFromUser(20);
                if (supplier->removeItem(newInput)) {
                    cout << "\n\t\033[32mItem removed from the list!!\033[0m";
                }
                else {
                    throw invalid_argument("Item not found !!");
                }
                break;

            case 5:
                return;

            default:
                throw invalid_argument("Invalid Choice Entered !");
                break;
            }
        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    }
}


void SupplierCollection::merge(vector<Supplier*>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Supplier*> leftArr(n1);
    vector<Supplier*> rightArr(n2);

    for (int i = 0; i < n1; ++i)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i]->getID() <= rightArr[j]->getID()) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void SupplierCollection::mergeSort(vector<Supplier*>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

void SupplierCollection::sortItems() {
    if (!supplierList.empty())
        mergeSort(supplierList, 0, supplierList.size() - 1);
}

Supplier* SupplierCollection::findSupplierByName(string name) {
    try {
        if (!nameExists(name)) {
            throw runtime_error("Supplier with name " + name + " not found !!!");
        }
        else {
            for (auto& s : supplierList) {
                if (s->getName() == name) {
                    return s;
                }
            }
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
    return NULL;
}

Supplier* SupplierCollection::findSupplierById(int id){
    try {
        if (!idExists(id)) {
            throw runtime_error("Supplier with idS " + to_string(id) + " not found !!!");
        }
        else {
            for (auto& s : supplierList) {
                if (s->getID() == id) {
                    return s;
                }
            }
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
    return NULL;
}

bool SupplierCollection::supplierExists(Supplier& supplier){
    for (auto& s : supplierList) {
        if (s->getName() == supplier.getName()) {
            return true;
        }
        else if (s->getID() == supplier.getID()) {
            return true;
        }
    }
    return false;
}

bool SupplierCollection::nameExists(string name){
    for (auto& s : supplierList) {
        if (s->getName() == name) {
            return true;
        }
    }
    return false;
}

bool SupplierCollection::idExists(int id){
    for (auto& s : supplierList) {
        if (s->getID() == id) {
            return true;
        }
    }
    return false;
}

void SupplierCollection::loadFromFile(string filename) {
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
            throw runtime_error("Supplier List not Found!!!");
        }

        getline(reader, read); // For ignoring title line
        while (getline(reader, read)) {

            Supplier* s = new Supplier();
            s->Supplier::setDetails(read);
            addToList(*s);
            delete s;
        }

        reader.close();
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void SupplierCollection::saveToFile(string filename) {
    ofstream Writer;
    try {
        Writer.open(filename);

        if (!Writer) {
            throw runtime_error("File failed to open!!");
        }

        Writer << "supplierId,supplierName,contactInfo,itemSupplied....\n";

        for (const auto& s : supplierList) {
            s->Supplier::WriteToFile(Writer);
            delete s;
        }
        supplierList.clear();

        Writer.close();
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void SupplierCollection::displayList(){
    cout << "\t\t\t\t\t\t\033[34m---SUPPLIER LIST---\033[0m\n\t\t\t\t\t\t";
    DrawBlueLine(19, '-');
    cout << "\n\n\t";

    DrawBlueLine(120, '=');
    cout << endl;
    cout << "\n\t\t\033[32m" << setw(8) << left << "Supplier Id";
    cout << "\t\t" << setw(17) << left << "Name";
    cout << "\t\t" << setw(20) << left << "Contact Info";
    cout << "\t\t" << setw(15) << left << "Items Supplied\033[0m\n\t";
    DrawBlueLine(120, '=');
    cout << endl << endl;

    for (auto& s : supplierList) {
        cout << s;
    }
}
