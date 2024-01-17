#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <initializer_list>
#include <cassert>


template<typename T>
class MyList
{
public:
    struct Node
    {
        T value{};
        int index{};
        Node* next{ new Node{} };
        Node* previous{ new Node{} };

        Node* operator++()
        {
            return this->next;
        }

        Node* operator--()
        {
            return this->previous;
        }

    };

    MyList();
    MyList(std::initializer_list<T> list);
    MyList(const MyList& list);
    MyList(MyList&& list) noexcept;
    ~MyList();

    MyList& operator=(const MyList& list) noexcept;
    friend bool operator==(const MyList& l1, const MyList l2);
    friend bool operator!=(const MyList& l1, const MyList l2);
    friend bool operator>(const MyList& l1, const MyList l2);
    friend bool operator<(const MyList& l1, const MyList l2);

    Node* begin();
    Node* end();

    bool empty() const;
    int size() const;
    void clear();
    void erase();
    void insert(T value, int index);
    void push_back(T value);
    void push_front(T value);
    T pop_back();
    T pop_front();
    void swap();
    void merge();

private:
    Node* m_start{};
    Node* m_end{};
    int m_size{};
};

template<typename T>
MyList<T>::MyList()
{
    m_start = new Node{0, 0, m_end, nullptr};
    m_end = new Node{0, 1, nullptr, m_start};
    m_size = 2;
}

template<typename T>
MyList<T>::MyList(std::initializer_list<T> list)
{
    m_start->value = *list;

}

template<typename T>
void MyList<T>::push_back(T value)
{

}

template<typename T>
void MyList<T>::insert(T value, int index)
{
    int distanseToEnd { m_size - index - 1}; //we have to decide where
    int distanseToStart { index + 1 };       //to start the search

    if(distanseToStart > distanseToEnd)
    {
        Node* searchPoint { m_end };
        for(; searchPoint->index != index; ++searchPoint)
        {};
        assert(searchPoint && "Invalid index in insert()");

        Node newElement{ new Node{value, searchPoint->next, searchPoint}};

        searchPoint->next = newElement;

        newElement->next->previous = newElement;
    }
    else
    {

    }

}

#endif //MYLIST_H
