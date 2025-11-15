#ifndef MENU_CPP
#define MENU_CPP

#include "Menu.h"
#include <iostream>
#include <cstdlib>
#include <limits>
using namespace std;


/**
 * @brief Funkcja pomocnicza do czyszczenia ekranu konsoli.
 * * Uzywa "cls" dla systemow Windows i "clear" dla systemow uniksowych (Linux/macOS).
 * @see https://medium.com/@ryan_forrester_/c-screen-clearing-how-to-guide-cff5bf764ccd
 */
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Wstrzymuje wykonanie programu do momentu nacisniecia klawisza Enter.
 * * Czyści bufor wejsciowy, aby zapewnic, ze oczekuje na swieze nacisniecie klawisza Enter.
 */
void pause() {
    cout << "\nNacisnij Enter, aby kontynuowac...";
    // Czyści bufor wejsciowy przed oczekiwaniem na Enter
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (cin.rdbuf()->in_avail() != 0) {
        // Dodatkowe cin.get() na wypadek, gdyby Enter zostal juz wcisniety
        cin.get();
    } else {
        cin.get();
    }
}

/**
 * @brief Konstruktor klasy Menu.
 * * Inicjuje menu glowne, dodajac opcje zwiazane z operacjami na Drzewie BST.
 */
Menu::Menu() {
    cout << "Drzewo BST\n";
    // Uzywa this->list.push_back dla czytelnosci i unikniecia bledow
    this->list.push_back( {"Dodaj element",     [this]() { this->handleDodaj(); }} );
    this->list.push_back( {"Usun element",      [this]() { this->handleUsun(); }} );
    this->list.push_back( {"Wyswietl drzewo",   [this]() { this->handleWyswietl(); }} );
    this->list.push_back( {"Usun cale drzewo",  [this]() { this->handleUsunWszystko(); }} );
    this->list.push_back( {"Zapisz drzewo do pliku", [this]() { this->handleZapiszDoPliku(); }} );
    this->list.push_back( {"Wczytaj drzewo z pliku", [this]() { this->handleWczytajZPliku(); }} );
}

/**
 * @brief Destruktor klasy Menu.
 * * Obecnie pusty, ale moze byc uzyty do zwolnienia zasobow w przyszlosci.
 */
Menu::~Menu() {}

/**
 * @brief Obsluguje opcje dodawania elementu do drzewa BST.
 * * Prosi uzytkownika o podanie wartosci i dodaje ja do wewnetrznego obiektu `tree`.
 */
void Menu::handleDodaj() {
    int wartosc;
    cout << "Podaj wartosc do dodania: ";
    cin >> wartosc;
    //! TODO: add data to tree
    tree.add(wartosc);
    cout << "Dodano " << wartosc << "\n";
}

/**
 * @brief Obsluguje opcje usuwania elementu z drzewa BST.
 * * Prosi uzytkownika o podanie wartosci i usuwa ja z wewnetrznego obiektu `tree`.
 */
void Menu::handleUsun() {
    int wartosc;
    cout << "Podaj wartosc do usuniecia: ";
    cin >> wartosc;
    tree.remove(wartosc);
}

/**
 * @brief Obsluguje opcje wyswietlania drzewa BST.
 * * Wyswietla podmenu, pozwalajac uzytkownikowi wybrac jedna z czterech metod wyswietlania:
 * graficzne, pre-order, in-order lub post-order.
 */
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

/**
 * @brief Obsluguje opcje usuwania calego drzewa BST.
 * * Wywoluje metode `clear()` na wewnetrznym obiekcie `tree`.
 */
void Menu::handleUsunWszystko() {
    tree.clear();
    cout << "Drzewo zostalo wyczyszczone\n";
}

/**
 * @brief Obsluguje opcje zapisywania drzewa BST do pliku.
 * * Prosi uzytkownika o podanie nazwy pliku i wywoluje `saveToFile()` na obiekcie `tree`.
 */
void Menu::handleZapiszDoPliku() {
    string filename;
    cout << "Podaj nazwe pliku do zapisu (np. plik.bin): ";
    cin >> filename;
    tree.saveToFile(filename);
}

/**
 * @brief Obsluguje opcje wczytywania drzewa BST z pliku.
 * * Prosi uzytkownika o podanie nazwy pliku i wywoluje `loadFromFile()` na obiekcie `tree`.
 */
void Menu::handleWczytajZPliku() {
    string filename;
    cout << "Podaj nazwe pliku do wczytania (np. plik.bin): ";
    cin >> filename;
    tree.loadFromFile(filename);
}

/**
 * @brief Glowna petla programu.
 * * Wyswietla menu glowne, obsluguje wybor uzytkownika i wywoluje odpowiednie funkcje obslugi.
 * Kontynuuje dzialanie, dopoki uzytkownik nie wybierze opcji zamkniecia programu (0).
 */
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
            break; // Zamknij program
        }

        if (choose < 1 || choose > (int) this->list.size())
        {
            cout << "Wybierz poprawna opcje!\n";
            continue;
        }

        // Wywolanie odpowiedniej funkcji obslugi
        this->list[choose-1].second();
        // Pominięcie pauzy po wyswietleniu drzewa, poniewaz ta funkcja ma wlasna logike pauzy
        if(this->list[choose-1].first != "Wyswietl drzewo") pause();
    }

}

#endif