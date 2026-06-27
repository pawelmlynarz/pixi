// © 2026 Pawel Mlynarz

// pxcore
#include "misc/core_delegates.h"
#include "modules/module_interface.h"
#include "styles/editor_style.h"

// pxfrontend
#include "app/pixi_application.h"
#include "rendering/renderer.h"
#include "rendering/imgui_renderer.h"

// imgui
#include "imgui.h"

namespace {

using namespace px;
using namespace px::ed;

void initializeImGuiContext() {
    auto& pixiRenderer{dynamic_cast<Renderer&>(SimpleApplication::get().getRenderer())};
    ImGui::SetCurrentContext(static_cast<ImGuiContext*>(pixiRenderer.getImGuiRenderer().getImguiContext()));
}

void initializeImGuiEditorStyleSet() {
    EdStyle::setDefaultStyle();
}

struct EditorFrontendModule {
    static void startupModule() {
        CoreDelegates::onEditorInitComplete.addLambda([]() {
            initializeImGuiContext();
            initializeImGuiEditorStyleSet();
        });
    }

    static void shutdownModule() {}
};

IMPLEMENT_MODULE(EditorFrontendModule);

} // namespace
