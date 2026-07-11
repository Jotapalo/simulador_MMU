#include "ui/Menu.h"

#include <iostream>
#include <string>

#include "core/Simulator.h"


void Menu::run() {
    std::cout << "MMU Simulator\n";
    std::cout << "1) Traduccion de Direcciones (Paginacion 1 nivel)\n";
    std::cout << "2) Reemplazo de paginas (FIFO/LRU/OPT)\n";
    std::cout << "0) Salir\n";

    int choice = -1;
    std::cout << "Opcion: ";
    std::cin >> choice;

    if (choice == 0) return;

    std::string path;
    if (choice == 1) {
        std::cout << "Ruta del archivo translation (ej: examples/translation1.txt): ";
        std::cin >> path;
        Simulator::runTranslation(path);
    } else if (choice == 2) {
        std::cout << "Ruta del archivo replacement (ej: examples/replacement1.txt): ";
        std::cin >> path;
        Simulator::runReplacement(path);
    } else {
        std::cout << "Opción no válida\n";
    }
}

