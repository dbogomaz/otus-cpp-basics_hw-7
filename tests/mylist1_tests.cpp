// @file mylist1_tests.cpp
#include <gtest/gtest.h>

// можно не писать полный путь, если настроены include_directories в CMakeLists.txt
#include "mylist_1.h"
// #include "mylist_1/mylist_1.h"

//- создание контейнера
TEST(MyList1_Test, CreateContainer) {
    MyList_1<int> container;
    EXPECT_EQ(container.size(), 0);
}
//- вставка элементов в конец
TEST(MyList1_Test, InsertAtEnd) {
    MyList_1<int> container;
    container.push_back(1);
    container.push_back(2);
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
}
//- вставка элементов в начало
TEST(MyList1_Test, InsertAtBeginning) {
    MyList_1<int> container{1, 2, 3};
    container.insert(0, 0);
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 1);
}
//- вставка элементов в середину
TEST(MyList1_Test, InsertInMiddle) {
    MyList_1<int> container{1, 2, 4, 5};
    container.insert(2, 3);  // Вставляем 3 на позицию с индексом 2
    EXPECT_EQ(container.size(), 5);
    EXPECT_EQ(container[2], 3);
    EXPECT_EQ(container[3], 4);
}
//- удаление элементов из конца
TEST(MyList1_Test, EraseFromEnd) {
    MyList_1<int> container{1, 2, 3};
    container.erase(2);  // Удаляем элемент с индексом 2
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
}
//- удаление элементов из начала
TEST(MyList1_Test, EraseFromBeginning) {
    MyList_1<int> container{1, 2, 3};
    container.erase(0);  // Удаляем элемент с индексом 0
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 2);
    EXPECT_EQ(container[1], 3);
}
//- удаление элементов из середины
TEST(MyList1_Test, EraseFromMiddle) {
    MyList_1<int> container{1, 2, 3, 4, 5};
    container.erase(2);  // Удаляем элемент с индексом 2
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 4);
    EXPECT_EQ(container[3], 5);
}
//- получение элементов из контейнера
TEST(MyList1_Test, GetElements) {
    MyList_1<int> container{10, 20, 30};
    EXPECT_EQ(container.at(0), 10);
    EXPECT_EQ(container.at(1), 20);
    EXPECT_EQ(container.at(2), 30);
    EXPECT_EQ(container[0], 10);
    EXPECT_EQ(container[1], 20);
    EXPECT_EQ(container[2], 30);
}
//- получение размера контейнера (фактическое количество элементов)
TEST(MyList1_Test, SizeCheck) {
    MyList_1<int> container{0, 1, 2, 3, 4};
    EXPECT_EQ(container.size(), 5);
    container.push_back(5);
    EXPECT_EQ(container.size(), 6);
    container.erase(0);
    EXPECT_EQ(container.size(), 5);
    container.clear();
    EXPECT_EQ(container.size(), 0);
}