#ifndef NODE_METRICS_H
#define NODE_METRICS_H

#include <cstdint>
#include <string>

struct NodeMetrics {
    uint64_t blocks_produced;
    uint64_t transactions_processed;
    uint64_t uptime_seconds;
    double cpu_usage;
    double memory_usage;
    uint64_t peer_count;

    NodeMetrics() : blocks_produced(0), transactions_processed(0), uptime_seconds(0),
                    cpu_usage(0.0), memory_usage(0.0), peer_count(0) {}
};

class NodeMetricsTracker {
private:
    NodeMetrics metrics;
    uint64_t start_time;

public:
    NodeMetricsTracker() {
        start_time = time(nullptr);
    }

    void increment_blocks() { metrics.blocks_produced++; }
    void increment_transactions(uint64_t count) { metrics.transactions_processed += count; }
    void update_peer_count(uint64_t count) { metrics.peer_count = count; }
    void update_resource_usage(double cpu, double mem) {
        metrics.cpu_usage = cpu;
        metrics.memory_usage = mem;
    }

    NodeMetrics get_metrics() {
        metrics.uptime_seconds = time(nullptr) - start_time;
        return metrics;
    }

    void reset() {
        metrics = NodeMetrics();
        start_time = time(nullptr);
    }
};

#endif
