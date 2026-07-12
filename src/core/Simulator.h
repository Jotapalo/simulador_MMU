#pragma once

#include <string>

class Simulator {
public:
    // Traduce direcciones virtuales a direcciones físicas.
    //
    // Parámetros:
    // - filePath: ruta del archivo de configuración (ej. examples/translation1.txt).
    //
    // Acción:
    // - Lee la configuración (page_size, num_pages, num_frames, page_table, virtual_addresses).
    // - Para cada dirección virtual imprime si está mapeada y, si lo está, calcula PA usando:
    //   pageIndex = VA / page_size, offset = VA % page_size.
    static void runTranslation(const std::string& filePath);

    // Simula reemplazo de páginas para una secuencia de referencias.
    //
    // Parámetros:
    // - filePath: ruta del archivo de configuración (ej. examples/replacement1.txt).
    //
    // Acción:
    // - Lee num_frames y la secuencia de referencias.
    // - Ejecuta FIFO, LRU y OPT sobre la MISMA secuencia y reporta hits/faults.
    static void runReplacement(const std::string& filePath);
};





