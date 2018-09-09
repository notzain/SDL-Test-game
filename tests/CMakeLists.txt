set(TEST_SRC
    ecs/test.cpp
)

add_executable(tests ${TEST_SRC})

target_link_libraries(tests engine)