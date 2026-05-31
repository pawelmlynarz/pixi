// © 2026 Pawel Mlynarz

#pragma once

// pxcore
#include "tools/asserts.h"

// NRI
#include "NRI.h"

#define RHI_ABORT_ON_FAILURE(Res)        \
    if ((Res) != nri::Result::SUCCESS) { \
        Assert(false);                   \
    }

#define RHI_ABORT_ON_FALSE(Res) \
    if (!(Res)) {               \
        Assert(false);          \
    }
