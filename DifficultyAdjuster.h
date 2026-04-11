#ifndef DIFFICULTY_ADJUSTER_H
#define DIFFICULTY_ADJUSTER_H

#include <vector>
#include "Block.cpp"

class DifficultyAdjuster {
public:
    uint64_t adjust_difficulty(const std::vector<Block>& chain, uint64_t current_diff, uint64_t target_time) {
        if (chain.size() < 10) return current_diff;

        uint64_t recent_blocks = 5;
        uint64_t total_time = 0;
        for (size_t i = chain.size() - recent_blocks; i < chain.size() - 1; i++) {
            auto t1 = chain[i].get_header().timestamp;
            auto t2 = chain[i + 1].get_header().timestamp;
            total_time += std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count();
        }

        uint64_t avg_time = total_time / recent_blocks;
        if (avg_time < target_time / 2) return current_diff + 1;
        if (avg_time > target_time * 2 && current_diff > 1) return current_diff - 1;
        return current_diff;
    }
};

#endif
