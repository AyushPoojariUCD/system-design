#include <iostream>
#include <unordered_map>
#include <mutex>

// LRU Cache implementation
// Compile: g++ -std=c++17 lru_cache.cpp -o lru_cache
// Run: ./lru_cache

class LRUCache {
private:
    struct Node {
        int key;
        int value;
        Node* prev;
        Node* next;
        Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
    };

    int capacity;
    std::unordered_map<int, Node*> cache; // key -> node
    Node* head; // dummy head (most recent comes after head)
    Node* tail; // dummy tail (least recent comes before tail)
    std::mutex mtx; // protect cache for thread-safety

    // remove node from current position
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // add node right after head (most recent)
    void addToFront(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    // move existing node to front
    void moveToFront(Node* node) {
        removeNode(node);
        addToFront(node);
    }

    // pop the least recently used node (node before tail)
    Node* popTail() {
        Node* node = tail->prev;
        if (node == head) return nullptr; // empty
        removeNode(node);
        return node;
    }

public:
    LRUCache(int cap) : capacity(cap) {
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        // cleanup nodes
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
    }

    // Get value for key if exists, else -1
    int get(int key) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = cache.find(key);
        if (it == cache.end()) return -1;
        Node* node = it->second;
        moveToFront(node);
        return node->value;
    }

    // Put key,value into cache. If key exists, update and move to front.
    void put(int key, int value) {
        std::lock_guard<std::mutex> lock(mtx);
        auto it = cache.find(key);
        if (it != cache.end()) {
            Node* node = it->second;
            node->value = value;
            moveToFront(node);
        } else {
            if ((int)cache.size() == capacity) {
                Node* lru = popTail();
                if (lru) {
                    cache.erase(lru->key);
                    delete lru;
                }
            }
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addToFront(newNode);
        }
    }

    // For debugging: print current cache from most recent to least recent
    void debugPrint() {
        std::lock_guard<std::mutex> lock(mtx);
        Node* cur = head->next;
        std::cout << "Cache (MRU -> LRU): ";
        while (cur != tail) {
            std::cout << "[" << cur->key << ":" << cur->value << "] ";
            cur = cur->next;
        }
        std::cout << "\n";
    }
};

// Demo main
int main() {
    LRUCache cache(2); // capacity 2

    cache.put(1, 10);
    cache.put(2, 20);
    cache.debugPrint(); // [2:20] [1:10]

    std::cout << "get(1): " << cache.get(1) << "\n"; // returns 10
    cache.debugPrint(); // [1:10] [2:20]

    cache.put(3, 30); // evicts key 2
    cache.debugPrint(); // [3:30] [1:10]

    std::cout << "get(2): " << cache.get(2) << "\n"; // returns -1

    cache.put(4, 40); // evicts key 1
    cache.debugPrint(); // [4:40] [3:30]

    std::cout << "get(1): " << cache.get(1) << "\n"; // -1
    std::cout << "get(3): " << cache.get(3) << "\n"; // 30
    std::cout << "get(4): " << cache.get(4) << "\n"; // 40

    return 0;
}
