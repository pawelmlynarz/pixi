// © 2026 Pawel Mlynarz

#include "rhi.h"
#include "rhi_context.h"

// pxcore
#include "tools/asserts.h"
#include "tools/utility.h"

// NRI
#include "shader_utils.h"

namespace px {

namespace {

UniquePtr<RHIContext> RHIContextInst{nullptr};

nri::GraphicsAPI GetBackendForPlatform() {
#if PLATFORM_WINDOWS
    PX_TODO("Make possible to override via command line.");
    return nri::GraphicsAPI::VK;
#else
#error Unsupported platform: no RHI specified.
#endif
}
} // namespace

void InitializeRHI() {
    Assert(!RHIContextInst);
    RHIContextInst = MakeUnique<RHIContext>(GetBackendForPlatform());
    RHIContextInst->Initialize();
}

RHIContext& GetRHIContext() {
    Assert(RHIContextInst);
    return *RHIContextInst;
}

void ShutdownRHI() {
    Assert(RHIContextInst);
    RHIContextInst->Shutdown();
}

nri::GraphicsAPI GetBackend() {
    return RHIContextInst->GetBackend();
}

} // namespace px
