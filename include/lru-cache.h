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
    std::list<Node<Key, Value>> cache_list;
    std::unordered_map<Key, typename std::list<Node<Key, Value>>::iterator> cache_map;
    bool has(const Key& key);
    void removeLeastRecentlyUsed();
    void insertFront(const Node<Key, Value>& node);
    void moveToFront(const Key& key);
};

template<typename Key, typename Value>
bool LRUCache<Key, Value>::has(const Key& key) {
    return cache_map.find(key) != cache_map.end();
}

template<typename Key, typename Value>
Value LRUCache<Key, Value>::get(const Key& key) {
    if (!has(key)) {
        throw KeyError("Invalid get. Key not found.");
    }
    moveToFront(key);
    return (*cache_map[key]).val;
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::insert(const Key& key, const Value& value) {
    if (has(key)) {
        (*cache_map[key]).val = value;
        moveToFront(key);
    }
    else {
        if (cache_list.size() == max_cache_size) {
            removeLeastRecentlyUsed();
        }
        insertFront(Node{key, value});
    }
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::moveToFront(const Key& key) {
    cache_list.splice(cache_list.begin(), cache_list, cache_map[key]);
    cache_map[key] = cache_list.begin();
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::removeLeastRecentlyUsed() {
    const Key key = cache_list.back().key;
    cache_map.erase(key);
    cache_list.pop_back();
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::insertFront(const Node<Key, Value>& node) {
    cache_list.push_front(node);
    cache_map[node.key] = cache_list.begin();
}
