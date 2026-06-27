// © 2026 Pawel Mlynarz

#pragma once

// pxcore
#include "tools/utility.h"

namespace px {

/*
 *  Simple widget base class.
 */
class SWidget : public EnableSharedFromThis<SWidget> {
  public:
    virtual ~SWidget() = default;
};

} // namespace px

#define SWIDGET_PROPERTY(type, name) \
  private:                           \
    type name##_{};                  \
                                     \
  public:                            \
    auto& name(type const& value) {  \
        (name##_) = value;           \
        return *this;                \
    }                                \
                                     \
    type const& get##name() const {  \
        return name##_;              \
    }
