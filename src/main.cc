#include <fstream>
#include <iostream>
#include <string>
#include <utility>

#include "experience.h"
#include "generator.h"
#include "time-point.h"

const int Generator::kLenSpacing = 2;
const char Generator::kPunctuation = '*';
const std::pair<char, char> Generator::kBranchPair = { '_', '-' };

int main(int argc, char** argv) {
    Generator gen(TimePoint(2019, 5));

    gen.append(
        Experience(
            TimePoint(2018, 5),
            TimePoint(2018, 8),
            "0  Pay Tax @California"));

    gen.append(
        Experience(
            TimePoint(2018, 5),
            TimePoint(2018, 8),
            "1  Pay Tax @California"));

    gen.append(
        Experience(
            TimePoint(2018, 6),
            TimePoint(2018, 9),
            "2  Pay Tax @California"));

    gen.append(
        Experience(
            TimePoint(2018, 4),
            TimePoint(2018, 7),
            "3  Pay Tax @California"));

    gen.append(
        Experience(
            TimePoint(2019, 2),
            TimePoint(2019, 5),
            "4  Sleep @Home"));

    gen.append(
        Experience(
            TimePoint(2019, 2),
            TimePoint(2019, 5),
            "5  Sleep @Home"));

    gen.append(
        Experience(
            TimePoint(2018, 3),
            TimePoint(2018, 9),
           "6 Play Zelda @Texas"));

    gen.append(
        Experience(
            TimePoint(2018, 8),
            TimePoint(2019, 1),
            "7 Play Zelda @Texas"));

    gen.append(
        Experience(
            TimePoint(2016, 8),
            TimePoint(2018, 12),
            "8 Play Zelda @Texas"));

    gen.append(
        Experience(
            TimePoint(2018, 1),
            TimePoint(2018, 5),
            "9 Test @Production"));
    
    auto out = gen.generate();
    std::cout << out << std::endl;
    return 0;
}