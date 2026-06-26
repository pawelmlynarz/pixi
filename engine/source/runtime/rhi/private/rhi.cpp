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

UniquePtr<RHIContext> rhiContextInst{nullptr};

nri::GraphicsAPI getBackendForPlatform() {
#if PLATFORM_WINDOWS
    pxToDo("Make possible to override via command line.");
    return nri::GraphicsAPI::VK;
#else
#error Unsupported platform: no RHI specified.
#endif
}
} // namespace

void initializeRhi() {
    pxAssert(!rhiContextInst);
    rhiContextInst = makeUnique<RHIContext>(getBackendForPlatform());
    rhiContextInst->initialize();
}

RHIContext& getRhiContext() {
    pxAssert(rhiContextInst);
    return *rhiContextInst;
}

void shutdownRhi() {
    pxAssert(rhiContextInst);
    rhiContextInst->shutdown();
}

nri::GraphicsAPI getBackend() {
    return rhiContextInst->getBackend();
}

} // namespace px
