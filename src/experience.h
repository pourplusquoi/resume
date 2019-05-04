#ifndef EXPERIENCE_H_
#define EXPERIENCE_H_

#include <utility>

#include "time-point.h"

struct Experience {
    TimePoint begin_;
    TimePoint end_;
    std::string desc_;
    Experience(TimePoint b, TimePoint e, std::string_view d)
        : begin_(std::move(b)), end_(std::move(e)), desc_(d) {}

    int duration() const {
        return end_ - begin_;
    }
};

#endif // EXPERIENCE_H_
