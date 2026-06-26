// © 2026 Pawel Mlynarz

#pragma once

#include "editor_engine_module.h"

// pxengine
#include "pixi_engine.h"

namespace px::ed {

class PixiEditorEngine final : public PixiEngine {
};

PXEDITOR_ENGINE_API PixiEditorEngine& getEditorEngine();

} // namespace px::ed
