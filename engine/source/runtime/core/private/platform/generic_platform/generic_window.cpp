// © 2026 Pawel Mlynarz

#include "platform/generic_platform/generic_window.h"

namespace px {

void GenericWindow::InitializeWindow(SharedPtr<PlatformApplication> OwningApplication, GenericWindowDefinition const& WindowDefinition) {
    OwningApplication_ = std::move(OwningApplication);
    Definition_ = WindowDefinition;
}

} // namespace px
