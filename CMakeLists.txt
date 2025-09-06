cmake_minimum_required(VERSION 3.10.0)

project(myContainers VERSION 1.1.0 LANGUAGES C CXX)

set(PROJECT_SOURCE 
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Подключение GoogleTest
add_subdirectory(googletest)

set(TEST_SOURCE 
    tests/myvector_tests.cpp
    tests/mylist1_tests.cpp
    tests/mylist2_tests.cpp
    tests/additional_tests.cpp
)

add_executable(${PROJECT_NAME}_test ${TEST_SOURCE})

set_target_properties(${PROJECT_NAME}_test PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Подключение заголовочных файлов googletest и googlemock
target_include_directories(${PROJECT_NAME}_test PRIVATE 
    ${PROJECT_SOURCE_DIR}/googletest/googletest/include
    ${PROJECT_SOURCE_DIR}/googletest/googlemock/include
    ${PROJECT_SOURCE_DIR}/src
)

# Линковка тестов с gtest и gtest_main
target_link_libraries(${PROJECT_NAME}_test PRIVATE 
    #gtest
    gtest_main
)

# Добавление тестов в CMake
enable_testing()
add_test(NAME MyContainersTest COMMAND ${PROJECT_NAME}_test)