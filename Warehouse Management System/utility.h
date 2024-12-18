#pragma once

#include "warehouse.h"
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <cctype>
#include <algorithm>
#include <string>
#include <regex>

// Input functions
static int getNumberFromUser(int len) {
    string numStr = "";
    char ch;

    for (int i = 0; i < len; ) {
        ch = _getch();
        if (ch >= '0' && ch <= '9') {
            cout << ch;
            numStr += ch;
            i++;
        }
        else if (ch == '\r') {
            cout << endl;
            break;
        }
        else if (ch == '\b') {
            if (i > 0) {
                cout << "\b \b";
                numStr.pop_back();
                i--;
            }
        }
        else {
            cout << "\a";
        }
    }

    return stoi(numStr);
}
static float getfloatFromUser(int len) {
    string numStr = "";
    char ch;
    bool decimalPointEncountered = false;

    for (int i = 0; i < len; ) {
        ch = _getch();
        if (ch >= '0' && ch <= '9') {
            cout << ch;
            numStr += ch;
            i++;
        }
        else if (ch == '\r') {
            cout << endl;
            break;
        }
        else if (ch == '\b') {
            if (i > 0) {
                cout << "\b \b";
                if (numStr.back() == '.') {
                    decimalPointEncountered = false;
                }
                numStr.pop_back();
                i--;
            }
        }
        else if (ch == '.') {
            if (!decimalPointEncountered) {
                cout << ch;
                numStr += ch;
                decimalPointEncountered = true;
                i++;
            }
            else {
                cout << "\a";
            }
        }
        else {
            cout << "\a";
        }
    }

    return stof(numStr);
}
static int getPinFromUser() {
    string numStr = "";
    char ch;

    for (int i = 0; i < 4; ) {
        ch = _getch();
        if (ch >= '0' && ch <= '9') {
            cout << '*';
            numStr += ch;
            i++;
        }
        else if (ch == '\r') {
            cout << endl;
            break;
        }
        else if (ch == '\b') {
            if (i > 0) {
                cout << "\b \b";
                numStr.pop_back();
                i--;
            }
        }
        else {
            cout << "\a";
        }
    }

    return stoi(numStr);
}
static int getChoiceFromUser(int len) {
    char ch;
 
    while (true) {
        ch = _getch();
        if (ch >= '1' && ch <= (char)(len + '0')) {
            cout << ch;
            break;
        }
        else {
            cout << "\a";
        }
    }
 
    return (ch - '0');
}
static string getStringFromUser(int len) {
    string str;
    char ch;

    for (int i = 0; i < len; i++) {
        ch = _getch();

        if (isalnum(ch) || ch == ' ') {
            str.push_back(toupper(ch));
            cout << ch;
        }
        else if (ch == '\b') {
            if (!str.empty()) {
                str.pop_back();
                cout << "\b \b";
                i -= 2;
            }
        }
        else if (ch == '\r' || ch == '\n') {
            if (!str.empty()) {
                cout << endl;
                break;
            }
            else {
                cout << "\a";
            }
        }
        else {
            cout << "\a";
        }
    }

    return str;
}

// Functions to check Validation
static bool isValidEmail(const string& email) {
    const regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    return regex_match(email, pattern);
}
static bool isValidName(const string& name) {
    if (std::all_of(name.begin(), name.end(), ::isdigit)) {
        return false;
    }
    return true;
}

// Function to create a pop-up notification
static bool ShowNotification(const wchar_t* title, const wchar_t* message) {
    int response = MessageBox(
        NULL,           // No owner window
        message,        // Message to display
        title,          // Title of the notification
        MB_YESNO | MB_ICONWARNING// Buttons and icon style
    );

    if (response == IDYES) {
        return true;
    }
    else if (response == IDNO) {
        return false;
    }
}

