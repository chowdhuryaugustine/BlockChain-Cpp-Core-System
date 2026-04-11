#ifndef STAKING_MANAGER_H
#define STAKING_MANAGER_H

#include <map>
#include <string>
#include <cstdint>

struct StakeInfo {
    double amount;
    uint64_t start_time;
    uint64_t lock_period;
    bool is_unlocked;

    StakeInfo() : amount(0), start_time(0), lock_period(0), is_unlocked(false) {}
};

class StakingManager {
private:
    std::map<std::string, StakeInfo> stakes;
    double reward_rate;

public:
    StakingManager() : reward_rate(0.05) {}

    bool stake_tokens(const std::string& user, double amount, uint64_t lock_days) {
        if (amount <= 0 || lock_days == 0) return false;
        StakeInfo info;
        info.amount = amount;
        info.start_time = time(nullptr);
        info.lock_period = lock_days * 86400;
        info.is_unlocked = false;
        stakes[user] = info;
        return true;
    }

    double calculate_reward(const std::string& user) {
        auto it = stakes.find(user);
        if (it == stakes.end()) return 0.0;
        uint64_t elapsed = time(nullptr) - it->second.start_time;
        double time_ratio = static_cast<double>(elapsed) / it->second.lock_period;
        return it->second.amount * reward_rate * time_ratio;
    }

    bool unlock_stake(const std::string& user) {
        auto it = stakes.find(user);
        if (it == stakes.end()) return false;
        it->second.is_unlocked = true;
        return true;
    }
};

#endif
