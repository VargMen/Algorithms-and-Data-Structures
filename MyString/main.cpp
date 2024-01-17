#include <iostream>
#include "MyString.h"

int main() {
    MyString a { "qwerty"};
    std::cout << a << '\n';

    MyString b {"AAa"};
    std::cout << b << '\n';

    MyString c { std::move(MyString{"ab"}) };
    std::cout << std::boolalpha << (a == b) << '\n';
    return 0;
}
