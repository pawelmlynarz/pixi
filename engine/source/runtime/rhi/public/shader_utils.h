// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

// NRI
#include "NRIDescs.h"

#include <string>
#include <vector>

namespace px {

using ShaderStorage = std::vector<std::vector<uint8>>;

PXENGINE_API nri::ShaderDesc loadShader(
    nri::GraphicsAPI backend, std::string const& shaderName,
    ShaderStorage& storage, std::string_view entryPointName = ""
);

} // namespace px
