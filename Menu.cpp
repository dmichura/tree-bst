#include "Menu.h"
#include <iostream>
#include <cstdlib>
using namespace std;


// community function to clear screen console
// https://medium.com/@ryan_forrester_/c-screen-clearing-how-to-guide-cff5bf764ccd
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void o1()
{
    cout << "opcja1\n";
}

Menu::Menu() {
    cout << "Drzewo BST\n";
    // klasa bst
    this->list.push_back( {"dodawanie", o1} );
    this->list.push_back( {"odejmowanie", o1} );
}

Menu::~Menu() {}

void Menu::run() {
    while (true)
    {
        clearScreen();
        cout << "\n==========================\n";
        for (size_t i = 0; i < this->list.size(); i++)
        {
            cout << i+1 << ". " << this->list[i].first << "\n";
        }
        cout << "==========================\n";

        int choose;
        cout << "  >> ";
        cin >> choose;
        cout << "\nWybrales: " << choose << "";

        if (choose < 1 || choose > (int) this->list.size())
        {
            cout << "Wybierz poprawną opcję!\n";
            continue;
        }
    }

}
