// © 2026 Pawel Mlynarz

#pragma once

// NRI
#include "NRI.h"
#include "Extensions/NRIHelper.h"
#include "Extensions/NRIStreamer.h"
#include "Extensions/NRISwapChain.h"

#include <type_traits>

namespace px {

class RHIInterface
    : public nri::CoreInterface,
      public nri::HelperInterface,
      public nri::StreamerInterface,
      public nri::SwapChainInterface {
  public:
    template <typename TInterface>
        requires std::is_base_of_v<TInterface, RHIInterface>
    TInterface* As() { return static_cast<TInterface*>(this); }

    template <typename TInterface>
        requires std::is_base_of_v<TInterface, RHIInterface>
    TInterface const* As() const { return static_cast<TInterface const*>(this); }

    bool HasCore() const;
    bool HasHelper() const;
    bool HasStreamer() const;
    bool HasSwapChain() const;
};

inline bool RHIInterface::HasCore() const {
    return GetDeviceDesc != nullptr;
}

inline bool RHIInterface::HasHelper() const {
    return CalculateAllocationNumber != nullptr;
}

inline bool RHIInterface::HasStreamer() const {
    return CreateStreamer != nullptr;
}

inline bool RHIInterface::HasSwapChain() const {
    return CreateSwapChain != nullptr;
}

} // namespace px
