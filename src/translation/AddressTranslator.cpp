#include "translation/AddressTranslator.h"

#include "io/FileReader.h" // TranslationConfig

AddressTranslator::AddressTranslator(const TranslationConfig& cfg)
    : pageSize_(cfg.pageSize),
      numPages_(cfg.numPages),
      numFrames_(cfg.numFrames),
      pageTable_(cfg.pageTable) {}

TranslationResult AddressTranslator::translate(int virtualAddress) const {
    // Descomposición:
    // pageIndex = virtualAddress / pageSize
    // offset    = virtualAddress % pageSize
    TranslationResult res;

    if (virtualAddress < 0) return res;


    const int pageIndex = virtualAddress / pageSize_;
    const int offset = virtualAddress % pageSize_;

    res.pageIndex = pageIndex;
    res.offset = offset;

    if (pageIndex < 0 || pageIndex >= numPages_) {
        res.mapped = false;
        return res;
    }

    const int frameIndex = (pageIndex < static_cast<int>(pageTable_.size())) ? pageTable_[pageIndex] : -1;
    res.frameIndex = frameIndex;

    if (frameIndex < 0 || frameIndex >= numFrames_) {
        res.mapped = false;
        return res;
    }

    res.mapped = true;
    res.physicalAddress = frameIndex * pageSize_ + offset;
    return res;
}

