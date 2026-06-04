// © 2026 Pawel Mlynarz

// pxcore
#include "misc/core_delegates.h"
#include "modules/module_interface.h"

// pxfrontend
#include "app/pixi_application.h"
#include "rendering/renderer.h"
#include "rendering/imgui_renderer.h"

namespace px {

struct EditorCoreModule {
    void StartupModule() {
        CoreDelegates::OnEngineLoopInitComplete.AddLambda([]() {
            // Init ImGuiContext for this module.
            auto& PixiRenderer{dynamic_cast<Renderer&>(SimpleApplication::Get().GetRenderer())};
            ImGui::SetCurrentContext(static_cast<ImGuiContext*>(PixiRenderer.GetImGuiRenderer().GetImguiContext()));
        });
    }

    void ShutdownModule() {}
};

IMPLEMENT_MODULE(EditorCoreModule);

} // namespace px
