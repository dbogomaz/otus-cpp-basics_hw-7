// @file: mylist_2.h
#ifndef MYLIST_2_H
#define MYLIST_2_H

template <typename T>
class MyList_2 {
public:
    class Node;

    class iterator;
    class const_iterator;

    explicit MyList_2(const size_t size = 0);  // конструктор по умолчанию и с параметром размера
    MyList_2(const std::initializer_list<T> initList);  // конструктор инициализации списком
    MyList_2(const MyList_2 &other);                    // конструктор копирования
    MyList_2(MyList_2 &&other) noexcept;                // конструктор перемещения
    MyList_2 &operator=(const MyList_2 &other);         // оператор присваивания копированием
    MyList_2 &operator=(MyList_2 &&other) noexcept;     // оператор присваивания перемещением
    bool operator==(const MyList_2 &other) const;       // оператор сравнения
    bool operator!=(const MyList_2 &other) const;       // оператора сравнения
    ~MyList_2();                                        // деструктор

    void push_back(const T &value);                   // добавление элемента в конец списка
    void insert(const size_t index, const T &value);  // добавление по индексу
    void erase(const size_t index);                   // удаление по индексу
    void clear();                                     // очистка списка
    size_t size() const;                              // текущий размер

    T &at(const size_t index);
    const T &at(size_t index) const;
    T &operator[](const size_t index);
    const T &operator[](const size_t index) const;

    iterator begin() noexcept;
    iterator end() noexcept;
    const_iterator begin() const noexcept;
    const_iterator end() const noexcept;

    void print() const;  // вывод в консоль

private:
    size_t m_size{0};            // текущий размер
    Node *m_firstNode{nullptr};  // указатель на первый элемент
    Node *m_lastNode{nullptr};   // указатель на последний элемент

    void copyFrom(const MyList_2 &other);      // копирование из другого списка
    void moveFrom(MyList_2 &&other) noexcept;  // перемещение из другого списка
    void checkIndex(const size_t index, const char *function_name) const;  // проверка индекса
};

template <typename T>
class MyList_2<T>::Node {
public:
    Node *next{nullptr};  // указатель на следующий элемент
    Node *prev{nullptr};  // указатель на предыдущий элемент
    T data{};             // данные элемента
};

template <typename T>
class MyList_2<T>::iterator {
public:
    explicit iterator(Node *node = nullptr, MyList_2 *list = nullptr);
    T &operator*() const;
    T *get() const;
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    bool operator==(const iterator &other) const;
    bool operator!=(const iterator &other) const;

private:
    Node *m_node;
    MyList_2 *m_list;  // Нужен для декрементации
};

template <typename T>
class MyList_2<T>::const_iterator {
public:
    explicit const_iterator(const Node *node = nullptr, const MyList_2 *list = nullptr);
    const T &operator*() const;
    const T *get() const;
    const_iterator &operator++();
    const_iterator operator++(int);
    const_iterator &operator--();
    const_iterator operator--(int);
    bool operator==(const const_iterator &other) const;
    bool operator!=(const const_iterator &other) const;

private:
    const Node *m_node;
    const MyList_2 *m_list;  // Нужен для декрементации
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const MyList_2<T> &myVector);

#include "mylist_2.ipp"

#endif  // MYLIST_2_H