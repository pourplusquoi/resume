#ifndef COMPARE_H_
#define COMPARE_H_

template <typename Derived>
struct Compare {};

template <class Derived>
bool operator==(const Compare<Derived>& lhs, const Compare<Derived>& rhs) {
    decltype(auto) dl = static_cast<const Derived&>(lhs);
    decltype(auto) dr = static_cast<const Derived&>(rhs); 
    return !dl.operator<(dr) && !dr.operator<(dl);
}

template <class Derived>
bool operator>(const Compare<Derived>& lhs, const Compare<Derived>& rhs) {
    decltype(auto) dl = static_cast<const Derived&>(lhs);
    decltype(auto) dr = static_cast<const Derived&>(rhs); 
    return dr.operator<(dl);
}

template <class Derived>
bool operator<=(const Compare<Derived>& lhs, const Compare<Derived>& rhs) {
    decltype(auto) dl = static_cast<const Derived&>(lhs);
    decltype(auto) dr = static_cast<const Derived&>(rhs); 
    return dl.operator<(dr) || operator==(lhs, rhs);
}

template <class Derived>
bool operator>=(const Compare<Derived>& lhs, const Compare<Derived>& rhs) {
    return operator>(lhs, rhs) || operator==(lhs, rhs);
}

#endif // COMPARE_H_
