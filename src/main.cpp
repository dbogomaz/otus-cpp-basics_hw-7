// file: main.cpp
#include <cassert>
#include <iostream>

#include "mylist_1/mylist_1.h"
#include "mylist_2/mylist_2.h"
#include "myvector/myvector.h"

int main() {
    std::cout << std::endl;

    MyList_2<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    list.print();
    std::cout << std::endl;

    std::cout << "Обратная итерация: ";
    auto it = list.end();
    if (it != list.begin()) {  // Проверяем, что список не пустой
        do {
            --it;  // Сначала двигаемся назад
            std::cout << *it << " ";
        } while (it != list.begin());
    }
    std::cout << std::endl;

    std::cout << list << std::endl;

    std::cout << std::endl;
    return 0;
}