#include "replacement/OPT.h"

#include <limits>

OPT::OPT(int numFrames) : numFrames_(numFrames), frames_(numFrames, -1) {}

static size_t nextUseIndex(size_t currentIndex, int pageId, const std::vector<int>& refs) {
    for (size_t i = currentIndex + 1; i < refs.size(); ++i) {
        if (refs[i] == pageId) return i;
    }
    return std::numeric_limits<size_t>::max();
}

void OPT::reference(int pageId, size_t currentIndex, const std::vector<int>& refs) {
    if (resident_.count(pageId)) {
        stats_.hits++;
        return;
    }

    stats_.pageFaults++;

    // buscar frame vacío
    for (int i = 0; i < numFrames_; ++i) {
        if (frames_[i] == -1) {
            frames_[i] = pageId;
            resident_.insert(pageId);
            return;
        }
    }

    // elegir víctima: la que se usa más tarde (o nunca)
    size_t bestNext = 0;
    int victimIdx = -1;
    bool first = true;

    for (int i = 0; i < numFrames_; ++i) {
        int candidatePage = frames_[i];
        size_t nu = nextUseIndex(currentIndex, candidatePage, refs);
        if (first || nu > bestNext) {
            bestNext = nu;
            victimIdx = i;
            first = false;
        }
    }

    // reemplazar
    int oldPage = frames_[victimIdx];
    resident_.erase(oldPage);
    frames_[victimIdx] = pageId;
    resident_.insert(pageId);
}

ReplacementStats OPT::getStats() const { return stats_; }