// Functions to draw lines
static void DrawGreenLine(int n,unsigned char ch)
{
    for (int i = 0; i < n; i++)
        cout << "\033[32m" << ch << "\033[0m";
}
static void DrawRedLine(int n,unsigned char ch)
{
    for (int i = 0; i < n; i++)
        cout << "\033[31m" << ch << "\033[0m";
}
static void DrawBlueLine(int n,unsigned char ch)
{
    for (int i = 0; i < n; i++)
        cout << "\033[34m" << ch << "\033[0m";
}

// Loading screen animation
static void LoadingScreen(string title) {
    system("cls");
    int c = 219;
    cout << "\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\t   "+title+"...\n\n\t\t\t\t";
    for (int i = 1; i <= 50; i++) {
        cout << char(c);
        Sleep(10);
    }
    system("cls");
    cout << "\033[0m";
}

// Function to pause screen and continue on any button
static void Pause() {
    cout << "\n\n\n\033[33m";
    system("pause");
    cout << "\033[0m";
}

// Introduction Page
static void Intro() {
    cout << "\t\t\t    ";
    DrawBlueLine(1, 201);
    DrawBlueLine(53, 205);
    DrawBlueLine(1, 187);
    cout << "\n\t\t\t    \033[34m" << char(186)<< string(53, ' ') << char(186) << "\n\t\t\t    "<<char(186) << string(53, ' ') << char(186)<<"\033[0m";
    cout << "\n\t\t\t    \033[34m"<<char(186)<<"\033[33m" << string(19, ' ') << setw(12) << internal << "WAREHOUSE " << string(22, ' ') << "\033[34m" << char(186) << "\033[0m";
    cout << "\n\t\t\t    \033[34m" << char(186) << string(53, ' ') << char(186) << "\033[0m";
    cout << "\n\t\t\t    \033[34m" << char(186) << "\033[33m" << string(18, ' ') << setw(12) << internal << "MANAGEMENT" << string(23, ' ') << "\033[34m" << char(186) << "\033[0m";
    cout << "\n\t\t\t    \033[34m" << char(186) << string(53, ' ') << char(186) << "\033[0m";
    cout << "\n\t\t\t    \033[34m" << char(186) << "\033[33m" << string(16, ' ') << setw(12) << internal << "SYSTEM" << string(25, ' ') << "\033[34m" << char(186) << "\033[0m";
    cout << "\n\t\t\t    \033[34m"<<char(186) << string(53, ' ') << char(186) << "\n\t\t\t    "<< char(186) << string(53, ' ') << char(186) << "\n\t\t\t    "<<char(186) << string(53, ' ') << char(186)<<"\033[0m";
    cout << "\n\t\t\t    \033[34m" << char(186) << "\033[0m" << string(9, ' ') << "MADE BY : Asad Tauqeer & Asim Raza" << string(10, ' ') << "\033[34m" << char(186) << "\033[0m";
    cout << "\n\t\t\t    \033[34m" << char(186) << string(53, ' ') << char(186) << "\033[0m";
    cout << "\n\t\t\t    \033[34m" << char(186) << "\033[0m" << string(8, ' ') << "ROLL NO. : 23021519-160 & 23021519-135" << string(7, ' ') << "\033[34m" << char(186) << "\033[0m";
    cout << "\n\t\t\t    \033[34m" << char(186) << string(53, ' ') << char(186) << "\n\t\t\t    " << char(186) << string(53, ' ') << char(186) << "\033[0m";
    cout << "\n\t\t\t    ";
    DrawBlueLine(1, 200);
    DrawBlueLine(53, 205);
    DrawBlueLine(1, 188);
    Pause();
}

