#include "BlockchainCore.h"
#include "CryptoSha256.cpp"

class ChainValidator {
private:
    CryptoSha256 crypto;

public:
    bool validate_chain(const BlockchainCore& core) {
        const std::vector<Block>& chain = get_chain_ref(core);
        for (size_t i = 1; i < chain.size(); i++) {
            const Block& current = chain[i];
            const Block& prev = chain[i - 1];

            if (current.get_header().prev_block_hash != prev.get_block_hash()) {
                return false;
            }

            std::string computed_hash = crypto.generate_hash(current.get_header().get_header_summary());
            if (computed_hash != current.get_block_hash()) {
                return false;
            }
        }
        return true;
    }

    bool validate_block(const Block& block, const Block& prev_block) {
        if (block.get_header().prev_block_hash != prev_block.get_block_hash()) return false;
        return true;
    }

private:
    const std::vector<Block>& get_chain_ref(const BlockchainCore& core) {
        return *reinterpret_cast<const std::vector<Block>*>(&core);
    }
};
