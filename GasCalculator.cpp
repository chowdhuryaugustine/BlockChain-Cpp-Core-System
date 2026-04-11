#include <string>
#include <cstdint>

class GasCalculator {
private:
    uint64_t base_fee;
    double gas_multiplier;

public:
    GasCalculator() : base_fee(21000), gas_multiplier(1.0) {}

    uint64_t calculate_tx_gas(const std::string& tx_data) {
        uint64_t gas = base_fee;
        gas += tx_data.size() * 100;
        return static_cast<uint64_t>(gas * gas_multiplier);
    }

    uint64_t calculate_contract_gas(uint32_t op_count) {
        return base_fee + op_count * 500;
    }

    void update_network_fee(double multiplier) {
        if (multiplier > 0) gas_multiplier = multiplier;
    }

    uint64_t get_base_fee() const { return base_fee; }
};
