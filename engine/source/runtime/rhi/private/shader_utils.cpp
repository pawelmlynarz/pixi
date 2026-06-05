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

constexpr std::array ShaderExtensions{
    ShaderMeta("", nri::StageBits::NONE),
    ShaderMeta(".vs.", nri::StageBits::VERTEX_SHADER),
    ShaderMeta(".tcs.", nri::StageBits::TESS_CONTROL_SHADER),
    ShaderMeta(".tes.", nri::StageBits::TESS_EVALUATION_SHADER),
    ShaderMeta(".gs.", nri::StageBits::GEOMETRY_SHADER),
    ShaderMeta(".fs.", nri::StageBits::FRAGMENT_SHADER),
    ShaderMeta(".cs.", nri::StageBits::COMPUTE_SHADER),
};

constexpr std::string_view GetShaderIntmdExtension(nri::GraphicsAPI const Backend) {
    switch (Backend) {
    case nri::GraphicsAPI::D3D11:
        return ".dxbc";
    case nri::GraphicsAPI::D3D12:
        return ".dxil";
    case nri::GraphicsAPI::VK:
        return ".spirv";
    default: {
        AssertMsgf(false, "Shader intermediate extension format not specified.");
        return "";
    }
    }
}

std::string_view GetFileName(std::string const& Path) {
    std::string_view const View(Path);
    
    size_t const SlashPos{Path.find_last_of("\\/")};
    if (SlashPos != std::string::npos) {
        return View.substr(SlashPos + 1);
    }
    return "";
}

enum class DataFolder : uint8_t {
    ROOT,
    SHADERS,
};

std::string GetFullPath(std::string const& LocalPath, DataFolder const DataFolder) {
    std::string Path{};
    if (DataFolder == DataFolder::SHADERS) {
        Path = "_Shaders/";
    }

    for (uint32_t I{0}; I < 4; ++I) {
        if (std::filesystem::exists(Path)) {
            break;
        }
        Path.reserve(Path.size() + 3);
        Path.insert(0, "../");
    }
    return Path + LocalPath;
}

bool LoadFile(std::string const& Path, std::vector<uint8_t>& Data) {
    std::ifstream File(Path, std::ios::binary);

    if (!File) {
        Assert(false);
        Data.clear();
        return false;
    }

    File.seekg(0, std::ios::end);
    std::streamsize const Size{File.tellg()};
    File.seekg(0, std::ios::beg);

    if (Size <= 0) {
        Data.clear();
        return false;
    }

    Data.resize(static_cast<size_t>(Size));

    if (!File.read(reinterpret_cast<char*>(Data.data()), Size)) {
        Data.clear();
        return false;
    }

    return true;
}

} // namespace

nri::ShaderDesc LoadShader(nri::GraphicsAPI const Backend, std::string const& ShaderName, ShaderStorage& Storage, std::string_view const EntryPointName) {
    std::string_view const ExtensionStr{GetShaderIntmdExtension(Backend)};
    std::string const Path{GetFullPath(ShaderName + std::string(ExtensionStr), DataFolder::SHADERS)};
    nri::ShaderDesc ShaderDesc{};

    for (auto const& Extension : ShaderExtensions)
    {
        if (Path.rfind(Extension.Extension) == std::string::npos){
            continue;
        }

        Storage.emplace_back();
        std::vector<uint8>& Code{Storage.back()};

        if (LoadFile(Path, Code)) {
            ShaderDesc.stage = Extension.Stage;
            ShaderDesc.bytecode = Code.data();
            ShaderDesc.size = Code.size();
            ShaderDesc.entryPointName = EntryPointName.data();
        }
        break;
    }
    RHI_ABORT_ON_FALSE(ShaderDesc.size != 0);
    
    return ShaderDesc;
}

} // namespace px
