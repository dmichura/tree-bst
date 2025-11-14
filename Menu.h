#ifndef MENU_H
#define MENU_H

#include <vector>
#include <functional>
#include <string>
#include "BST.h"

class Menu {
private:
    std::vector<std::pair<std::string, std::function<void()>>> list;
    BST tree;

    void handleDodaj();
    void handleUsun();
    void handleWyswietl();
    void handleUsunWszystko();
    void handleZapiszDoPliku();
    void handleWczytajZPliku();
public:
    Menu();
    ~Menu();
    void run();
};

#endif
