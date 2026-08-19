// © 2026 Pawel Mlynarz

#include "editor_core_launch.h"
#include "editor_mainframe.h"
#include "styles/editor_style.h"

// pxEngine
#include "app/pixi_application.h"
#include "rendering/renderer.h"
#include "rendering/imgui_renderer.h"

namespace px::ed {

namespace {

struct ImGuiEdHelper {
    static void initImGuiEditorContext() {
        auto& pxRenderer{PixiApplication::get().getRenderer()};
        ImGui::SetCurrentContext(static_cast<ImGuiContext*>(pxRenderer.getImGuiRenderer().getImguiContext()));
    }

    static void initImGuiEditorStyleSet() {
        EdStyle::setDefaultStyle();
    }
};

SharedPtr<EditorMainFrameWindow> sEditorMainFrameWindow{nullptr};

bool createEditorMainFrame() {
    sEditorMainFrameWindow = makeShared<EditorMainFrameWindow>();

    sEditorMainFrameWindow->title("Pixi Editor")
        .size({1920, 1080})
        .decorated(true)
        .resizable(true);

    return PixiApplication::get().addWindow(sEditorMainFrameWindow, true);
}

} // namespace

i32 editorInit() {
    pxAssert(!sEditorMainFrameWindow);

    if (!createEditorMainFrame()) {
        return -1;
    }

    ImGuiEdHelper::initImGuiEditorContext();
    ImGuiEdHelper::initImGuiEditorStyleSet();

    return 0;
}

void editorExit() {
    if (sEditorMainFrameWindow) {
        sEditorMainFrameWindow->destroyNativeWindow();
        sEditorMainFrameWindow.reset();
    }
}

} // namespace px::ed
