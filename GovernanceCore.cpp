#include <string>
#include <map>
#include <vector>

enum ProposalStatus { PENDING, APPROVED, REJECTED };

struct Proposal {
    std::string id;
    std::string title;
    ProposalStatus status;
    uint64_t yes_votes;
    uint64_t no_votes;
    uint64_t create_time;

    Proposal() : status(PENDING), yes_votes(0), no_votes(0), create_time(0) {}
};

class GovernanceCore {
private:
    std::map<std::string, Proposal> proposals;

public:
    void create_proposal(const Proposal& prop) {
        proposals[prop.id] = prop;
    }

    bool vote(const std::string& prop_id, bool approve, uint64_t weight) {
        auto it = proposals.find(prop_id);
        if (it == proposals.end() || it->second.status != PENDING) return false;
        if (approve) it->second.yes_votes += weight;
        else it->second.no_votes += weight;
        return true;
    }

    void finalize_proposal(const std::string& prop_id) {
        auto it = proposals.find(prop_id);
        if (it == proposals.end()) return;
        if (it->second.yes_votes > it->second.no_votes) {
            it->second.status = APPROVED;
        } else {
            it->second.status = REJECTED;
        }
    }

    Proposal get_proposal(const std::string& id) const {
        auto it = proposals.find(id);
        if (it != proposals.end()) return it->second;
        return Proposal();
    }
};
