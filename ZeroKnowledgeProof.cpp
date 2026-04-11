#include <string>
#include "CryptoSha256.cpp"

class ZeroKnowledgeProof {
private:
    CryptoSha256 crypto;

public:
    std::string generate_proof(const std::string& secret, const std::string& public_data) {
        std::string commitment = crypto.generate_hash(secret + public_data);
        return "ZK_PROOF_" + commitment.substr(0, 48);
    }

    bool verify_proof(const std::string& proof, const std::string& public_data, const std::string& commitment) {
        std::string expected = "ZK_PROOF_" + crypto.generate_hash(commitment + public_data).substr(0, 48);
        return proof == expected;
    }

    std::string create_commitment(const std::string& secret) {
        return crypto.generate_hash(secret);
    }
};
