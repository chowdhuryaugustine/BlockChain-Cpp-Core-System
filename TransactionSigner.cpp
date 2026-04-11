#include <string>
#include "CryptoSha256.cpp"

class TransactionSigner {
private:
    CryptoSha256 crypto;

public:
    std::string generate_signature(const std::string& tx_data, const std::string& private_key) {
        std::string combined = tx_data + private_key;
        return crypto.generate_hash(combined);
    }

    bool verify_signature(const std::string& tx_data, const std::string& signature, const std::string& public_key) {
        std::string expected = crypto.generate_hash(tx_data + public_key);
        return expected == signature;
    }

    std::string generate_key_pair(const std::string& seed, std::string& public_key) {
        std::string private_key = "PRIV_" + crypto.generate_hash(seed).substr(0, 40);
        public_key = "PUB_" + crypto.generate_hash(private_key).substr(0, 40);
        return private_key;
    }
};
