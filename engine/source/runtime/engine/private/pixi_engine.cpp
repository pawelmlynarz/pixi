// © 2026 Pawel Mlynarz

#include "pixi_engine.h"
#include "pixi_engine_internal.h"

// pxcore
#include "hal/platform_time.h"

#include <thread>

namespace px {

namespace {

SharedPtr<PixiEngine> PixiEngineInst{nullptr};

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

    TimingInfo& Info{TimingInfo_};

    Info.CurrentRealTime = PlatformTime::Now().AsSeconds();
    Info.CurrentDeltaTime = static_cast<float>(Info.CurrentRealTime - LastRealTime);

    Assert(Info.CurrentDeltaTime >= 0);

    if (Info.CurrentDeltaTime < MinFrameTime) {
        double const SleepTime{MinFrameTime - Info.CurrentDeltaTime};

        PX_TODO("Use Platform HAL and improve accuracy");
        std::this_thread::sleep_for(std::chrono::duration<double>(SleepTime));

        Info.CurrentRealTime = PlatformTime::Now().AsSeconds();
        Info.CurrentDeltaTime = static_cast<float>(Info.CurrentRealTime - LastRealTime);
    }

    LastRealTime = Info.CurrentRealTime;
}

float PixiEngine::GetDeltaTime() const {
    return TimingInfo_.CurrentDeltaTime;
}

float PixiEngine::GetFPS() const {
    return TimingInfo_.CurrentDeltaTime <= 0.f ? 0.f : 1.0f / TimingInfo_.CurrentDeltaTime;
}

} // namespace px
