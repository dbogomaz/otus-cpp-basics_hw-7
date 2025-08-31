#include <iostream>
#include <cassert>
#include "../src/myvector/myvector.h"
#include "../src/mylist_1/mylist_1.h"
#include "../src/mylist_2/mylist_2.h"

namespace tests {

template <typename T>
void containerTest() {
    std::cout << "=== Starting container tests ===" << std::endl;
    
    // 1. создание объекта контейнера для хранения объектов типа int
    T container{0, 1, 2, 3, 4};
    std::cout << "1. Container created: " << container << std::endl;
    
    // 2. добавление в контейнер десяти элементов (0, 1 … 9)
    for (size_t value = 5; value < 10; value++) {
        container.push_back(value);
    }
    std::cout << "2. Added elements 5-9: " << container << std::endl;
    
    // 3. вывод содержимого контейнера на экран
    // ожидаемый результат: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
    std::cout << "3. Current content: " << container << std::endl;
    T expected1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert(container == expected1 && "Test 3 failed: content mismatch");
    std::cout << "✓ Test 3 passed" << std::endl;
    
    // 4. вывод размера контейнера на экран
    // ожидаемый результат: 10
    std::cout << "4. Size: " << container.size() << std::endl;
    assert(container.size() == 10 && "Test 4 failed: size mismatch");
    std::cout << "✓ Test 4 passed" << std::endl;
    
    // 5. удаление третьего (по счёту), пятого и седьмого элементов
    container.erase(7 - 1); // 7-й элемент (индекс 6)
    container.erase(5 - 1); // 5-й элемент (индекс 4)
    container.erase(3 - 1); // 3-й элемент (индекс 2)
    std::cout << "5. After erasing elements 3,5,7: " << container << std::endl;
    
    // 6. вывод содержимого контейнера на экран
    // ожидаемый результат: 0, 1, 3, 5, 7, 8, 9
    T expected2{0, 1, 3, 5, 7, 8, 9};
    assert(container == expected2 && "Test 6 failed: content after erase mismatch");
    std::cout << "6. Content: " << container << std::endl;
    std::cout << "✓ Test 6 passed" << std::endl;
    
    // 7. добавление элемента 10 в начало контейнера
    container.insert(0, 10);
    std::cout << "7. After inserting 10 at beginning: " << container << std::endl;
    
    // 8. вывод содержимого контейнера на экран
    // ожидаемый результат: 10, 0, 1, 3, 5, 7, 8, 9
    T expected3{10, 0, 1, 3, 5, 7, 8, 9};
    assert(container == expected3 && "Test 8 failed: content after insert at 0 mismatch");
    std::cout << "8. Content: " << container << std::endl;
    std::cout << "✓ Test 8 passed" << std::endl;
    
    // 9. добавление элемента 20 в середину контейнера
    size_t middle_index = container.size() / 2;
    container.insert(middle_index, 20);
    std::cout << "9. After inserting 20 at middle (index " << middle_index << "): " << container << std::endl;
    
    // 10. вывод содержимого контейнера на экран
    // ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9
    T expected4{10, 0, 1, 3, 20, 5, 7, 8, 9};
    assert(container == expected4 && "Test 10 failed: content after insert at middle mismatch");
    std::cout << "10. Content: " << container << std::endl;
    std::cout << "✓ Test 10 passed" << std::endl;
    
    // 11. добавление элемента 30 в конец контейнера
    container.push_back(30);
    std::cout << "11. After pushing back 30: " << container << std::endl;
    
    // 12. вывод содержимого контейнера на экран
    // ожидаемый результат: 10, 0, 1, 3, 20, 5, 7, 8, 9, 30
    T expected5{10, 0, 1, 3, 20, 5, 7, 8, 9, 30};
    assert(container == expected5 && "Test 12 failed: content after push_back mismatch");
    std::cout << "12. Content: " << container << std::endl;
    std::cout << "✓ Test 12 passed" << std::endl;
    
    // Тестирование итераторов
    std::cout << "Testing iterators:" << std::endl;
    for (auto iter = container.begin(); iter != container.end(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    
    // Дополнительные тесты
    std::cout << "Final size: " << container.size() << std::endl;
    
    std::cout << "=== All tests passed! ===" << std::endl << std::endl;
}

}  // namespace tests

int main() { 
    tests::containerTest<MyVector<int>>();
    tests::containerTest<MyList_1<int>>();
    tests::containerTest<MyList_2<int>>();
    return 0;
}