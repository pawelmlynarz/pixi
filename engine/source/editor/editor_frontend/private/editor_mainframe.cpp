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

void BuildMainFrameDockSpaceLayout(ImGuiViewport* const Viewport, ImGuiID const DockSpaceID) {

    ImGui::DockBuilderRemoveNode(DockSpaceID);
    ImGui::DockBuilderAddNode(DockSpaceID, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(DockSpaceID, Viewport->Size);

    std::vector<ImGuiID> DockNodes;
    ImGuiID DockCenterID{DockSpaceID};

    { // Header
        ImGuiID const DockHeaderID{
            ImGui::DockBuilderSplitNode(DockCenterID, ImGuiDir_Up, 0.1f, nullptr, &DockCenterID)
        };
        ImGui::DockBuilderSetNodeSize(DockHeaderID, ImVec2(Viewport->Size.x, 50));
        ImGui::DockBuilderDockWindow(CStr(WID_Header), DockHeaderID);
        ImGui::DockBuilderGetNode(DockHeaderID)->LocalFlags |= ImGuiDockNodeFlags_NoResizeX | ImGuiDockNodeFlags_NoResizeY;
        DockNodes.emplace_back(DockHeaderID);
    }

    { // Footer
        ImGuiID const DockFooterID{
            ImGui::DockBuilderSplitNode(DockCenterID, ImGuiDir_Down, 0.1f, nullptr, &DockCenterID)
        };
        ImGui::DockBuilderSetNodeSize(DockFooterID, ImVec2(Viewport->Size.x, 50));
        ImGui::DockBuilderDockWindow(CStr(WID_Footer), DockFooterID);
        ImGui::DockBuilderGetNode(DockFooterID)->LocalFlags |= ImGuiDockNodeFlags_NoResizeX | ImGuiDockNodeFlags_NoResizeY;
        DockNodes.emplace_back(DockFooterID);
    }

    { // Inspector
        ImGuiID const DockInspectorID{
            ImGui::DockBuilderSplitNode(DockCenterID, ImGuiDir_Right, 0.2f, nullptr, &DockCenterID)
        };
        ImGui::DockBuilderDockWindow(CStr(WID_Inspector), DockInspectorID);
        DockNodes.emplace_back(DockInspectorID);
    }

    ImGuiID const DockBottomID{
        ImGui::DockBuilderSplitNode(DockCenterID, ImGuiDir_Down, 0.25f, nullptr, &DockCenterID)
    };

    { // Console & Asset Browser
        ImGuiID DockConsoleID{};
        ImGuiID const DockAssetBrowserID{
            ImGui::DockBuilderSplitNode(DockBottomID, ImGuiDir_Left, 0.25f, nullptr, &DockConsoleID)
        };
        ImGui::DockBuilderDockWindow(CStr(WID_AssetBrowser), DockAssetBrowserID);
        DockNodes.emplace_back(DockAssetBrowserID);

        ImGui::DockBuilderDockWindow(CStr(WID_Console), DockConsoleID);
        DockNodes.emplace_back(DockConsoleID);
    }

    { // Scene Hierarchy & Viewport
        ImGuiID const DockSceneHierarchyID{
            ImGui::DockBuilderSplitNode(DockCenterID, ImGuiDir_Left, 0.25f, nullptr, &DockCenterID)
        };
        ImGui::DockBuilderDockWindow(CStr(WID_SceneHierarchy), DockSceneHierarchyID);
        DockNodes.emplace_back(DockSceneHierarchyID);

        ImGui::DockBuilderDockWindow(CStr(WID_Viewport), DockCenterID);
        DockNodes.emplace_back(DockCenterID);
    }

#if !WITH_IMGUI_TAB_BARS
    for (auto& DockNodeID : DockNodes) {
        ImGui::DockBuilderGetNode(DockNodeID)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
    }
#endif

    ImGui::DockBuilderFinish(DockSpaceID);
}

void CreateMainFrameDockSpace(ImGuiViewport* const Viewport) {
    ImDockSpaceConfig const DockSpaceConfig{
        .Name = "MainFrameDockSpace",
        .WindowPadding{ImVec2(5.0f, 5.0f)},
        .DockSpaceFlags = ImGuiDockNodeFlags_PassthruCentralNode,
        .HostWindowFlags =
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus,
        .BuildDockSpaceLayoutStrategy = BuildMainFrameDockSpaceLayout
    };
    ImDockSpace const DockSpace{Viewport, DockSpaceConfig};
}

} // namespace

SEditorMainFrame::SEditorMainFrame() {
    Widgets_.emplace_back(MakeUnique<ImHeader>(WID_Header));
    Widgets_.emplace_back(MakeUnique<ImFooter>(WID_Footer));
    Widgets_.emplace_back(MakeUnique<ImAssetBrowser>(WID_AssetBrowser));
    Widgets_.emplace_back(MakeUnique<ImInspector>(WID_Inspector));
    Widgets_.emplace_back(MakeUnique<ImConsole>(WID_Console));
    Widgets_.emplace_back(MakeUnique<ImSceneHierarchy>(WID_SceneHierarchy));
    Widgets_.emplace_back(MakeUnique<ImViewport>(WID_Viewport));
}

SEditorMainFrame::~SEditorMainFrame() = default;

void SEditorMainFrame::DrawImGui() {
    ImGuiViewport* const Viewport{ImGui::GetMainViewport()};
    Assert(Viewport != nullptr);

    CreateMainFrameDockSpace(Viewport);

    for (auto& Widget : Widgets_) {
        Widget->Draw();
    }
}

} // namespace px::ed
