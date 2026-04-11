#ifndef SIGNATURE_VERIFIER_H
#define SIGNATURE_VERIFIER_H

#include <string>
#include "CryptoSha256.cpp"

class SignatureVerifier {
private:
    CryptoSha256 crypto;

public:
    bool verify_block_signature(const std::string& block_hash, const std::string& signature, const std::string& pub_key) {
        std::string computed = crypto.generate_hash(block_hash + pub_key);
        return computed == signature;
    }

    bool verify_transaction(const std::string& tx_hash, const std::string& sig, const std::string& pub_key) {
        return verify_block_signature(tx_hash, sig, pub_key);
    }

    std::string sign_data(const std::string& data, const std::string& priv_key) {
        return crypto.generate_hash(data + priv_key);
    }
};

#endif
