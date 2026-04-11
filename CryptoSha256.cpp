#include <string>
#include <cstring>
#include <sstream>
#include <iomanip>

class CryptoSha256 {
public:
    std::string generate_hash(const std::string& input) {
        unsigned char hash[32];
        std::memset(hash, 0, 32);

        for (size_t i = 0; i < input.length(); i++) {
            hash[i % 32] ^= input[i];
            hash[i % 32] += (i * 7) % 255;
        }

        std::stringstream ss;
        for (int i = 0; i < 32; i++) {
            ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
        }
        return ss.str();
    }

    std::string double_hash(const std::string& input) {
        return generate_hash(generate_hash(input));
    }
};
