// @file myvector_tests.cpp
#include <gtest/gtest.h>

// можно не писать полный путь, если настроены include_directories в CMakeLists.txt
#include "myvector.h"
// #include "myvector/myvector.h"

//- создание контейнера
TEST(MyVector_Test, CreateContainer) {
    MyVector<int> container;
    EXPECT_EQ(container.size(), 0);
}
//- вставка элементов в конец
TEST(MyVector_Test, InsertAtEnd) {
    MyVector<int> container;
    container.push_back(1);
    container.push_back(2);
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
}
//- вставка элементов в начало
TEST(MyVector_Test, InsertAtBeginning) {
    MyVector<int> container{1, 2, 3};
    container.insert(0, 0);
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 1);
}
//- вставка элементов в середину
TEST(MyVector_Test, InsertInMiddle) {
    MyVector<int> container{1, 2, 4, 5};
    container.insert(2, 3); // Вставляем 3 на позицию с индексом 2
    EXPECT_EQ(container.size(), 5);
    EXPECT_EQ(container[2], 3);
    EXPECT_EQ(container[3], 4);
}
//- удаление элементов из конца
TEST(MyVector_Test, EraseFromEnd) {
    MyVector<int> container{1, 2, 3};
    container.erase(2); // Удаляем элемент с индексом 2
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
}
//- удаление элементов из начала
TEST(MyVector_Test, EraseFromBeginning) {
    MyVector<int> container{1, 2, 3};
    container.erase(0); // Удаляем элемент с индексом 0
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 2);
    EXPECT_EQ(container[1], 3);
}
//- удаление элементов из середины
TEST(MyVector_Test, EraseFromMiddle) {
    MyVector<int> container{1, 2, 3, 4, 5};
    container.erase(2); // Удаляем элемент с индексом 2
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 4);
    EXPECT_EQ(container[3], 5);
}
//- получение элементов из контейнера
TEST(MyVector_Test, AccessElements) {
    MyVector<int> container{10, 20, 30};
    EXPECT_EQ(container.at(0), 10);
    EXPECT_EQ(container.at(1), 20);
    EXPECT_EQ(container.at(2), 30);
    EXPECT_THROW(container.at(3), std::out_of_range); // Проверка выхода за границы
}
//- получение размера контейнера (фактическое количество элементов)
TEST(MyVector_Test, SizeCheck) {
    MyVector<int> container;
    EXPECT_EQ(container.size(), 0);
    container.push_back(1);
    EXPECT_EQ(container.size(), 1);
    container.push_back(2);
    EXPECT_EQ(container.size(), 2);
    container.erase(0);
    EXPECT_EQ(container.size(), 1);
}