// @file additional_tests.cpp
// Дополнительные тесты для проверки контейнеров MyVector, MyList_1 и MyList_2
#include <gtest/gtest.h>

// можно не писать полный путь, если настроены include_directories в CMakeLists.txt
#include "mylist_1.h"
#include "mylist_2.h"
#include "myvector.h"
// #include "../src/mylist_1/mylist_1.h"
// #include "../src/mylist_2/mylist_2.h"
// #include "../src/myvector/myvector.h"

//**Дополнительное задание 1.**
// Реализовать `unit-тест` на копирование контейнера.
// Тест должен проверять, что после копирования одного объекта контейнера
// в другой содержимое обоих контейнеров одинаково
template <typename T>
void testContainerCopy() {
    T original{0, 1, 2, 3, 4};
    T copy = original;  // вызов копирующего конструктора
    EXPECT_EQ(original, copy) << "Copy constructor failed: контейнеры не равны после копирования";
    original.push_back(5);
    EXPECT_NE(original, copy)
        << "Copy constructor failed: контейнеры равны после изменения оригинала";
}
TEST(ContainerCopyTest, MyVector) { testContainerCopy<MyVector<int>>(); }
TEST(ContainerCopyTest, MyList1) { testContainerCopy<MyList_1<int>>(); }
TEST(ContainerCopyTest, MyList2) { testContainerCopy<MyList_2<int>>(); }

//**Дополнительное задание 2.**
// Реализовать unit-тест на удаление контейнера.
// Тест должен проверять, что для всех элементов внутри контейнера был
// вызван деструктор во время уничтожения объекта контейнера.
template <typename T>
class TestElement {  // вспомогательный класс для подсчёта вызовов конструктора и деструктора
public:
    static int instance_count;                             // счётчик живых экземпляров
    TestElement() { ++instance_count; }                    // конструктор по умолчанию
    TestElement(const TestElement&) { ++instance_count; }  // конструктор копирования
    ~TestElement() { --instance_count; }
};
template <typename T>
int TestElement<T>::instance_count = 0;  // инициализация статического члена
template <typename Container>
void testContainerDestruction() {
    {
        Container container;
        //std::cout << "container.size() = " << container.size() << std::endl;
        for (int i = 0; i < 10; ++i) {
            container.push_back(TestElement<int>());
        }
        //std::cout << "container.size() = " << container.size() << std::endl;
        EXPECT_EQ(TestElement<int>::instance_count, 10)
            << "Контейнер заполнен: неверный счётчик экземпляров";
    }
    EXPECT_EQ(TestElement<int>::instance_count, 0)
        << "Контейнер уничтожен: деструкторы элементов не вызваны";
}

// Специализация для MyVector потому что у него конструктор выззывается с учетом capacity
template <>
void testContainerDestruction<MyVector<TestElement<int>>>() { 
     {
        MyVector<TestElement<int>> container;
        container.reserve(10);  // Учитываем специфику вектора
        for (int i = 0; i < 10; ++i) {
            container.push_back(TestElement<int>());
        }
        EXPECT_EQ(TestElement<int>::instance_count, 10)
            << "Контейнер заполнен: неверный счётчик экземпляров";
    }
    EXPECT_EQ(TestElement<int>::instance_count, 0)
        << "Контейнер уничтожен: деструкторы элементов не вызваны";
}
TEST(ContainerDestructionTest, MyVector) { testContainerDestruction<MyVector<TestElement<int>>>(); }
TEST(ContainerDestructionTest, MyList1) { testContainerDestruction<MyList_1<TestElement<int>>>(); }
TEST(ContainerDestructionTest, MyList2) { testContainerDestruction<MyList_2<TestElement<int>>>(); }

//**Дополнительное задание 3.**
// Добавить `unit-тест` на перемещение контейнера
//(вызов перемещающего оператора присваивания).
template <typename T>
void testContainerMove() {
    T original{0, 1, 2, 3, 4};
    T moved = std::move(original);  // вызов перемещающего конструктора
    T expected{0, 1, 2, 3, 4};     // создаём контейнер для сравнения
    EXPECT_EQ(moved, expected)
        << "Move constructor failed: перемещённый контейнер не содержит ожидаемые значения";
    EXPECT_EQ(original.size(), 0)
        << "Move constructor failed: оригинальный контейнер не пуст";
}
TEST(ContainerMoveTest, MyVector) { testContainerMove<MyVector<int>>(); }
TEST(ContainerMoveTest, MyList1) { testContainerMove<MyList_1<int>>(); }
TEST(ContainerMoveTest, MyList2) { testContainerMove<MyList_2<int>>(); }