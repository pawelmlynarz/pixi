// © 2026 Pawel Mlynarz

#include "window/generic_window.h"

namespace px {

void GenericWindow::InitializeWindow(SharedPtr<PlatformApplication> const OwningApplication, GenericWindowDefinition const& WindowDefinition) {
    OwningApplication_ = OwningApplication;
    Definition_ = WindowDefinition;
}

} // namespace px
