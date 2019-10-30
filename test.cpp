#include <iostream>
#include "MyString.h"

int main() {
    MyString x = "Hello ";
    MyString y = "World!";
    std::cout << x << y << std::endl;
    x[0] = 'C';
    MyString s = x + y;
    x += y;
    std::cout << s <<std::endl << x << std::endl;
    const MyString alma = "alma";
    std::cout << alma[0] << std::endl;
    MyString almafa = alma;
    (almafa += 'f') += 'a';
    std::cout << almafa << std::endl;
    MyString input;
    std::cin >> input;
    x = std::move(input);
    std::cout << x << std::endl;

}

