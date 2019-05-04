#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <algorithm>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

#include "experience.h"
#include "time-point.h"

struct Generator {
    const TimePoint now_;
    std::vector<Experience> data_;
    mutable std::unordered_map<int, std::string_view> desc_map_;
    
    static const int kLenSpacing;
    static const char kPunctuation;
    static const std::pair<char, char> kBranchPair;
    
    Generator(TimePoint now) : now_(std::move(now)) {}

    enum class Status { head, mid, tail };
    struct Detail {
        Status status_;
        int index_;
        int spacing_;
        Detail(Status s, int idx, int space)
            : status_(s), index_(idx), spacing_(space) {}
    };
    using DetailCollection = std::vector<Detail>;

    void append(Experience exp) {
        if (exp.begin_ < exp.end_)
            data_.emplace_back(std::move(exp));
    }

    std::string generate() {
        std::sort(data_.begin(), data_.end(),
            [](const auto& lhs, const auto& rhs) {
                int ldur = lhs.duration();
                int rdur = rhs.duration();
                if (ldur != rdur)
                    return ldur > rdur;
                return lhs.begin_ < rhs.begin_;
            });
        TimePoint epoch = earliest();
        auto timeline = create_timeline(epoch);
        return build_from(epoch, timeline);
    }

    std::string build_from(const TimePoint& epoch,
                           const std::vector<DetailCollection>& timeline) const {
        std::vector<std::string> line_vec;
        TimePoint point = epoch;

        int line_num = 0;
        for (const auto& elem : timeline) {
            std::vector<const Detail*> overflow;
            line_vec.emplace_back(
                build_line_from(line_num++, point, elem, overflow));

            // Deals with overflow.
            for (int i = 0; i < overflow.size(); i++) {
                std::string line = "         |";
                
                char filler = (point == now_) ? ' ' : kBranchPair.second;
                line += std::string(overflow.at(i)->spacing_ - 1, filler) + kPunctuation;
                
                for (int j = i + 1; j < overflow.size(); j++) {
                    int temp = overflow.at(j)->spacing_ - overflow.at(i)->spacing_;
                    line += std::string(temp - 1, ' ') + "|";
                }
                
                line_vec.emplace_back(line);
                desc_map_.insert({ line_num++, data_.at(overflow.at(i)->index_).desc_ });
            }

            ++point;
        }

        // Adds desc at the end.
        append_desc_each_line(line_vec);

        std::string res;
        std::reverse(line_vec.begin(), line_vec.end());
        for (std::string& line : line_vec) {
            res += std::move(line);
            res.push_back('\n');
        }
        return res;
    }

    void append_desc_each_line(std::vector<std::string>& line_vec) const {
        int indent = 0;
        for (const auto& elem : desc_map_) {
            indent = std::max(
                indent, static_cast<int>(line_vec.at(elem.first).size()));
        }
        indent += 2; // Additional space before description.
        for (const auto& elem : desc_map_) {
            std::string& line = line_vec.at(elem.first);
            line += std::string(indent - line.size(), ' ');
            line += elem.second;
        }
    }

    std::string build_line_from(int line_num,
                                const TimePoint& point,
                                const DetailCollection& collection,
                                std::vector<const Detail*>& overflow) const {
        std::string line = point.to_string_as_head();
        
        int next_pos = 1;
        bool tail_taken = false;
        
        for (const Detail& detail : collection) {
            int padding_num = detail.spacing_ - next_pos;
            next_pos += padding_num + 1;

            switch (detail.status_) {
                case Status::head:
                    line += std::string(padding_num, kBranchPair.first) + "|";
                    break;
                
                case Status::mid:
                    line += std::string(padding_num, ' ') + "|";
                    break;
                
                case Status::tail:
                    if (!tail_taken) { // Doesn't overflow.
                        tail_taken = true;
                        char filler = (point == now_) ? ' ' : kBranchPair.second;
                        line += std::string(padding_num, filler) + kPunctuation;
                        desc_map_.insert({ line_num, data_.at(detail.index_).desc_ });
                    } else { // Overflows.
                        line += std::string(padding_num, ' ') + "|";
                        overflow.push_back(&detail);
                    }
                    break;
            }
        }
        return line;
    }

    std::vector<DetailCollection> create_timeline(const TimePoint& epoch) const {
        std::vector<DetailCollection> timeline((now_ - epoch) + 1);
        for (int i = 0; i < data_.size(); i++) {
            int boffset = data_.at(i).begin_ - epoch;
            int eoffset = data_.at(i).end_ - epoch;

            int spacing = 0;
            for (int i = boffset; i <= eoffset; i++)
                spacing = std::max(
                    spacing, static_cast<int>(timeline[i].size())*kLenSpacing);
            spacing += 2;

            timeline[boffset].emplace_back(Status::head, i, spacing);
            timeline[eoffset].emplace_back(Status::tail, i, spacing);

            for (int i = boffset + 1; i < eoffset; i++)
                timeline[i].emplace_back(Status::mid, i, spacing);
        }
        return timeline;
    }

    TimePoint earliest() const {
        int epoch_year = 9999;
        for (const auto& point : data_) {
            epoch_year = std::min(epoch_year, point.begin_.year_);
        }
        return TimePoint(epoch_year, 1);
    }
};

#endif // GENERATOR_H_
