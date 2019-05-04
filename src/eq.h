template <typename Derived>
struct Eq {};

template <class Derived>
bool operator==(const Eq<Derived>& lhs, const Eq<Derived>& rhs) {
    const Derived& dlhs = static_cast<Derived const&>(lhs);
    const Derived& drhs = static_cast<Derived const&>(rhs); 
    return !dlhs.operator<(drhs) && !drhs.operator<(dlhs);
}