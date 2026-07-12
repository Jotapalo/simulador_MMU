#pragma once

#include <vector>

struct TranslationConfig;

// Resultado de traducir una dirección virtual.
// - mapped: indica si existe mapeo válido en la tabla de páginas y marco disponible.
// - pageIndex/frameIndex/offset: descomposición de la dirección.
// - physicalAddress: dirección física calculada (válida si mapped==true).
struct TranslationResult {
    bool mapped{false};
    int pageIndex{-1};
    int frameIndex{-1};
    int offset{-1};
    int physicalAddress{-1};
};


class AddressTranslator {
public:
    // Crea un traductor usando una configuración de memoria virtual y física.
    //
    // Parámetros:
    // - cfg: estructura con pageSize, numPages, numFrames, pageTable y/o parámetros relacionados.
    explicit AddressTranslator(const TranslationConfig& cfg);

    // Traduce una dirección virtual (VA) a una dirección física (PA) si existe mapeo.
    //
    // Parámetros:
    // - virtualAddress: dirección virtual en decimal.
    //
    // Retorno:
    // - TranslationResult con:
    //   mapped=false si el pageIndex queda fuera de rango o si no existe marco válido.
    //   mapped=true y physicalAddress calculada si hay mapeo.
    TranslationResult translate(int virtualAddress) const;

private:
    int pageSize_{};
    int numPages_{};
    int numFrames_{};
    std::vector<int> pageTable_; // -1 si no mapeada
};



