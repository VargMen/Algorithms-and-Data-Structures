#include <iostream>
#include "MyList.h"

int main()
{
    MyList list {1, 2, 3, 4, 5, 6 ,7};
    std::cout << list << '\n';

    list.erase(2);
    std::cout << list << '\n';
    return 0;
}