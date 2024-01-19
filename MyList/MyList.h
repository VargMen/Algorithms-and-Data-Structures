#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <initializer_list>
#include <cassert>
#include <algorithm> // for std::swap


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

    MyList();
    MyList(std::initializer_list<T> list);
    ~MyList();


    MyList& operator=(const MyList& list);

    bool operator==(const MyList& list);
    bool operator!=(const MyList& list) { return !(*this == list); }
    bool operator>(const MyList& list);
    bool operator<(const MyList& list) { return !(*this > list); }

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

    Node* find(int index);
    T front() { return m_start->value; }
    T back() { return m_end->value; }
    bool empty() const { return m_start; } // if start is not nullptr so is not empty
    int size() const;
    void clear();
    void erase(int index);
    void erase(int first, int last);
    void insert(T value, int index);
    void push_back(T value);
    void push_front(T value);
    T pop_back();
    T pop_front();
    void swap(MyList& list);
    void merge(MyList& list);

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

    if(index == size())
    {
        push_back(value);
        return;
    }
    if(!index) // index == 0
    {
        push_front(value);
        return;
    }

    auto* newElement { new Node{ value } };
    auto* current { find(index) };

    newElement->previous = current->previous;
    current->previous->next = newElement;

    newElement->next = current;
    current->previous = newElement;
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
MyList<T>::Node* MyList<T>::find(int index)
{
    int listSize { size() };
    assert(index < listSize && index >= 0 && "Index is out of bounds in erase()");

    if(!index) //index == 0
    {
        return m_start;
    }
    if(index == listSize - 1) //if it is index of last element
    {
        return m_end;
    }

    int distanceFromEnd {listSize - index - 1};
    int distanceFromStart {index};
    int counter{};

    Node* current {nullptr};
    if(distanceFromStart <= distanceFromEnd)
    {
        current = m_start;
        while(counter != index)
        {
            current = current->next;
            ++counter;
        }
    }
    else
    {
        current = m_end;
        while(counter != distanceFromEnd)
        {
            current = current->previous;
            ++counter;
        }
    }
    return current;
}

template<typename T>
void MyList<T>::erase(int index)
{
    int listSize { size() };
    assert(index < listSize && index >= 0 && "Index is out of bounds in erase()");

    if(!index) //index == 0
    {
        pop_front();
        return;
    }
    if(index == listSize - 1)
    {
        pop_back();
        return;
    }

    auto current {find(index)};

    current->previous->next = current->next; //now the node before the current
    //points to the node after the current

    current->next->previous = current->previous;//it is the same here but in reverse

    current->next = nullptr;
    current->previous = nullptr;
    delete current;
}

template<typename T>
void MyList<T>::erase(int first, int last)
{
    assert(first != last && "Arguments first and last cannot be equal in erase()");

    int listSize { size() };
    assert(first <= last && "Bad arguments first and last in erase()");
    assert(first < listSize && first >= 0 && "Argument first is out of bounds in erase()");
    assert(last < listSize && last >= 0 && "Argument last is out of bounds in erase()");


    auto* firstNode{ find(first) }; //elements will be deleted after that including the element with the index last
    auto* lastNode{ find(last) }; //this will be deleted

    auto* current {firstNode->next};

    while(current != lastNode && current) //element after the current != nullptr
    {
        current = current->next;
        delete current->previous;
    }

    firstNode->next = current->next;
    if(current) //if it is not the last element
        current->previous = firstNode;
    else
        m_end = firstNode;

}

template<typename T>
void MyList<T>::merge(MyList& list)
{
    if(this == &list)
        return;

    m_end->next = list.m_start;
    list.m_start->previous = m_end;

    m_end = list.m_end;

    list.m_start = nullptr;
    list.m_end = nullptr;
}

template<typename T>
void MyList<T>::swap(MyList& list)
{
    std::swap(m_start, list.m_start);
    std::swap(m_end, list.m_end);
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

template<typename T>
bool MyList<T>::operator==(const MyList& list)
{
    auto* firstCurrent { m_start };
    auto* secondCurrent { list.m_start };

    while(firstCurrent) // while firstCurrent != list.m_end->next
    {
        if(firstCurrent->value != secondCurrent->value)
            return false;

        firstCurrent = firstCurrent->next;
        secondCurrent = secondCurrent->next;
    }

    return true;
}

template<typename T>
bool MyList<T>::operator>(const MyList& list)
{
    int firstSize { size() };
    int secondSize{ list.size() };
    if(firstSize == secondSize)
    {
        auto* firstCurrent { m_start };
        auto* secondCurrent { list.m_start };

        while(firstCurrent) // while firstCurrent != list.m_end->next
        {
            if(firstCurrent->value < secondCurrent->value)
                return false;

            firstCurrent = firstCurrent->next;
            secondCurrent = secondCurrent->next;
        }
        return true;
    }
    return firstSize > secondSize;
}
#endif //MYLIST_H

