// © 2026 Pawel Mlynarz

// pxcore
#include "common/platform.h"

namespace px {

extern int32 EngineMain();

namespace {

int32 LaunchWindowsStartup(
    [[maybe_unused]] HINSTANCE Instance,
    [[maybe_unused]] HINSTANCE PrevInstance,
    [[maybe_unused]] char* CmdLine,
    [[maybe_unused]] int32 ShowCmd
) {

    return EngineMain();
}

} // namespace

} // namespace px

int WINAPI WinMain(_In_ HINSTANCE Instance, _In_opt_ HINSTANCE PrevInstance, _In_ char* CmdLine, _In_ int ShowCmd) {
    int const Result{px::LaunchWindowsStartup(Instance, PrevInstance, CmdLine, ShowCmd)};
    return Result;
}
