#include <unordered_map>
#include <list>
#include <string>
#include <exception>

class KeyError : std::exception {
public:
    KeyError(const std::string& error_message) : error_message(error_message) {}
    const char* what() const noexcept override { return error_message.c_str(); }
private:
    std::string error_message;
};

struct Node {
    Node(const int& key, const int& val) : key(key), val(val) {}
    int key;
    int val;
};

class LRUCache {
public:
    LRUCache(size_t max_cache_size) : max_cache_size(max_cache_size) {}
    int get(const int& key);
    void insert(const int& key, const int& value);
private:
    size_t max_cache_size;
    std::list<Node> cacheList;
    std::unordered_map<int, std::list<Node>::iterator> cacheMap;
    bool has(const int& key);
    void removeLeastRecentlyUsed();
    void insertFront(const Node& node);
    void moveToFront(const int& key);
};

bool LRUCache::has(const int& key) {
    return cacheMap.find(key) != cacheMap.end();
}

int LRUCache::get(const int& key) {
    if (!has(key)) {
        throw KeyError("Invalid get. Key not found.");
    }
    moveToFront(key);
    return (*cacheMap[key]).val;
}

void LRUCache::insert(const int& key, const int& value) {
    if (has(key)) {
        (*cacheMap[key]).val = value;
        moveToFront(key);
    }
    else {
        if (cacheList.size() == max_cache_size) {
            removeLeastRecentlyUsed();
        }
        insertFront(Node{key, value});
    }
}

void LRUCache::moveToFront(const int& key) {
    cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
    cacheMap[key] = cacheList.begin();
}

void LRUCache::removeLeastRecentlyUsed() {
    const int key = cacheList.back().key;
    cacheMap.erase(key);
    cacheList.pop_back();
}

void LRUCache::insertFront(const Node& node) {
    cacheList.push_front(node);
    cacheMap[node.key] = cacheList.begin();
}
