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

PXRHI_API nri::ShaderDesc loadShader(
    nri::GraphicsAPI backend, std::string const& shaderName,
    ShaderStorage& storage, std::string_view entryPointName = ""
);

} // namespace px
