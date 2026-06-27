// © 2026 Pawel Mlynarz

#pragma once

namespace px {

template <typename TModuleClass>
concept ModuleInterface =
    requires(TModuleClass Class) {
        { Class.startupModule() } -> std::same_as<void>;
        { Class.shutdownModule() } -> std::same_as<void>;
    };

/**
 * Super simple RAII wrapper that calls StartupModule and ShutdownModule.
 */
template <ModuleInterface TModuleClass>
struct ModuleWrapper {
    // NOLINTBEGIN
    ModuleWrapper() { Module_.startupModule(); }
    virtual ~ModuleWrapper() { Module_.shutdownModule(); }

    TModuleClass Module_;
    // NOLINTEND
};

} // namespace px

#define IMPLEMENT_MODULE(ModuleClassName) \
    ModuleWrapper<ModuleClassName> Module;
