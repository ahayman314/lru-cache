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

    template<typename Key>
    struct Node {
        Node(const Key& key, const int& val) : key(key), val(val) {}
        Key key;
        int val;
    };

    template<typename Key>
    class LRUCache {
    public:
        LRUCache(size_t max_cache_size) : max_cache_size(max_cache_size) {}
        int get(const Key& key);
        void insert(const Key& key, const int& value);
    private:
        size_t max_cache_size;
        std::list<Node<Key>> cacheList;
        std::unordered_map<Key, typename std::list<Node<Key>>::iterator> cacheMap;
        bool has(const Key& key);
        void removeLeastRecentlyUsed();
        void insertFront(const Node<Key>& node);
        void moveToFront(const Key& key);
    };

    template<typename Key>
    bool LRUCache<Key>::has(const Key& key) {
        return cacheMap.find(key) != cacheMap.end();
    }

    template<typename Key>
    int LRUCache<Key>::get(const Key& key) {
        if (!has(key)) {
            throw KeyError("Invalid get. Key not found.");
        }
        moveToFront(key);
        return (*cacheMap[key]).val;
    }

    template<typename Key>
    void LRUCache<Key>::insert(const Key& key, const int& value) {
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

    template<typename Key>
    void LRUCache<Key>::moveToFront(const Key& key) {
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        cacheMap[key] = cacheList.begin();
    }

    template<typename Key>
    void LRUCache<Key>::removeLeastRecentlyUsed() {
        const Key key = cacheList.back().key;
        cacheMap.erase(key);
        cacheList.pop_back();
    }

    template<typename Key>
    void LRUCache<Key>::insertFront(const Node<Key>& node) {
        cacheList.push_front(node);
        cacheMap[node.key] = cacheList.begin();
    }
