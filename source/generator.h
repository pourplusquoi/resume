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

class Generator {
public:
    static constexpr int kLenSpacing = 2;
    static constexpr int kFoldThreshold = 12;
    static constexpr char kPunctuation = '*';
    static constexpr char kPrefix[] = "         |";
    static constexpr char kFoldPrefix[] = "     ... |";
    static constexpr std::pair<char, char> kBranchPair = { '_', '-' };

    explicit Generator(const TimePoint& now) noexcept : now_(now) {}
    explicit Generator(TimePoint&& now) noexcept : now_(std::move(now)) {}

    void append(const Experience& exp) {
        if (exp.begin <= exp.end)
            data_.emplace_back(exp);
    }

    void append(Experience&& exp) {
        if (exp.begin <= exp.end)
            data_.emplace_back(std::move(exp));
    }

    std::string generate() {
        std::sort(data_.begin(), data_.end(),
            [](const auto& lhs, const auto& rhs) {
                int ldur = lhs.duration();
                int rdur = rhs.duration();
                if (ldur != rdur)
                    return ldur > rdur;
                return lhs.begin < rhs.begin;
            });

        TimePoint epoch = earliest();
        auto timeline = create_timeline(epoch);

        return build_from(std::move(epoch), timeline);
    }

private:
    const TimePoint now_;
    std::vector<Experience> data_;
    
    mutable std::unordered_map<int, std::string_view> desc_map_;

    enum class Status { head, mid, tail };
    
    struct Detail {
        Status status;
        int index;
        int indent;
        Detail(Status s, int idx, int indent)
            : status(s), index(idx), indent(indent) {}
    };
    
    using DetailCollection = std::vector<Detail>;

    TimePoint earliest() const {
        int epoch_year = 9999;
        for (const auto& point : data_) {
            epoch_year = std::min(epoch_year, point.begin.year);
        }
        return TimePoint(epoch_year, 1);
    }

    std::vector<DetailCollection> create_timeline(const TimePoint& epoch) const {
        std::vector<DetailCollection> timeline((now_ - epoch) + 1);
        std::vector<int> indent_map(data_.size());

        for (int i = 0; i < data_.size(); i++) {
            int boffset = data_[i].begin - epoch;
            int eoffset = data_[i].end - epoch;

            int indent = 0;
            for (int j = boffset; j <= eoffset; j++) {
                if (!timeline[j].empty()) {
                    indent = std::max(
                        indent, indent_map[timeline[j].back().index]);
                }
            }
            indent += kLenSpacing;

            // Records the indent to the indent map.
            indent_map[i] = indent;

            // When experience begin equals end.
            if (eoffset > boffset)
                timeline[boffset].emplace_back(Status::head, i, indent);
            timeline[eoffset].emplace_back(Status::tail, i, indent);

            for (int j = boffset + 1; j < eoffset; j++)
                timeline[j].emplace_back(Status::mid, i, indent);
        }
        return timeline;
    }

    std::string build_from(TimePoint&& point,
                           const std::vector<DetailCollection>& timeline) const {
        std::vector<std::string> line_vec;

        int line_num = 0;
        for (const auto& elem : timeline) {
            std::vector<const Detail*> overflow;
            line_vec.emplace_back(
                build_line_from(line_num++, point, elem, overflow));

            // Builds and adds overflow lines, if any.
            if (!overflow.empty()) {
                attach_overflow_lines(
                    point == now_, line_num, overflow, elem, line_vec);
            }

            ++point;
        }

        // Adds desc at the end.
        append_desc_each_line(line_vec);

        line_vec = fold(line_vec);
        std::reverse(line_vec.begin(), line_vec.end());

        std::string res;
        for (std::string& line : line_vec) {
            res += std::move(line);
            res.push_back('\n');
        }
        return res;
    }

