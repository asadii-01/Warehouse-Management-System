#include "LinkedList.h"
#include "utility.h"

LinkedList::LinkedList()
{
	start = nullptr;
	current = nullptr;
	next = nullptr;
}

LinkedList::~LinkedList()
{
	delete start;
	delete current;
	delete next;
}

void LinkedList::createNode(StockItem* item)
{
    if (start == nullptr)
    {
        start = new node(item);
        current = start;
    }
    else
    {
        current = start;
        while (current->adrs != nullptr) {
            current = current->adrs;
        }

        next = new node(item);
        current->adrs = next;
        current = next;
    }
}

bool LinkedList::find(StockItem* item)
{
    current = start;
    while (current != nullptr)
    {
        if (current->item == item)
        {
            return true;
        }
        current = current->adrs;
    }

    return false;
}

StockItem* LinkedList::findById(int itemId)
{
    current = start;
    while (current != nullptr)
    {
        if (current->item->getStockId() == itemId)
        {
            return current->item;
        }
        current = current->adrs;
    }
    return nullptr;
}

StockItem* LinkedList::findByName(string name)
{
    current = start;
    while (current != nullptr)
    {
        if (current->item->getName() == name)
        {
            return current->item;
        }
        current = current->adrs;
    }
    return nullptr;
}

bool LinkedList::idExists(int id)
{
    current = start;
    while (current != nullptr)
    {
        if (current->item->getStockId() == id)
        {
            return true;
        }
        current = current->adrs;
    }
    return false;
}

bool LinkedList::nameExists(string name)
{
    current = start;
    while (current != nullptr)
    {
        if (current->item->getName() == name)
        {
            return true;
        }
        current = current->adrs;
    }
    return false;
}

bool LinkedList::itemExists(StockItem* item)
{
    current = start;
    while (current != nullptr)
    {
        if (current->item->getName() == item->getName() || current->item->getStockId() == item->getStockId())
        {
            return true;
        }
        current = current->adrs;
    }
    return false;
}

void LinkedList::nodeInBetween(int p, StockItem* item)
{
}

void LinkedList::lowStockCheck(bool& lowStock, vector<StockItem*>& stock)
{
    current = start;

    while (current != nullptr) {
        if (current->item->getQuantity() <= 5 && current->item->getQuantity() > 0) {
            cout << "\n\n\t\t\033[31m ALERT !!!\033[0m\n\n\t\tLow on stock for item " << current->item->getName() << endl;
            lowStock = true;
            stock.push_back(current->item);
        }
        else if (current->item->getQuantity() == 0) {
            cout << "\n\n\t\t\033[31m ALERT !!!\033[0m\n\n\t\tStock level empty for item " << current->item->getName() << endl;
            lowStock = true;
            stock.push_back(current->item);
        }

        current = current->adrs;
    }
}

void LinkedList::saveToFile(ofstream& W)
{
    current = start;
    while (current != nullptr)
    {
        current->item->WriteToFile(W);
        current = current->adrs;
    }
}

void LinkedList::deleteNode(string name, bool& itemFound)
{
    node* prev = nullptr;
    current = start;
    while (current != nullptr) {
        if (current->item->getName() == name) {
            if (current != start) {
                prev->adrs = current->adrs;
            }
            else {
                start = current->adrs;
            }
            itemFound = true;
            break;
        }
        prev = current;
        current = current->adrs;
    }
}

void LinkedList::clearList()
{
    node* temp;
    current = start;
    while (current != nullptr)
    {
        temp = current;
        current = current->adrs;
        delete temp;
    }
    start = nullptr;
}

bool LinkedList::display(int choice)
{
    switch (choice)
    {
    case 1:
        current = start;
        while(current != nullptr){
            if ((current->item->getCategory()) == ELECTRONICS) {
                cout << current->item;
            }
            current = current->adrs;
        }
        break;

    case 2:
        current = start;
        while (current != nullptr) {
            if ((current->item->getCategory()) == COMPUTER) {
                cout << current->item;
            }
            current = current->adrs;
        }
        break;

    case 3:
        current = start;
        while (current != nullptr) {
            if ((current->item->getCategory()) == AUTOMOTIVE) {
                cout << current->item;
            }
            current = current->adrs;
        }
        break;

    case 4:
        current = start;
        while (current != nullptr) {
            if ((current->item->getCategory()) == SPORTS) {
                cout << current->item;
            }
            current = current->adrs;
        }
        break;

    case 5:
        current = start;
        while (current != nullptr) {
            if ((current->item->getCategory()) == CLOTHING) {
                cout << current->item;
            }
            current = current->adrs;
        }
        break;

    case 6:
        current = start;
        while (current != nullptr) {
            if ((current->item->getCategory()) == FURNITURE) {
                cout << current->item;
            }
            current = current->adrs;
        }
        break;

    case 7:
        return true;

    default:
        throw invalid_argument("Entered an invalid choice !!!");
        break;
    }

    return false;
}

void LinkedList::insertionSort()
{

    if (isSorted())
    {
        return;
    }

    node* temp;
    node* sorted = nullptr;
    current = start;
    while (current != nullptr)
    {
        next = current->adrs;

        if (sorted == nullptr || sorted->item->getStockId() >= current->item->getStockId())
        {
            current->adrs = sorted;
            sorted = current;
        }
        else
        {
            temp = sorted;
            while (temp->adrs != nullptr && temp->adrs->item->getStockId() < current->item->getStockId())
            {
                temp = temp->adrs;
            }
            current->adrs = temp->adrs;
            temp->adrs = current;
        }

        current = next;
    }

    start = sorted;

}

bool LinkedList::isSorted()
{
    if (start == nullptr || start->adrs == nullptr)
    {
        return true;
    }

    current = start;
    while (current->adrs != nullptr)
    {
        if (current->item->getStockId() > current->adrs->item->getStockId())
        {
            return false;
        }
        current = current->adrs;
    }

    return true;
}
