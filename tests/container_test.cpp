// @file container_test.cpp
#include <gtest/gtest.h>

#include "mylist_1.h"
#include "mylist_2.h"
#include "myvector.h"

// Шаблонный тестовый класс
template <typename T>
class ContainerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Код, выполняемый перед каждым тестом
        container = new T();
    }
    void TearDown() override {
        // Код, выполняемый после каждого теста
        delete container;
    }

    T* container;
};

// Определяем типы для тестирования
using ContainerTypes = ::testing::Types<MyVector<int>, MyList_1<int>, MyList_2<int>>;
TYPED_TEST_SUITE(ContainerTest, ContainerTypes);

//- создание контейнера
TYPED_TEST(ContainerTest, CreateContainer) { EXPECT_EQ(this->container->size(), 0); }

//- вставка элементов в конец
TYPED_TEST(ContainerTest, InsertAtEnd) {
    this->container->push_back(1);
    this->container->push_back(2);
    EXPECT_EQ(this->container->size(), 2);
    EXPECT_EQ((*this->container)[0], 1);
    EXPECT_EQ((*this->container)[1], 2);
}
