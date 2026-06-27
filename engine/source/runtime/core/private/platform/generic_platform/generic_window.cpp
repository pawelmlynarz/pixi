// © 2026 Pawel Mlynarz

#include "platform/generic_platform/generic_window.h"

namespace px {

void PlatformWindow::initializeWindow(SharedPtr<PlatformApplication> owningApplication, PlatformWindowDefinition const& windowDefinition) {
    OwningApplication_ = std::move(owningApplication);
    Definition_ = windowDefinition;
}

} // namespace px
