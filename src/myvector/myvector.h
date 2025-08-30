// @file: myvector.h
#ifndef MYVECTOR_H
#define MYVECTOR_H

template <typename T>
class MyVector {
public:
    class iterator;
    class const_iterator;

    explicit MyVector(const size_t size = 0);
    MyVector(const std::initializer_list<T> initList);
    MyVector(const MyVector &other);
    MyVector(MyVector &&other) noexcept;
    MyVector &operator=(const MyVector &other);
    MyVector &operator=(MyVector &&other) noexcept;
    bool operator==(const MyVector &other) const;
    bool operator!=(const MyVector &other) const;
    ~MyVector();

    void push_back(const T &value);
    void insert(const size_t index, const T &value);
    void erase(const size_t index);
    size_t capacity() const;
    size_t size() const;
    void reserve(const size_t new_capacity);
    T &at(const size_t index);
    const T &at(size_t index) const;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    void print() const;

    T &operator[](const size_t index);
    const T &operator[](const size_t index) const;

private:
    size_t m_capacity{1};                          // вместимость
    size_t m_size{0};                              // текущий размер
    static constexpr float CAPACITY_FACTOR{1.5f};  // коэффициент выделения памяти
    T *m_data{nullptr};

    void copyFrom(const MyVector &other);
    void moveFrom(MyVector &&other) noexcept;
    void checkIndex(const size_t index, const char *function_name) const;
    void growCapacity();  // увеличение вместимости
};

template <typename T>
class MyVector<T>::iterator {
public:
    explicit iterator(T *ptr = nullptr);
    T &operator*() const;
    T *get() const;
    iterator &operator++();
    iterator operator++(int);
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;

private:
    T *m_ptr;
};

template <typename T>
class MyVector<T>::const_iterator {
public:
    explicit const_iterator(const T *ptr = nullptr);
    const T &operator*() const;
    const T *get() const;
    const_iterator &operator++();
    const_iterator operator++(int);
    bool operator==(const const_iterator &other) const;
    bool operator!=(const const_iterator &other) const;

private:
    const T *m_ptr;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const MyVector<T> &myVector);

#include "myvector.ipp"

#endif  // MYVECTOR_H