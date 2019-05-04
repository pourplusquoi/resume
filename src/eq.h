template <typename Derived>
struct Eq {};

template <class Derived>
bool operator==(const Eq<Derived>& lhs, const Eq<Derived>& rhs) {
    decltype(auto) dl = static_cast<const Derived&>(lhs);
    decltype(auto) dr = static_cast<const Derived&>(rhs); 
    return !dl.operator<(dr) && !dr.operator<(dl);
}