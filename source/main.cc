#include <ctime>
#include <iostream>
#include <string>
#include <utility>

#include "experience.h"
#include "file-io.h"
#include "generator.h"
#include "time-point.h"

const int Generator::kLenSpacing = 2;
const int Generator::kFoldThreshold = 6;
const char Generator::kPunctuation = '*';
const char* Generator::kPrefix = "         |";
const std::pair<char, char> Generator::kBranchPair = { '_', '-' };

int main(int argc, char** argv) {
    if (argc != 2 && argc != 3) {
        std::cout << "[ERROR] Damn, invalid args...\n"
                  << "Usage: ./timeline-gen [input-file] [output-file]\n"
                  << "       [required]  input-file     Where I parse from.\n"
                  << "       [optional]  output-file    Where I write timeline,"
                  << " otherwise I write to stdout." << std::endl;
        return -1;
    }

    const char* infile = argv[1];
    const char* outfile = (argc == 2) ? nullptr : argv[2];

    std::vector<Experience> experience;
    if (!FileIO::read(infile, experience)) {
        std::cout << "[ERROR] Damn, cannot read file: "
                  << infile << std::endl;
        return 1;
    }

    // Gets current local time.
    auto time = std::time(nullptr);
    auto local_time = std::localtime(&time);
    
    TimePoint now(local_time->tm_year + 1900, local_time->tm_mon + 1);
    Generator timeline(std::move(now));

    for (const Experience& exp : experience) {
        timeline.append(exp);
    }

    std::string out = timeline.generate();
    if (!outfile) {
        std::cout << out << std::endl;
    } else {
        if (!FileIO::write(outfile, out)) {
            std::cout << "[ERROR] Damn, cannot write file: "
                      << outfile << std::endl;
            return 2;
        } else {
            std::cout << "[INFO] FYI, timeline is written to file: "
                      << outfile << std::endl;
        }
    }

    return 0;
}
