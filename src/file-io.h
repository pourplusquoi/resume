#ifndef FILE_IO_H_
#define FILE_IO_H_

#include <array>
#include <fstream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

#include "experience.h"
#include "time-point.h"

struct FileIO {
public:
    static bool read(const char* filename,
                     std::vector<Experience>& exps) noexcept {
        std::ifstream in(filename);
        if (!in.is_open())
            return false;

        std::array<char, 500> buffer;
        while (in.getline(&buffer[0], 500)) {
            std::stringstream ss(&buffer[0]);

            // Skips empty and comment lines.
            if (buffer[0] == '\0' || buffer[0] == '\n' || buffer[0] == '#')
                continue;

            // begin_end: { begin_yr, begin_mo, end_yr, end_mo }
            std::array<int, 4> begin_end;
            std::array<char, 10> number;
            for (int i = 0; i < 4; i++) {
                if (!ss.getline(&number[0], 10, ' '))
                    return false;
                begin_end[i] = std::atoi(&number[0]);
            }

            std::string desc;
            std::getline(ss, desc);

            exps.emplace_back(
                TimePoint(begin_end[0], begin_end[1]),
                TimePoint(begin_end[2], begin_end[3]),
                std::move(desc));
        }
        return true;
    }

    static bool write(const char* filename,
                      std::string_view data) noexcept {
        std::ofstream out(filename);
        if (!out.is_open())
            return false;
        out << data;
        return true;
    }
};

#endif // FILE_IO_H_