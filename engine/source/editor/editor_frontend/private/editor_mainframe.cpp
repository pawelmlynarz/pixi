// © 2026 Pawel Mlynarz

#include "editor_mainframe.h"

// pxfrontend
#include "pixi_editor_engine.h"

// imgui
#include "imgui.h"
#include "imgui_internal.h"

namespace px::ed {

namespace {

using WidgetName = char const*;

WidgetName NameHeader{"Header"};
WidgetName NameInspector{"Inspector"};
WidgetName NameAssetBrowser{"AssetBrowser"};
WidgetName NameConsole{"Console"};
WidgetName NameFooter{"Footer"};
WidgetName NameSceneHierarchy{"SceneHierarchy"};
WidgetName NameViewport{"Viewport"};

ImGuiID CreateDockSpace(ImGuiViewport const* const Viewport) {
    ImGuiDockNodeFlags DockSpaceFlags{ImGuiDockNodeFlags_PassthruCentralNode};
    ImGuiWindowFlags HostWindowFlags{0};

    ImGui::SetNextWindowPos(Viewport->WorkPos);
    ImGui::SetNextWindowSize(Viewport->WorkSize);
    ImGui::SetNextWindowViewport(Viewport->ID);

    HostWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
    HostWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    if (DockSpaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) {
        HostWindowFlags |= ImGuiWindowFlags_NoBackground;
    }

    ImGuiID const DockSpaceID{ImGui::GetID("DockSpace")};

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("MainFrameDockSpace", nullptr, HostWindowFlags);
    {
        ImGuiIO& IO{ImGui::GetIO()};
        Assert(IO.ConfigFlags & ImGuiConfigFlags_DockingEnable);
        ImGui::DockSpace(DockSpaceID, ImVec2(0.0f, 0.0f), DockSpaceFlags, nullptr);
    }
    ImGui::End();
    ImGui::PopStyleVar(3);

    return DockSpaceID;
}

void SetDefaultDockSpaceLayout(ImGuiViewport* const Viewport, ImGuiID const DockspaceID) {
    ImGui::DockBuilderRemoveNode(DockspaceID);
    ImGui::DockBuilderAddNode(DockspaceID, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(DockspaceID, Viewport->Size);

    ImGuiID DockCenterID{DockspaceID};

    ImGuiID DockUpID{ImGui::DockBuilderSplitNode(
        DockCenterID,
        ImGuiDir_Up,
        0.1f,
        nullptr,
        &DockCenterID
    )};
    ImGui::DockBuilderSetNodeSize(DockUpID, ImVec2(Viewport->Size.x, 50));

    ImGuiID DockFooterID{ImGui::DockBuilderSplitNode(
        DockCenterID,
        ImGuiDir_Down,
        0.1f,
        nullptr,
        &DockCenterID
    )};

    ImGuiID DockRightID{ImGui::DockBuilderSplitNode(
        DockCenterID,
        ImGuiDir_Right,
        0.2f,
        nullptr,
        &DockCenterID
    )};

    ImGuiID DockBottomID{ImGui::DockBuilderSplitNode(
        DockCenterID,
        ImGuiDir_Down,
        0.25f,
        nullptr,
        &DockCenterID
    )};

    ImGuiID DockBottomRightID;
    ImGuiID DockBottomLeftID{ImGui::DockBuilderSplitNode(
        DockBottomID,
        ImGuiDir_Left,
        0.25f,
        nullptr,
        &DockBottomRightID
    )};

    ImGuiID DockLeftID{ImGui::DockBuilderSplitNode(
        DockCenterID,
        ImGuiDir_Left,
        0.25f,
        nullptr,
        &DockCenterID
    )};

    ImGui::DockBuilderDockWindow(NameHeader, DockUpID);
    ImGui::DockBuilderGetNode(DockUpID)->LocalFlags |=
        ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResizeX | ImGuiDockNodeFlags_NoResizeY;

    ImGui::DockBuilderDockWindow(NameInspector, DockRightID);
    ImGui::DockBuilderGetNode(DockRightID)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;

    ImGui::DockBuilderDockWindow(NameAssetBrowser, DockBottomLeftID);
    ImGui::DockBuilderGetNode(DockBottomLeftID)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
    
    ImGui::DockBuilderDockWindow(NameConsole, DockBottomRightID);
    ImGui::DockBuilderGetNode(DockBottomRightID)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
    
    ImGui::DockBuilderDockWindow(NameFooter, DockFooterID);
    ImGui::DockBuilderGetNode(DockFooterID)->LocalFlags |=
        ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoResizeX | ImGuiDockNodeFlags_NoResizeY;

    ImGui::DockBuilderDockWindow(NameSceneHierarchy, DockLeftID);
    ImGui::DockBuilderGetNode(DockLeftID)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
    
    ImGui::DockBuilderDockWindow(NameViewport, DockCenterID);
    ImGui::DockBuilderGetNode(DockCenterID)->LocalFlags |= ImGuiDockNodeFlags_NoTabBar;
    
    ImGui::DockBuilderFinish(DockspaceID);
}

} // namespace

void SEditorMainFrame::DrawImGui() {
    ImGuiViewport* const Viewport{ImGui::GetMainViewport()};
    Assert(Viewport != nullptr);

    ImGuiID const DockspaceID{CreateDockSpace(Viewport)};

    static bool bFistTime{true};
    if (bFistTime) {
        SetDefaultDockSpaceLayout(Viewport, DockspaceID);
        bFistTime = false;
    }

    ImGuiWindowFlags constexpr WindowFlags{
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus
    };

    ImGui::Begin(NameHeader, nullptr, WindowFlags);
    {
    }
    ImGui::End();

    ImGui::Begin(NameSceneHierarchy, nullptr, WindowFlags);
    {
    }
    ImGui::End();

    ImGui::Begin(NameViewport, nullptr, WindowFlags);
    {
    }
    ImGui::End();

    ImGui::Begin(NameInspector, nullptr, WindowFlags);
    {
    }
    ImGui::End();

    ImGui::Begin(NameAssetBrowser, nullptr, WindowFlags);
    {
    }
    ImGui::End();

    ImGui::Begin(NameConsole, nullptr, WindowFlags);
    {
    }
    ImGui::End();

    ImGui::Begin(NameFooter, nullptr, WindowFlags);
    {
    }
    ImGui::End();
}

} // namespace px::ed
