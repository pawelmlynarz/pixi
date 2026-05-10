// © 2026 Pawel Mlynarz

// core
#include "common/platform.h"

namespace px {

extern int32 EngineMain();

int32 LaunchWindowsStartup(HINSTANCE, HINSTANCE, char*, int32, const TCHAR*) {
    return EngineMain();
}

} // namespace px

using namespace px;

int32 WINAPI WinMain(_In_ HINSTANCE hInInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ char* pCmdLine, _In_ int nCmdShow) {
    int32 const Result{LaunchWindowsStartup(hInInstance, hPrevInstance, pCmdLine, nCmdShow, nullptr)};
    return Result;
}
