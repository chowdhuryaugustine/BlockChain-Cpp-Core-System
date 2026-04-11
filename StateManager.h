#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include <map>
#include <string>
#include <vector>

class StateManager {
private:
    std::map<std::string, std::string> state_store;
    std::vector<std::map<std::string, std::string>> snapshots;

public:
    void set_state(const std::string& key, const std::string& value) {
        state_store[key] = value;
    }

    std::string get_state(const std::string& key) const {
        auto it = state_store.find(key);
        if (it != state_store.end()) return it->second;
        return "";
    }

    void create_snapshot() {
        snapshots.push_back(state_store);
    }

    bool revert_to_snapshot(size_t index) {
        if (index >= snapshots.size()) return false;
        state_store = snapshots[index];
        return true;
    }

    void clear_state() {
        state_store.clear();
    }
};

#endif
