#pragma once

#include <string>

class Simulator {
public:
    // Ejecuta la traducción de una lista de direcciones virtuales a direcciones físicas.
    // La traducción usa paginación de 1 nivel (tabla de páginas por página virtual).
    static void runTranslation(const std::string& filePath);

    // Ejecuta un simulador de reemplazo de páginas para una secuencia de referencias.
    // Compara FIFO, LRU y OPT sobre la misma configuración.
    static void runReplacement(const std::string& filePath);
};


