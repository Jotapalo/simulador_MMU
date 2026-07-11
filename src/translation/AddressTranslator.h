#pragma once

#include <vector>

struct TranslationConfig;

struct TranslationResult {
    bool mapped{false};
    int pageIndex{-1};
    int frameIndex{-1};
    int offset{-1};
    int physicalAddress{-1};
};

class AddressTranslator {
public:
    explicit AddressTranslator(const TranslationConfig& cfg);

    TranslationResult translate(int virtualAddress) const;

private:
    int pageSize_{};
    int numPages_{};
    int numFrames_{};
    std::vector<int> pageTable_; // -1 si no mapeada
};

