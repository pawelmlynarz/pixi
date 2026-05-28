// © 2026 Pawel Mlynarz

#include "widgets/swindow.h"
#include "app/base_application.h"
#include "rendering/base_renderer.h"

// pxcore
#include "window/generic_window.h"

namespace px {

void SWindow::SetNativeWindow(WeakPtr<GenericWindow> const& NativeWindow) {
    NativeWindow_ = NativeWindow;
}

SharedPtr<GenericWindow> SWindow::GetNativeWindow() const {
    return NativeWindow_.lock();
}

void SWindow::ShowWindow() {
    if (!bHasEverBeenShown_) {
        BaseApplication::Get().GetRenderer().CreateViewport(SharedThis(this));
    }

    if (SharedPtr const NativeWindow{NativeWindow_.lock()}; NativeWindow != nullptr) {
        NativeWindow->Show();
    }

    bHasEverBeenShown_ = true;
}

void SWindow::HideWindow() {
    if (SharedPtr Window{NativeWindow_.lock()}) {
        Window->Hide();
    }
}

void SWindow::DestoryNativeWindow() {
    if (SharedPtr Window{NativeWindow_.lock()}) {
        Window->DestroyWindow();
    }
}

void SWindow::Draw() {
}

} // namespace px
