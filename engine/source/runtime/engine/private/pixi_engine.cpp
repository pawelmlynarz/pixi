// © 2026 Pawel Mlynarz

#include "pixi_engine.h"
#include "pixi_engine_internal.h"

// pxcore
#include "common/platform_time.h"

#include <thread>

namespace px {

namespace {

SharedPtr<PixiEngine> PixiEngineInst{nullptr};

double CurrentRealTime{0.f};
float CurrentDeltaTime{0.f};

constexpr double MaxTickRate{60.0};
constexpr double MinFrameTime{1.0 / MaxTickRate};

} // namespace

int32 InitializeEngine(SharedPtr<PixiEngine> const& Engine) {
    PixiEngineInst = Engine;
    return 0;
}

void DestroyEngine() {
    PixiEngineInst.reset();
}

PixiEngine& GetEngine() {
    Assert(PixiEngineInst != nullptr);
    return *PixiEngineInst;
}

void PixiEngine::UpdateTimeAndHandleMaxTickRate() {
    static double LastRealTime{PlatformTime::Now().AsSeconds() - 0.0001};

    CurrentRealTime = PlatformTime::Now().AsSeconds();
    CurrentDeltaTime = static_cast<float>(CurrentRealTime - LastRealTime);

    Assert(CurrentDeltaTime >= 0);

    if (CurrentDeltaTime < MinFrameTime) {
        double const SleepTime{MinFrameTime - CurrentDeltaTime};

        PX_TODO("Use Platform HAL and improve accuracy");
        std::this_thread::sleep_for(std::chrono::duration<double>(SleepTime));

        CurrentRealTime = PlatformTime::Now().AsSeconds();
        CurrentDeltaTime = static_cast<float>(CurrentRealTime - LastRealTime);
    }

    LastRealTime = CurrentRealTime;
}

float PixiEngine::GetDeltaTime() const {
    return CurrentDeltaTime;
}

float PixiEngine::GetFPS() const {
    return CurrentDeltaTime <= 0.f ? 0.f : 1.0f / CurrentDeltaTime;
}

} // namespace px
