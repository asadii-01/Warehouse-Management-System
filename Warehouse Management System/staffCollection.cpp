#include "staffCollection.h"
#include "utility.h"

vector<Staff*> StaffCollection::getStaffList() {
    return staffList;
}

void StaffCollection::addToList(Staff& s) {
    Staff* st = new Staff(s.getID(), s.getName(), s.getRole(), s.getContactInfo(), s.getPin());
    staffList.push_back(st);
}

void StaffCollection::removeFromList(string name){
    bool staffFound = false;

    for (int i = 0; i <= staffList.size(); i++) {
        if (staffList[i]->getName() == name) {
            staffList.erase(staffList.begin() + i);
            staffFound = true;
            break;
        }
    }
    if (!staffFound) {
        throw runtime_error("Staff with name " + name + " not found !!!");
    }
}

void StaffCollection::modifyDetails(string name){
    Staff* staff = findStaffByName(name);

    cout << "\n\n\t\t01. Change Name";
    cout << "\n\n\t\t02. Change Role";
    cout << "\n\n\t\t03. Change Email";
    cout << "\n\n\t\t04. Done";
    while (true) {
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-6) : \033[0m";
        int opt = getChoiceFromUser(6);

        string newInput = "";
        int newInt = 0;

        try {
            switch (opt) {

            case 1:
                while (true) {
                    cout << "\n\n\t\tEnter new name : ";
                    newInput = getStringFromUser(20);

                    if (nameExists(newInput)) {
                        cerr << "\n\t\033[31mStaff with this name already exists !!\t Try Again with different value.\033[0m";
                    }
                    else {
                        staff->setName(newInput);
                        cout << "\n\t\033[32mName updated!!\033[0m";
                        break;
                    }
                }
                break;

            case 2:
                cout << "\n\n\t\tEnter role to change to : ";
                newInput = getStringFromUser(20);

                if (stringToRole(newInput) == NONE) {
                    throw invalid_argument("Role not found!!!");
                    break;
                }
                else {
                    staff->setRole(stringToRole(newInput));
                    cout << "\n\t\033[32mRole updated!!\033[0m";
                    break;
                }

            case 3:
                cout << "\n\n\t\tEnter new email : ";
                cin >> newInput;
                if (!isValidEmail(newInput)) {
                    throw invalid_argument("Email Invlaid!!");
                }
                staff->setContactInfo(newInput);
                cout << "\n\t\033[32mEmail updated!!\033[0m";
                break;

            case 4:
                return;

            default:
                throw invalid_argument("Invalid Choice Entered!!");
                break;
            }
        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    }
}

void StaffCollection::modifyPersonalDetails(string name){
    Staff* staff = findStaffByName(name);

    cout << "\n\n\t\t01. Change Name";
    cout << "\n\n\t\t02. Change Role";
    cout << "\n\n\t\t03. Change Email";
    cout << "\n\n\t\t04. Change Pin";
    cout << "\n\n\t\t05. Done";
    while (true) {
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-5) : \033[0m";
        int opt = getChoiceFromUser(6);

        string newInput = "";
        int newInt = 0;

        try {
            switch (opt) {

            case 1:
                while (true) {
                    cout << "\n\n\t\tEnter new name : ";
                    newInput = getStringFromUser(25);

                    if (nameExists(newInput)) {
                        cerr << "\n\t\033[31mThis name already exists !!\t Try Again with different name.\033[0m";
                    }
                    else {
                        staff->setName(newInput);
                        cout << "\n\t\033[32m Name updated!!\033[0m";
                        break;
                    }
                }
                break;

            case 2:
                cout << "\n\n\t\tEnter role to change to : ";
                newInput = getStringFromUser(20);

                if (stringToRole(newInput) == NONE) {
                    throw invalid_argument("Role not found!!!");
                    break;
                }
                else {
                    staff->setRole(stringToRole(newInput));
                    cout << "\n\t\033[32mRole updated!!\033[0m";
                    break;
                }

            case 3:
                cout << "\n\n\t\tEnter new email : ";
                cin >> newInput;
                if (mailExists(newInput)) {
                    cerr << "\n\t\033[31mThis mail already exists !!\t Try Again with different mail.\033[0m";
                }
                else {
                    staff->setContactInfo(newInput);
                    cout << "\n\t\033[32mEmail updated!!\033[0m";
                    break;
                }
                
            case 4:
                cout << "\n\n\t\tEnter new pin : ";
                newInt = getNumberFromUser(4);
                staff->setPin(newInt);
                cout << "\n\t\033[32mPin updated!!\033[0m";
                break;

            case 5:
                system("cls");
                return;

            default:
                throw invalid_argument("Invalid Choice Entered!!");
                break;
            }
        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    }
}

void StaffCollection::personalProfile(Staff* user) {
    int ch = 0;
    bool back = false;
    LoadingScreen("Loading");
    while (!back) {
        cout << "\n\n\n\t\t\t\t\t    \033[32m:: PERSONAL PROFILE  ::\033[0m\n\t\t\t\t\t    ";
        DrawGreenLine(22, '-');
        cout << "\n\n";


        cout << "\n\t\t\t\033[32mStaff Id:\033[0m\t" << user->getID();
        cout << "\n\t\t\t\033[32mName:\033[0m\t\t" << user->getName();
        cout << "\n\t\t\t\033[32mRole:\033[0m\t\t" << user->roleToString(user->getRole());
        cout << "\n\t\t\t\033[32mE-mail:\033[0m\t\t" << user->getContactInfo();
        cout << "\n\t\t\t\033[32mPin:\033[0m\t\t" << user->getPin() << endl;

        cout << "\n\n\t\t01. UPDATE PROFILE";
        cout << "\n\n\t\t02. BACK";
        cout << "\n\n\t\t\033[33mChoose what you want to do (1-2) : \033[0m";

        ch = getChoiceFromUser(2);

        try {
            switch (ch) {
            case 1:
                modifyPersonalDetails(user->getName());
                break;
            case 2:
                back = true;
                break;
            default:
                throw runtime_error("Invalid Choice !!");
                break;
            }
        }
        catch (exception& e) {
            cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
            Pause();
        }
    }
}

Staff* StaffCollection::findStaffByName(string name){
    try {
        if (!nameExists(name)) {
            throw runtime_error("Staff with name " + name + " not found !!!");
        }
        else {
            for (auto& s : staffList) {
                if (s->getName() == name) {
                    return s;
                }
            }
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
    return NULL;
}

Staff* StaffCollection::findStaffById(int id){
    try {
        if (!idExists(id)) {
            throw runtime_error("Staff with name " + to_string(id) + " not found !!!");
        }
        else {
            for (auto& s : staffList) {
                if (s->getID() == id) {
                    return s;
                }
            }
        }
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
    return NULL;
}

void StaffCollection::newLogIn(Staff* s) {
    string name = "";
    cout << "\n\n\t\t\033[34m Welcome new member !!\033[0m";

    cout << "\n\n\t\tSet a pin for future login : ";
    s->setPin(getPinFromUser());
}

bool StaffCollection::staffExists(Staff& st) {
    for (auto& s : staffList) {
        if (s->getName() == st.getName()) {
            return true;
        }
        else if (s->getID() == st.getID()) {
            return true;
        }
    }
    return false;
}

bool StaffCollection::idExists(int id) {
    for (auto& s : staffList) {
        if (s->getID() == id) {
            return true;
        }
    }
    return false;
}

bool StaffCollection::nameExists(string name){
    for (auto& s : staffList) {
        if (s->getName() == name) {
            return true;
        }
    }
    return false;
}

bool StaffCollection::mailExists(string mail){
    for (auto& s : staffList) {
        if (s->getContactInfo() == mail) {
            return true;
        }
    }
    return false;
}

void StaffCollection::loadFromFile(string filename) {
    // Makes a new file if no file is found
    ofstream file;
    file.open(filename, ios::in);
    if (!file) {
        file.open(filename);
        file << "staffId,staffName,role,email,pin\n";
    }
    file.close();
    
    try {
        ifstream reader;
        string read;
        reader.open(filename);

        if (!reader) {
            throw runtime_error("Staff List not Found!!!");
        }

        getline(reader, read); // For ignoring title line
        while (getline(reader, read)) {

            Staff* s = new Staff();
            s->Staff::setDetails(read);
            addToList(*s);
            delete s;
            s = NULL;
        }

        reader.close();
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void StaffCollection::saveToFile(string filename) {
    try {
        ofstream Writer;
        Writer.open(filename);

        if (!Writer) {
            throw runtime_error("File failed to open!!");
        }

        Writer << "staffId,staffName,role,email,pin\n";

        for (const auto& s : staffList) {
            s->Staff::WriteToFile(Writer);
            delete s;
        }
        staffList.clear();

        Writer.close();
    }
    catch (exception& e) {
        cerr << "\n\n\t\033[31mError: " << e.what() << "\033[0m" << endl;
        Pause();
    }
}

void StaffCollection::displayList() {
    cout << "\t\t\t\t\t\t\t\033[34m---STAFF LIST---\033[0m\n\t\t\t\t\t\t\t";
    DrawBlueLine(15, '-');
    cout << endl << endl << "\t";

    DrawBlueLine(130, '=');
    cout << endl;
    cout << "\n\t\t\033[32m" << setw(8) << left << "Staff Id";
    cout << "\t\t" << setw(17) << left << "Name";
    cout << "\t\t" << setw(17) << left << "Role";
    cout << "\t\t" << setw(25) << left << "E-mail\033[0m" << endl << "\t";
    DrawBlueLine(130, '=');
    cout << endl;
    
    for (auto& s : staffList) {
        cout << s << endl;
    }
}