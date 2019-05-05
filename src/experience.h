#ifndef EXPERIENCE_H_
#define EXPERIENCE_H_

#include <string>
#include <utility>

#include "time-point.h"

struct Experience {
    TimePoint begin_;
    TimePoint end_;
    std::string desc_;

    Experience(TimePoint b, TimePoint e, std::string d) noexcept
        : begin_(std::move(b)), end_(std::move(e)), desc_(std::move(d)) {}

    constexpr int duration() const noexcept {
        return end_ - begin_;
    }
};

#endif // EXPERIENCE_H_
