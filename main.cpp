#include "json.hpp"
#include <fstream>
#include <unordered_map>
#include "Menu.h"

using namespace nlohmann;

//unordered_map< string, vector<string>> listOfLists;?
string getFilename();
void getListFromFile(const string& filename);
string getCurrentOption();
bool runMainMenu(const string& option);
void saveListToFile(const string& filename);
void deleteList();
void viewList();
bool runViewMenu(const string& name, const string& option);
void removeItem(const string& name);
void displayListOfLists();
void addList();
void displayCurrentList(const string& name);
bool runAddMenu(const string& name, const string& option);
void addItem(const string& name);

json listOfLists;
Menu mainMenu = *new Menu(vector<string>(
        {"\n", "Main Menu", "--------------", "1. Add List", "2. View List", "3. Delete List", "4. Quit/Save"}));
Menu addMenu = *new Menu(vector<string>({"\n", "Add List Menu", "--------------", "1. Add Item", "2. Quit"}));
Menu viewMenu = *new Menu(
        vector<string>({"\n", "List Options", "--------------", "1. Add Item", "2. Remove Item", "3. Quit"}));

int main() {
    bool done = false;
    getListFromFile(getFilename());
//    cout << listOfLists << endl;
    while (!done) {
        mainMenu.DisplayMenu();
        string option = getCurrentOption();
        done = runMainMenu(option);
    }
    saveListToFile(getFilename());
    return 0;
}

void saveListToFile(const string& filename) {
    try {
        ofstream file(filename, ios_base::out);
        file << setw(4) << listOfLists << endl;
        file.close();
    }
    catch (...) {
        cout << "Error occurred in uploading lists to file: " << filename << ".";
    }
}

string getFilename() {
    string filename;
    cout << "What file do you want to open from/save to?" << endl;
    cin >> filename;
    return filename;
}

void getListFromFile(const string& filename) {
    try {
        ifstream file(filename);
        listOfLists = json::parse(file);
        file.close();
    }
    catch (...) {
        cout << "File doesn't exist working from blank." << endl;
    }
}

string getCurrentOption() {
    string option;
    cout << "\nWhat is your choice? " << endl;
    getline(cin, option);
    return option;
}

bool runMainMenu(const string& option) {
    if (option == "1") {
        addList();
    } else if (option == "2") {
        viewList();
    } else if (option == "3") {
        deleteList();
    } else if (option == "4") {
        return true;
    }
    return false;
}

void deleteList() {
    displayListOfLists();
    string option;
    cout << "Which list should be deleted?" << endl;
    cin >> option;
    cout << "Are you sure you want to delete the list? (y/n) ";
    string check;
    cin >> check;
    if (check == "y") {
        listOfLists.erase(option);
    }
}

void displayListOfLists() {
    cout << "\nList of Lists:" << endl;
    int count = 1;
    for (auto &it: listOfLists.items()) {
        cout << count << ". " << it.key() << endl;
        count++;
    }
}

void viewList() {
    displayListOfLists();
    int quitSpot = listOfLists.size() + 1;
    cout << quitSpot << ". quit" << endl;
    bool validOption = false;
    string name = getCurrentOption();
    bool firstRun = true;
    while (!validOption) {
        if (!firstRun) {
            name = getCurrentOption();
        }
        if (listOfLists.contains(name)) {
            displayCurrentList(name);
            validOption = true;
        } else if (name == "quit") {
            return;
        } else {
            cout << "\nInvalid Option.\n";
        }
        firstRun = false;
    }
    firstRun = true;
    bool done = false;
    while (!done) {
        if (!firstRun) {
            displayCurrentList(name);
        } else {
            firstRun = false;
        }
        viewMenu.DisplayMenu();
        string option = getCurrentOption();
        done = runViewMenu(name, option);
    }
}

bool runViewMenu(const string& name, const string& option) {
    if (option == "1") {
        addItem(name);
    } else if (option == "2") {
        removeItem(name);
    } else {
        return true;
    }
    return false;
}

void removeItem(const string& name) {
    cout << "What item should be removed?";
    string item = getCurrentOption();
    for (auto i = 0; i < listOfLists[name].size(); i++) {
        if (listOfLists[name][i] == item) {
            listOfLists[name].erase(i);
        }
    }
}

void addList() {
    cout << "\nWhat is the list name?" << endl;
    string name;
    getline(cin, name);
    if (listOfLists.contains(name)) {
        cout << "List already exists.";
        return;
    }
    listOfLists[name] = {};
    bool done = false;
    while (!done) {
        displayCurrentList(name);
        addMenu.DisplayMenu();
        string option = getCurrentOption();
        done = runAddMenu(name, option);
    }
}

void displayCurrentList(const string& name) {
    cout << "\nCurrent contents of " << name << ":" << endl;
    int count = 1;
    for (string item: listOfLists.at(name)) {
        cout << count << ". " << item << endl;
        count++;
    }
}

bool runAddMenu(const string& name, const string& option) {
    if (option == "1") {
        addItem(name);
    } else if (option == "2") {
        return true;
    }
    return false;
}

void addItem(const string& name) {
    cout << "What would you like to add to " << name << "?" << endl;
    string item = getCurrentOption();
    listOfLists[name].emplace_back(item);
}