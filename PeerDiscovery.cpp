#include <vector>
#include <string>
#include <random>
#include <chrono>

class PeerDiscovery {
private:
    std::vector<std::string> bootstrap_nodes;
    std::vector<std::string> discovered_peers;

public:
    PeerDiscovery() {
        bootstrap_nodes = {
            "192.168.1.100:8080",
            "192.168.1.101:8080",
            "192.168.1.102:8080"
        };
    }

    void discover_peers() {
        std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(1, 10);

        for (const auto& node : bootstrap_nodes) {
            if (dist(rng) > 3) {
                discovered_peers.push_back(node);
            }
        }

        for (int i = 0; i < 5; i++) {
            std::string peer = "192.168.1." + std::to_string(110 + i) + ":8080";
            discovered_peers.push_back(peer);
        }
    }

    std::vector<std::string> get_available_peers() const {
        return discovered_peers;
    }

    void add_bootstrap_node(const std::string& node) {
        bootstrap_nodes.push_back(node);
    }
};
