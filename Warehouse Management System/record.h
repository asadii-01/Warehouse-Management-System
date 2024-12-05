#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <stack>

using namespace std;

class Record {

private:
    stack<string> activities;
    stack<string> attendance;
    stack<string> supplierInteractions;

    // Method to get the current time as a string
    string getCurrentTime();

    // Helper Function to display stack
    void displayStack(stack<string>& myStack);

public:
    // Method to log an activity
    void logActivity(string activity);

    // Method to log a supplier interaction
    void logInteraction(string interaction);

    // Method to log attendence of staff
    void logAttendance(string attendance);

    // Method to save the log to a file
    void saveToFile(string filename);

    // Method to clear the log
    void clearActivityLog();
    void clearAttendanceLog();
    void clearInteractionsLog();

    // Method to load previous log entries from a file
    void loadFromFile(string filename);

    // Method to display the log
    void displayActivityLog();

    // Method to display the attendance
    void displayAttendanceLog();

    // Method to display the interactions
    void displaySupplierInteractionsLog();
};