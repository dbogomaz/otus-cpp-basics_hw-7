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
