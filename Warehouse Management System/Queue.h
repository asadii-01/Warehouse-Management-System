#pragma once

#include "order.h"

class Queue
{
private:
	vector<Order*> list;
	int front = -1, rear = -1;

public:

	void enqueue(Order* o);

	void dequeue();

	void dequeueByID(int id, bool& itemFound);

	vector<Order*> allOrders();

	Order* findById(int id);

	bool find(Order* o);

	void priortize();

	//void displayOrders();
};

