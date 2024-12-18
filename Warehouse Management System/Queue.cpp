#include "Queue.h"

void Queue::enqueue(Order* o)
{

    if (front == -1)
    {
        front = 0;
        rear = 0;
        list.push_back(o);
    }
    else
    {
        rear++;
        list.push_back(o);
    }
}

void Queue::dequeue()
{
    if (front == -1 || list.empty())
    {
        cout << "Queue is empty\n";
        return;
    }
    else
    {
        list.erase(list.begin());
        front++;
    }
}

void Queue::dequeueByID(int id, bool& idFound)
{
    if (front == -1 || list.empty())
    {
        cout << "Queue is empty\n";
        return;
    }

    for (int i = 0; i <= list.size(); i++) {
        if (list[i]->getOrderId() == id) {
            list.erase(list.begin()+i);
            idFound = true;
            break;
        }
    }

    if (idFound) {
        if (list.empty())
        {
            front = -1;
            rear = -1;
        }
        else
        {
            rear = list.size() - 1;
        }
    }
}

vector<Order*> Queue::allOrders()
{
    return list;
}

Order* Queue::findById(int id)
{
    for (const auto& o : list) {
        if (o->getOrderId() == id) {
            return o;
        }
    }

    return nullptr;
}

bool Queue::find(Order* o)
{
    for (const auto& order : list) {
        if (order == o) {
            return true;
        }
    }

    return false;
}

void Queue::priortize()
{
    for (int i = 1; i < list.size(); i++)
    {
        auto key = list[i];
        int j = i - 1;
        while (j >= 0 && key->getOrderId() < list[j]->getOrderId())
        {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}

void Queue::clear()
{
    list.clear();
}



//void Queue::displayOrders()
//{
//    for (const auto& order : list) {
//        cout << order;
//    }
//}
