#include <cassert>
#include <iostream>

#include "translation/AddressTranslator.h"
#include "io/FileReader.h"

int main() {
    // Usar el mismo formato de config pero en memoria no es trivial; probamos con traducción simple.
    TranslationConfig cfg;
    cfg.pageSize = 256;
    cfg.numPages = 4;
    cfg.numFrames = 2;
    cfg.pageTable = {0, 1, -1, 0};
    cfg.virtualAddresses = {0, 300, 512, 700};

    AddressTranslator t(cfg);

    auto r0 = t.translate(0);
    assert(r0.mapped);
    assert(r0.physicalAddress == 0);

    auto r300 = t.translate(300); // page 1 offset 44 -> frame 1 => 256 + 44
    assert(r300.mapped);
    assert(r300.physicalAddress == 1 * 256 + (300 % 256));

    auto r512 = t.translate(512); // page 2 unmapped
    assert(!r512.mapped);

    std::cout << "test_translation.cpp OK\n";
    return 0;
}

