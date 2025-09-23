#include <iostream>
#include <vector>
#include <string>
#include <functional>  // for std::hash

using namespace std;

class BloomFilter {
    vector<bool> bitArray;
    int size;   // number of bits
    int k;      // number of hash functions

    // Different hash functions generated using salt
    size_t hash(const string &item, int seed) const {
        hash<string> h;
        return (h(item + to_string(seed))) % size;
    }

public:
    BloomFilter(int m, int k) : size(m), k(k) {
        bitArray.resize(m, false);
    }

    // Insert element
    void insert(const string &item) {
        for (int i = 0; i < k; i++) {
            int pos = hash(item, i);
            bitArray[pos] = true;
        }
    }

    // Check membership
    bool possiblyContains(const string &item) const {
        for (int i = 0; i < k; i++) {
            int pos = hash(item, i);
            if (!bitArray[pos]) return false;  // definitely not present
        }
        return true;  // probably present
    }
};

int main() {
    // Bloom Filter with size 20 bits and 3 hash functions
    BloomFilter bf(20, 3);

    // Insert elements
    bf.insert("apple");
    bf.insert("banana");
    bf.insert("cherry");

    // Queries
    cout << "apple? " << (bf.possiblyContains("apple") ? "Probably Yes" : "No") << endl;
    cout << "banana? " << (bf.possiblyContains("banana") ? "Probably Yes" : "No") << endl;
    cout << "mango? " << (bf.possiblyContains("mango") ? "Probably Yes" : "No") << endl;

    return 0;
}
