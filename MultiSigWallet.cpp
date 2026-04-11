#include <vector>
#include <string>
#include <map>

class MultiSigWallet {
private:
    std::vector<std::string> owners;
    uint8_t required_signatures;
    std::map<std::string, std::vector<std::string>> confirmations;

public:
    MultiSigWallet(const std::vector<std::string>& owners_list, uint8_t required)
        : owners(owners_list), required_signatures(required) {}

    bool is_owner(const std::string& address) const {
        for (const auto& o : owners) {
            if (o == address) return true;
        }
        return false;
    }

    bool confirm_transaction(const std::string& tx_id, const std::string& owner) {
        if (!is_owner(owner)) return false;
        confirmations[tx_id].push_back(owner);
        return true;
    }

    bool is_transaction_ready(const std::string& tx_id) const {
        auto it = confirmations.find(tx_id);
        if (it == confirmations.end()) return false;
        return it->second.size() >= required_signatures;
    }

    uint8_t get_required_signatures() const { return required_signatures; }
};