// Exit page
static void Exit() {
    system("cls");

    cout << "\t\t\t    ";
    DrawRedLine(1, 201);
    DrawRedLine(60, 205);
    DrawRedLine(1, 187);
    cout << "\n\t\t\t    \033[31m"<<char(186) << string(60, ' ') << char(186) << "\n\t\t\t    "<< char(186) << string(60, ' ') << char(186) <<"\033[0m";
    cout << "\n\t\t\t    \033[31m"<<char(186)<<"\033[0m" << string(5, ' ') << "Thanks for using the Warehouse Managment System." << string(6, ' ') << "\033[31m "<<char(186)<<" \033[0m";
    cout << "\n\t\t\t    \033[31m"<< char(186) << string(60, ' ') << char(186) <<"\033[0m";
    cout << "\n\t\t\t    \033[31m"<<char(186)<<"\033[0m" << string(11, ' ') << "You have exited the program safetly" << string(13, ' ') << "\033[31m "<<char(186)<<" \033[0m";
    cout << "\n\t\t\t    \033[31m"<< char(186) << string(60, ' ') << char(186) <<"\033[0m" << "\n\t\t\t    \033[31m"<< char(186) << string(60, ' ') << char(186) <<"\033[0m";
    cout << "\n\t\t\t    ";
    DrawRedLine(1, 200);
    DrawRedLine(60, 205);
    DrawRedLine(1, 188);
    cout << endl;
}

// Main Menu 
static void showMainMenu() {
    system("cls");
    cout << "\n\n\n\t\t\t\t\t    \033[32m:: MAIN MENU ::\033[0m\n\t\t\t\t\t    ";
    DrawGreenLine(15, '-');
    cout << "\n\n\t\t01. INVENTORY MANAGMENT";
    cout << "\n\n\t\t02. ORDER MANAGMENT";
    cout << "\n\n\t\t03. STAFF MANAGMENT";
    cout << "\n\n\t\t04. SUPPLY MANAGMENT";
    cout << "\n\n\t\t05. EXIT";
    cout << "\n\n\t\t\033[33mChoose what you want to do (1-5) : \033[0m";
}


// Iostream operator overloading
static istream& operator>>(istream& cin, StockItem* s) {

    cout << "\n\n\t\tEnter Stock ID: ";
    s->stockId = getNumberFromUser(4);

    if (s->stockId == 0) {
        throw invalid_argument("Item with id number 0 cannot be made !!\t Try Again with different values.");
    }

    cout << "\n\n\t\tEnter Name of Item: ";
    s->name = getStringFromUser(20);

    if (!isValidName(s->name)) {
        throw invalid_argument("Item with such name cannot be made !!\t Try Again with different values.");
    }

    cout << "\n\n\t\tEnter Price: ";
    s->price = getfloatFromUser(6);

    if (s->price == 0) {
        throw invalid_argument("Item with price 0 Rs cannot be made !!\t Try Again with different values.");
    }

    cout << "\n\n\t\tEnter Quantity: ";
    s->quantity = getNumberFromUser(5);

    if (s->quantity == 0) {
        throw invalid_argument("Item with quantity 0 cannot be made !!\t Try Again with different values.");
    }

    cout << "\n\n\t\tCategories are : ELECTRONICS, COMPUTER, AUTOMOTIVE, SPORTS, CLOTHING, FURNITURE";
    int count = 0;
    while (count != 3) {
        cout << "\n\n\t\tEnter Category: ";
        s->category = s->stringToCategory(getStringFromUser(20));

        if (s->category == NON) {
            cout << "\n\t\tInvalid Category!! Try Again\n\t\tYou have " << 3-count << " tries left.";
        }
        else {
            break;
        }
        
        count++;
    }

    if (s->category == NON) {
        throw invalid_argument("You entered incorrect category!!");
    }

    return cin;
}
static ostream& operator<<(ostream& cout, StockItem* s) {
    cout << "\t\t" << setw(8) << left << s->stockId;
    cout << "\t\t" << setw(20) << left << s->name;
    cout << "\t\t" << setw(8) << left << s->price;
    cout << "\t\t" << setw(20) << left << s->categoryToString(s->category);
    cout << "\t\t" << setw(8) << left << s->quantity << endl;

    return cout;
}

