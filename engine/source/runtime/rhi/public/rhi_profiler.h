// © 2026 Pawel Mlynarz

#pragma once

// NRI
#include "NRI.h"

#include <string_view>

namespace px {

struct GPUScopeProfile {
    GPUScopeProfile(nri::CoreInterface const& NRI, nri::CommandBuffer& CommandBuffer, std::string_view Name)
        : NRI_(NRI),
          CommandBuffer_(CommandBuffer) {
        NRI_.CmdBeginAnnotation(CommandBuffer, Name.data(), nri::BGRA_UNUSED);
    }

    ~GPUScopeProfile() {
        NRI_.CmdEndAnnotation(CommandBuffer_);
    }

    GPUScopeProfile(GPUScopeProfile const& Other) = delete;

  private:
    nri::CoreInterface const& NRI_;
    nri::CommandBuffer& CommandBuffer_;
};

} // namespace px
