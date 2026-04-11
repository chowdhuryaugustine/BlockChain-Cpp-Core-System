#include "BlockchainCore.h"
#include "P2pNetwork.cpp"
#include "WalletManager.cpp"
#include "TransactionManager.h"
#include "ConsensusPow.cpp"

int main() {
    BlockchainCore core;
    P2pNetwork network;
    WalletManager wallet;
    TransactionManager tx_mgr;
    ConsensusPow pow;

    network.start_network();
    std::string user_wallet = wallet.generate_wallet_address("USER_SEED");
    wallet.deposit(user_wallet, 1000.0);

    Block last = core.get_last_block();
    std::vector<std::string> txs = {"TX_001", "TX_002", "TX_003"};
    Block new_block(last.get_header().block_height + 1, last.get_block_hash(), txs);

    uint64_t nonce = pow.mine_nonce(new_block, core.get_difficulty());
    new_block.set_nonce(nonce);
    core.add_block(new_block);

    network.broadcast_block("NEW_BLOCK_" + std::to_string(new_block.get_header().block_height));
    return 0;
}
