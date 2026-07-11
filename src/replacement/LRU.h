#pragma once

#include "replacement/ReplacementAlgorithm.h"

#include <list>
#include <unordered_map>

class LRU : public ReplacementAlgorithm {
public:
    explicit LRU(int numFrames);

    void reference(int pageId, size_t currentIndex, const std::vector<int>& refs) override;
    ReplacementStats getStats() const override;

private:
    int numFrames_;
    ReplacementStats stats_;

    // Lista con MRU al frente, LRU al final.
    std::list<int> lruList_;
    std::unordered_map<int, std::list<int>::iterator> where_;
};

