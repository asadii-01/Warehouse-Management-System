#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

class Record {

private:
    vector<string> activities;

    vector<string> attendance;

    // Method to get the current time as a string
    string getCurrentTime();

public:
    // Method to log an activity
    void logActivity(string activity);

    // Method to log attendence of staff
    void logAttendance(string attendance);

    // Method to save the log to a file
    void saveToFile(string filename);

    // Method to clear the log
    void clearActivityLog();
    void clearAttendanceLog();

    // Method to load previous log entries from a file
    void loadFromFile(string filename);

    // Method to display the log
    void displayActivityLog();

    // Method to display the attendance
    void displayAttendanceLog();
};