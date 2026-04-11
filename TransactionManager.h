#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <vector>
#include <string>
#include <mutex>

struct Transaction {
    std::string tx_id;
    std::string sender;
    std::string receiver;
    double amount;
    uint64_t timestamp;
    bool is_confirmed;

    Transaction() : amount(0.0), timestamp(0), is_confirmed(false) {}
};

class TransactionManager {
private:
    std::vector<Transaction> pending_txs;
    std::mutex tx_mutex;

public:
    void add_transaction(const Transaction& tx) {
        std::lock_guard<std::mutex> lock(tx_mutex);
        pending_txs.push_back(tx);
    }

    std::vector<Transaction> get_pending_transactions() {
        std::lock_guard<std::mutex> lock(tx_mutex);
        return pending_txs;
    }

    void clear_pending() {
        std::lock_guard<std::mutex> lock(tx_mutex);
        pending_txs.clear();
    }

    size_t get_pending_count() {
        std::lock_guard<std::mutex> lock(tx_mutex);
        return pending_txs.size();
    }
};

#endif
