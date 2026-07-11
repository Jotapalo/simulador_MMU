#include "io/FileReader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

static std::string trim(const std::string& s) {
    const auto b = s.find_first_not_of(" \t\r\n");
    if (b == std::string::npos) return "";
    const auto e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

static bool isCommentOrEmpty(const std::string& line) {
    auto t = trim(line);
    return t.empty() || t[0] == '#';
}

TranslationConfig FileReader::readTranslationConfig(const std::string& filePath) {
    std::ifstream in(filePath);
    if (!in.is_open()) {
        throw std::runtime_error("No se pudo abrir archivo: " + filePath);
    }

    TranslationConfig cfg;
    std::string line;

    bool inPageTable = false;
    bool inVirtual = false;

    while (std::getline(in, line)) {
        if (isCommentOrEmpty(line)) continue;

        std::stringstream ss(trim(line));
        std::string token;
        ss >> token;

        if (token == "page_size") {
            ss >> cfg.pageSize;
        } else if (token == "num_pages") {
            ss >> cfg.numPages;
        } else if (token == "num_frames") {
            ss >> cfg.numFrames;
        } else if (token == "page_table") {
            inPageTable = true;
            inVirtual = false;
            cfg.pageTable.assign(cfg.numPages, -1);
        } else if (token == "virtual_addresses") {
            inPageTable = false;
            inVirtual = true;
            cfg.virtualAddresses.clear();
        } else if (inPageTable) {
            int pageIdx = -1;
            int frameIdx = -1;
            // formato: page_index frame_index
            ss.clear();
            ss.str(trim(line));
            ss >> pageIdx >> frameIdx;
            if (pageIdx < 0 || pageIdx >= cfg.numPages) {
                throw std::runtime_error("page_index fuera de rango en translation config");
            }
            cfg.pageTable[pageIdx] = frameIdx;
        } else if (inVirtual) {
            int va = 0;
            ss.clear();
            ss.str(trim(line));
            ss >> va;
            cfg.virtualAddresses.push_back(va);
        }
    }

    if (cfg.pageTable.size() != static_cast<size_t>(cfg.numPages)) {
        cfg.pageTable.assign(cfg.numPages, -1);
    }

    return cfg;
}

ReplacementConfig FileReader::readReplacementConfig(const std::string& filePath) {
    std::ifstream in(filePath);
    if (!in.is_open()) {
        throw std::runtime_error("No se pudo abrir archivo: " + filePath);
    }

    ReplacementConfig cfg;
    std::string line;

    bool inRefs = false;

    while (std::getline(in, line)) {
        if (isCommentOrEmpty(line)) continue;

        std::stringstream ss(trim(line));
        std::string token;
        ss >> token;

        if (token == "num_frames") {
            ss >> cfg.numFrames;
        } else if (token == "references") {
            inRefs = true;
            cfg.references.clear();
        } else if (inRefs) {
            // Puede venir en una sola línea con varios números
            int v;
            // reparsear toda la línea
            ss.clear();
            ss.str(trim(line));
            while (ss >> v) cfg.references.push_back(v);
        }
    }

    return cfg;
}

