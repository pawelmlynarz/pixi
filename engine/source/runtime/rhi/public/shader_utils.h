// © 2026 Pawel Mlynarz

#pragma once

#include "rhi_module.h"

// pxcore
#include "common/types.h"

// NRI
#include "NRIDescs.h"

#include <string>
#include <vector>

namespace px {

using ShaderStorage = std::vector<std::vector<uint8>>;

PXRHI_API nri::ShaderDesc LoadShader(
    nri::GraphicsAPI Backend, std::string const& ShaderName,
    ShaderStorage& Storage, std::string_view EntryPointName = ""
);

} // namespace px
