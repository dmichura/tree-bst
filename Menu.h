#ifndef MENU_H
#define MENU_H

#include <vector>
#include <functional>
#include <string>
#include "BST.h"

/**
 * @brief Klasa Menu zarzadzajaca interfejsem uzytkownika i operacjami na Drzewie BST.
 *
 * Klasa obsluguje wyswietlanie glownego menu i podmenu, zbieranie danych wejsciowych od uzytkownika
 * oraz wywolywanie odpowiednich metod na wewnetrznym obiekcie BST.
 */
class Menu {
private:
    /**
     * @brief Lista opcji menu.
     * * Kazda para przechowuje nazwe opcji (string) oraz funkcje do wywolania (std::function<void()>)
     * w momencie wyboru opcji.
     */
    std::vector<std::pair<std::string, std::function<void()>>> list;

    /**
     * @brief Glowny obiekt Drzewa BST, na ktorym wykonywane sa operacje.
     */
    BST tree;

    /**
     * @brief Obsluguje dodawanie nowego elementu do drzewa.
     */
    void handleDodaj();

    /**
     * @brief Obsluguje usuwanie elementu z drzewa.
     */
    void handleUsun();

    /**
     * @brief Obsluguje wyswietlanie drzewa (wybor metody: graficzna, pre-, in-, post-order).
     */
    void handleWyswietl();

    /**
     * @brief Obsluguje usuniecie wszystkich elementow z drzewa.
     */
    void handleUsunWszystko();

    /**
     * @brief Obsluguje zapisanie aktualnego stanu drzewa do pliku.
     */
    void handleZapiszDoPliku();

    /**
     * @brief Obsluguje wczytanie drzewa z pliku, zastepujac biezacy stan.
     */
    void handleWczytajZPliku();

public:
    /**
     * @brief Konstruktor klasy Menu.
     * * Inicjuje liste opcji menu.
     */
    Menu();

    /**
     * @brief Destruktor klasy Menu.
     */
    ~Menu();

    /**
     * @brief Uruchamia glowna petle programu i wyswietla menu glowne.
     * * Kontynuuje dzialanie do momentu wybrania opcji 'Zamknij program'.
     */
    void run();
};

#endif