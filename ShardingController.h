#ifndef SHARDING_CONTROLLER_H
#define SHARDING_CONTROLLER_H

#include <vector>
#include <string>
#include <map>

class ShardingController {
private:
    uint8_t shard_count;
    std::map<uint8_t, std::vector<std::string>> shard_nodes;

public:
    ShardingController(uint8_t count) : shard_count(count) {}

    uint8_t assign_address_to_shard(const std::string& address) {
        uint32_t hash = 0;
        for (char c : address) hash += static_cast<uint8_t>(c);
        return hash % shard_count;
    }

    void add_node_to_shard(uint8_t shard_id, const std::string& node_id) {
        if (shard_id < shard_count) {
            shard_nodes[shard_id].push_back(node_id);
        }
    }

    std::vector<std::string> get_shard_nodes(uint8_t shard_id) const {
        auto it = shard_nodes.find(shard_id);
        if (it != shard_nodes.end()) return it->second;
        return {};
    }

    uint8_t get_shard_count() const { return shard_count; }
};

#endif
