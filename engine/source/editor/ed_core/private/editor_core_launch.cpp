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
        auto& pxRenderer{dynamic_cast<Renderer&>(SimpleApplication::get().getRenderer())};
        ImGui::SetCurrentContext(static_cast<ImGuiContext*>(pxRenderer.getImGuiRenderer().getImguiContext()));
    }

    static void initImGuiEditorStyleSet() {
        EdStyle::setDefaultStyle();
    }
};

SharedPtr<EditorMainFrameWindow> editorMainFrameWindow{nullptr};

bool createEditorMainFrame() {
    editorMainFrameWindow = makeShared<EditorMainFrameWindow>();

    editorMainFrameWindow->title("Pixi Editor")
        .size({1920, 1080})
        .decorated(true)
        .resizable(true);

    return SimpleApplication::get().addWindow(editorMainFrameWindow, true);
}

} // namespace

int32 editorInit() {
    pxAssert(!editorMainFrameWindow);

    if (!createEditorMainFrame()) {
        return -1;
    }
    
    ImGuiEdHelper::initImGuiEditorContext();
    ImGuiEdHelper::initImGuiEditorStyleSet();
    
    return 0;
}

void editorExit() {
    if (editorMainFrameWindow) {
        editorMainFrameWindow->destoryNativeWindow();
        editorMainFrameWindow.reset();
    }
}

} // namespace px::ed
