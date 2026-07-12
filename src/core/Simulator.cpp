#include "core/Simulator.h"

#include <iostream>

#include "io/FileReader.h"
#include "translation/AddressTranslator.h"
#include "replacement/FIFO.h"
#include "replacement/LRU.h"
#include "replacement/OPT.h"


void Simulator::runTranslation(const std::string& filePath) {
    TranslationConfig cfg = FileReader::readTranslationConfig(filePath);

    AddressTranslator translator(cfg);
    std::cout << "=== Traduccion Virtual -> Fisica ===\n";
    std::cout << "page_size=" << cfg.pageSize << " num_pages=" << cfg.numPages << " num_frames=" << cfg.numFrames << "\n";

    for (auto vaddr : cfg.virtualAddresses) {
        auto res = translator.translate(vaddr);
        std::cout << "VA " << vaddr << " -> ";
        if (!res.mapped) {
            std::cout << "[NO MAPEADA]";
        } else {
            std::cout << "PA " << res.physicalAddress << " (page=" << res.pageIndex << ", offset=" << res.offset
                      << ", frame=" << res.frameIndex << ")";
        }
        std::cout << "\n";
    }
}

void Simulator::runReplacement(const std::string& filePath) {
    ReplacementConfig cfg = FileReader::readReplacementConfig(filePath);

    std::cout << "=== Simulador Reemplazo de paginas===\n";
    std::cout << "num_frames=" << cfg.numFrames << "\n";
    std::cout << "references=";
    for (size_t i = 0; i < cfg.references.size(); ++i) {
        std::cout << cfg.references[i] << (i + 1 == cfg.references.size() ? "\n" : " ");
    }
    std::cout << "-------------------------------------\n";

    // FIFO
    {
        FIFO algo(cfg.numFrames);
        for (size_t i = 0; i < cfg.references.size(); ++i) {
            algo.reference(cfg.references[i], i, cfg.references);
        }
        auto s = algo.getStats();
        std::cout << "FIFO: hits=" << s.hits << " faults=" << s.pageFaults << "\n";
    }

    // LRU
    {
        LRU algo(cfg.numFrames);
        for (size_t i = 0; i < cfg.references.size(); ++i) {
            algo.reference(cfg.references[i], i, cfg.references);
        }
        auto s = algo.getStats();
        std::cout << "LRU : hits=" << s.hits << " faults=" << s.pageFaults << "\n";
    }

    // OPT
    {
        OPT algo(cfg.numFrames);
        for (size_t i = 0; i < cfg.references.size(); ++i) {
            algo.reference(cfg.references[i], i, cfg.references);
        }
        auto s = algo.getStats();
        std::cout << "OPT : hits=" << s.hits << " faults=" << s.pageFaults << "\n";
    }
}

