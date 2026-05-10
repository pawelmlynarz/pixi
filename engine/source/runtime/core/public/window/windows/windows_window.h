// © 2026 Pawel Mlynarz

#pragma once

#include "window/generic_window.h"

namespace px {

class WindowsWindow final : public GenericWindow {
  public:
    ~WindowsWindow() = default;

    virtual void* GetOSWindowHandle() const;
};

} // namespace px
