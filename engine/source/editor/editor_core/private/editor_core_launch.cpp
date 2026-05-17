// © 2026 Pawel Mlynarz

#include "editor_core_launch.h"

// pxcore
#include "app/engine_application.h"

namespace px::ed {

namespace {

bool CreateMainEditorWindow() {
    GenericWindowDefinition constexpr EditorMainWindowDef{
        .WidthDesired = 1920,
        .HeightDesired = 1080
    };
    return GetApplication().AddWindow(EditorMainWindowDef, true);
}

} // namespace

int32 EditorInit() {
    if (!CreateMainEditorWindow())
        return -1;
    return 0;
}

void EditorExit() {
}

} // namespace px::ed
