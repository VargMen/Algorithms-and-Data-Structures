#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

class MyString
{
public:
    explicit MyString(const char* str);
    MyString(const MyString& str);
    MyString(MyString&& str) noexcept;
    ~MyString() { delete[] m_data; }

    int size() const { return m_size; }
    void clear();
    void erase();
    void insert(char symbol, int index);
    void append(char symbol) { insert(symbol, m_size - 1); }
    void replace(int pos, int len, const MyString& str);
    int find(const MyString& str, int pos = 0) const;
    MyString substr(int index, int length);
    MyString substr(int index) { return substr(index, m_size - index); }
    bool empty() const;


    MyString& operator= (const MyString& str) noexcept;
    MyString operator+=(const MyString& str);
    char operator[](int index) const;
    friend bool operator== (const MyString& str_1, const MyString& str_2);
    friend bool operator> (const MyString& str_1, const MyString& str_2);
    friend bool operator< (const MyString& str_1, const MyString& str_2) { return !(str_1 > str_2); }
    friend std::ostream& operator<< (std::ostream& out, const MyString& str_2);
    friend std::istream& operator>> (std::istream& in, MyString& str_2);

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
