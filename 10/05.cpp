#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <cstdint>

uint32_t RSHash(const std::string& str) {
    uint32_t b = 378551, a = 63689, hash = 0;
    for (char c : str) { hash = hash * a + c; a *= b; }
    return hash;
}
uint32_t JSHash(const std::string& str) {
    uint32_t hash = 1315423911;
    for (char c : str) hash ^= ((hash << 5) + c + (hash >> 2));
    return hash;
}
uint32_t PJWHash(const std::string& str) {
    uint32_t hash = 0, test = 0;
    for (char c : str) {
        hash = (hash << 4) + c;
        if ((test = hash & 0xF0000000L) != 0) hash = ((hash ^ (test >> 24)) & (~0xF0000000L));
    }
    return hash;
}
uint32_t ELFHash(const std::string& str) {
    uint32_t hash = 0, x = 0;
    for (char c : str) {
        hash = (hash << 4) + c;
        if ((x = hash & 0xF0000000L) != 0) hash ^= (x >> 24);
        hash &= ~x;
    }
    return hash;
}
uint32_t BKDRHash(const std::string& str) {
    uint32_t seed = 131, hash = 0;
    for (char c : str) hash = (hash * seed) + c;
    return hash;
}
uint32_t SDBMHash(const std::string& str) {
    uint32_t hash = 0;
    for (char c : str) hash = c + (hash << 6) + (hash << 16) - hash;
    return hash;
}
uint32_t DJBHash(const std::string& str) {
    uint32_t hash = 5381;
    for (char c : str) hash = ((hash << 5) + hash) + c;
    return hash;
}
uint32_t DEKHash(const std::string& str) {
    uint32_t hash = str.length();
    for (char c : str) hash = ((hash << 5) ^ (hash >> 27)) ^ c;
    return hash;
}
uint32_t FNVHash(const std::string& str) {
    uint32_t fnv_prime = 0x811C9DC5, hash = 0;
    for (char c : str) { hash *= fnv_prime; hash ^= c; }
    return hash;
}

int main() {
    std::vector<int> counts = {1000, 5000, 10000, 50000, 100000};
    auto runner = [&](auto func, std::string name) {
        std::cout << name << " results (Count:Collisions):\n";
        for (int n : counts) {
            std::unordered_set<uint32_t> seen;
            int collisions = 0;
            for (int i = 0; i < n; ++i) {
                if (!seen.insert(func("str_" + std::to_string(i))).second) collisions++;
            }
            std::cout << n << ":" << collisions << " ";
        }
        std::cout << "\n\n";
    };
    runner(RSHash, "RS"); runner(JSHash, "JS"); runner(PJWHash, "PJW");
    runner(ELFHash, "ELF"); runner(BKDRHash, "BKDR"); runner(SDBMHash, "SDBM");
    runner(DJBHash, "DJB"); runner(DEKHash, "DEK"); runner(FNVHash, "FNV");
    return 0;
}