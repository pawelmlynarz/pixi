// © 2026 Pawel Mlynarz

#include "editor_mainframe.h"
#include "editor_const.h"
#include "widgets/dockspace.h"
#include "widgets/panels/common_panels.h"

// imgui
#include "imgui.h"
#include "imgui_internal.h"

// Set to 1 to reveal TabBars (useful for drag & drop widgets repositioning).
#define WITH_IMGUI_TAB_BARS 0

namespace px::ed {

namespace {

void buildMainFrameDockSpaceLayout(ImGuiViewport* const viewport, ImGuiID const dockSpaceId) {

    ImGui::DockBuilderRemoveNode(dockSpaceId);
    ImGui::DockBuilderAddNode(dockSpaceId, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockSpaceId, viewport->Size);

    std::vector<ImGuiID> dockNodes;
    ImGuiID dockCenterId{dockSpaceId};

    { // Header
        ImGuiID const dockHeaderId{
            ImGui::DockBuilderSplitNode(dockCenterId, ImGuiDir_Up, 0.1f, nullptr, &dockCenterId)
        };
        ImGui::DockBuilderSetNodeSize(dockHeaderId, ImVec2(viewport->Size.x, 50));
        ImGui::DockBuilderDockWindow(cStr(widHeader), dockHeaderId);
        ImGui::DockBuilderGetNode(dockHeaderId)->LocalFlags |= ImGuiDockNodeFlags_NoResizeX | ImGuiDockNodeFlags_NoResizeY;
        dockNodes.emplace_back(dockHeaderId);
    }

    { // Footer
        ImGuiID const dockFooterId{
            ImGui::DockBuilderSplitNode(dockCenterId, ImGuiDir_Down, 0.1f, nullptr, &dockCenterId)
        };
        ImGui::DockBuilderSetNodeSize(dockFooterId, ImVec2(viewport->Size.x, 50));
        ImGui::DockBuilderDockWindow(cStr(widFooter), dockFooterId);
        ImGui::DockBuilderGetNode(dockFooterId)->LocalFlags |= ImGuiDockNodeFlags_NoResizeX | ImGuiDockNodeFlags_NoResizeY;
        dockNodes.emplace_back(dockFooterId);
    }

    { // Inspector
        ImGuiID const dockInspectorId{
            ImGui::DockBuilderSplitNode(dockCenterId, ImGuiDir_Right, 0.2f, nullptr, &dockCenterId)
        };
        ImGui::DockBuilderDockWindow(cStr(widInspector), dockInspectorId);
        dockNodes.emplace_back(dockInspectorId);
    }

    ImGuiID const dockBottomId{
        ImGui::DockBuilderSplitNode(dockCenterId, ImGuiDir_Down, 0.25f, nullptr, &dockCenterId)
    };

    { // Console & Asset Browser
        ImGuiID dockConsoleId{};
        ImGuiID const dockAssetBrowserId{
            ImGui::DockBuilderSplitNode(dockBottomId, ImGuiDir_Left, 0.25f, nullptr, &dockConsoleId)
        };
        ImGui::DockBuilderDockWindow(cStr(widAssetBrowser), dockAssetBrowserId);
        dockNodes.emplace_back(dockAssetBrowserId);

        ImGui::DockBuilderDockWindow(cStr(widConsole), dockConsoleId);
        dockNodes.emplace_back(dockConsoleId);
    }

    { // Scene Hierarchy & Viewport
        ImGuiID const dockSceneHierarchyId{
            ImGui::DockBuilderSplitNode(dockCenterId, ImGuiDir_Left, 0.25f, nullptr, &dockCenterId)
        };
        ImGui::DockBuilderDockWindow(cStr(widSceneHierarchy), dockSceneHierarchyId);
        dockNodes.emplace_back(dockSceneHierarchyId);

        ImGui::DockBuilderDockWindow(cStr(widViewport), dockCenterId);
        dockNodes.emplace_back(dockCenterId);
    }

#if !WITH_IMGUI_TAB_BARS
    for (auto& dockNodeId : dockNodes) {
        ImGui::DockBuilderGetNode(dockNodeId)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
    }
#endif

    ImGui::DockBuilderFinish(dockSpaceId);
}

void createMainFrameDockSpace(ImGuiViewport* const viewport) {
    ImDockSpaceConfig const dockSpaceConfig{
        .Name = "MainFrameDockSpace",
        .WindowPadding{ImVec2(5.0f, 5.0f)},
        .DockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode,
        .HostWindowFlags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus,
        .BuildDockSpaceLayoutStrategy = buildMainFrameDockSpaceLayout
    };
    ImDockSpace const dockSpace{viewport, dockSpaceConfig};
}

} // namespace

SEditorMainFrame::SEditorMainFrame() {
    widgets_.emplace_back(makeUnique<ImHeader>(widHeader));
    widgets_.emplace_back(makeUnique<ImFooter>(widFooter));
    widgets_.emplace_back(makeUnique<ImAssetBrowser>(widAssetBrowser));
    widgets_.emplace_back(makeUnique<ImInspector>(widInspector));
    widgets_.emplace_back(makeUnique<ImConsole>(widConsole));
    widgets_.emplace_back(makeUnique<ImSceneHierarchy>(widSceneHierarchy));
    widgets_.emplace_back(makeUnique<ImViewport>(widViewport));
}

SEditorMainFrame::~SEditorMainFrame() = default;

void SEditorMainFrame::drawImGui() {
    ImGuiViewport* const viewport{ImGui::GetMainViewport()};
    pxAssert(viewport != nullptr);

    createMainFrameDockSpace(viewport);

    for (auto& widget : widgets_) {
        widget->draw();
    }
}

} // namespace px::ed
