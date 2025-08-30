// @file: mylist_2.ipp

#include <sstream>
#include <stdexcept>

#include "mylist_2.h"

// Конструктор по умолчанию и с параметром размера
template <typename T>
MyList_2<T>::MyList_2(const size_t size) : m_size{size} {
    if (m_size > 0) {
        m_firstNode = new Node();
        m_lastNode = m_firstNode;
        for (size_t i = 1; i < m_size; i++) {
            Node *newNode = new Node();
            m_lastNode->next = newNode;
            newNode->prev = m_lastNode;
            m_lastNode = newNode;
        }
    }
}

// Конструктор инициализации списком
template <typename T>
MyList_2<T>::MyList_2(const std::initializer_list<T> initList) : m_size{initList.size()} {
    if (m_size > 0) {
        auto it = initList.begin();
        m_firstNode = new Node();
        m_firstNode->data = *it;
        m_lastNode = m_firstNode;
        ++it;
        for (size_t i = 1; i < m_size; i++) {
            Node *newNode = new Node();
            newNode->data = *it;
            m_lastNode->next = newNode;
            newNode->prev = m_lastNode;
            m_lastNode = newNode;
            ++it;
        }
    }
}

// Конструктор копирования
template <typename T>
MyList_2<T>::MyList_2(const MyList_2 &other) {
    copyFrom(other);
}

// Конструктор перемещения
template <typename T>
MyList_2<T>::MyList_2(MyList_2 &&other) noexcept {
    moveFrom(std::move(other));
}

