#include "MyString.h"

#include <iostream>
#include <algorithm>
#include <cassert>

MyString::MyString(const char* str)
{
    assert(str != nullptr && "Invalid construction");
    int size { stringSize(str) };

    m_size = size;
    m_data = new char[m_size + 1]{};

    std::copy_n(str, size, m_data);

}

MyString::MyString(const MyString& str)
{
    if(str.empty())
    {
        erase();
        return;
    }
    m_size = str.m_size;
    m_data = new char[m_size + 1]{};

    std::copy_n(str.m_data, m_size, m_data);
}

MyString::MyString(MyString&& str) noexcept
{
    delete[] m_data;
    m_data = str.m_data;
    m_size = str.m_size;

    str.m_data = nullptr;
    str.m_size = 0;
}


MyString& MyString::operator= (const MyString& str) noexcept
{
    if(this == &str)
        return *this;

    delete[] m_data;
    m_size = str.m_size;
    m_data = new char[m_size + 1]{};

    std::copy_n(str.m_data, m_size, m_data);

    return *this;
}


MyString MyString::operator+=(const MyString& str)
{
    char* data { new char[m_size + str.m_size + 1]{} };

    std::copy_n(m_data, m_size, data);
    std::copy_n(str.m_data, str.m_size, data + m_size);

    return MyString{data};
}

char MyString::operator[](int index) const
{
    assert(index >= 0 && index <= m_size && "Index is out of bounds in []");
    return m_data[index];
}

std::ostream& operator<< (std::ostream& out, const MyString& str)
{
    for(int i{0}; i < str.m_size; ++i)
        out << str[i];
    return out;

}

bool operator== (const MyString& str_1, const MyString& str_2)
{
    if(str_1.m_size != str_2.m_size)
        return false;
    for(int i{0}; i < str_1.m_size; ++i)
        if(str_1[i] != str_2[i])
            return false;

    return true;
}

bool operator> (const MyString& str_1, const MyString& str_2)
{
    if(str_1.m_size != str_2.m_size)
        return (str_1.m_size > str_2.m_size);

    for(int i{0}; i < str_1.m_size; ++i)
        if(str_1[i] < str_2[i])
            return false;

    return true;
}

std::istream& operator>> (std::istream& in, MyString& str)
{
    delete[] str.m_data;

    char buffer[1024]{};
    in.getline(buffer, sizeof(buffer));

    int size { stringSize(buffer) };

    str.m_data = new char[size + 1]{};
    str.m_size = size;
    std::copy_n(buffer, size, str.m_data);

    return in;
}

void MyString::resize(int newSize)
{
    assert(newSize >= 0 && "Negative size in resize()");
    char* data{ new char[newSize+1]{} };

    for(int i{0}; i < newSize; ++i)
    {
        if(i == m_size) //if newSize > m_size we leave the rest elements with zeros
            break;
        data[i] = m_data[i];
    }

    delete[] m_data;
    m_data = data;
    m_size = newSize;

    data = nullptr;
}

bool MyString::empty() const
{
    return !m_size; // m_size == 0
}

void MyString::erase()
{
    assert(m_data != nullptr && "Erase of empty string");

    delete[] m_data;
    m_data = nullptr;
    m_size = 0;
}

void MyString::clear()
{
    for(int i{0}; i < m_size; ++i)
        m_data[i] = ' ';
}

void MyString::insert(char symbol, int index)
{
    assert(index >= 0 && index <= m_size && "Index is out of bounds in insert()");

    // size + 2 because we should store '\0' and new symbol
    char* data { new char[m_size + 2]{} };
    std::copy_n(m_data, index, data);
    data[index] = symbol;
    std::copy_n(m_data + index, m_size - index, data + index + 1);

    m_data = data;
    ++m_size;

    data = nullptr;
}

void MyString::replace(int pos, int len, const MyString& str)
{
    assert(pos >= 0 && pos < m_size && "Invalid position in replace()");
    assert(len >= 0 && (pos + len + 1) < m_size && "Invalid length in replace()");
    assert(str.m_data != nullptr && "Invalid string for replace");

    int newSize { m_size - len + str.m_size};
    char* data { new char[newSize + 1]{} };

    std::copy_n(m_data, pos, data);
    std::copy_n(str.m_data, str.m_size, data + pos);
    std::copy_n(m_data+pos, m_size - pos, data + pos + str.m_size);


    m_data = data;
    m_size = newSize;

    data = nullptr;
}

MyString MyString::substr(int index, int length)
{
    assert(index >= 0 && index < m_size && "Invalid index in substr()");
    assert((index + length) <= m_size && "Invalid length for this index in substr()");

    char* data { new char[length + 1]{} };
    std::copy_n(m_data + index, length, data);

    return MyString{data};
}

int MyString::find(const MyString& str, int pos) const
{
    assert(pos >= 0 && pos < m_size && "Invalid position in find()");

    for(int i{0}; i < m_size; ++i)
    {
        if(m_data[i] == str[0])
        {
            int posOfMatch{i};
            for(int j{0}; j < str.m_size + 1; ++j)
            {
                if(j == str.m_size) //if our j == size of str it means that we found match
                    return posOfMatch;

                if(m_data[i] != str.m_data[j])
                    break;

                ++i;
            }
        }
    }
    return -1;
}
