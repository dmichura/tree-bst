#ifndef MENU_CPP
#define MENU_CPP

#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <limits>
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

void pause() {
    cout << "\nNacisnij Enter, aby kontynuowac...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.rdbuf()->in_avail() != 0) {
        cin.get();
    } else {
        cin.get();
    }
}

Menu::Menu() {
    cout << "Drzewo BST\n";
    // klasa bst
    this->list.push_back( {"Dodaj element",     [this]() { this->handleDodaj(); }} );
    this->list.push_back( {"Usun element",      [this]() { this->handleUsun(); }} );
    this->list.push_back( {"Wyswietl drzewo",   [this]() { this->handleWyswietl(); }} );
    this->list.push_back( {"Usun cale drzewo",  [this]() { this->handleUsunWszystko(); }} );
    this->list.push_back( {"Zapisz drzewo do pliku", [this]() { this->handleZapiszDoPliku(); }} );
    this->list.push_back( {"Wczytaj drzewo z pliku", [this]() { this->handleWczytajZPliku(); }} );
}

Menu::~Menu() {}

void Menu::handleDodaj() {
    int wartosc;
    cout << "Podaj wartosc do dodania: ";
    cin >> wartosc;
    //! TODO: add data to tree
    tree.add(wartosc);
    cout << "Dodano " << wartosc << "\n";
}

void Menu::handleUsun() {
    int wartosc;
    cout << "Podaj wartosc do usuniecia: ";
    cin >> wartosc;
    tree.remove(wartosc);
}
void Menu::handleWyswietl() {
    int metoda = -1;
    while(metoda != 0) {
        clearScreen();
        cout << "==========================\n";
        cout << "  Wybierz metode wyswietlania\n";
        cout << "==========================\n";
        cout << "  1. Wyswietl Graficznie (Struktura)\n";
        cout << "  2. Pre-order  (KLP - lista)\n";
        cout << "  3. In-order   (LKP - lista posortowana)\n";
        cout << "  4. Post-order (LPK - lista)\n";
        cout << "  0. Powrot do menu glownego\n";
        cout << "==========================\n";
        cout << "  >> ";

        cin >> metoda;

        if (cin.fail()) {
            cout << "\nBlad! Wpisz poprawna liczbe\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
            continue;
        }

        cout << "\n";
        switch(metoda) {
            case 1:
                tree.displayGraphical();
                pause();
                break;
            case 2:
                tree.displayPreorder();
                pause();
                break;
            case 3:
                tree.displayInorder();
                pause();
                break;
            case 4:
                tree.displayPostorder();
                pause();
                break;
            case 0:
                break;
            default:
                cout << "Niepoprawna opcja, sprobuj ponownie\n";
                pause();
                break;
        }
    }
}
void Menu::handleUsunWszystko() {
    tree.clear();
    cout << "Drzewo zostalo wyczyszczone\n";
}
void Menu::handleZapiszDoPliku() {
    string filename;
    cout << "Podaj nazwe pliku do zapisu (np. plik.bin): ";
    cin >> filename;
    tree.saveToFile(filename);
}
void Menu::handleWczytajZPliku() {
    string filename;
    cout << "Podaj nazwe pliku do wczytania (np. plik.bin): ";
    cin >> filename;
    tree.loadFromFile(filename);
}

void Menu::run() {
    int choose = -1;

    while (true)
    {
        clearScreen();
        cout << "\n==========================\n";
        cout << "         MENU               \n";
        cout << "==========================\n";
        for (size_t i = 0; i < this->list.size(); i++)
        {
            cout << "  " << i+1 << ". " << this->list[i].first << "\n";
        }
        cout << "  0. Zamknij program\n";
        cout << "==========================\n";
        cout << "  >> ";
        
        cin >> choose;

        if (cin.fail()) {
            cout << "\nBlad! Wpisz poprawna liczbe\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choose == 0) {
            break;
        }

        if (choose < 1 || choose > (int) this->list.size())
        {
            cout << "Wybierz poprawną opcję!\n";
            continue;
        }

        this->list[choose-1].second();
        if(this->list[choose-1].first != "Wyswietl drzewo") pause();
    }

}

#endif
