//
// Created by bradl on 11/1/2022.
//

#include "Menu.h"

Menu::Menu(vector<string> newMenu)
{
   menu = newMenu;
}

void Menu::DisplayMenu()
{
   for (const auto &item: menu)
      cout << item << endl;
}
