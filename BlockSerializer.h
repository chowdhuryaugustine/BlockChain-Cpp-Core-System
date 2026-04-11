#ifndef BLOCK_SERIALIZER_H
#define BLOCK_SERIALIZER_H

#include "Block.cpp"
#include <string>
#include <sstream>
#include <vector>

class BlockSerializer {
public:
    std::string serialize(const Block& block) {
        std::stringstream ss;
        auto header = block.get_header();
        ss << header.block_height << "|"
           << header.prev_block_hash << "|"
           << header.merkle_root << "|"
           << header.nonce << "|"
           << header.difficulty << "|";

        auto txs = block.get_transactions();
        ss << txs.size() << "|";
        for (const auto& tx : txs) {
            ss << tx << "|";
        }
        ss << block.get_block_hash();
        return ss.str();
    }

    Block deserialize(const std::string& data) {
        std::vector<std::string> parts = split(data, '|');
        std::vector<std::string> txs;
        size_t tx_count = std::stoull(parts[5]);
        for (size_t i = 0; i < tx_count; i++) {
            txs.push_back(parts[6 + i]);
        }
        Block block(std::stoull(parts[0]), parts[1], txs);
        return block;
    }

private:
    std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream token_stream(s);
        while (std::getline(token_stream, token, delimiter)) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

#endif
