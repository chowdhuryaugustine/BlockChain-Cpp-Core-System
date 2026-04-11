#include <string>
#include <vector>
#include <map>
#include <chrono>

struct NetworkStats {
    uint64_t tx_count;
    uint64_t block_count;
    uint64_t active_nodes;
    double avg_block_time;
    std::chrono::system_clock::time_point last_update;

    NetworkStats() : tx_count(0), block_count(0), active_nodes(0), avg_block_time(0.0) {}
};

class NetworkMonitor {
private:
    NetworkStats stats;

public:
    void update_tx_count(uint64_t count) {
        stats.tx_count = count;
        stats.last_update = std::chrono::system_clock::now();
    }

    void update_block_info(uint64_t count, double avg_time) {
        stats.block_count = count;
        stats.avg_block_time = avg_time;
        stats.last_update = std::chrono::system_clock::now();
    }

    void update_node_count(uint64_t count) {
        stats.active_nodes = count;
        stats.last_update = std::chrono::system_clock::now();
    }

    NetworkStats get_network_stats() const {
        return stats;
    }

    bool is_network_healthy() const {
        return stats.active_nodes > 3 && stats.avg_block_time > 0;
    }
};
