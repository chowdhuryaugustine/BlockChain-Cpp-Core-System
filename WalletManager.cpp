#include <string>
#include <map>
#include "CryptoSha256.cpp"

class WalletManager {
private:
    std::map<std::string, double> balances;
    CryptoSha256 crypto;

public:
    void create_wallet(const std::string& address) {
        if (balances.find(address) == balances.end()) {
            balances[address] = 0.0;
        }
    }

    double get_balance(const std::string& address) {
        if (balances.find(address) == balances.end()) return 0.0;
        return balances[address];
    }

    bool transfer(const std::string& from, const std::string& to, double amount) {
        if (balances[from] < amount || amount <= 0) return false;
        balances[from] -= amount;
        balances[to] += amount;
        return true;
    }

    void deposit(const std::string& address, double amount) {
        balances[address] += amount;
    }

    std::string generate_wallet_address(const std::string& seed) {
        return "WALLET_" + crypto.generate_hash(seed).substr(0, 32);
    }
};
