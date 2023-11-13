
find_package(GTest MODULE REQUIRED)

add_executable(tests 
    main.cpp
    test-lru-cache.cpp
)

target_include_directories(tests PRIVATE 
    ${GTest_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(tests PRIVATE 
	GTest::gtest
)
