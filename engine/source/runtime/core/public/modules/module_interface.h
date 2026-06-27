// © 2026 Pawel Mlynarz

#pragma once

namespace px {

template <typename TModuleClass>
concept ModuleInterface =
    requires(TModuleClass instance) {
        { instance.startupModule() } -> std::same_as<void>;
        { instance.shutdownModule() } -> std::same_as<void>;
    };

/**
 * Super simple RAII wrapper that calls StartupModule and ShutdownModule.
 */
template <ModuleInterface TModuleClass>
struct ModuleWrapper {
    // NOLINTBEGIN
    ModuleWrapper() { module_.startupModule(); }
    virtual ~ModuleWrapper() { module_.shutdownModule(); }

    TModuleClass module_;
    // NOLINTEND
};

} // namespace px

#define IMPLEMENT_MODULE(ModuleClassName) \
    ModuleWrapper<ModuleClassName> module;
