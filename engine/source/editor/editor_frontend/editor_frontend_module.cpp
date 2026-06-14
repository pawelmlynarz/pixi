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

void InitializeImGuiContext() {
    auto& PixiRenderer{dynamic_cast<Renderer&>(SimpleApplication::Get().GetRenderer())};
    ImGui::SetCurrentContext(static_cast<ImGuiContext*>(PixiRenderer.GetImGuiRenderer().GetImguiContext()));
}

void InitializeImGuiEditorStyleSet() {
    EdStyle::SetDefaultStyle();
}

struct EditorFrontendModule {
    static void StartupModule() {
        CoreDelegates::OnEngineLoopInitComplete.AddLambda([]() {
            InitializeImGuiContext();
            InitializeImGuiEditorStyleSet();
        });
    }

    static void ShutdownModule() {}
};

IMPLEMENT_MODULE(EditorFrontendModule);

} // namespace
