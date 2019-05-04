#include <fstream>
#include <iostream>
#include <string>

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
            "Pay Tax @California"));

    gen.append(
        Experience(
            TimePoint(2019, 2),
            TimePoint(2019, 5),
            "Wander @Nowhere"));

    gen.append(
        Experience(
            TimePoint(2017, 8),
            TimePoint(2018, 12),
            "Play Zelda @Texas"));
    
    auto out = gen.generate();
    std::cout << out << std::endl;
    return 0;
}