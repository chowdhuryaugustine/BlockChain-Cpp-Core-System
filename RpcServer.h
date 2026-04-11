#ifndef RPC_SERVER_H
#define RPC_SERVER_H

#include <string>
#include <functional>
#include <map>

class RpcServer {
private:
    uint16_t port;
    bool running;
    std::map<std::string, std::function<std::string(std::string)>> handlers;

public:
    RpcServer(uint16_t p) : port(p), running(false) {}

    void start() {
        running = true;
    }

    void stop() {
        running = false;
    }

    void register_method(const std::string& name, std::function<std::string(std::string)> handler) {
        handlers[name] = handler;
    }

    std::string call_method(const std::string& name, const std::string& params) {
        if (handlers.find(name) == handlers.end()) return "ERROR: METHOD NOT FOUND";
        return handlers[name](params);
    }

    bool is_running() const { return running; }
    uint16_t get_port() const { return port; }
};

#endif
