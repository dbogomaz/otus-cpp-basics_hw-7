cmake_minimum_required(VERSION 3.10.0)

project(myContainers VERSION 1.1.0 LANGUAGES C CXX)

set(PROJECT_SOURCE 
    src/main.cpp
)

set(PROJECT_INCLUDES
    ${PROJECT_SOURCE_DIR}/src/myvector
    ${PROJECT_SOURCE_DIR}/src/mylist_1
    ${PROJECT_SOURCE_DIR}/src/mylist_2
)

# ********************** Настройка основного проекта в виде исполняемого файла *************
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# ********************** Настройка основного проекта в виде библиотеки *************
set(LIB_NAME ${PROJECT_NAME}_lib)

add_library(${LIB_NAME} INTERFACE) # INTERFACE потому что шаблонные классы

set_target_properties(${LIB_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Настройка include для библиотеки чтобы можно было видеть заголовочные файлы
target_include_directories(${LIB_NAME} INTERFACE ${PROJECT_INCLUDES})

# Линковка библиотеки с основным проектом
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIB_NAME})

# ********************** Подключение GoogleTest **********************
add_subdirectory(googletest)

set(TEST_SOURCE 
    tests/container_test.cpp
    # tests/myvector_tests.cpp
    # tests/mylist1_tests.cpp
    # tests/mylist2_tests.cpp
    # tests/additional_tests.cpp
)

set(TEST_NAME ${PROJECT_NAME}_test)

add_executable(${TEST_NAME} ${TEST_SOURCE})

set_target_properties(${TEST_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Настройка include для тестов чтобы можно было видеть заголовочные файлы
target_include_directories(${TEST_NAME} PRIVATE ${PROJECT_INCLUDES})

target_link_libraries(${TEST_NAME} PRIVATE 
    #GTest::gtest
    GTest::gtest_main
    ${LIB_NAME}
)

# Добавление тестов в CMake
enable_testing()
add_test(NAME MyContainersTest COMMAND ${TEST_NAME})