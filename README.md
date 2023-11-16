### LRU Cache
A header-only LRU cache with C++11.

In addition to standard LRU cache implementations, this cache allows cache re-sizing.

In the future, thread-safety is another feature that may be supproted. 

Main operations:
- Insert: insert a new key-value pair
- Get: retrieve value for a given key
- Size: get the current cache size
- Max Size: get the current max cache size
- Resize: change the current cache size, clearing least frequent items if getting smaller
- Clear: Remove all elements in the cache   

### Quickstart
To get started, copy the header file, and use the LRU Cache: 

```cpp
#include "lru-cache.h"
#include <iostream>

lru_cache::LRUCache<std::string, int> lru_cache{1};

// Insert and get
lru_cache.insert("key1", 5);
lru_cache.insert("key2", 6);

int val2 = lru_cache.get("key2");

try {
    int val1 = lru_cache.get("key1");
}
catch (lru_cache::KeyError &e) {
    std::cout << "Cache error for 'key1': " << e.what() << std::endl;
}

// Size
int cache_size = lru_cache.size();
int current_max_size = lru_cache.maxSize();

// Resize and clear
lru_cache.resize(5);
lru_cache.clear();
```

### Design
The 'get' and 'insert' operations both have O(1) time complexity by using an `std::list` and `std::unordered_map`.

The `std::list` contains the key-value pairs, while the `std::unordered_map` contains keys mapping to iterators in the list.

### In-Progress
Currently, I am prototyping some the LRU Cache

### Future Steps
- Refine CMake and Conan
- Add CI/CD with GitHub actions
- Add dev container for consistent development experience
