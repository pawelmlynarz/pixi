// © 2026 Pawel Mlynarz

#include "platform/generic_platform/generic_window.h"

namespace px {

void GenericWindow::initializeWindow(SharedPtr<PlatformApplication> owningApplication, GenericWindowDefinition const& windowDefinition) {
    OwningApplication_ = std::move(owningApplication);
    Definition_ = windowDefinition;
}

} // namespace px
