#include "doublylinkedlist.h"
#include "utility.h"

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    /*Node* current = head;
    while (current) {
        Node* toDelete = current;
        current = current->adrs;
        delete toDelete->data;
        delete toDelete;
    }*/
    head = nullptr;
    tail = nullptr;
}

void DoublyLinkedList::addToTail(Staff* s) {
    Node* newNode = new Node(s);
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->adrs = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void DoublyLinkedList::removeByName(const string& name) {
    Node* current = head;
    while (current) {
        if (current->data->getName() == name) {
            if (current->prev) current->prev->adrs = current->adrs;
            if (current->adrs) current->adrs->prev = current->prev;
            if (current == head) head = current->adrs;
            if (current == tail) tail = current->prev;
            delete current->data;
            delete current;
            return;
        }
        current = current->adrs;
    }
    throw runtime_error("Staff with name " + name + " not found!");
}

void DoublyLinkedList::display() const {
    Node* current = head;
    while (current) {
        cout << current->data << endl;
        current = current->adrs;
    }
}

void DoublyLinkedList::bubbleSortByID() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current->adrs) {
            if (current->data->getID() > current->adrs->data->getID()) {
                swap(current->data, current->adrs->data);
                swapped = true;
            }
            current = current->adrs;
        }
    } while (swapped);
}

void DoublyLinkedList::bubbleSortByName() {
    if (!head) return;

    bool swapped;
    do {
        swapped = false;
        Node* current = head;
        while (current->adrs) {
            if (current->data->getName() > current->adrs->data->getName()) {
                swap(current->data, current->adrs->data);
                swapped = true;
            }
            current = current->adrs;
        }
    } while (swapped);
}

vector<Staff*> DoublyLinkedList::getList()
{
    vector<Staff*> list;
    Node* current = head;
    while (current) {
        list.push_back(current->data);
        current = current->adrs;
    }

    return list;
}

Staff* DoublyLinkedList::findByName(const string& name) {
    Node* current = head;
    while (current) {
        if (current->data->getName() == name) {
            return current->data;
        }
        current = current->adrs;
    }
    throw runtime_error("Staff with name " + name + " not found!");
}



Staff* DoublyLinkedList::findByID(int id) {
    /*Node* current = head;
    while (current) {
        if (current->data->getID() == id) {
            return current->data;
        }
        current = current->adrs;
    }
    throw runtime_error("Staff with ID " + to_string(id) + " not found!");*/

    if (head == nullptr) return nullptr;

    Node* start = head;
    Node* end = nullptr;

    while (start != end) {
        Node* mid = getMiddle(start, end);

        if (mid == nullptr)
        {
            throw runtime_error("Staff with ID " + to_string(id) + " not found!");
        }

        if (mid->data->getID() == id) {
            return mid->data;
        }
        else if (mid->data->getID() < id) {
            start = mid->adrs;
        }
        else {
            end = mid;
        }
    }
    throw runtime_error("Staff with ID " + to_string(id) + " not found!");
}

bool DoublyLinkedList::idExists(int id)
{
    Node* current = head;
    while (current) {
        if (current->data->getID() == id) {
            return true;
        }
        current = current->adrs;
    }
    return false;
}

DoublyLinkedList::Node* DoublyLinkedList::getMiddle(Node* start, Node* end)
{
    if (start == nullptr) return nullptr;

    Node* slow = start;
    Node* fast = start;

    while (fast != end && fast->adrs != end) {
        fast = fast->adrs->adrs;
        slow = slow->adrs;
    }
    return slow;
}

bool DoublyLinkedList::nameExists(const std::string& name)
{
    Node* current = head;
    while (current) {
        if (current->data->getName() == name) {
            return true;
        }
        current = current->adrs;
    }
    return false;
}