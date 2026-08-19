// © 2026 Pawel Mlynarz

#include "pixi_engine.h"
#include "pixi_engine_internal.h"
#include "hal/platform_time.h"

#include <thread>

namespace px {

namespace {

SharedPtr<PixiEngine> sPixiEngine{nullptr};

constexpr f64 maxTickRate{60.0};
constexpr f64 minFrameTime{1.0 / maxTickRate};

} // namespace

i32 initializeEngine(SharedPtr<PixiEngine> const& engine) {
    sPixiEngine = engine;
    return 0;
}

void destroyEngine() {
    sPixiEngine.reset();
}

PixiEngine& getEngine() {
    pxAssert(sPixiEngine != nullptr);
    return *sPixiEngine;
}

void PixiEngine::updateTimeAndHandleMaxTickRate() {
    static f64 lastRealTime{PlatformTime::now().asSeconds() - 0.0001};

    TimingInfo& info{TimingInfo_};

    info.CurrentRealTime = PlatformTime::now().asSeconds();
    info.CurrentDeltaTime = static_cast<f32>(info.CurrentRealTime - lastRealTime);

    pxAssert(info.CurrentDeltaTime >= 0);

    if (info.CurrentDeltaTime < minFrameTime) {
        f64 const sleepTime{minFrameTime - info.CurrentDeltaTime};

        pxToDo("Use Platform HAL and improve accuracy");
        std::this_thread::sleep_for(std::chrono::duration<f64>(sleepTime));

        info.CurrentRealTime = PlatformTime::now().asSeconds();
        info.CurrentDeltaTime = static_cast<f32>(info.CurrentRealTime - lastRealTime);
    }

    lastRealTime = info.CurrentRealTime;
}

f32 PixiEngine::getDeltaTime() const {
    return TimingInfo_.CurrentDeltaTime;
}

f32 PixiEngine::getFps() const {
    return TimingInfo_.CurrentDeltaTime <= 0.f ? 0.f : 1.0f / TimingInfo_.CurrentDeltaTime;
}

} // namespace px
