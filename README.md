### LRU Cache
A header-only LRU cache with C++11. 

In comparison to common C++ LRU cache implementation, this library will have a few additional features and advantages:
- Cache Resizing: many LRU caches require a size on initialization, but cannot be subsequently changed
- Move semantics: values can be moved for the insertion operation

In the future, thread-safety is another feature that may be supproted. 
Main operations:
- Insert: insert a new key-value pair
- Get: retrieve value for a given key
- Exists: check if given key is in the cache
- Size: get the current cache size
- Resize: change the current cache size, clearing least frequent items if getting smaller
- Clear: Remove all elements in the cache   

### Design
The 'get' and 'insert' operations both have O(1) time complexity by using an `std::list` and `std::unordered_map`.

The `std::list` contains the key-value pairs, while the `std::unordered_map` contains keys mapping to iterators in the list.

### In-Progress
Currently, I am prototyping some the LRU Cache

### Future Steps
- Refine CMake and Conan
- Add CI/CD with GitHub actions
- Add dev container for consistent development experience
