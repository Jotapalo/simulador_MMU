#pragma once

#include <string>
#include <vector>

struct TranslationConfig {
    int pageSize{};
    int numPages{};
    int numFrames{};
    std::vector<int> pageTable;            // size=numPages, value=-1 if unmapped
    std::vector<int> virtualAddresses;    // decimal virtual addresses
};

struct ReplacementConfig {
    int numFrames{};
    std::vector<int> references;          // page IDs
};

class FileReader {
public:
    static TranslationConfig readTranslationConfig(const std::string& filePath);
    static ReplacementConfig readReplacementConfig(const std::string& filePath);
};

