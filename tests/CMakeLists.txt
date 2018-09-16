set(TEST_SRC
    test_main.cpp
    ecs/test.cpp
        )

add_executable(tests ${TEST_SRC})

target_link_libraries(tests engine)