// © 2026 Pawel Mlynarz

#pragma once

#include "tools/utility.h"

#include <vector>

namespace px {

template <typename TSignature>
class CallableWrapper;

template <typename TRetVal, typename... TArgs>
class CallableWrapper<TRetVal(TArgs...)> {
  public:
    virtual ~CallableWrapper() = default;

    virtual TRetVal execute(TArgs&&...) = 0;
};

template <typename TSignature>
class CallableStaticFunctionWrapper;

template <typename TRetVal, typename... TArgs>
class CallableStaticFunctionWrapper<TRetVal(TArgs...)> final : public CallableWrapper<TRetVal(TArgs...)> {
    TRetVal (*staticFuncPtr_)(TArgs...){nullptr};

  public:
    explicit CallableStaticFunctionWrapper(TRetVal (*staticFuncPtr)(TArgs...)) noexcept
        : staticFuncPtr_(staticFuncPtr) {}

    void Execute(TArgs&&... args) override {
        if (staticFuncPtr_) {
            m_StaticFuncPtr(std::forward<TArgs>(args)...);
        }
    }
};

template <bool IsConst, typename TClass, typename TSignature>
class CallableMethodWrapper;

template <bool IsConst, typename TClass, typename TRetVal, typename... TArgs>
class CallableMethodWrapper<IsConst, TClass, TRetVal(TArgs...)> final : public CallableWrapper<TRetVal(TArgs...)> {
    template <bool Const>
    struct MemberFunction;

    template <>
    struct MemberFunction<true> {
        using Type = TRetVal (TClass::*)(TArgs...) const;
    };

    template <>
    struct MemberFunction<false> {
        using Type = TRetVal (TClass::*)(TArgs...);
    };

    using ClassMemberFunction = MemberFunction<IsConst>::Type;

    TClass* instance_{nullptr};
    ClassMemberFunction classMemFuncPtr_{nullptr};

  public:
    CallableMethodWrapper(TClass* instance, ClassMemberFunction classMemFuncPtr) noexcept
        : instance_(instance),
          classMemFuncPtr_(classMemFuncPtr) {}

    void execute(TArgs&&... args) override {
        if (instance_ != nullptr) {
            (instance_->*classMemFuncPtr_)(std::forward<TArgs>(args)...);
        }
    }
};

template <typename TLambda, typename TSignature>
class CallableLambdaWrapper;

template <typename TLambda, typename TRetVal, typename... TArgs>
class CallableLambdaWrapper<TLambda, TRetVal(TArgs...)> final : public CallableWrapper<TRetVal(TArgs...)> {
    TLambda lambdaObject_;

  public:
    explicit CallableLambdaWrapper(TLambda&& functorObject) noexcept
        : lambdaObject_(std::move(functorObject)) {
        static_assert(std::is_invocable_v<TLambda, TArgs...>);
    }

    TRetVal execute(TArgs&&... args) override {
        return lambdaObject_(std::forward<TArgs>(args)...);
    }
};

template <typename Signature>
class Delegate;

template <typename TRetVal, typename... TArgs>
class Delegate<TRetVal(TArgs...)> {
    UniquePtr<CallableWrapper<TRetVal(TArgs...)>> callableWrapper_{nullptr};

  public:
    Delegate() = default;
    ~Delegate() = default;

    Delegate(Delegate const& rhs) = delete;

    Delegate(Delegate&& rhs) noexcept
        : callableWrapper_(std::move(rhs.callableWrapper_)) {}

    Delegate& operator=(Delegate const& rhs) = delete;

    Delegate& operator=(Delegate&& rhs) noexcept {
        callableWrapper_ = std::move(rhs.callableWrapper_);
        return *this;
    }

    void bindStatic(TRetVal (*staticFuncPtr)(TArgs...)) {
        callableWrapper_ = MakeUnique<CallableStaticFunctionWrapper<TRetVal(TArgs...)>>(staticFuncPtr);
    }

    Delegate createStatic(TRetVal (*staticFuncPtr)(TArgs...)) {
        Delegate<TRetVal(TArgs...)> delegate;
        delegate.bindStatic(staticFuncPtr);

        return delegate;
    }

