// © 2026 Pawel Mlynarz

#pragma once

#include "editor_engine.h"

// pxcore
#include "common/types.h"
#include "tools/utility.h"

namespace px::ed {

[[nodiscard]]
PXEDITOR_ENGINE_API int32 InitializeEditorEngine(SharedPtr<EditorEngine> const& EditorEngine);

} // namespace px::ed
