#pragma once
#include "staff.h"

class DoublyLinkedList {
private:
    struct Node {
        Staff* data;
        Node* adrs;
        Node* prev;
        Node(Staff* s) : data(s), adrs(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void addToTail(Staff* s);
    void removeByName(const std::string& name);
    void display() const;
    void bubbleSortByID();
    void bubbleSortByName();
    vector<Staff*> getList();

    Staff* findByName(const std::string& name);
    Staff* findByID(int id);

    bool nameExists(const std::string& name);
    bool idExists(int id);

    //helper function
    Node* getMiddle(Node* start, Node* end);
};
