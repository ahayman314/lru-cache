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

template<typename Key, typename Value>
struct Node {
    Node(const Key& key, const Value& val) : key(key), val(val) {}
    Key key;
    Value val;
};

template<typename Key, typename Value>
class LRUCache {
public:
    LRUCache(size_t max_cache_size) : max_cache_size(max_cache_size) {}
    Value get(const Key& key);
    void insert(const Key& key, const Value& value);
private:
    size_t max_cache_size;
    std::list<Node<Key, Value>> cacheList;
    std::unordered_map<Key, typename std::list<Node<Key, Value>>::iterator> cacheMap;
    bool has(const Key& key);
    void removeLeastRecentlyUsed();
    void insertFront(const Node<Key, Value>& node);
    void moveToFront(const Key& key);
};

template<typename Key, typename Value>
bool LRUCache<Key, Value>::has(const Key& key) {
    return cacheMap.find(key) != cacheMap.end();
}

template<typename Key, typename Value>
Value LRUCache<Key, Value>::get(const Key& key) {
    if (!has(key)) {
        throw KeyError("Invalid get. Key not found.");
    }
    moveToFront(key);
    return (*cacheMap[key]).val;
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::insert(const Key& key, const Value& value) {
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

template<typename Key, typename Value>
void LRUCache<Key, Value>::moveToFront(const Key& key) {
    cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
    cacheMap[key] = cacheList.begin();
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::removeLeastRecentlyUsed() {
    const Key key = cacheList.back().key;
    cacheMap.erase(key);
    cacheList.pop_back();
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::insertFront(const Node<Key, Value>& node) {
    cacheList.push_front(node);
    cacheMap[node.key] = cacheList.begin();
}
