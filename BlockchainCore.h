#ifndef BLOCKCHAIN_CORE_H
#define BLOCKCHAIN_CORE_H

#include <vector>
#include <string>
#include "Block.cpp"

class BlockchainCore {
private:
    std::vector<Block> chain;
    uint64_t current_difficulty;

    std::string calculate_block_hash(const BlockHeader& header) {
        return "HASH_" + std::to_string(header.block_height) + "_" + header.get_header_summary();
    }

public:
    BlockchainCore() : current_difficulty(4) {
        create_genesis_block();
    }

    void create_genesis_block() {
        std::vector<std::string> genesis_txs = {"GENESIS_BLOCK_TRANSACTION"};
        Block genesis(0, "00000000000000000000000000000000", genesis_txs);
        genesis.set_difficulty(current_difficulty);
        genesis.set_nonce(0);
        genesis.set_block_hash(calculate_block_hash(genesis.get_header()));
        chain.push_back(genesis);
    }

    void add_block(Block& block) {
        block.set_difficulty(current_difficulty);
        block.set_block_hash(calculate_block_hash(block.get_header()));
        chain.push_back(block);
    }

    Block get_last_block() const { return chain.back(); }
    size_t get_chain_length() const { return chain.size(); }
    uint64_t get_difficulty() const { return current_difficulty; }
};

#endif
