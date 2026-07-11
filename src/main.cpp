#include <iostream>
#include "ui/Menu.h"

int main() {
    try {
        Menu menu;
        menu.run();
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}

