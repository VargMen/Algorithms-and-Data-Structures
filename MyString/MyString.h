#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

class MyString
{
public:
    MyString(const char* str = "");
    MyString(const MyString& str);
    MyString(MyString&& str) noexcept;
    ~MyString() { delete[] m_data; }

    char front() { return m_data[0]; }
    char back() { return m_data[m_size-1]; }
    char* data() { return m_data; }
    void push_back(char newChar) { insert(newChar,m_size-1);}
    char pop_back();
    void resize(int newSize);
    int size() const { return m_size; }
    void clear();
    void erase();
    void insert(char symbol, int index);
    void append(char symbol) { insert(symbol, m_size - 1); }
    void replace(int pos, int len, const MyString& str);
    int find(const MyString& str, int pos = 0, int numOfChars = 0) const;
    MyString substr(int index, int length);
    MyString substr(int index) { return substr(index, m_size - index); }
    bool empty() const;


    MyString& operator= (const MyString& str) noexcept;
    MyString& operator= (MyString&& str) noexcept;
    MyString operator+=(const MyString& str);
    friend MyString operator+(const MyString& str_1, const MyString& str_2);
    char operator[](int index) const;
    bool operator== (const MyString& str) const;
    bool operator!= (const MyString& str) const { return !(*this == str); }
    bool operator> (const MyString& str) const;
    bool operator< (const MyString& str) const { return !(*this > str); }
    friend std::ostream& operator<< (std::ostream& out, const MyString& str);
    friend std::istream& operator>> (std::istream& in, MyString& str);

private:
    char* m_data{};
    int m_size{};
};

inline int stringSize(const char* str)
{
    int count{0};
    for(; str[count] != '\0'; ++count)
    {}
    return count;
}


#endif //MYSTRING_H
