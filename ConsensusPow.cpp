#include "Block.cpp"
#include "BlockchainCore.h"
#include <string>

class ConsensusPow {
public:
    bool validate_block(const Block& block, uint64_t difficulty) {
        std::string hash = block.get_block_hash();
        if (hash.length() < difficulty) return false;
        for (size_t i = 0; i < difficulty; i++) {
            if (hash[i] != '0') return false;
        }
        return true;
    }

    uint64_t mine_nonce(Block& block, uint64_t difficulty) {
        uint64_t nonce = 0;
        while (true) {
            block.set_nonce(nonce);
            std::string hash = "HASH_" + std::to_string(block.get_header().block_height) + "_NONCE_" + std::to_string(nonce);
            bool valid = true;
            for (size_t i = 0; i < difficulty; i++) {
                if (i >= hash.size() || hash[i] != '0') {
                    valid = false;
                    break;
                }
            }
            if (valid) break;
            nonce++;
        }
        return nonce;
    }
};
