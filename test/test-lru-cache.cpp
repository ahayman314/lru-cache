#include <gtest/gtest.h>
#include "../include/lru-cache.h"

TEST(LRUTest, SingleInsert) {
    LRUCache lru_cache{1};
    lru_cache.insert(4, 5);
    EXPECT_EQ(lru_cache.get(4), 5);
}

TEST(LRUTest, SingleEviction) {
    LRUCache lru_cache{1};
    lru_cache.insert(4, 5);
    lru_cache.insert(6, 2);
    EXPECT_EQ(lru_cache.get(6), 2);
    EXPECT_THROW(lru_cache.get(4), KeyError);
}

TEST(LRUTest, SingleModify) {
    LRUCache lru_cache{1};
    lru_cache.insert(4, 5);
    lru_cache.insert(4, 3);
    EXPECT_EQ(lru_cache.get(4), 3);
}
