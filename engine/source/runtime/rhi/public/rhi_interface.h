// © 2026 Pawel Mlynarz

#pragma once

// NRI
#include "NRI.h"
#include "Extensions/NRIHelper.h"
#include "Extensions/NRIStreamer.h"
#include "Extensions/NRISwapChain.h"

namespace px {

class RHIInterface
    : public nri::CoreInterface,
      public nri::HelperInterface,
      public nri::StreamerInterface,
      public nri::SwapChainInterface {
public:
    bool HasCore() const {
        return GetDeviceDesc != nullptr;
    }
    
    bool HasHelper() const {
        return CalculateAllocationNumber != nullptr;
    }
    
    bool HasStreamer() const {
        return CreateStreamer != nullptr;
    }
    
    bool HasSwapChain() const {
        return CreateSwapChain != nullptr;
    }
};

} // namespace px
