// @file containertest.cpp
#include <gtest/gtest.h>
#include "mylist_2/mylist_2.h"

//- создание контейнера
TEST(MyList2_Test, CreateContainer) {
    MyList_2<int> container;
    EXPECT_EQ(container.size(), 0);
}
//- вставка элементов в конец
TEST(MyList2_Test, InsertAtEnd) {
    MyList_2<int> container;
    container.push_back(1);
    container.push_back(2);
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
}
//- вставка элементов в начало
TEST(MyList2_Test, InsertAtBeginning) {
    MyList_2<int> container{1, 2, 3};
    container.insert(0, 0);
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 0);
    EXPECT_EQ(container[1], 1);
}
//- вставка элементов в середину
TEST(MyList2_Test, InsertInMiddle) {
    MyList_2<int> container{1, 2, 4, 5};
    container.insert(2, 3); // Вставляем 3 на позицию с индексом 2
    EXPECT_EQ(container.size(), 5);
    EXPECT_EQ(container[2], 3);
    EXPECT_EQ(container[3], 4);
}
//- удаление элементов из конца
TEST(MyList2_Test, EraseFromEnd) {
    MyList_2<int> container{1, 2, 3};
    container.erase(2); // Удаляем элемент с индексом 2
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
}
//- удаление элементов из начала
TEST(MyList2_Test, EraseFromBeginning) {
    MyList_2<int> container{1, 2, 3};
    container.erase(0); // Удаляем элемент с индексом 0
    EXPECT_EQ(container.size(), 2);
    EXPECT_EQ(container[0], 2);
    EXPECT_EQ(container[1], 3);
}
//- удаление элементов из середины
TEST(MyList2_Test, EraseFromMiddle) {
    MyList_2<int> container{1, 2, 3, 4, 5};
    container.erase(2); // Удаляем элемент с индексом 2
    EXPECT_EQ(container.size(), 4);
    EXPECT_EQ(container[0], 1);
    EXPECT_EQ(container[1], 2);
    EXPECT_EQ(container[2], 4);
    EXPECT_EQ(container[3], 5);
}
//- получение элементов из контейнера
TEST(MyList2_Test, AccessElements) {
    MyList_2<int> container{10, 20, 30, 40, 50};
    EXPECT_EQ(container.at(0), 10);
    EXPECT_EQ(container.at(1), 20);
    EXPECT_EQ(container.at(2), 30);
    EXPECT_EQ(container.at(3), 40);
    EXPECT_EQ(container.at(4), 50);
    EXPECT_EQ(container[0], 10);
    EXPECT_EQ(container[1], 20);
    EXPECT_EQ(container[2], 30);
    EXPECT_EQ(container[3], 40);
    EXPECT_EQ(container[4], 50);
}
//- получение размера контейнера (фактическое количество элементов)
TEST(MyList2_Test, SizeCheck) {
    MyList_2<int> container{0, 1, 2, 3, 4};
    EXPECT_EQ(container.size(), 5);
    container.push_back(5);
    EXPECT_EQ(container.size(), 6);
    container.erase(0);
    EXPECT_EQ(container.size(), 5);
    container.insert(2, 10);
    EXPECT_EQ(container.size(), 6);
}