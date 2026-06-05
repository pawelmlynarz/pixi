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

    virtual TRetVal Execute(TArgs&&...) = 0;
};

template <typename TSignature>
class CallableStaticFunctionWrapper;

template <typename TRetVal, typename... TArgs>
class CallableStaticFunctionWrapper<TRetVal(TArgs...)> final : public CallableWrapper<TRetVal(TArgs...)> {
    TRetVal (*StaticFuncPtr_)(TArgs...){nullptr};

  public:
    explicit CallableStaticFunctionWrapper(TRetVal (*StaticFuncPtr)(TArgs...)) noexcept
        : StaticFuncPtr_(StaticFuncPtr) {}

    void Execute(TArgs&&... Args) override {
        if (StaticFuncPtr_) {
            m_StaticFuncPtr(std::forward<TArgs>(Args)...);
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

    TClass* Instance_{nullptr};
    ClassMemberFunction ClassMemFuncPtr_{nullptr};

  public:
    CallableMethodWrapper(TClass* Instance, ClassMemberFunction ClassMemFuncPtr) noexcept
        : Instance_(Instance),
          ClassMemFuncPtr_(ClassMemFuncPtr) {}

    void Execute(TArgs&&... Args) override {
        if (Instance_ != nullptr) {
            (Instance_->*ClassMemFuncPtr_)(std::forward<TArgs>(Args)...);
        }
    }
};

template <typename TLambda, typename TSignature>
class CallableLambdaWrapper;

template <typename TLambda, typename TRetVal, typename... TArgs>
class CallableLambdaWrapper<TLambda, TRetVal(TArgs...)> final : public CallableWrapper<TRetVal(TArgs...)> {
    TLambda LambdaObject_;

  public:
    explicit CallableLambdaWrapper(TLambda&& FunctorObject) noexcept
        : LambdaObject_(std::move(FunctorObject)) {
        static_assert(std::is_invocable_v<TLambda, TArgs...>);
    }

    TRetVal Execute(TArgs&&... Args) override {
        return LambdaObject_(std::forward<TArgs>(Args)...);
    }
};

template <typename Signature>
class Delegate;

template <typename TRetVal, typename... TArgs>
class Delegate<TRetVal(TArgs...)> {
    UniquePtr<CallableWrapper<TRetVal(TArgs...)>> CallableWrapper_{nullptr};

  public:
    Delegate() = default;
    ~Delegate() = default;

    Delegate(Delegate const& Rhs) = delete;

    Delegate(Delegate&& Rhs) noexcept
        : CallableWrapper_(std::move(Rhs.CallableWrapper_)) {}

    Delegate& operator=(Delegate const& Rhs) = delete;

    Delegate& operator=(Delegate&& Rhs) noexcept {
        CallableWrapper_ = std::move(Rhs.CallableWrapper_);
        return *this;
    }

    void BindStatic(TRetVal (*StaticFuncPtr)(TArgs...)) {
        CallableWrapper_ = MakeUnique<CallableStaticFunctionWrapper<TRetVal(TArgs...)>>(StaticFuncPtr);
    }

    Delegate CreateStatic(TRetVal (*StaticFuncPtr)(TArgs...)) {
        Delegate<TRetVal(TArgs...)> Delegate_;
        Delegate_.BindStatic(StaticFuncPtr);

        return Delegate_;
    }

    template <typename TClass>
    void BindRaw(TClass* Instance, TRetVal (TClass::*ClassMemFuncPtr)(TArgs...)) {
        CallableWrapper_ = MakeUnique<CallableMethodWrapper<false, TClass, TRetVal(TArgs...)>>(Instance, ClassMemFuncPtr);
    }

    template <typename TClass>
    static Delegate CreateRaw(TClass* Instance, TRetVal (TClass::*ClassMemFuncPtr)(TArgs...)) {
        Delegate<TRetVal(TArgs...)> Delegate_;
        Delegate_.BindRaw(Instance, ClassMemFuncPtr);

        return Delegate_;
    }

    template <typename TClass>
    void BindRaw(TClass* Instance, TRetVal (TClass::*ClassMemFuncConstPtr)(TArgs...) const) {
        CallableWrapper_ = MakeUnique<CallableMethodWrapper<true, TClass, TRetVal(TArgs...)>>(Instance, ClassMemFuncConstPtr);
    }

    template <typename TClass>
    static Delegate CreateRaw(TClass* Instance, TRetVal (TClass::*ClassMemFuncPtr)(TArgs...) const) {
        Delegate<TRetVal(TArgs...)> Delegate_;
        Delegate_.BindRaw(Instance, ClassMemFuncPtr);

        return Delegate_;
    }

    template <typename TLambda>
    void BindLambda(TLambda&& LambdaObject) {
        CallableWrapper_ = MakeUnique<CallableLambdaWrapper<std::decay_t<TLambda>, TRetVal(TArgs...)>>(std::forward<TLambda>(LambdaObject));
    }

    template <typename TLambda>
    static Delegate CreateLambda(TLambda&& LambdaObject) {
        Delegate<TRetVal(TArgs...)> Delegate_;
        Delegate_.BindLambda(std::forward<TLambda>(LambdaObject));

        return Delegate_;
    }

    explicit operator bool() const {
        return CallableWrapper_ != nullptr;
    }

    void ExecuteIfBound(TArgs&&... Args) {
        if (CallableWrapper_) {
            CallableWrapper_->Execute(std::forward<TArgs>(Args)...);
        }
    }
};

template <typename TSignature>
class MulticastDelegate;

template <typename TRetVal, typename... TArgs>
class MulticastDelegate<TRetVal(TArgs...)> {
    std::vector<Delegate<TRetVal(TArgs...)>> Delegates_;

  public:
    void AddStatic(TRetVal (*StaticFuncPtr)(TArgs...)) {
        Delegate<TRetVal(TArgs...)> Delegate_;
        Delegate_.BindStatic(StaticFuncPtr);

        Delegates_.emplace_back(std::move(Delegate_));
    }

    template <typename TClass>
    void AddRaw(TClass* Instance, TRetVal (TClass::*ClassMemFuncPtr)(TArgs...)) {
        Delegate<TRetVal(TArgs...)> Delegate_;
        Delegate_.BindRaw(Instance, ClassMemFuncPtr);

        Delegates_.emplace_back(std::move(Delegate_));
    }

    template <typename TClass>
    void AddRaw(TClass* Instance, TRetVal (TClass::*ClassMemFuncConstPtr)(TArgs...) const) {
        Delegate<TRetVal(TArgs...)> Delegate_;
        Delegate_.BindRaw(Instance, ClassMemFuncConstPtr);

        Delegates_.emplace_back(std::move(Delegate_));
    }

    template <typename TLambda>
    void AddLambda(TLambda&& LambdaObject) {
        Delegate<TRetVal(TArgs...)> Delegate_;
        Delegate_.BindLambda(std::forward<TLambda>(LambdaObject));

        Delegates_.emplace_back(std::move(Delegate_));
    }

    explicit operator bool() const {
        return !Delegates_.empty();
    }

    template <typename... TArgs>
    void Broadcast(TArgs&&... Args) {
        for (auto& Delegate_ : Delegates_) {
            Delegate_.ExecuteIfBound(std::forward<TArgs>(Args)...);
        }
    }
};

} // namespace px

#define DECLARE_DELEGATE(DelegateName, ...) \
    using DelegateName = px::Delegate<void(__VA_ARGS__)>;

#define DECLARE_MULTICAST_DELEGATE(DelegateName, ...) \
    using DelegateName = px::MulticastDelegate<void(__VA_ARGS__)>;

using SimpleDelegate = px::Delegate<void(void)>;
