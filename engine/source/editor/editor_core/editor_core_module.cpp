// © 2026 Pawel Mlynarz

// pxcore
#include "misc/core_delegates.h"
#include "modules/module_interface.h"

// pxfrontend
#include "app/pixi_application.h"
#include "rendering/renderer.h"
#include "rendering/imgui_renderer.h"

// imgui
#include "imgui.h"

namespace {

struct EditorCoreModule {
    static void StartupModule() {
        using namespace px;
    
        CoreDelegates::OnEngineLoopInitComplete.AddLambda([]() {
            // Init ImGuiContext for this module.
            auto& PixiRenderer{dynamic_cast<Renderer&>(SimpleApplication::Get().GetRenderer())};
            ImGui::SetCurrentContext(static_cast<ImGuiContext*>(PixiRenderer.GetImGuiRenderer().GetImguiContext()));
        });
    }

    static void ShutdownModule() {}
};

px::IMPLEMENT_MODULE(EditorCoreModule);

} // namespace
