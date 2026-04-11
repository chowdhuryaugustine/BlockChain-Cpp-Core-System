#include <string>
#include <map>
#include <vector>

class SmartContractBase {
private:
    std::string contract_address;
    std::map<std::string, std::string> storage;
    bool is_active;

public:
    SmartContractBase(const std::string& addr) : contract_address(addr), is_active(true) {}

    virtual void execute(const std::vector<std::string>& params) = 0;

    void set_storage(const std::string& key, const std::string& value) {
        storage[key] = value;
    }

    std::string get_storage(const std::string& key) const {
        auto it = storage.find(key);
        if (it != storage.end()) return it->second;
        return "";
    }

    void activate() { is_active = true; }
    void deactivate() { is_active = false; }
    bool is_contract_active() const { return is_active; }
    std::string get_address() const { return contract_address; }
};
