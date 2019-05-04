#ifndef TIME_POINT_H_
#define TIME_POINT_H_

#include <algorithm>
#include <string>
#include <vector>

#include "eq.h"

struct TimePoint : Eq<TimePoint> {
    int year_;
    int month_;
    const static std::vector<std::string> kMonthName;
    
    TimePoint(int year, int month) {
        year_ = std::max(1970, std::min(9999, year));
        month_ = std::max(1, std::min(12, month));
    }

    bool operator<(const TimePoint& that) const {
        if (this->year_ < that.year_)
            return true;
        if (this->month_ < that.month_)
            return true;
        return false;
    }

    int operator-(const TimePoint& that) const {
        return (this->year_ - that.year_)*12 + (this->month_ - that.month_);
    }

    TimePoint& operator++() {
        this->month_++;
        if (this->month_ > 12) {
            this->year_++;
            this->month_ -= 12;
        }
        return *this;
    }

    std::string to_string_as_head() const {
        std::string head;
        if (this->month_ == 1)
            head += std::to_string(this->year_);
        else head += "    ";

        head += " " + kMonthName[this->month_] + " |";
        return head;
    }
};

const std::vector<std::string> TimePoint::kMonthName {
    "", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

#endif // TIME_POINT_H_
