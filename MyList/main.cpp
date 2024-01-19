#include <iostream>
#include "MyList.h"

int main()
{
    MyList l1{1, 2, 3, 4, 5};

    MyList l2{1, 2, 3, 4, 5};

    std::cout << std::boolalpha << (l1 != l2) << '\n';
}
