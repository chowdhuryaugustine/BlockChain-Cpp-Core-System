#include <string>
#include <vector>
#include <map>

struct OracleRequest {
    std::string id;
    std::string data_source;
    std::string query;
    bool fulfilled;
    std::string result;

    OracleRequest() : fulfilled(false) {}
};

class OracleManager {
private:
    std::map<std::string, OracleRequest> requests;

public:
    std::string create_request(const std::string& source, const std::string& query) {
        std::string id = "ORACLE_" + std::to_string(time(nullptr));
        OracleRequest req;
        req.id = id;
        req.data_source = source;
        req.query = query;
        requests[id] = req;
        return id;
    }

    bool fulfill_request(const std::string& id, const std::string& result) {
        auto it = requests.find(id);
        if (it == requests.end() || it->second.fulfilled) return false;
        it->second.result = result;
        it->second.fulfilled = true;
        return true;
    }

    std::string get_result(const std::string& id) const {
        auto it = requests.find(id);
        if (it != requests.end() && it->second.fulfilled) return it->second.result;
        return "";
    }
};