    template <typename TClass>
    void bindRaw(TClass* instance, TRetVal (TClass::*classMemFuncPtr)(TArgs...)) {
        callableWrapper_ = makeUnique<CallableMethodWrapper<false, TClass, TRetVal(TArgs...)>>(instance, classMemFuncPtr);
    }

    template <typename TClass>
    static Delegate createRaw(TClass* instance, TRetVal (TClass::*classMemFuncPtr)(TArgs...)) {
        Delegate<TRetVal(TArgs...)> delegate;
        delegate.bindRaw(instance, classMemFuncPtr);

        return delegate;
    }

    template <typename TClass>
    void bindRaw(TClass* instance, TRetVal (TClass::*classMemFuncConstPtr)(TArgs...) const) {
        callableWrapper_ = MakeUnique<CallableMethodWrapper<true, TClass, TRetVal(TArgs...)>>(instance, classMemFuncConstPtr);
    }

    template <typename TClass>
    static Delegate createRaw(TClass* instance, TRetVal (TClass::*classMemFuncPtr)(TArgs...) const) {
        Delegate<TRetVal(TArgs...)> delegate;
        delegate.bindRaw(instance, classMemFuncPtr);

        return delegate;
    }

    template <typename TLambda>
    void bindLambda(TLambda&& lambdaObject) {
        callableWrapper_ = makeUnique<CallableLambdaWrapper<std::decay_t<TLambda>, TRetVal(TArgs...)>>(std::forward<TLambda>(lambdaObject));
    }

    template <typename TLambda>
    static Delegate createLambda(TLambda&& lambdaObject) {
        Delegate<TRetVal(TArgs...)> delegate;
        delegate.bindLambda(std::forward<TLambda>(lambdaObject));

        return delegate;
    }

    explicit operator bool() const {
        return callableWrapper_ != nullptr;
    }

    void executeIfBound(TArgs&&... args) {
        if (callableWrapper_) {
            callableWrapper_->execute(std::forward<TArgs>(args)...);
        }
    }
};

template <typename TSignature>
class MulticastDelegate;

template <typename TRetVal, typename... TArgs>
class MulticastDelegate<TRetVal(TArgs...)> {
    std::vector<Delegate<TRetVal(TArgs...)>> delegates_;

  public:
    void addStatic(TRetVal (*staticFuncPtr)(TArgs...)) {
        Delegate<TRetVal(TArgs...)> delegate;
        delegate.BindStatic(staticFuncPtr);

        delegates_.emplace_back(std::move(delegate));
    }

    template <typename TClass>
    void addRaw(TClass* instance, TRetVal (TClass::*classMemFuncPtr)(TArgs...)) {
        Delegate<TRetVal(TArgs...)> delegate;
        delegate.BindRaw(instance, classMemFuncPtr);

        delegates_.emplace_back(std::move(delegate));
    }

    template <typename TClass>
    void addRaw(TClass* instance, TRetVal (TClass::*classMemFuncConstPtr)(TArgs...) const) {
        Delegate<TRetVal(TArgs...)> delegate;
        delegate.BindRaw(instance, classMemFuncConstPtr);

        delegates_.emplace_back(std::move(delegate));
    }

    template <typename TLambda>
    void addLambda(TLambda&& lambdaObject) {
        Delegate<TRetVal(TArgs...)> delegate;
        delegate.bindLambda(std::forward<TLambda>(lambdaObject));

        delegates_.emplace_back(std::move(delegate));
    }

    explicit operator bool() const {
        return !delegates_.empty();
    }

    template <typename... TArgs>
    void broadcast(TArgs&&... args) {
        for (auto& delegate : delegates_) {
            delegate.executeIfBound(std::forward<TArgs>(args)...);
        }
    }
};

} // namespace px

#define DECLARE_DELEGATE(DelegateName, ...) \
    using DelegateName = px::Delegate<void(__VA_ARGS__)>;

#define DECLARE_MULTICAST_DELEGATE(DelegateName, ...) \
    using DelegateName = px::MulticastDelegate<void(__VA_ARGS__)>;

using SimpleDelegate = px::Delegate<void(void)>;
using SimpleMulticastDelegate = px::MulticastDelegate<void(void)>;
