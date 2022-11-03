//
// Created by bradl on 11/1/2022.
//
#include <iostream>
#include <vector>
#ifndef LISTOFLISTSCPP_MENU_H
#define LISTOFLISTSCPP_MENU_H

using namespace std;

class Menu {
protected:
    vector<string> menu;

public:
    Menu(vector<string>);
    void DisplayMenu();
};


#endif //LISTOFLISTSCPP_MENU_H
