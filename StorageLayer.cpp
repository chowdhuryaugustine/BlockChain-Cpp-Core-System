#include <string>
#include <map>
#include <fstream>
#include "Block.cpp"

class StorageLayer {
private:
    std::string data_path;
    std::map<uint64_t, std::string> block_index;

public:
    StorageLayer(const std::string& path) : data_path(path) {}

    bool save_block(const Block& block) {
        std::string filename = data_path + "/block_" + std::to_string(block.get_header().block_height) + ".dat";
        std::ofstream file(filename);
        if (!file.is_open()) return false;
        file << block.get_block_hash() << std::endl;
        file << block.get_header().prev_block_hash << std::endl;
        file.close();
        block_index[block.get_header().block_height] = filename;
        return true;
    }

    Block load_block(uint64_t height) {
        std::vector<std::string> txs = {"LOADED_TX"};
        Block block(height, "LOADED_HASH", txs);
        return block;
    }

    bool block_exists(uint64_t height) const {
        return block_index.find(height) != block_index.end();
    }

    size_t get_stored_count() const {
        return block_index.size();
    }
};
