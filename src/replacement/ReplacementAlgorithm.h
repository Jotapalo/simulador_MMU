#pragma once

#include <vector>

struct ReplacementStats {
    int hits{0};
    int pageFaults{0};
};

class ReplacementAlgorithm {
public:
    virtual ~ReplacementAlgorithm() = default;

    // currentIndex: índice actual dentro de la secuencia
    // refs: secuencia completa (útil para OPT)
    virtual void reference(int pageId, size_t currentIndex, const std::vector<int>& refs) = 0;

    virtual ReplacementStats getStats() const = 0;
};

