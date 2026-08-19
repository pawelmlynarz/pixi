// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "pixi_editor_engine.h"

namespace px::ed {

[[nodiscard]]
PX_ENGINE_EDITOR_API i32 initializeEditorEngine(SharedPtr<PixiEditorEngine> const& editorEngine);

} // namespace px::ed
