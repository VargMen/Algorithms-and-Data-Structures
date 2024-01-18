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
        Node* next{};
        Node* previous{};

        Node(T value = 0)
        : value(value), next{nullptr}, previous{nullptr}
        {
        }
    };

    struct Iterator
    {
        Node* node{};

        Iterator(Node* node)
        : node(node)
        {}
        Iterator& operator+(int value)
        {
            for(int i{0}; i < value; ++i)
            {
                assert(node && "Iterator is out of bounds in operator +");
                node = node->next;
            }
            return *this;
        }

        Iterator& operator++()
        {
            return (*this + 1);
        }

        Iterator& operator-(int value)
        {
            for(int i{value}; i > 0; --i)
            {
                assert(node && "Iterator is out of bounds in operator +");
                node = node->previous;
            }
            return *this;
        }

        T value() { return node->value; }
        Node* element() { return node; }
    };
    MyList();
    MyList(std::initializer_list<T> list);
    ~MyList();


    MyList& operator=(const MyList& list);

    bool operator==(const MyList list);
    bool operator!=(const MyList list);
    bool operator>(const MyList list);
    bool operator<(const MyList list);

    friend std::ostream& operator<<(std::ostream& out, const MyList& list)
    {
        auto* current { list.m_start };
        out << '(';
        while(current)
        {
            if(!current->next) // if it is the last element
            {
                out << current->value;
                break;
            }
            out << current->value << ", ";
            current = current->next;
        }
        out << ')';

        return out;
    }

    Node* begin() { return m_start; }
    Node* end() { return m_end; }

    T front() { return m_start->value; }
    T back() { return m_end->value; }
    bool empty() const { return m_start; } // if start is not nullptr so is not empty
    int size() const;
    void clear();
    void erase(const Iterator& first, const Iterator& last);
    void erase(const Iterator& pos);
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
};

template<typename T>
MyList<T>::MyList()
:m_start{nullptr}, m_end{nullptr}
{
}

template<typename T>
MyList<T>::MyList(std::initializer_list<T> list)
{
    for(const auto& e: list)
        push_back(e);
}


template<typename T>
MyList<T>::~MyList()
{
    while(m_start) // node != nullptr
    {
        delete m_start->previous;
        m_start = m_start->next;
    }
}

template<typename T>
void MyList<T>::push_back(T value)
{
    Node* node { new Node{value} };
    node->previous = m_end;
    if(m_end) // if m_end == nullptr
        m_end->next = node;
    if(!m_start) // if m_start == nullptr
        m_start = node;
    m_end = node;
}

template<typename T>
void MyList<T>::push_front(T value)
{
    Node* node {new Node{value} };
    node->next = m_start;
    if(m_start)
        m_start->previous = node;
    if(!m_end)
        m_end = node;
    m_start = node;
}

template<typename T>
T MyList<T>::pop_back()
{
    T returnValue { m_end->value };
    auto* beforEnd { m_end->previous };
    beforEnd->next = nullptr; //now the element before the end does not point to the end element

    delete m_end;

    m_end = beforEnd;

    return returnValue;
}

template<typename T>
T MyList<T>::pop_front()
{
    T returnValue { m_start->value };
    auto* afterStart { m_start->next };
    afterStart->previous = nullptr; //now the element after the start does not point to the start element

    delete m_start;

    m_start = afterStart;

    return returnValue;
}
template<typename T>
void MyList<T>::insert(T value, int index)
{

}
template<typename T>
void MyList<T>::clear()
{
    while (m_start) // while start != end->next which is nullptr
    {
        delete m_start->previous;
        m_start = m_start->next;
    }
    m_end->previous = nullptr;
}

template<typename T>
int MyList<T>::size() const
{
    auto* current { m_start };
    int counter{};
    while(current)
    {
        current = current->next;
        ++counter;
    }

    return counter;
}

template<typename T>
void MyList<T>::erase(const Iterator& first, const Iterator& last)
{
}

template<typename T>
void MyList<T>::erase(const Iterator& pos)
{
    auto* previousElement { pos.node->previous };
    previousElement->next = nullptr;
    m_end = previousElement;

    while(pos.node)
    {
        delete pos.node;
        ++pos.node;
    }
}


template<typename T>
MyList<T>& MyList<T>::operator=(const MyList& list)
{
    if (this == &list)
        return *this;

    auto* current {list.m_start};
    while(current)
    {
        push_back(current->value);

        current = current->next;
    }

    return *this;
}
#endif //MYLIST_H
