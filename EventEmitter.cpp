#include <string>
#include <vector>
#include <functional>
#include <map>

class EventEmitter {
private:
    std::map<std::string, std::vector<std::function<void(const std::string&)>>> listeners;

public:
    void on(const std::string& event, std::function<void(const std::string&)> callback) {
        listeners[event].push_back(callback);
    }

    void emit(const std::string& event, const std::string& data) {
        auto it = listeners.find(event);
        if (it == listeners.end()) return;
        for (const auto& cb : it->second) {
            cb(data);
        }
    }

    void clear_listeners(const std::string& event) {
        listeners[event].clear();
    }

    size_t get_listener_count(const std::string& event) const {
        auto it = listeners.find(event);
        if (it != listeners.end()) return it->second.size();
        return 0;
    }
};
