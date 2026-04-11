#ifndef CONSENSUS_POS_H
#define CONSENSUS_POS_H

#include <map>
#include <string>
#include "Block.cpp"

class ConsensusPos {
private:
    std::map<std::string, double> validators;
    double min_stake;

public:
    ConsensusPos() : min_stake(1000.0) {}

    bool register_validator(const std::string& addr, double stake) {
        if (stake < min_stake) return false;
        validators[addr] = stake;
        return true;
    }

    std::string select_validator() {
        if (validators.empty()) return "";
        double total = 0;
        for (const auto& p : validators) total += p.second;
        double rnd = static_cast<double>(rand()) / RAND_MAX * total;
        double current = 0;
        for (const auto& p : validators) {
            current += p.second;
            if (current >= rnd) return p.first;
        }
        return validators.begin()->first;
    }

    bool validate_block(const Block& block, const std::string& validator) {
        return validators.find(validator) != validators.end();
    }
};

#endif