static ostream& operator<<(ostream& cout, Staff* s) {
    cout << "\t\t" << setw(8) << left << s->ID;
    cout << "\t\t" << setw(17) << left << s->name;
    cout << "\t\t" << setw(17) << left << s->roleToString(s->role);
    cout << "\t\t" << setw(25) << left << s->contactInfo;

    return cout;
}
static istream& operator>>(istream& cin, Staff* s) {

    cout << "\n\n\t\tEnter Staff ID : ";
    s->ID = getNumberFromUser(4);

    if (s->ID == 0) {
        throw invalid_argument("Staff id cannot be zero !!\t Try Again with different values.");
    }

    cout << "\n\n\t\tEnter Name : ";
    s->name = getStringFromUser(20);

    if (!isValidName(s->name)) {
        throw invalid_argument("staff with such name cannot be made !!\t Try Again with different values.");
    }

    cout << "\n\n\t\tEnter Email: ";
    cin >> s->contactInfo;
    
    if (!isValidEmail(s->contactInfo)) {
        throw invalid_argument("Invalid Email!!");
    }
    
    cout << "\n\n\t\tRoles are: MANAGER, INVENTORY_CLERK, SHIPPING_CLERK, STAFF_SUPERVISOR, OPERATOR, SECURITY_GAURD";
    cout << "\n\t\tEnter Role: ";
    s->role = s->stringToRole(getStringFromUser(20));
    s->pin = 0;

    return cin;
}

static istream& operator>>(istream& cin, Order* o) {

    cout << "\n\n\t\tEnter Order ID: ";
    o->orderId = getNumberFromUser(4);

    //o->addItems();

    return cin;
}
static ostream& operator<<(ostream& cout, Order* o) {
    bool first = true;
    cout << "\t\t" << setw(9) << left << o->orderId;
    for (const auto& item : o->items) {
        if (first) {
            cout << "\t\t" << setw(25) << left << item.first << setw(5) << left << item.second << endl;
            first = false;
        }
        else {
            cout << "\t\t\t\t\t" << setw(25) << left << item.first << setw(5) << left << item.second << endl;
        }
    }
    cout << endl;

    return cout;
}

static ostream& operator<<(ostream& cout, Supplier* s) {
    bool first = true;
    cout << "\t\t" << setw(8) << left << s->ID;
    cout << "\t\t" << setw(17) << left << s->name;
    cout << "\t\t" << setw(20) << left << s->contactInfo;
    for (auto& i : s->itemsSupplied) {
        if (first) {
            cout << "\t\t" << setw(15) << left << i << endl;
            first = false;
        }
        else {
            cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t" << setw(20) << left << i << endl;
        }
    }
    cout << endl;
    return cout;
}
static istream& operator>>(istream& cin, Supplier* s) {

    cout << "\n\n\t\tEnter Supplier ID : ";
    s->ID = getNumberFromUser(4);

    if (s->ID == 0) {
        throw invalid_argument("Invalid id!!");
    }
    cout << "\n\n\t\tEnter Name : ";
    s->name = getStringFromUser(20);

    if (!isValidName(s->name)) {
        throw invalid_argument("Invalid name!!");
    }
    cout << "\n\n\t\tEnter Email: ";
    cin >> s->contactInfo;

    if (!isValidEmail(s->contactInfo)) {
        throw invalid_argument("Invalid Email!!");
    }

    /*string input;
    do
    {
        cout << "\n\n\t\tEnter Name of the item : ";
        input = getStringFromUser(20);

        if (!isValidName(input)) {
            throw invalid_argument("Invalid item name!!");
        }

        s->addItem(input);

        cout << "\n\n\t\t\033[33mWant to add another item to the order? <Y/N> : \033[0m ";
        input = getStringFromUser(1);

        if (input == "N") {
            break;
        }
        else if (input == "Y") {
            continue;
        }
        else {
            cerr << "\033[31mInvalid choice !! choose between Y or N\033[0m";
        }

    } while (true);*/

    return cin;
}