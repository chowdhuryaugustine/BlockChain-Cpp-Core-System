#ifndef TOKEN_STANDARD_H
#define TOKEN_STANDARD_H

#include <string>
#include <map>
#include <mutex>

class TokenStandard {
private:
    std::string name;
    std::string symbol;
    uint8_t decimals;
    uint64_t total_supply;
    std::map<std::string, uint64_t> balances;
    std::mutex mtx;

public:
    TokenStandard(const std::string& n, const std::string& s, uint8_t d, uint64_t supply)
        : name(n), symbol(s), decimals(d), total_supply(supply) {}

    bool transfer(const std::string& from, const std::string& to, uint64_t amount) {
        std::lock_guard<std::mutex> lock(mtx);
        if (balances[from] < amount) return false;
        balances[from] -= amount;
        balances[to] += amount;
        return true;
    }

    void mint(const std::string& address, uint64_t amount) {
        std::lock_guard<std::mutex> lock(mtx);
        balances[address] += amount;
        total_supply += amount;
    }

    uint64_t balance_of(const std::string& address) {
        std::lock_guard<std::mutex> lock(mtx);
        return balances[address];
    }

    std::string get_token_info() const {
        return name + " (" + symbol + ") - Decimals: " + std::to_string(decimals);
    }
};

#endif
