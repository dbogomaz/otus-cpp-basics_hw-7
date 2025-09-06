cmake_minimum_required(VERSION 3.10.0)

project(myContainers VERSION 1.1.0 LANGUAGES C CXX)

set(PROJECT_SOURCE 
    src/main.cpp
)

# ********************** Настройка основного проекта в виде исполняемого файла *************
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE})

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# следующий код перенесен в библиотеку ${PROJECT_NAME}_lib
## Настройка include для библиотеки чтобы можно было видеть заголовочные файлы
#target_include_directories(${PROJECT_NAME} PRIVATE 
#    ${PROJECT_SOURCE_DIR}/src/myvector
#    ${PROJECT_SOURCE_DIR}/src/mylist_1
#    ${PROJECT_SOURCE_DIR}/src/mylist_2
#)

# ********************** Настройка основного проекта в виде библиотеки *************
add_library(${PROJECT_NAME}_lib INTERFACE) # INTERFACE потому что шаблонные классы

set_target_properties(${PROJECT_NAME}_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Настройка include для библиотеки чтобы можно было видеть заголовочные файлы
target_include_directories(${PROJECT_NAME}_lib INTERFACE
    ${PROJECT_SOURCE_DIR}/src/myvector
    ${PROJECT_SOURCE_DIR}/src/mylist_1
    ${PROJECT_SOURCE_DIR}/src/mylist_2
)

# Линковка библиотеки с основным проектом
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

# ********************** Подключение GoogleTest **********************
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

# Настройка include для тестов чтобы можно было видеть заголовочные файлы
target_include_directories(${PROJECT_NAME}_test PRIVATE 
    ${PROJECT_SOURCE_DIR}/src/myvector
    ${PROJECT_SOURCE_DIR}/src/mylist_1
    ${PROJECT_SOURCE_DIR}/src/mylist_2 
)

target_link_libraries(${PROJECT_NAME}_test PRIVATE 
    #GTest::gtest
    GTest::gtest_main
    ${PROJECT_NAME}_lib
)

# Добавление тестов в CMake
enable_testing()
add_test(NAME MyContainersTest COMMAND ${PROJECT_NAME}_test)