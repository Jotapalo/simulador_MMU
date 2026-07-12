#include <iostream>
#include <vector>

#include "replacement/FIFO.h"
#include "replacement/LRU.h"
#include "replacement/OPT.h"

int main() {
    const std::vector<int> refs = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    const int frames = 3;

    FIFO fifo(frames);
    LRU lru(frames);
    OPT opt(frames);

    for (size_t i = 0; i < refs.size(); ++i) {
        fifo.reference(refs[i], i, refs);
        lru.reference(refs[i], i, refs);
        opt.reference(refs[i], i, refs);
    }

    auto sf = fifo.getStats();
    auto sl = lru.getStats();
    auto so = opt.getStats();

    std::cout << "FIFO hits=" << sf.hits << " faults=" << sf.pageFaults << "\n";
    std::cout << "LRU  hits=" << sl.hits << " faults=" << sl.pageFaults << "\n";
    std::cout << "OPT  hits=" << so.hits << " faults=" << so.pageFaults << "\n";
    return 0;
}

