
#pragma once

#include "OpaqueHandle.h"
#include "Optional.h"
#include <chrono>
#include <cstdlib>
#include <functional>
#include <memory>
#include <new>
#include <type_traits>

namespace ffi
{

template<typename T, class SfinaePlaceholder = void>
struct Conversion {
    static T
    toFfi(const T& t) {
        return t;
    }

    static T
    toFfi(T&& t) {
        return t;
    }

    static T
    toCpp(const T& t) {
        return t;
    }
};

template<class T>
struct Conversion<T, typename std::enable_if<std::is_class<T>::value>::type> {
    static FfiOpaqueHandle
    toFfi(const T& t) {
        return reinterpret_cast<FfiOpaqueHandle>(new (std::nothrow) T(t));
    }

    static FfiOpaqueHandle
    toFfi(T&& t) {
        return reinterpret_cast<FfiOpaqueHandle>(new (std::nothrow) T(std::forward<T>(t)));
    }

    static T
    toCpp(FfiOpaqueHandle ref) {
        return *reinterpret_cast<T*>(ref);
    }
};

template<class T>
struct Conversion<std::shared_ptr<T>, typename std::enable_if<std::is_class<std::shared_ptr<T>>::value>::type> {
    static FfiOpaqueHandle
    toFfi(const std::shared_ptr<T>& ptr) {
        return ptr ? reinterpret_cast<FfiOpaqueHandle>(new (std::nothrow) std::shared_ptr<T>(ptr)) : 0;
    }

    static FfiOpaqueHandle
    toFfi(std::shared_ptr<T>&& ptr) {
        return ptr ? reinterpret_cast<FfiOpaqueHandle>(new (std::nothrow) std::shared_ptr<T>(std::forward<std::shared_ptr<T>>(ptr))) : 0;
    }

    static std::shared_ptr<T>
    toCpp(FfiOpaqueHandle ref) {
        return ref ? *reinterpret_cast<std::shared_ptr<T>*>(ref) : std::shared_ptr<T>{};
    }
};

template<typename T>
struct Conversion<optional<T>, typename std::enable_if<std::is_class<optional<T>>::value>::type> {
    static FfiOpaqueHandle
    toFfi(optional<T> t) {
        return t
            ? reinterpret_cast<FfiOpaqueHandle>(new (std::nothrow) optional<T>(std::move(t)))
            : 0;
    }

    static optional<T>
    toCpp(const FfiOpaqueHandle& handle) {
        return handle
            ? *reinterpret_cast<optional<T>*>(handle)
            : optional<T>{};
    }
};

template<class T>
struct Conversion<T, typename std::enable_if<std::is_enum<T>::value>::type> {
    static uint32_t
    toFfi(const T& t) {
        return static_cast<uint32_t>(t);
    }

    static uint32_t
    toFfi(T&& t) {
        return static_cast<uint32_t>(t);
    }

    static T
    toCpp(uint32_t ref) {
        return static_cast<T>(ref);
    }
};

template<class Clock, class Duration>
struct Conversion<
    std::chrono::time_point<Clock, Duration>,
    typename std::enable_if<std::is_class<std::chrono::time_point<Clock, Duration>>::value>::type
> {
    static uint64_t
    toFfi(const std::chrono::time_point<Clock, Duration>& t) {
        using namespace std::chrono;
        return duration_cast<microseconds>(t.time_since_epoch()).count();
    }

    static uint64_t
    toFfi(std::chrono::time_point<Clock, Duration>&& t) {
        using namespace std::chrono;
        return duration_cast<microseconds>(t.time_since_epoch()).count();
    }

    static std::chrono::time_point<Clock, Duration>
    toCpp(uint64_t t) {
        using namespace std::chrono;
        return time_point<Clock, Duration>(duration_cast<Duration>(microseconds(t)));
    }
};

template<class Clock, class Duration>
struct Conversion<
    optional<std::chrono::time_point<Clock, Duration>>,
    typename std::enable_if<std::is_class<optional<std::chrono::time_point<Clock, Duration>>>::value>::type
> {
    static FfiOpaqueHandle
    toFfi(optional<std::chrono::time_point<Clock, Duration>> t) {
        return t
            ? reinterpret_cast<FfiOpaqueHandle>(
                new (std::nothrow) optional<uint64_t>(
                    Conversion<std::chrono::time_point<Clock, Duration>>::toFfi(*t)
                )
            ) : 0;
    }

    static optional<std::chrono::time_point<Clock, Duration>>
    toCpp(const FfiOpaqueHandle& handle) {
        return handle
            ? optional<std::chrono::time_point<Clock, Duration>>(
                Conversion<std::chrono::time_point<Clock, Duration>>::toCpp(
                    **reinterpret_cast<optional<uint64_t>*>(handle)
                )
            ) : optional<std::chrono::time_point<Clock, Duration>>{};
    }
};

template<class Rep, class Period>
struct Conversion<std::chrono::duration<Rep, Period>, typename std::enable_if<std::is_class<std::chrono::duration<Rep, Period>>::value>::type> {
    static uint64_t
    toFfi(const std::chrono::duration<Rep, Period>& t) {
        return std::chrono::duration_cast<std::chrono::microseconds>(t).count();
    }

    static uint64_t
    toFfi(std::chrono::duration<Rep, Period>&& t) {
        return std::chrono::duration_cast<std::chrono::microseconds>(t).count();
    }

    static std::chrono::duration<Rep, Period>
    toCpp(uint64_t microseconds_value) {
        using namespace std::chrono;
        auto num = Period::den * microseconds::period::num;
        auto den = Period::num * microseconds::period::den;
        auto micro_division = std::lldiv(microseconds_value * num, den);
        auto result_value = micro_division.quot;

        // Rounding
        if (2 * micro_division.rem >= den) {
            result_value += 1;
        }

        return std::chrono::duration<Rep, Period>(result_value);
    }
};

template<class Rep, class Period>
struct Conversion<
    optional<std::chrono::duration<Rep, Period>>,
    typename std::enable_if<std::is_class<optional<std::chrono::duration<Rep, Period>>>::value>::type
> {
    static FfiOpaqueHandle
    toFfi(optional<std::chrono::duration<Rep, Period>> t) {
        return t
            ? reinterpret_cast<FfiOpaqueHandle>(
                new (std::nothrow) optional<uint64_t>(
                    Conversion<std::chrono::duration<Rep, Period>>::toFfi(*t)
                )
            ) : 0;
    }

    static optional<std::chrono::duration<Rep, Period>>
    toCpp(const FfiOpaqueHandle& handle) {
        return handle
            ? optional<std::chrono::duration<Rep, Period>>(
                Conversion<std::chrono::duration<Rep, Period>>::toCpp(
                    **reinterpret_cast<optional<uint64_t>*>(handle)
                )
            ) : optional<std::chrono::duration<Rep, Period>>{};
    }
};

}