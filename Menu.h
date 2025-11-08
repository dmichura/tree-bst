#ifndef MENU_H
#define MENU_H

#include <vector>
#include <functional>
#include <string>

class Menu {
private:
    std::vector<std::pair<std::string, std::function<void()>>> list;
public:
    Menu();
    ~Menu();
    void run();
    void add();
};

#endif
