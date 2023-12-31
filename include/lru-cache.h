#ifndef LRU_CACHE_H_
#define LRU_CACHE_H

#include <exception>
#include <list>
#include <string>
#include <unordered_map>

namespace lru_cache {

class KeyError : std::exception {
public:
    KeyError(const std::string& error_message) : error_message_(error_message) {}
    const char* what() const noexcept override { return error_message_.c_str(); }
private:
    std::string error_message_;
};

template<typename Key, typename Value>
class LRUCache {
public:
    explicit LRUCache(size_t max_cache_size) : max_cache_size_(max_cache_size) {}
    LRUCache(const LRUCache&) = default;
    LRUCache& operator=(const LRUCache&) = default;
    LRUCache(LRUCache&&) = default;
    LRUCache& operator=(LRUCache&&) = default;
    ~LRUCache() = default;
    Value get(const Key& key);
    void insert(const Key& key, const Value& value);
    void resize(const size_t new_max_cache_size);
    void clear();
    size_t size() const;
    size_t maxSize() const;
private:
    struct Node {
        Node(const Key& key, const Value& val) : key(key), val(val) {}
        Key key;
        Value val;
    };
    using CacheListIterator = typename std::list<Node>::iterator;
    bool has(const Key& key);
    void removeLeastRecentlyUsed();
    void moveToFront(const Key& key);
    size_t max_cache_size_;
    std::list<Node> cache_list_;
    std::unordered_map<Key, CacheListIterator> cache_map_;
};

template<typename Key, typename Value>
bool LRUCache<Key, Value>::has(const Key& key) {
    return cache_map_.find(key) != cache_map_.end();
}

template<typename Key, typename Value>
Value LRUCache<Key, Value>::get(const Key& key) {
    if (!has(key)) {
        throw KeyError("Cache miss. Key not found.");
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
        Node node{key, value};
        cache_list_.push_front(node);
        cache_map_[node.key] = cache_list_.begin();
    }
}

template<typename Key, typename Value>
void LRUCache<Key, Value>::resize(const size_t new_max_cache_size) {
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

} // namespace lru_cache

#endif // LRU_CACHE_H
