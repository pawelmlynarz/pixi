// © 2026 Pawel Mlynarz

#include "shader_utils.h"
#include "rhi_asserts.h"

#include <array>
#include <filesystem>
#include <fstream>

namespace px {

namespace {

struct ShaderMeta {
    std::string_view Extension;
    nri::StageBits Stage;
};

constexpr std::array shaderExtensions{
    ShaderMeta("", nri::StageBits::NONE),
    ShaderMeta(".vs.", nri::StageBits::VERTEX_SHADER),
    ShaderMeta(".tcs.", nri::StageBits::TESS_CONTROL_SHADER),
    ShaderMeta(".tes.", nri::StageBits::TESS_EVALUATION_SHADER),
    ShaderMeta(".gs.", nri::StageBits::GEOMETRY_SHADER),
    ShaderMeta(".fs.", nri::StageBits::FRAGMENT_SHADER),
    ShaderMeta(".cs.", nri::StageBits::COMPUTE_SHADER),
};

constexpr std::string_view getShaderIntmdExtension(nri::GraphicsAPI const backend) {
    switch (backend) {
    case nri::GraphicsAPI::D3D11:
        return ".dxbc";
    case nri::GraphicsAPI::D3D12:
        return ".dxil";
    case nri::GraphicsAPI::VK:
        return ".spirv";
    default: {
        pxAssertMsgf(false, "Shader intermediate extension format not specified.");
        return "";
    }
    }
}

std::string_view getFileName(std::string const& path) {
    std::string_view const view(path);

    size_t const slashPos{path.find_last_of("\\/")};
    if (slashPos != std::string::npos) {
        return view.substr(slashPos + 1);
    }
    return "";
}

enum class DataFolder : uint8_t {
    ROOT,
    SHADERS,
};

std::string getFullPath(std::string const& localPath, DataFolder const dataFolder) {
    std::string path{};
    if (dataFolder == DataFolder::SHADERS) {
        path = "_Shaders/";
    }

    for (uint32_t i{0}; i < 4; ++i) {
        if (std::filesystem::exists(path)) {
            break;
        }
        path.reserve(path.size() + 3);
        path.insert(0, "../");
    }
    return path + localPath;
}

bool loadFile(std::string const& path, std::vector<uint8_t>& data) {
    std::ifstream file(path, std::ios::binary);

    if (!file) {
        pxAssert(false);
        data.clear();
        return false;
    }

    file.seekg(0, std::ios::end);
    std::streamsize const size{file.tellg()};
    file.seekg(0, std::ios::beg);

    if (size <= 0) {
        data.clear();
        return false;
    }

    data.resize(static_cast<size_t>(size));

    if (!file.read(reinterpret_cast<char*>(data.data()), size)) {
        data.clear();
        return false;
    }

    return true;
}

} // namespace

nri::ShaderDesc loadShader(nri::GraphicsAPI const backend, std::string const& shaderName, ShaderStorage& storage, std::string_view const entryPointName) {
    std::string_view const extensionStr{getShaderIntmdExtension(backend)};
    std::string const path{getFullPath(shaderName + std::string(extensionStr), DataFolder::SHADERS)};
    nri::ShaderDesc shaderDesc{};

    for (auto const& extension : shaderExtensions) {
        if (path.rfind(extension.Extension) == std::string::npos) {
            continue;
        }

        storage.emplace_back();
        std::vector<uint8>& code{storage.back()};

        if (loadFile(path, code)) {
            shaderDesc.stage = extension.Stage;
            shaderDesc.bytecode = code.data();
            shaderDesc.size = code.size();
            shaderDesc.entryPointName = entryPointName.data();
        }
        break;
    }
    RHI_ABORT_ON_FALSE(shaderDesc.size != 0);

    return shaderDesc;
}

} // namespace px
