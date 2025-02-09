#pragma once
#include <functional>
#include <bits/move.h>
#include <type_traits>

namespace kilo {
    template<class>
    class func_base;

    template<class R, class... Args>
    class func_base<R(Args...)> {
    public:
        virtual ~func_base() = default;

        virtual func_base *clone() const = 0;

        virtual void destroy() noexcept = 0;

        virtual R operator()(Args &&...) const = 0;
    };

    template<class, class>
    class func;

    template<class F, class R, class... Args>
    class func<F, R(Args...)> final : public func_base<R(Args...)> {
    private:
        F callable;

    public:
        explicit func(const F &f) : callable(f) {
        }

        explicit func(F &&f) noexcept : callable(std::move(f)) {
        }

        func_base<R(Args...)> *clone() const override {
            return new func(callable);
        }

        void destroy() noexcept override {
            delete this;
        }

        R operator()(Args &&... args) const override {
            return callable(std::forward<Args>(args)...);
        }
    };

    template<class>
    class function;

    template<class R, class... Args>
    class function<R(Args...)> {
    public:
        using base_type = func_base<R(Args...)>;

        base_type *fptr{nullptr};

        function() = default;

        template<class F, class DecayF = typename std::decay<F>::type>
        explicit function(F &&f) {
            // 处理传入的可调用对象为空的情况
            if constexpr (std::is_invocable_v<DecayF, Args...>) {
                using func_type = func<DecayF, R(Args...)>;
                fptr = new func_type(std::forward<F>(f));
            }
        }

        // 拷贝构造函数
        function(const function &other) {
            if (other.fptr != nullptr) {
                fptr = other.fptr->clone();
            }
        }

        // 移动构造函数
        function(function &&other) noexcept {
            fptr = other.fptr;
            other.fptr = nullptr;
        }

        // 析构函数
        ~function() {
            if (fptr != nullptr) {
                fptr->destroy();
            }
        }

        // 拷贝赋值运算符
        function& operator=(const function &other) {
            if (this != &other) {
                if (fptr != nullptr) {
                    fptr->destroy();
                }
                if (other.fptr != nullptr) {
                    fptr = other.fptr->clone();
                } else {
                    fptr = nullptr;
                }
            }
            return *this;
        }

        // 移动赋值运算符
        function& operator=(function &&other) noexcept {
            if (this != &other) {
                if (fptr != nullptr) {
                    fptr->destroy();
                }
                fptr = other.fptr;
                other.fptr = nullptr;
            }
            return *this;
        }

        R operator()(Args &&... args) const {
            if (fptr != nullptr) {
                return fptr->operator()(std::forward<Args>(args)...);
            }
            throw std::bad_function_call();
        }
    };
}