#include "record.h"
#include "utility.h"

string Record::getCurrentTime() {
    time_t now = time(nullptr);
    struct tm timeInfo;

    localtime_s(&timeInfo, &now);

    char timeInStr[80];
    strftime(timeInStr, sizeof(timeInStr), "%Y-%m-%d %H:%M:%S", &timeInfo);
    return timeInStr;
}

void Record::logActivity(string activity) {
    string timestampedActivity = getCurrentTime() + "\t\t\t" + activity;
    activities.push(timestampedActivity);
}

void Record::logInteraction(string interaction)
{
    string timestampedActivity = getCurrentTime() + "\t\t\t" + interaction;
    supplierInteractions.push(timestampedActivity);
}

void Record::logAttendance(string at){
    string timestampedAttendence = getCurrentTime() + "\t\t\t" + at;
    attendance.push(timestampedAttendence);
}

void Record::saveToFile(string filename) {
    ofstream Writer;
    Writer.open(filename);
    try {
        if (!Writer) {
            throw runtime_error("File failed to open!!");
        }

        Writer <<  "Time Recorded   \t\t\tActivity\n";

        stack<string> temp = activities;

        while (!temp.empty()) {
            Writer << temp.top() << endl;
            temp.pop();
        }
        
        Writer << "attendance\n";

        temp = attendance;
        while (!temp.empty()) {
            Writer << temp.top() << endl;
            temp.pop();
        }

        Writer << "interactions\n";

        temp = supplierInteractions;
        while (!temp.empty()) {
            Writer << temp.top() << endl;
            temp.pop();
        }

    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
    Writer.close();
}

void Record::clearActivityLog() {
    while (!activities.empty()) {
        activities.pop();
    }
}

void Record::clearAttendanceLog(){
    while (!attendance.empty()) {
        attendance.pop();
    }
}

void Record::clearInteractionsLog()
{
    while (!supplierInteractions.empty()) {
        supplierInteractions.pop();
    }
}

void Record::loadFromFile(string filename) {
    // Makes a new file if no file is found
    ofstream file;
    file.open(filename, ios::in);
    if (!file) {
        file.open(filename);
        file << "Time Recorded   \t\t\tActivity\n";
    }
    file.close();


    try {
        ifstream reader;
        string read;
        reader.open(filename);

        if (!reader) {
            throw runtime_error("Record not Found!!!");
        }

        getline(reader, read); //for ignoring title line
        while (getline(reader, read)) {
            if (read == "attendance") {
                break;
            }
            else {
                activities.push(read);
            }
        }

        while (getline(reader, read)) {
            if (read == "interactions") {
                break;
            }
            else {
                attendance.push(read);
            }
        }

        while (getline(reader, read)) {
            supplierInteractions.push(read);
        }

        reader.close();
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void Record::displayActivityLog() {
    string input;
    system("cls");
    cout << "\t\t\t\t\t\t\t\033[34m---REPORT---\033[0m\n\t\t\t\t\t\t\t";
    DrawBlueLine(12, '-');
    cout << endl << endl << "\t";

    DrawBlueLine(120, '=');
    cout << endl;
    cout << "\n\t\t\033[34m     Time Recorded   \t\t\t\t\tActivity\033[0m\n\t";
    DrawBlueLine(120, '=');
    cout << endl;

    if (activities.size() == 0) {
        cout << "\n\n\t\t\033[31mNo Record found.\033[0m";
        Pause();
    }
    else {

        displayStack(activities);

        while (true) {
            cout << "\n\n\t\t\033[33mWant to clear record? <Y/N> : \033[0m ";
            input = getStringFromUser(1);

            if (input == "N") {
                break;
            }
            else if (input == "Y") {
                clearActivityLog();
                cout << "\n\n\t\tRecord cleared.";
                Pause();
                break;
            }
            else {
                cerr << "\033[31mInvalid choice !! choose between Y or N\033[0m";

            }
        }
    }
}

void Record::displayAttendanceLog() {
    string input;
    system("cls");
    cout << "\t\t\t\t\t\t\t\033[34m---REPORT---\033[0m\n\t\t\t\t\t\t\t";
    DrawBlueLine(12, '-');
    cout << endl << endl << "\t";

    DrawBlueLine(100, '=');
    cout << endl;
    cout << "\n\t\t\033[34m     Time Recorded   \t\t\t\t\tAttendance\033[0m\n\t";
    DrawBlueLine(100, '=');
    cout << endl;
    if (attendance.size() == 0) {
        cout << "\n\n\t\t\033[31mNo Record found.\033[0m";
        Pause();
    }
    else {

        displayStack(attendance);

        while (true) {
            cout << "\n\n\t\t\033[33mWant to clear record? <Y/N> : \033[0m ";
            input = getStringFromUser(1);

            if (input == "N") {
                break;
            }
            else if (input == "Y") {
                clearAttendanceLog();
                cout << "\n\n\t\tRecord cleared.";
                Pause();
                break;
            }
            else {
                cerr << "\033[31mInvalid choice !! choose between Y or N\033[0m";

            }
        }
    }
}

void Record::displaySupplierInteractionsLog()
{
    string input;
    system("cls");
    cout << "\t\t\t\t\t\t\t\033[34m---REPORT---\033[0m\n\t\t\t\t\t\t\t";
    DrawBlueLine(12, '-');
    cout << endl << endl << "\t";

    DrawBlueLine(100, '=');
    cout << endl;
    cout << "\n\t\t\033[34m     Time Recorded   \t\t\t\t\tInteraction\033[0m\n\t";
    DrawBlueLine(100, '=');
    cout << endl;
    if (supplierInteractions.empty()) {
        cout << "\n\n\t\t\033[31mNo Record found.\033[0m";
        Pause();
    }
    else {
        displayStack(supplierInteractions);

        while (true) {
            cout << "\n\n\t\t\033[33mWant to clear record? <Y/N> : \033[0m ";
            input = getStringFromUser(1);

            if (input == "N") {
                break;
            }
            else if (input == "Y") {
                clearInteractionsLog();
                cout << "\n\n\t\tRecord cleared.";
                Pause();
                break;
            }
            else {
                cerr << "\033[31mInvalid choice !! choose between Y or N\033[0m";

            }
        }
    }
}

void Record::displayStack(stack<string>& myStack)
{
    stack<string> temp = myStack;

    while (!temp.empty()) {
        cout << "\n\n\t\t" << temp.top() << endl;
        temp.pop();
    }
}
