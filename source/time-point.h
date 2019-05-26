#ifndef TIME_POINT_H_
#define TIME_POINT_H_

#include <algorithm>
#include <array>
#include <string>

#include "compare.h"

struct TimePoint : Compare<TimePoint> {
    int year;
    int month;
    static constexpr std::array<const char*, 13> kMonthName {
        "", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
    };
    
    // Default constructor.
    constexpr TimePoint() noexcept : year(1970), month(1) {}

    constexpr TimePoint(int year, int month) noexcept
        : year(std::max(1970, std::min(9999, year))),
          month(std::max(1, std::min(12, month))) {}

    constexpr bool operator<(const TimePoint& that) const noexcept {
        if (this->year != that.year)
            return this->year < that.year;
        return this->month < that.month;
    }

    constexpr int operator-(const TimePoint& that) const noexcept {
        return (this->year - that.year)*12 + (this->month - that.month);
    }

    constexpr TimePoint& operator++() noexcept {
        this->month++;
        if (this->month > 12) {
            this->year++;
            this->month -= 12;
        }
        return *this;
    }

    std::string to_string_as_head() const noexcept {
        std::string head;
        if (this->month == 1)
            head += std::to_string(this->year);
        else head += "    ";

        head += " " + std::string(kMonthName[this->month]) + " |";
        return head;
    }
};

#endif  // TIME_POINT_H_
