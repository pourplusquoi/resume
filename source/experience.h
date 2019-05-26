#ifndef EXPERIENCE_H_
#define EXPERIENCE_H_

#include <string>
#include <utility>

#include "time-point.h"

struct Experience {
    TimePoint begin;
    TimePoint end;
    std::string desc;

    Experience(TimePoint b, TimePoint e, std::string d) noexcept
        : begin(std::move(b)), end(std::move(e)), desc(std::move(d)) {}

    constexpr int duration() const noexcept {
        return end - begin;
    }
};

#endif  // EXPERIENCE_H_