    std::string build_line_from(int line_num,
                                const TimePoint& point,
                                const DetailCollection& collection,
                                std::vector<const Detail*>& overflow) const {
        std::string line = point.to_string_as_head();
        
        int next_pos = 0;
        bool tail_taken = false;
        
        for (const Detail& detail : collection) {
            int indent_num = detail.indent - next_pos - 1;
            next_pos = detail.indent;

            switch (detail.status) {
                case Status::head:
                    line += std::string(indent_num, kBranchPair.first) + "|";
                    break;
                
                case Status::mid:
                    line += std::string(indent_num, ' ') + "|";
                    break;
                
                case Status::tail:
                    if (!tail_taken) { // Doesn't overflow.
                        tail_taken = true;
                        char filler = (point == now_) ? ' ' : kBranchPair.second;
                        line += std::string(indent_num, filler) + kPunctuation;
                        desc_map_.insert({
                            line_num,
                            data_[detail.index].desc
                        });
                    } else { // Overflows.
                        line += std::string(indent_num, ' ') + "|";
                        overflow.push_back(&detail);
                    }
                    break;
            }
        }
        return line;
    }

    void attach_overflow_lines(bool at_head, int& line_num,
                               const std::vector<const Detail*>& overflow,
                               const DetailCollection& affected,
                               std::vector<std::string>& line_vec) const {
        // Prepares for overflow.
        std::string prefix = std::string(kPrefix);
        const auto& tail = line_vec.back();

        int next_pos = 0;
        if (!at_head) {
            int start = overflow.front()->indent + prefix.size() - 2;
            next_pos = static_cast<int>(
                tail.rfind('|', start) - prefix.size() + 1);

            std::string keep = tail.substr(prefix.size(), next_pos);
            std::replace_if(keep.begin(), keep.end(),
                [](char c) { return c != ' ' && c != '|'; }, ' ');
            prefix += keep;
        }

        // Deals with overflow.
        for (int i = 0; i < overflow.size(); i++) {
            std::string line = prefix;

            int indent_num = overflow[i]->indent - next_pos - 1;
            char filler = at_head ? ' ' : kBranchPair.second;
            line += std::string(indent_num, filler) + kPunctuation;

            // Finds the first affected point.
            int idx = 0;
            for (const Detail& detail : affected) {
                idx++;
                if (overflow[i] == &detail)
                    break;
            }

            // Stitches the event line of affected experience.
            for (int j = idx; j < affected.size(); j++) {
                int margin = affected[j].indent -
                             affected[j - 1].indent - 1;
                line += std::string(margin, ' ') + "|";
            }

            line_vec.emplace_back(line);
            desc_map_.insert({
                line_num++,
                data_[overflow[i]->index].desc
            });
        }
    }

    void append_desc_each_line(std::vector<std::string>& line_vec) const {
        int indent = 0;
        for (const auto& elem : desc_map_) {
            indent = std::max(
                indent, static_cast<int>(line_vec[elem.first].size()));
        }
        indent += kLenSpacing; // Additional space before description.
        for (const auto& elem : desc_map_) {
            std::string& line = line_vec[elem.first];
            line += std::string(indent - line.size(), ' ');
            line += elem.second;
        }
    }

    std::vector<std::string> fold(const std::vector<std::string>& lines) const {
        std::vector<int> keep(1, 0);
        for (int i = 1, skip = strlen(kPrefix), count = 0; i < lines.size(); i++) {
            if (i < lines.size() - 1 &&
                std::string_view(lines[keep.back()]).substr(skip) ==
                    std::string_view(lines[i]).substr(skip)) {
                count++;
            } else {
                if (count < kFoldThreshold) {
                    for (; count > 0; count--) {
                        keep.push_back(keep.back() + 1);
                    }
                    keep.push_back(i);
                } else {
                    count = 0;
                    for (int j = 0; j < kFoldThreshold / 3 - 1; j++) {
                        keep.push_back(keep.back() + 1);
                    }
                    keep.push_back(-1);
                    for (int j = kFoldThreshold / 3; j >= 0; j--) {
                        keep.push_back(i - j);
                    }
                }
            }
        }

        std::vector<std::string> folded;
        for (int idx : keep) {
            if (idx < 0) {
                std::string connect = std::string(kFoldPrefix);
                connect += folded.back().substr(connect.size());

                std::replace_if(connect.begin(), connect.end(),
                    [](char c) { return c == '|'; }, '~');
                folded.emplace_back(std::move(connect));
            } else {
                folded.emplace_back(lines[idx]);
            }
        }
        return folded;
    }
};

#endif  // GENERATOR_H_
