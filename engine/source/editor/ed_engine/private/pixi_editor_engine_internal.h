// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "pixi_editor_engine.h"

namespace px::ed {

[[nodiscard]]
PXENGINE_EDITOR_API int32 initializeEditorEngine(SharedPtr<PixiEditorEngine> const& editorEngine);

} // namespace px::ed
