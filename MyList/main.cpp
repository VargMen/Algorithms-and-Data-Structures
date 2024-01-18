#include <iostream>
#include <list>
#include "MyList.h"

int main()
{
    MyList l{1, 2, 3, 4, 5};
    std::cout << l << '\n';

    l.erase(MyList<int>::Iterator{l.begin()});
}