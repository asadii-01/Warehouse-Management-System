#pragma once

#include "supplier.h"
#include "collection.h"

class SupplierCollection : public Supplier, public Collection {

private:
	vector<Supplier*> supplierList;

public:

	// Destructor
	~SupplierCollection() = default;

	// Getter
    vector<Supplier*> getSupplierList();

	// Add new supplier to list
    void addToList(Supplier& s);

	// Add supplier to list
	void removeFromList(string name) override;

	// Modify details of supplier 
	void modifyDetails(string name) override;

	// Merge Sort
	void merge(vector<Supplier*>& arr, int left, int mid, int right);
	void mergeSort(vector<Supplier*>& arr, int left, int right);
	void sortItems();

	// Find a staff by its name
	Supplier* findSupplierByName(string name);
	Supplier* findSupplierById(int id);

	// Check if values already exists
	bool supplierExists(Supplier& s);
	bool nameExists(string name) override;
	bool idExists(int id) override;

    // Read Data from file
    void loadFromFile(string filename) override;

    // Write data to files
    void saveToFile(string filename) override;

	// Display List of suppliers
	void displayList() override;
};

