#include "replacement/LRU.h"

LRU::LRU(int numFrames) : numFrames_(numFrames) {}

void LRU::reference(int pageId, size_t, const std::vector<int>&) {
    auto it = where_.find(pageId);
    if (it != where_.end()) {
        stats_.hits++;
        // mover a frente
        lruList_.erase(it->second);
        lruList_.push_front(pageId);
        where_[pageId] = lruList_.begin();
        return;
    }

    stats_.pageFaults++;

    if (static_cast<int>(lruList_.size()) >= numFrames_) {
        int victim = lruList_.back();
        lruList_.pop_back();
        where_.erase(victim);
    }

    lruList_.push_front(pageId);
    where_[pageId] = lruList_.begin();
}

ReplacementStats LRU::getStats() const { return stats_; }

