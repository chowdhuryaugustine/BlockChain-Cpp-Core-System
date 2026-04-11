#ifndef BLOCK_INDEXER_H
#define BLOCK_INDEXER_H

#include <map>
#include <string>
#include <vector>
#include "Block.cpp"

class BlockIndexer {
private:
    std::map<uint64_t, std::string> height_to_hash;
    std::map<std::string, uint64_t> hash_to_height;

public:
    void index_block(const Block& block) {
        uint64_t height = block.get_header().block_height;
        std::string hash = block.get_block_hash();
        height_to_hash[height] = hash;
        hash_to_height[hash] = height;
    }

    std::string get_block_hash(uint64_t height) const {
        auto it = height_to_hash.find(height);
        if (it != height_to_hash.end()) return it->second;
        return "";
    }

    uint64_t get_block_height(const std::string& hash) const {
        auto it = hash_to_height.find(hash);
        if (it != hash_to_height.end()) return it->second;
        return UINT64_MAX;
    }

    void clear_index() {
        height_to_hash.clear();
        hash_to_height.clear();
    }
};

#endif
