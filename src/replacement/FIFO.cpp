#include "replacement/FIFO.h"

FIFO::FIFO(int numFrames) : numFrames_(numFrames) {}

void FIFO::reference(int pageId, size_t, const std::vector<int>&) {
    if (resident_.count(pageId)) {
        stats_.hits++;
        return;
    }

    stats_.pageFaults++;

    if (static_cast<int>(resident_.size()) >= numFrames_) {
        int victim = queue_.front();
        queue_.pop_front();
        resident_.erase(victim);
    }

    resident_.insert(pageId);
    queue_.push_back(pageId);
}

ReplacementStats FIFO::getStats() const { return stats_; }

