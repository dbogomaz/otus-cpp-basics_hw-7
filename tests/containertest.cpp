#include <gtest/gtest.h>
#include "../src/mylist_1/mylist_1.h" // Подключаем правильный заголовочный файл

TEST(ContainerTest, BasicOperations) {
    MyList_1<int> list{0, 1, 2, 3, 4};
    EXPECT_EQ(list.size(), 5);

    list.push_back(5);
    EXPECT_EQ(list.size(), 6);
    EXPECT_EQ(list[5], 5);

    list.insert(0, 10);
    EXPECT_EQ(list.size(), 7);
    EXPECT_EQ(list[0], 10);

    list.erase(3); // Удаляем элемент с индексом 3
    EXPECT_EQ(list.size(), 6);
    EXPECT_EQ(list[3], 3); // Теперь на позиции 3 должен быть элемент со значением 3

    MyList_1<int> expected{10, 0, 1, 3, 4, 5};
    EXPECT_EQ(list, expected);
}

//TEST(ContainerTest, ConstIteratorBasic) {
//    // Создаём контейнер и добавляем элементы
//    MyList_1<int> list;
//    list.push_back(10);
//    list.push_back(20);
//    list.push_back(30);

//    // Проверяем, что итератор корректно проходит по элементам
//    int expected[] = {10, 20, 30};
//    int index = 0;

//    for (MyList_1<int>::const_iterator it = list.begin(); it != list.end(); ++it) {
//        ASSERT_LT(index, 3) << "Итератор вышел за пределы массива";
//        EXPECT_EQ(*it, expected[index]) << "Элемент на позиции " << index << " не соответствует ожидаемому";
//        ++index;
//    }

//    // Проверяем, что итератор прошёл все элементы
//    EXPECT_EQ(index, 3) << "Итератор не прошёл все элементы";
//}

//TEST(ContainerTest, ConstIteratorEmptyContainer) {
//    // Проверяем поведение итератора для пустого контейнера
//    MyList_1<int> empty_list;
//    MyList_1<int>::const_iterator it = empty_list.begin();
//    EXPECT_EQ(it, empty_list.end()) << "Итераторы begin и end должны быть равны для пустого контейнера";
//}

//TEST(ContainerTest, ConstIteratorSingleElement) {
//    // Проверяем итератор для контейнера с одним элементом
//    MyList_1<int> list;
//    list.push_back(42);

//    MyList_1<int>::const_iterator it = list.begin();
//    ASSERT_NE(it, list.end()) << "Итератор begin не должен быть равен end для контейнера с одним элементом";
//    EXPECT_EQ(*it, 42) << "Элемент не соответствует ожидаемому значению";
//    ++it;
//    EXPECT_EQ(it, list.end()) << "Итератор должен достичь end после одного шага";
//}