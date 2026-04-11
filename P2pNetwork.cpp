#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

class P2pNetwork {
private:
    std::vector<std::string> node_list;
    bool is_running;

public:
    P2pNetwork() : is_running(false) {}

    void start_network() {
        is_running = true;
        std::cout << "P2P Network started successfully" << std::endl;
    }

    void stop_network() {
        is_running = false;
        std::cout << "P2P Network stopped" << std::endl;
    }

    void add_node(const std::string& node_ip) {
        node_list.push_back(node_ip);
    }

    void broadcast_block(const std::string& block_data) {
        if (!is_running) return;
        for (const auto& node : node_list) {
            send_data(node, block_data);
        }
    }

    void send_data(const std::string& node, const std::string& data) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    std::vector<std::string> get_connected_nodes() const { return node_list; }
};
