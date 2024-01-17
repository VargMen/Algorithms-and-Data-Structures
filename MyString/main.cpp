#include <iostream>
#include "MyString.h"

int main() {
    MyString a {"aaa_bbb_ccc_aaa_bbb_ccc"};

    std::cout << a.find("aaa", 15) << '\n';
    return 0;
}
