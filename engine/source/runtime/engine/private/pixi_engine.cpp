// © 2026 Pawel Mlynarz

#include "pixi_engine.h"
#include "pixi_engine_internal.h"
#include "hal/platform_time.h"

#include <thread>

namespace px {

namespace {

SharedPtr<PixiEngine> pixiEngineInst{nullptr};

constexpr double maxTickRate{60.0};
constexpr double minFrameTime{1.0 / maxTickRate};

} // namespace

int32 initializeEngine(SharedPtr<PixiEngine> const& engine) {
    pixiEngineInst = engine;
    return 0;
}

void destroyEngine() {
    pixiEngineInst.reset();
}

PixiEngine& getEngine() {
    pxAssert(pixiEngineInst != nullptr);
    return *pixiEngineInst;
}

void PixiEngine::updateTimeAndHandleMaxTickRate() {
    static double lastRealTime{PlatformTime::now().asSeconds() - 0.0001};

    TimingInfo& info{TimingInfo_};

    info.CurrentRealTime = PlatformTime::now().asSeconds();
    info.CurrentDeltaTime = static_cast<float>(info.CurrentRealTime - lastRealTime);

    pxAssert(info.CurrentDeltaTime >= 0);

    if (info.CurrentDeltaTime < minFrameTime) {
        double const sleepTime{minFrameTime - info.CurrentDeltaTime};

        pxToDo("Use Platform HAL and improve accuracy");
        std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));

        info.CurrentRealTime = PlatformTime::now().asSeconds();
        info.CurrentDeltaTime = static_cast<float>(info.CurrentRealTime - lastRealTime);
    }

    lastRealTime = info.CurrentRealTime;
}

float PixiEngine::getDeltaTime() const {
    return TimingInfo_.CurrentDeltaTime;
}

float PixiEngine::getFps() const {
    return TimingInfo_.CurrentDeltaTime <= 0.f ? 0.f : 1.0f / TimingInfo_.CurrentDeltaTime;
}

} // namespace px
