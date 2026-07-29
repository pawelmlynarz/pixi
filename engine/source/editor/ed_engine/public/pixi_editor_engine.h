// © 2026 Pawel Mlynarz

#pragma once

// pxEngine
#include "pixi_engine.h"

namespace px::ed {

class PixiEditorEngine final : public PixiEngine {
};

PX_ENGINE_EDITOR_API PixiEditorEngine& getEditorEngine();

} // namespace px::ed
