// @file: myvector.ipp

#include <sstream>
#include <stdexcept>

#include "myvector.h"

template <typename T>
MyVector<T>::MyVector(const size_t size) : m_size{size} {
    if (m_size > 0) {
        m_capacity = static_cast<size_t>(m_size * CAPACITY_FACTOR);
    }
    m_data = new T[m_capacity]();  // скобки инициализируют элементы
}

template <typename T>
MyVector<T>::MyVector(const std::initializer_list<T> initList) : m_size{initList.size()} {
    if (m_size > 0) {
        m_capacity = static_cast<size_t>(m_size * CAPACITY_FACTOR);
    }
    m_data = new T[m_capacity];

    if (m_size > 0) {
        size_t i = 0;
        for (const auto &item : initList) {
            m_data[i++] = item;
        }
    }
}

template <typename T>
MyVector<T>::MyVector(const MyVector &other) {
    copyFrom(other);
}

template <typename T>
MyVector<T>::MyVector(MyVector &&other) noexcept {
    moveFrom(std::move(other));
}

template <typename T>
void MyVector<T>::moveFrom(MyVector &&other) noexcept {
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_data = other.m_data;

    other.m_capacity = 0;
    other.m_size = 0;
    other.m_data = nullptr;
}

template <typename T>
T &MyVector<T>::at(const size_t index) {
    checkIndex(index, "at");
    return m_data[index];
}

template <typename T>
const T &MyVector<T>::at(const size_t index) const {
    checkIndex(index, "at");
    return m_data[index];
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector &other) {
    if (this != &other) {
        delete[] m_data;
        copyFrom(other);
    }
    return *this;
}

template <typename T>
MyVector<T> &MyVector<T>::operator=(MyVector &&other) noexcept {
    if (this != &other) {
        delete[] m_data;
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename T>
bool MyVector<T>::operator==(const MyVector &other) const {
    if (m_size != other.m_size) {
        return false;
    }
    
    for (size_t i = 0; i < m_size; ++i) {
        if (m_data[i] != other.m_data[i]) {
            return false;
        }
    }
    
    return true;
}

template <typename T>
bool MyVector<T>::operator!=(const MyVector &other) const {
    return !(*this == other);
}

template <typename T>
T &MyVector<T>::operator[](const size_t index) {
    checkIndex(index, "operator[]");
    return m_data[index];
}

template <typename T>
void MyVector<T>::print() const {
    std::cout << "MyVector" << std::endl;

    std::cout << "\tm_size: " << m_size << std::endl;
    std::cout << "\tm_data: ";
    for (size_t i = 0; i < m_size; ++i) {
        std::cout << m_data[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "\tm_capacity: " << m_capacity << std::endl;
    std::cout << "\tm_data: ";
    for (size_t i = 0; i < m_capacity; ++i) {
        std::cout << m_data[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
const T &MyVector<T>::operator[](const size_t index) const {
    checkIndex(index, "operator[]");
    return m_data[index];
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const MyVector<T> &myVector) {
    for (size_t i = 0; i < myVector.size(); ++i) {
        os << myVector.at(i) << " ";
    }
    return os;
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] m_data;
}

template <typename T>
void MyVector<T>::push_back(const T &value) {
    if (m_size == m_capacity) {
        growCapacity();
    }
    m_data[m_size] = value;
    ++m_size;
}

template <typename T>
void MyVector<T>::insert(const size_t index, const T &value) {
    if (index == m_size) {
        push_back(value);
        return;
    }
    checkIndex(index, "insert");
    if (m_size == m_capacity) {
        growCapacity();
    }
    std::copy_backward(m_data + index, m_data + m_size, m_data + m_size + 1);
    m_data[index] = value;
    ++m_size;
}

template <typename T>
void MyVector<T>::erase(const size_t index) {
    checkIndex(index, "erase");
    std::move(m_data + index + 1, m_data + m_size, m_data + index);
    --m_size;
    m_data[m_size] = T();
}

template <typename T>
size_t MyVector<T>::capacity() const {
    return m_capacity;
}

template <typename T>
size_t MyVector<T>::size() const {
    return m_size;
}

template <typename T>
void MyVector<T>::reserve(const size_t new_capacity) {
    if (new_capacity > m_capacity) {
        T *new_data = new T[new_capacity];
        std::copy(m_data, m_data + m_size, new_data);

        delete[] m_data;
        m_data = new_data;
        m_capacity = new_capacity;
    }
}

template <typename T>
void MyVector<T>::copyFrom(const MyVector &other) {
    m_capacity = other.m_capacity;
    m_size = other.m_size;
    m_data = new T[m_capacity];

    std::copy(other.m_data, other.m_data + m_size, m_data);
}

template <typename T>
void MyVector<T>::checkIndex(const size_t index, const char *function_name) const {
    if (index >= m_size) {
        std::ostringstream oss;
        oss << "MyVector::" << function_name << "(): index " << index
            << " out of range (size: " << m_size << ")";
        throw std::out_of_range(oss.str());
    }
}

template <typename T>
void MyVector<T>::growCapacity() {
    size_t new_capacity = static_cast<size_t>(m_capacity * CAPACITY_FACTOR);
    // Гарантируем хотя бы минимальное увеличение
    if (new_capacity <= m_capacity) {
        new_capacity = m_capacity + 1;
    }
    reserve(new_capacity);
}



// Реализация методов iterator
template <typename T>
MyVector<T>::iterator::iterator(T* ptr) : m_ptr(ptr) {}

template <typename T>
T& MyVector<T>::iterator::operator*() const {
    return *m_ptr;
}

template <typename T>
T* MyVector<T>::iterator::get() const {
    return m_ptr;
}

template <typename T>
typename MyVector<T>::iterator& MyVector<T>::iterator::operator++() {
    ++m_ptr;
    return *this;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator++(int) {
    iterator temp = *this;
    ++m_ptr;
    return temp;
}

template <typename T>
bool MyVector<T>::iterator::operator==(const iterator& other) const {
    return m_ptr == other.m_ptr;
}

template <typename T>
bool MyVector<T>::iterator::operator!=(const iterator& other) const {
    return m_ptr != other.m_ptr;
}

// Реализация методов const_iterator
template <typename T>
MyVector<T>::const_iterator::const_iterator(const T* ptr) : m_ptr(ptr) {}

template <typename T>
const T& MyVector<T>::const_iterator::operator*() const {
    return *m_ptr;
}

template <typename T>
const T* MyVector<T>::const_iterator::get() const {
    return m_ptr;
}

template <typename T>
typename MyVector<T>::const_iterator& MyVector<T>::const_iterator::operator++() {
    ++m_ptr;
    return *this;
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::const_iterator::operator++(int) {
    const_iterator temp = *this;
    ++m_ptr;
    return temp;
}

template <typename T>
bool MyVector<T>::const_iterator::operator==(const const_iterator& other) const {
    return m_ptr == other.m_ptr;
}

template <typename T>
bool MyVector<T>::const_iterator::operator!=(const const_iterator& other) const {
    return m_ptr != other.m_ptr;
}


// Реализация методов MyVector для итераторов
template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin() noexcept {
    return iterator(m_data);
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::end() noexcept {
    return iterator(m_data + m_size);
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::begin() const noexcept {
    return const_iterator(m_data);
}

template <typename T>
typename MyVector<T>::const_iterator MyVector<T>::end() const noexcept {
    return const_iterator(m_data + m_size);
}

