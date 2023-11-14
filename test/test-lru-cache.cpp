#include <gtest/gtest.h>
#include "../include/lru-cache.h"

TEST(LRUTest, IntSingleInsert) {
    LRUCache<int, int> lru_cache{1};
    lru_cache.insert(4, 5);
    EXPECT_EQ(lru_cache.get(4), 5);
}

TEST(LRUTest, IntSingleEviction) {
    LRUCache<int, int> lru_cache{1};
    lru_cache.insert(4, 5);
    lru_cache.insert(6, 2);
    EXPECT_EQ(lru_cache.get(6), 2);
    EXPECT_THROW(lru_cache.get(4), KeyError);
}

TEST(LRUTest, IntSingleModify) {
    LRUCache<int, int> lru_cache{1};
    lru_cache.insert(4, 5);
    lru_cache.insert(4, 3);
    EXPECT_EQ(lru_cache.get(4), 3);
}

TEST(LRUTest, StringSingleInsert) {
    LRUCache<std::string, int> lru_cache{1};
    lru_cache.insert("key", 5);
    EXPECT_EQ(lru_cache.get("key"), 5);
}

TEST(LRUTest, StringSingleEviction) {
    LRUCache<std::string, int> lru_cache{1};
    lru_cache.insert("key1", 5);
    lru_cache.insert("key2", 2);
    EXPECT_EQ(lru_cache.get("key2"), 2);
    EXPECT_THROW(lru_cache.get("key1"), KeyError);
}

TEST(LRUTest, StringSingleModify) {
    LRUCache<std::string, int> lru_cache{1};
    lru_cache.insert("key", 5);
    lru_cache.insert("key", 3);
    EXPECT_EQ(lru_cache.get("key"), 3);
}

TEST(LRUTest, ResizeToZero) {
    LRUCache<std::string, int> lru_cache{1};
    lru_cache.insert("key", 5);
    lru_cache.resize(0);
    EXPECT_THROW(lru_cache.get("key"), KeyError);
}

TEST(LRUTest, ResizeToOne) {
    LRUCache<std::string, int> lru_cache{2};
    lru_cache.insert("key1", 5);
    lru_cache.insert("key2", 6);
    lru_cache.resize(1);
    EXPECT_THROW(lru_cache.get("key1"), KeyError);
    EXPECT_EQ(lru_cache.get("key2"), 6);
}
