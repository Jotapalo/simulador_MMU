#include <cassert>
#include <iostream>

#include "replacement/FIFO.h"
#include "replacement/LRU.h"
#include "replacement/OPT.h"

static void assertStats(const ReplacementStats& s, int expectedHits, int expectedFaults) {
    assert(s.hits == expectedHits);
    assert(s.pageFaults == expectedFaults);
}

int main() {
    // Secuencia del ejemplo (ver examples/replacement1.txt)
    const std::vector<int> refs = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    const int frames = 3;

    {
        FIFO algo(frames);
        for (size_t i = 0; i < refs.size(); ++i) {
            algo.reference(refs[i], i, refs);
        }
        auto s = algo.getStats();
        // Para FIFO con 3 marcos en esa secuencia (según implementación): hits=2, faults=10
        assertStats(s, 2, 10);

    }

    {
        LRU algo(frames);
        for (size_t i = 0; i < refs.size(); ++i) {
            algo.reference(refs[i], i, refs);
        }
        auto s = algo.getStats();
        // Para LRU con 3 marcos (según implementación): hits=3, faults=9
        assertStats(s, 3, 9);
    }


    {
        OPT algo(frames);
        for (size_t i = 0; i < refs.size(); ++i) {
            algo.reference(refs[i], i, refs);
        }
        auto s = algo.getStats();
        // Para OPT con 3 marcos: hits=5, faults=7
        assertStats(s, 5, 7);
    }

    std::cout << "test_replacement.cpp OK\n";
    return 0;
}

