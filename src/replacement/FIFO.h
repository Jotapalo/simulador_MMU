#pragma once

#include "replacement/ReplacementAlgorithm.h"

#include <deque>
#include <unordered_set>

class FIFO : public ReplacementAlgorithm {
public:
    explicit FIFO(int numFrames);

    void reference(int pageId, size_t currentIndex, const std::vector<int>& refs) override;
    ReplacementStats getStats() const override;

private:
    int numFrames_;
    std::deque<int> queue_;
    std::unordered_set<int> resident_;
    ReplacementStats stats_;
};

