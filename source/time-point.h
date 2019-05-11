#ifndef TIME_POINT_H_
#define TIME_POINT_H_

#include <algorithm>
#include <array>
#include <string>

#include "compare.h"

struct TimePoint : Compare<TimePoint> {
    int year_;
    int month_;
    static constexpr std::array<const char*, 13> kMonthName {
        "", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    
    // Default constructor.
    constexpr TimePoint() noexcept : year_(1970), month_(1) {}

    constexpr TimePoint(int year, int month) noexcept
        : year_(std::max(1970, std::min(9999, year))),
          month_(std::max(1, std::min(12, month))) {}

    constexpr bool operator<(const TimePoint& that) const noexcept {
        if (this->year_ != that.year_)
            return this->year_ < that.year_;
        return this->month_ < that.month_;
    }

    constexpr int operator-(const TimePoint& that) const noexcept {
        return (this->year_ - that.year_)*12 + (this->month_ - that.month_);
    }

    constexpr TimePoint& operator++() noexcept {
        this->month_++;
        if (this->month_ > 12) {
            this->year_++;
            this->month_ -= 12;
        }
        return *this;
    }

    std::string to_string_as_head() const noexcept {
        std::string head;
        if (this->month_ == 1)
            head += std::to_string(this->year_);
        else head += "    ";

        head += " " + std::string(kMonthName[this->month_]) + " |";
        return head;
    }
};

#endif  // TIME_POINT_H_
