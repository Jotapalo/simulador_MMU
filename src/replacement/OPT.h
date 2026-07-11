#pragma once

#include "replacement/ReplacementAlgorithm.h"

#include <unordered_set>
#include <vector>

class OPT : public ReplacementAlgorithm {
public:
    explicit OPT(int numFrames);

    void reference(int pageId, size_t currentIndex, const std::vector<int>& refs) override;
    ReplacementStats getStats() const override;

private:
    int numFrames_;
    ReplacementStats stats_;

    std::vector<int> frames_; // -1 vacías
    std::unordered_set<int> resident_;
};

