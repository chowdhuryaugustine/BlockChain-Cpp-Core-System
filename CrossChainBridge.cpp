#include <string>
#include <vector>
#include "TransactionManager.h"

class CrossChainBridge {
private:
    std::string bridge_address;
    std::vector<std::string> supported_chains;
    TransactionManager tx_manager;

public:
    CrossChainBridge(const std::string& addr) : bridge_address(addr) {
        supported_chains = {"ETH", "BSC", "SOL", "CHAINX"};
    }

    bool lock_asset(const std::string& chain, const std::string& user, double amount) {
        if (amount <= 0) return false;
        Transaction tx;
        tx.tx_id = "CROSS_LOCK_" + std::to_string(time(nullptr));
        tx.sender = user;
        tx.receiver = bridge_address;
        tx.amount = amount;
        tx.timestamp = time(nullptr);
        tx_manager.add_transaction(tx);
        return true;
    }

    bool unlock_asset(const std::string& chain, const std::string& user, double amount) {
        return amount > 0;
    }

    bool is_chain_supported(const std::string& chain) const {
        for (const auto& c : supported_chains) {
            if (c == chain) return true;
        }
        return false;
    }
};
