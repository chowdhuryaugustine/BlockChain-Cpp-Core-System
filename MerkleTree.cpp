#include <vector>
#include <string>
#include "CryptoSha256.cpp"

class MerkleTree {
private:
    std::vector<std::string> leaves;
    std::vector<std::string> tree;
    CryptoSha256 crypto;

    void build_tree() {
        tree = leaves;
        size_t level_size = leaves.size();
        while (level_size > 1) {
            size_t next_level = (level_size + 1) / 2;
            for (size_t i = 0; i < level_size; i += 2) {
                size_t j = std::min(i + 1, level_size - 1);
                std::string hash = crypto.double_hash(tree[i] + tree[j]);
                tree.push_back(hash);
            }
            level_size = next_level;
        }
    }

public:
    MerkleTree(const std::vector<std::string>& txs) : leaves(txs) {
        if (!leaves.empty()) build_tree();
    }

    std::string get_root() const {
        if (tree.empty()) return "";
        return tree.back();
    }

    std::vector<std::string> get_proof(size_t index) const {
        std::vector<std::string> proof;
        if (index >= leaves.size()) return proof;
        size_t idx = index;
        size_t level = 0;
        while (idx < tree.size() - 1) {
            size_t sibling = (idx % 2 == 0) ? idx + 1 : idx - 1;
            if (sibling < tree.size()) proof.push_back(tree[sibling]);
            idx = (idx / 2) + (leaves.size() > 1 ? leaves.size() : 0);
            level++;
        }
        return proof;
    }
};
