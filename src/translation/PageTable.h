#pragma once

#include <vector>

struct PageTable {
    std::vector<int> mapping; // pageIndex -> frameIndex, -1 si no mapeada
};

