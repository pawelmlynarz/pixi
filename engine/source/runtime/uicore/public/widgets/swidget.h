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

#define SWIDGET_PROPERTY(Type, Name, Field) \
  private:                                  \
    Type Field{};                           \
                                            \
  public:                                   \
    auto& Name(Type const& value) {         \
        Field = value;                      \
        return *this;                       \
    }                                       \
                                            \
    Type const& Get##Name() const {         \
        return Field;                       \
    }
