// © 2026 Pawel Mlynarz

#pragma once

#include "editor_engine_module.h"

// pxengine
#include "engine.h"

namespace px::ed {

class EditorEngine final : public Engine {
};

PXEDITOR_ENGINE_API EditorEngine& GetEditorEngine();

} // namespace px::ed
