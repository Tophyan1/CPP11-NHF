#include <iostream>
#include <cassert>
#include <cstring>
#include "MyString.h"


void test_new_Empty_MyString() {
    MyString empty;
    assert(strcmp(empty.c_str(), "") == 0);
}

void test_new_MyString_with_literal() {
    MyString literal("alma");
    assert(strcmp(literal.c_str(), "alma") == 0);
}

void test_new_MyString_with_other_MyString() {
    MyString s1("alma");
    MyString s2(s1);
    assert(strcmp(s1.c_str(), s2.c_str()) == 0);
}


void test_new_MyString_moveCtor() {
    MyString s1("alma");
    MyString s2 = std::move(s1);
    assert(strcmp(s2.c_str(), "alma") == 0);
}


void test_new_MyString_from_stdString() {
    std::string alma("alma");
    MyString str(alma);
    assert(strcmp(str.c_str(), "alma") == 0);
}

void test_all_Ctors() {
    test_new_Empty_MyString();
    test_new_MyString_with_literal();
    test_new_MyString_with_other_MyString();
    test_new_MyString_moveCtor();
    test_new_MyString_from_stdString();
}

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

    //New tests

    test_all_Ctors();





}

