#ifndef COMPARE_H_
#define COMPARE_H_

template <typename T>
struct Eq {};

template <typename T>
constexpr bool operator==(const Eq<T>& lhs, const Eq<T>& rhs) noexcept {
    decltype(auto) dl = static_cast<const T&>(lhs);
    decltype(auto) dr = static_cast<const T&>(rhs);
    return !(dl < dr) && !(dr < dl);
}

template <typename T>
struct Ne {};

template <typename T>
constexpr bool operator!=(const Ne<T>& lhs, const Ne<T>& rhs) noexcept {
    decltype(auto) dl = static_cast<const T&>(lhs);
    decltype(auto) dr = static_cast<const T&>(rhs);
    return dl < dr || dr < dl;
}

template <typename T>
struct Lt {};

template <typename T>
constexpr bool operator<(const Lt<T>& lhs, const Lt<T>& rhs) noexcept {
    decltype(auto) dl = static_cast<const T&>(lhs);
    decltype(auto) dr = static_cast<const T&>(rhs);
    return dl < dr;
}

template <typename T>
struct Gt {};

template <typename T>
constexpr bool operator>(const Gt<T>& lhs, const Gt<T>& rhs) noexcept {
    decltype(auto) dl = static_cast<const T&>(lhs);
    decltype(auto) dr = static_cast<const T&>(rhs);
    return dr < dl;
}

template <typename T>
struct Le {};

template <typename T>
constexpr bool operator<=(const Le<T>& lhs, const Le<T>& rhs) noexcept {
    decltype(auto) dl = static_cast<const T&>(lhs);
    decltype(auto) dr = static_cast<const T&>(rhs);
    return !(dr < dl);
}

template <typename T>
struct Ge {};

template <typename T>
constexpr bool operator>=(const Ge<T>& lhs, const Ge<T>& rhs) noexcept {
    decltype(auto) dl = static_cast<const T&>(lhs);
    decltype(auto) dr = static_cast<const T&>(rhs);
    return !(dl < dr);
}

template <typename T>
struct Compare : Eq<T>, Ne<T>, Lt<T>, Gt<T>, Le<T>, Ge<T> {};

#endif  // COMPARE_H_
