#ifndef LRU_CACHE_H_
#define LRU_CACHE_H

#include <exception>
#include <list>
#include <string>
#include <unordered_map>

namespace lru_cache {

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
    explicit LRUCache(size_t max_cache_size) : max_cache_size_(max_cache_size) {}
    Value get(const Key& key);
    void insert(const Key& key, const Value& value);
    void resize(size_t new_max_cache_size);
    void clear();
    size_t size() const;
    size_t maxSize() const;
private:
    size_t max_cache_size_;
    std::list<Node<Key, Value>> cache_list_;
    std::unordered_map<Key, typename std::list<Node<Key, Value>>::iterator> cache_map_;
    bool has(const Key& key);
    void removeLeastRecentlyUsed();
    void insertFront(const Node<Key, Value>& node);
    void moveToFront(const Key& key);
};

template<typename Key, typename Value>
bool LRUCache<Key, Value>::has(const Key& key) {
    return cache_map_.find(key) != cache_map_.end();
}

template<typename Key, typename Value>
Value LRUCache<Key, Value>::get(const Key& key) {
    if (!has(key)) {
        throw KeyError("Invalid get. Key not found.");
    }
    moveToFront(key);
    return (*cache_map_[key]).val;
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::insert(const Key& key, const Value& value) {
    if (has(key)) {
        (*cache_map_[key]).val = value;
        moveToFront(key);
    }
    else {
        if (cache_list_.size() == max_cache_size_) {
            removeLeastRecentlyUsed();
        }
        insertFront(Node{key, value});
    }
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::resize(size_t new_max_cache_size) {
    while (max_cache_size_ > new_max_cache_size) {
        removeLeastRecentlyUsed();
        max_cache_size_--;
    }
    max_cache_size_ = new_max_cache_size;
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::clear() {
    resize(0);
}

template<typename Key, typename Value>
size_t LRUCache<Key, Value>::size() const {
    return cache_list_.size();
}

template<typename Key, typename Value>
size_t LRUCache<Key, Value>::maxSize() const {
    return max_cache_size_;
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::moveToFront(const Key& key) {
    cache_list_.splice(cache_list_.begin(), cache_list_, cache_map_[key]);
    cache_map_[key] = cache_list_.begin();
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::removeLeastRecentlyUsed() {
    const Key key = cache_list_.back().key;
    cache_map_.erase(key);
    cache_list_.pop_back();
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::insertFront(const Node<Key, Value>& node) {
    cache_list_.push_front(node);
    cache_map_[node.key] = cache_list_.begin();
}

} // namespace lru_cache

#endif // LRU_CACHE_H
