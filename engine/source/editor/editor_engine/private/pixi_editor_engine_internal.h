// © 2026 Pawel Mlynarz

#pragma once

#include "pixi_editor_engine.h"

// pxcore
#include "common/types.h"
#include "tools/utility.h"

namespace px::ed {

[[nodiscard]]
PXEDITOR_ENGINE_API int32 InitializeEditorEngine(SharedPtr<PixiEditorEngine> const& EditorEngine);

} // namespace px::ed
