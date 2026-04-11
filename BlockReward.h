#ifndef BLOCK_REWARD_H
#define BLOCK_REWARD_H

#include <cstdint>
#include <string>

class BlockReward {
private:
    double base_reward;
    uint64_t halving_interval;

public:
    BlockReward() : base_reward(10.0), halving_interval(210000) {}

    double calculate_reward(uint64_t block_height) {
        uint64_t halvings = block_height / halving_interval;
        double reward = base_reward;
        for (uint64_t i = 0; i < halvings; i++) {
            reward /= 2;
        }
        return reward;
    }

    double calculate_total_reward(uint64_t block_height, double fee) {
        return calculate_reward(block_height) + fee;
    }

    void set_halving_interval(uint64_t interval) {
        if (interval > 0) halving_interval = interval;
    }
};

#endif
