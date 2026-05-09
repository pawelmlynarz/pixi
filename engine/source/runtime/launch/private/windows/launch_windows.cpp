// © 2026 Pawel Mlynarz

// core
#include "common/platform.h"

extern int32 EngineMain();

namespace {
int32 LaunchWindowsStartup(HINSTANCE, HINSTANCE, char *, int32, const TCHAR*) {
    return EngineMain();
}
} // namespace

int32 WINAPI WinMain(_In_ HINSTANCE hInInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ char *pCmdLine, _In_ int nCmdShow) {
    const int32 Result{LaunchWindowsStartup(hInInstance, hPrevInstance, pCmdLine, nCmdShow, nullptr)};
    return Result;
}
