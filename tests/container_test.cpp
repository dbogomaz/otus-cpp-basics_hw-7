// @file container_test.cpp
#include <gtest/gtest.h>

#include "mylist_1.h"
#include "mylist_2.h"
#include "myvector.h"

// Шаблонный тестовый класс
template <typename T>
class ContainerTest : public ::testing::Test {};

// Определяем типы для тестирования
using ContainerTypes = ::testing::Types<MyVector<int>, MyList_1<int>, MyList_2<int>>;
TYPED_TEST_SUITE(ContainerTest, ContainerTypes);

//- создание контейнера
TYPED_TEST(ContainerTest, CreateContainer) { 
    TypeParam container;
    EXPECT_EQ(container.size(), 0); }

//- вставка элементов в конец
TYPED_TEST(ContainerTest, InsertAtEnd) {
    TypeParam container;
    container.push_back(1);
    container.push_back(2);
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
}
//- вставка элементов в начало
TYPED_TEST(ContainerTest, InsertAtBeginning) {
    TypeParam container{1, 2, 3};
    container.insert(0, 0);
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 1);
}
//- вставка элементов в середину
TYPED_TEST(ContainerTest, InsertInMiddle) {
    TypeParam container{1, 2, 4, 5};
    container.insert(2, 3); // Вставляем 3 на позицию с индексом 2
    EXPECT_EQ(container.size(), 5);
    EXPECT_EQ(container[2], 3);
    EXPECT_EQ(container[3], 4);
}
//- удаление элементов из конца
TYPED_TEST(ContainerTest, EraseFromEnd) {
    TypeParam container{1, 2, 3};
    container.erase(2); // Удаляем элемент с индексом 2
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
}
//- удаление элементов из начала
TYPED_TEST(ContainerTest, EraseFromBeginning) {
    TypeParam container{1, 2, 3};
    container.erase(0); // Удаляем элемент с индексом 0
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 2);
    EXPECT_EQ(container[1], 3);
}
//- удаление элементов из середины
TYPED_TEST(ContainerTest, EraseFromMiddle) {
    TypeParam container{1, 2, 3, 4, 5};
    container.erase(2); // Удаляем элемент с индексом 2
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 4);
    EXPECT_EQ(container[3], 5);
}
//- получение элементов из контейнера
TYPED_TEST(ContainerTest, AccessElements) {
    TypeParam container{10, 20, 30};
    EXPECT_EQ(container.at(0), 10);
    EXPECT_EQ(container.at(1), 20);
    EXPECT_EQ(container.at(2), 30);
    EXPECT_THROW(container.at(3), std::out_of_range); // Проверка выхода за границы
}
//- получение размера контейнера (фактическое количество элементов)
TYPED_TEST(ContainerTest, SizeCheck) {
    TypeParam container;
    EXPECT_EQ(container.size(), 0);
    container.push_back(1);
    EXPECT_EQ(container.size(), 1);
    container.push_back(2);
    EXPECT_EQ(container.size(), 2);
    container.erase(0);
    EXPECT_EQ(container.size(), 1);
}