// © 2026 Pawel Mlynarz

#include "rhi.h"
#include "rhi_context.h"
#include "shader_utils.h"

namespace px {

namespace {

UniquePtr<RHIContext> sRhiContext{nullptr};

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
    pxAssert(!sRhiContext);
    sRhiContext = makeUnique<RHIContext>(getBackendForPlatform());
    sRhiContext->initialize();
}

RHIContext& getRhiContext() {
    pxAssert(sRhiContext);
    return *sRhiContext;
}

void shutdownRhi() {
    pxAssert(sRhiContext);
    sRhiContext->shutdown();
}

nri::GraphicsAPI getBackend() {
    return sRhiContext->getBackend();
}

} // namespace px
