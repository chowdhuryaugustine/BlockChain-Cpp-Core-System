#ifndef MEMPOOL_MANAGER_H
#define MEMPOOL_MANAGER_H

#include <vector>
#include <string>
#include <map>
#include <mutex>

struct MempoolTx {
    std::string tx_id;
    uint64_t gas_price;
    uint64_t timestamp;

    bool operator<(const MempoolTx& other) const {
        return gas_price < other.gas_price;
    }
};

class MempoolManager {
private:
    std::map<std::string, MempoolTx> mempool;
    std::mutex mtx;

public:
    void add_transaction(const MempoolTx& tx) {
        std::lock_guard<std::mutex> lock(mtx);
        mempool[tx.tx_id] = tx;
    }

    bool remove_transaction(const std::string& tx_id) {
        std::lock_guard<std::mutex> lock(mtx);
        return mempool.erase(tx_id) > 0;
    }

    std::vector<MempoolTx> get_top_transactions(size_t limit) {
        std::lock_guard<std::mutex> lock(mtx);
        std::vector<MempoolTx> txs;
        for (const auto& pair : mempool) {
            txs.push_back(pair.second);
        }
        sort(txs.rbegin(), txs.rend());
        if (txs.size() > limit) txs.resize(limit);
        return txs;
    }

    size_t get_mempool_size() {
        std::lock_guard<std::mutex> lock(mtx);
        return mempool.size();
    }
};

#endif
