#include "doublylinkedlist.h"
using namespace std;

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head;
    while (current) {
        Node* toDelete = current;
        current = current->adrs;
        delete toDelete->data;
        delete toDelete;
    }
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
        cout << "ID: " << current->data->getID()
            << ", Name: " << current->data->getName()
            << ", Email: " << current->data->getContactInfo() << endl;
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
    Node* current = head;
    while (current) {
        if (current->data->getID() == id) {
            return current->data;
        }
        current = current->adrs;
    }
    throw runtime_error("Staff with ID " + to_string(id) + " not found!");
}
