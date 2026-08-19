// © 2026 Pawel Mlynarz

// pxEngine
#include "common/types.h"

#include "Windows.h"

namespace px {

extern i32 engineMain();

namespace {

i32 launchWindowsStartup(
    [[maybe_unused]] HINSTANCE instance,
    [[maybe_unused]] HINSTANCE prevInstance,
    [[maybe_unused]] char* cmdLine,
    [[maybe_unused]] i32 showCmd
) {

    return engineMain();
}

} // namespace

} // namespace px

int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE prevInstance, _In_ char* cmdLine, _In_ int showCmd) {
    int const result{px::launchWindowsStartup(instance, prevInstance, cmdLine, showCmd)};
    return result;
}
