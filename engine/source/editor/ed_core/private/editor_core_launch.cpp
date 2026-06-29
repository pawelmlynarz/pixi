// © 2026 Pawel Mlynarz

#include "editor_core_launch.h"

// pxfrontend
#include "app/pixi_application.h"

// pxeditorfrontend
#include "editor_mainframe.h"

#include "rendering/renderer.h"
#include "rendering/imgui_renderer.h"
#include "styles/editor_style.h"

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

SharedPtr<SEditorMainFrame> editorMainFrameWindow{nullptr};

bool createEditorMainFrame() {
    editorMainFrameWindow = {makeShared<SEditorMainFrame>()};

    editorMainFrameWindow->Title("Pixi Editor")
        .Size({1920, 1080})
        .Decorated(true)
        .Resizable(true);

    pxAssert(SimpleApplication::get().addWindow(editorMainFrameWindow, true));

    return true;
}

} // namespace

int32 editorInit() {
    if (!createEditorMainFrame()) {
        return -1;
    }
    
    ImGuiEdHelper::initImGuiEditorContext();
    ImGuiEdHelper::initImGuiEditorStyleSet();
    
    return 0;
}

void editorExit() {
    editorMainFrameWindow->destoryNativeWindow();
    editorMainFrameWindow.reset();
}

} // namespace px::ed
