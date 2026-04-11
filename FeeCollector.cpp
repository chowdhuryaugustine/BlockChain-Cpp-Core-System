#include <string>
#include <map>

class FeeCollector {
private:
    std::string treasury_address;
    std::map<std::string, double> accumulated_fees;

public:
    FeeCollector(const std::string& treasury) : treasury_address(treasury) {}

    double collect_fee(const std::string& user, double amount) {
        if (amount <= 0) return 0.0;
        double fee = amount * 0.01;
        accumulated_fees[treasury_address] += fee;
        return fee;
    }

    double get_treasury_balance() const {
        auto it = accumulated_fees.find(treasury_address);
        if (it != accumulated_fees.end()) return it->second;
        return 0.0;
    }

    void distribute_fees(const std::map<std::string, double>& distribution) {
        for (const auto& pair : distribution) {
            accumulated_fees[pair.first] += pair.second;
        }
        accumulated_fees[treasury_address] = 0;
    }

    std::string get_treasury() const { return treasury_address; }
};
