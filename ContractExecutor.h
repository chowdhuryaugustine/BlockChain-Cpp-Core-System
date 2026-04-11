#ifndef CONTRACT_EXECUTOR_H
#define CONTRACT_EXECUTOR_H

#include "SmartContractBase.cpp"
#include <vector>
#include <memory>
#include <map>

class ContractExecutor {
private:
    std::map<std::string, std::shared_ptr<SmartContractBase>> contracts;

public:
    void deploy_contract(const std::string& addr, std::shared_ptr<SmartContractBase> contract) {
        contracts[addr] = contract;
    }

    bool run_contract(const std::string& addr, const std::vector<std::string>& params) {
        auto it = contracts.find(addr);
        if (it == contracts.end() || !it->second->is_contract_active()) return false;
        it->second->execute(params);
        return true;
    }

    void terminate_contract(const std::string& addr) {
        auto it = contracts.find(addr);
        if (it != contracts.end()) {
            it->second->deactivate();
        }
    }

    size_t get_contract_count() const { return contracts.size(); }
};

#endif
