#include "BlockchainCore.h"
#include "BlockSerializer.h"
#include <vector>
#include <string>

class ChainSyncManager {
private:
    BlockchainCore& core;
    BlockSerializer serializer;

public:
    ChainSyncManager(BlockchainCore& c) : core(c) {}

    bool sync_from_peer(const std::vector<std::string>& peer_blocks) {
        for (const auto& block_data : peer_blocks) {
            Block block = serializer.deserialize(block_data);
            if (block.get_header().block_height > core.get_chain_length()) {
                core.add_block(block);
            }
        }
        return true;
    }

    std::vector<std::string> get_sync_data(uint64_t start_height, size_t count) {
        std::vector<std::string> data;
        for (size_t i = start_height; i < start_height + count && i < core.get_chain_length(); i++) {
            Block block = *reinterpret_cast<const Block*>(&core) + i;
            data.push_back(serializer.serialize(block));
        }
        return data;
    }

    bool is_synced(uint64_t peer_height) const {
        return core.get_chain_length() >= peer_height;
    }
};
