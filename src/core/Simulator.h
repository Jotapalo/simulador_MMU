#pragma once

#include <string>

class Simulator {
public:
    // Ejecuta traducción virtual->física usando paginación 1 nivel.
    static void runTranslation(const std::string& filePath);

    // Ejecuta simulador de reemplazo de páginas (FIFO/LRU/OPT) y compara resultados.
    static void runReplacement(const std::string& filePath);
};

