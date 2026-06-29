// © 2026 Pawel Mlynarz

#pragma once

#include "pixi_editor_engine.h"

// pxcore
#include "common/types.h"
#include "tools/utility.h"

namespace px::ed {

[[nodiscard]]
PXENGINE_EDITOR_API int32 initializeEditorEngine(SharedPtr<PixiEditorEngine> const& editorEngine);

} // namespace px::ed