// Оператор присваивания копированием
template <typename T>
MyList_2<T> &MyList_2<T>::operator=(const MyList_2 &other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

// Оператор присваивания перемещением
template <typename T>
MyList_2<T> &MyList_2<T>::operator=(MyList_2 &&other) noexcept {
    if (this != &other) {
        clear();
        moveFrom(std::move(other));
    }
    return *this;
}

// Операторы сравнения
template <typename T>
bool MyList_2<T>::operator==(const MyList_2 &other) const {
    // Если оба списка пустые - они равны
    if (m_size == 0 && other.m_size == 0) return true;

    // Если размеры разные - списки не равны
    if (m_size != other.m_size) return false;

    // Сравнение по элементам
    Node *a = m_firstNode;
    Node *b = other.m_firstNode;
    while (a && b) {
        if (a->data != b->data) return false;
        a = a->next;
        b = b->next;
    }
    return true;
}

template <typename T>
bool MyList_2<T>::operator!=(const MyList_2 &other) const {
    return !(*this == other);
}

// Деструктор
template <typename T>
MyList_2<T>::~MyList_2() {
    clear();
}

// --- Методы изменения списка ---

template <typename T>
void MyList_2<T>::push_back(const T &value) {
    Node *newNode = new Node();
    newNode->data = value;
    if (m_size == 0) {
        m_firstNode = newNode;
        m_lastNode = newNode;
    } else {
        m_lastNode->next = newNode;
        newNode->prev = m_lastNode;
        m_lastNode = newNode;
    }
    ++m_size;
}

template <typename T>
void MyList_2<T>::insert(const size_t index, const T &value) {
    if (index == m_size) {
        push_back(value);
        return;
    }
    checkIndex(index, "insert");
    Node *newNode = new Node();
    newNode->data = value;
    // вставка в начало
    if (index == 0) {
        newNode->next = m_firstNode;
        m_firstNode->prev = newNode;
        m_firstNode = newNode;
    } else {
        Node *prevNode = m_firstNode;
        for (size_t i = 0; i < index - 1; ++i) {
            prevNode = prevNode->next;
        }
        newNode->next = prevNode->next;
        prevNode->next = newNode;

        newNode->prev = prevNode;
        if (newNode->next) {
            newNode->next->prev = newNode;
        }
    }
    ++m_size;
}

template <typename T>
void MyList_2<T>::erase(const size_t index) {
    checkIndex(index, "erase");
    Node *toDelete = nullptr;
    if (index == 0) {
        // Удаление первого элемента
        toDelete = m_firstNode;
        m_firstNode = m_firstNode->next;

        if (m_firstNode != nullptr) {
            m_firstNode->prev = nullptr;
        } else {
            m_lastNode = nullptr;
        }
    } else {
        // Поиск узла, предшествующего удаляемому
        Node *prev = m_firstNode;
        for (size_t i = 0; i < index - 1; ++i) {
            prev = prev->next;
        }
        toDelete = prev->next;
        prev->next = toDelete->next;
        if (toDelete->next) {
            toDelete->next->prev = prev;
        }
        if (prev->next == nullptr) {
            m_lastNode = prev;
        }
    }
    delete toDelete;
    --m_size;
}

template <typename T>
void MyList_2<T>::clear() {
    Node *current = m_firstNode;
    while (current != nullptr) {
        Node *nextNode = current->next;
        delete current;
        current = nextNode;
    }
    m_firstNode = nullptr;
    m_lastNode = nullptr;
    m_size = 0;
}

// --- Методы информации о списке ---

template <typename T>
size_t MyList_2<T>::size() const {
    return m_size;
}

// --- Методы доступа к элементам ---

template <typename T>
T &MyList_2<T>::at(const size_t index) {
    checkIndex(index, "at");
    Node *current = m_firstNode;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
const T &MyList_2<T>::at(size_t index) const {
    checkIndex(index, "at");
    Node *current = m_firstNode;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
T &MyList_2<T>::operator[](const size_t index) {
    return at(index);
}

template <typename T>
const T &MyList_2<T>::operator[](const size_t index) const {
    return at(index);
}

// --- Итераторы ---

template <typename T>
typename MyList_2<T>::iterator MyList_2<T>::begin() noexcept {
    return iterator(m_firstNode, this);
}

template <typename T>
typename MyList_2<T>::iterator MyList_2<T>::end() noexcept {
    return iterator(nullptr, this);
}

template <typename T>
typename MyList_2<T>::const_iterator MyList_2<T>::begin() const noexcept {
    return const_iterator(m_firstNode, this);
}

template <typename T>
typename MyList_2<T>::const_iterator MyList_2<T>::end() const noexcept {
    return const_iterator(nullptr, this);
}

template <typename T>
void MyList_2<T>::print() const {
    Node *current = m_firstNode;
    size_t index = 0;
    std::cout << "=== List Contents ===" << std::endl;
    std::cout << " Size: " << m_size << std::endl;
    std::cout << "First: " << m_firstNode << std::endl;
    std::cout << " Last: " << m_lastNode << std::endl;
    std::cout << "---------------------" << std::endl;
    while (current != nullptr) {
        std::cout << "Node-" << index++ << " " << current << "\n\tprev = " << current->prev
                  << "\n\tnext = " << current->next << "\n\tdata = " << current->data << std::endl;
        current = current->next;
    }
    if (m_size == 0) {
        std::cout << "List is empty" << std::endl;
    }
}

// --- Приватные методы ---

template <typename T>
void MyList_2<T>::copyFrom(const MyList_2 &other) {
    clear();
    if (other.m_size > 0) {
        Node *it = other.m_firstNode;
        m_firstNode = new Node();
        m_firstNode->data = it->data;
        m_lastNode = m_firstNode;
        it = it->next;
        for (size_t i = 1; i < other.m_size; i++) {
            Node *newNode = new Node();
            newNode->data = it->data;
            m_lastNode->next = newNode;
            newNode->prev = m_lastNode;
            m_lastNode = newNode;
            it = it->next;
        }
        m_lastNode->next = nullptr;
        m_size = other.m_size;
    }
}

template <typename T>
void MyList_2<T>::moveFrom(MyList_2 &&other) noexcept {
    clear();
    m_size = other.m_size;
    m_firstNode = other.m_firstNode;
    m_lastNode = other.m_lastNode;
    other.m_size = 0;
    other.m_firstNode = nullptr;
    other.m_lastNode = nullptr;
}

template <typename T>
void MyList_2<T>::checkIndex(const size_t index, const char *function_name) const {
    if (index >= m_size) {
        std::ostringstream oss;
        oss << "MyList_2::" << function_name << "(): index " << index
            << " out of range (size: " << m_size << ")";
        throw std::out_of_range(oss.str());
    }
}

// --- Реализация методов iterator ---

template <typename T>
MyList_2<T>::iterator::iterator(Node *node, MyList_2 *list) : m_node(node), m_list(list) {}

template <typename T>
T &MyList_2<T>::iterator::operator*() const {
    return m_node->data;
}

template <typename T>
T *MyList_2<T>::iterator::get() const {
    return &m_node->data;
}

template <typename T>
typename MyList_2<T>::iterator &MyList_2<T>::iterator::operator++() {
    if (m_node) {
        m_node = m_node->next;
    }
    return *this;
}

template <typename T>
typename MyList_2<T>::iterator MyList_2<T>::iterator::operator++(int) {
    iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename MyList_2<T>::iterator &MyList_2<T>::iterator::operator--() {
    if (m_node == nullptr) {
        // Если итератор указывает на end(), переходим к последнему элементу списка
        m_node = m_list->m_lastNode;
    } else {
        m_node = m_node->prev;
    }
    return *this;
}

template <typename T>
typename MyList_2<T>::iterator MyList_2<T>::iterator::operator--(int) {
    iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
bool MyList_2<T>::iterator::operator==(const iterator &other) const {
    return m_node == other.m_node;
}

template <typename T>
bool MyList_2<T>::iterator::operator!=(const iterator &other) const {
    return m_node != other.m_node;
}

// --- Реализация методов const_iterator ---

template <typename T>
MyList_2<T>::const_iterator::const_iterator(const Node *node, const MyList_2 *list)
    : m_node(node), m_list(list) {}

template <typename T>
const T &MyList_2<T>::const_iterator::operator*() const {
    return m_node->data;
}

template <typename T>
const T *MyList_2<T>::const_iterator::get() const {
    return &m_node->data;
}

template <typename T>
typename MyList_2<T>::const_iterator &MyList_2<T>::const_iterator::operator++() {
    if (m_node) {
        m_node = m_node->next;
    }
    return *this;
}

template <typename T>
typename MyList_2<T>::const_iterator MyList_2<T>::const_iterator::operator++(int) {
    const_iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename MyList_2<T>::const_iterator &MyList_2<T>::const_iterator::operator--() {
    if (m_node == nullptr) {
        // Если итератор указывает на end(), переходим к последнему элементу списка
        m_node = m_list->m_lastNode;
    } else {
        m_node = m_node->prev;
    }
    return *this;
}

template <typename T>
typename MyList_2<T>::const_iterator MyList_2<T>::const_iterator::operator--(int) {
    const_iterator temp = *this;
    --(*this);
    return temp;
}

template <typename T>
bool MyList_2<T>::const_iterator::operator==(const const_iterator &other) const {
    return m_node == other.m_node;
}

template <typename T>
bool MyList_2<T>::const_iterator::operator!=(const const_iterator &other) const {
    return m_node != other.m_node;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const MyList_2<T> &myList) {
    for (const auto &item : myList) {
        os << item << " ";
    }
    return os;
}
