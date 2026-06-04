// © 2026 Pawel Mlynarz

#pragma once

namespace px {

template <typename TModuleClass>
concept ModuleInterface =
    requires(TModuleClass Class) {
        { Class.StartupModule() } -> std::same_as<void>;
        { Class.ShutdownModule() } -> std::same_as<void>;
    };

/**
 * Super simple RAII wrapper that calls StartupModule and ShutdownModule.
 */
template <ModuleInterface TModuleClass>
struct ModuleWrapper {
    ModuleWrapper() { Module_.StartupModule(); }
    virtual ~ModuleWrapper() { Module_.ShutdownModule(); }

    TModuleClass Module_;
};

} // namespace px

#define IMPLEMENT_MODULE(ModuleClassName) \
    ModuleWrapper<ModuleClassName> Module;
