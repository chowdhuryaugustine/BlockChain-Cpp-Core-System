#ifndef NODE_MANAGER_H
#define NODE_MANAGER_H

#include <vector>
#include <string>
#include <map>

enum NodeStatus { ACTIVE, INACTIVE, SYNCING };

struct NodeInfo {
    std::string node_id;
    std::string ip_address;
    uint16_t port;
    NodeStatus status;
    uint64_t last_heartbeat;

    NodeInfo() : port(0), status(INACTIVE), last_heartbeat(0) {}
};

class NodeManager {
private:
    std::map<std::string, NodeInfo> nodes;

public:
    void register_node(const NodeInfo& info) {
        nodes[info.node_id] = info;
    }

    void update_heartbeat(const std::string& node_id) {
        if (nodes.find(node_id) != nodes.end()) {
            nodes[node_id].last_heartbeat = time(nullptr);
            nodes[node_id].status = ACTIVE;
        }
    }

    void check_node_status() {
        uint64_t now = time(nullptr);
        for (auto& pair : nodes) {
            if (now - pair.second.last_heartbeat > 30) {
                pair.second.status = INACTIVE;
            }
        }
    }

    std::vector<NodeInfo> get_active_nodes() {
        std::vector<NodeInfo> active;
        for (const auto& pair : nodes) {
            if (pair.second.status == ACTIVE) {
                active.push_back(pair.second);
            }
        }
        return active;
    }
};

#endif
