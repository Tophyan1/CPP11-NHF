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

void test_MyString_assignment() {
    MyString s1;
    MyString s2("alma");
    s1 = s2;
    assert(strcmp(s1.c_str(), "alma") == 0);
}

void test_MyString_move_assignment() {
    MyString s1;
    MyString s2("alma");
    s1 = std::move(s2);
    assert(strcmp(s1.c_str(), "alma") == 0);
}

void test_assignment_operators() {
    test_MyString_assignment();
    test_MyString_move_assignment();
}

void test_adding_char_and_MyString() {
    MyString str("alma");
    assert(strcmp((str + 'c').c_str(), "almac") == 0);
}

void test_adding_char_to_MyString() {
    MyString str("alma");
    str += 'c';
    assert(strcmp(str.c_str(), "almac") == 0);
}

void test_adding_MyString_and_MyString() {
    MyString s1("alma");
    MyString s2("fa");
    assert(strcmp((s1 + s2).c_str(), "almafa") == 0);
}

void test_adding_MyString_to_MyString() {
    MyString s1("alma");
    MyString s2("fa");
    s1 += s2;
    assert(strcmp(s1.c_str(), "almafa") == 0);
}

void test_adding_const_MyString_and_char() {
    const MyString s("alma");
    assert(strcmp((s + 'c').c_str(), "almac") == 0);
}

void test_adding_const_MyString_and_MyString() {
    const MyString s1("alma");
    MyString s2("fa");
    assert(strcmp((s1 + s2).c_str(), "almafa") == 0);
}

void test_simple_adding() {
    test_adding_char_and_MyString();
    test_adding_char_to_MyString();
    test_adding_const_MyString_and_char();
    test_adding_MyString_and_MyString();
    test_adding_MyString_to_MyString();
    test_adding_const_MyString_and_MyString();
}

void test_chain_adding_MyString_to_char() {
    MyString str("alma");
    str += 'f';
    str += 'a';
    assert(strcmp(str.c_str(), "almafa") == 0);
}

void test_chain_adding_MyString_to_MyString() {
    MyString s1("arany");
    MyString s2("alma");
    MyString s3("fa");
    s1 += s2;
    s1 += s3;
    assert(strcmp(s1.c_str(), "aranyalmafa") == 0);
}

void test_chained_adding() {
    test_chain_adding_MyString_to_char();
    test_chain_adding_MyString_to_MyString();
}

void test_adding() {
    test_simple_adding();
    test_chained_adding();
}


void test_indexing_MyString() {
    MyString str("Hello World!");
    assert(str[3] == 'l');
}

void test_indexing_const_MyString() {
    const MyString str("Hello World!");
    assert(str[3] == 'l');
}

void test_changing_MyString_by_indexing() {
    MyString str("Hello World!");
    str[5] = ',';
    assert(strcmp(str.c_str(), "Hello,World!") == 0);
}

void test_indexing() {
    test_indexing_MyString();
    test_indexing_const_MyString();
    test_changing_MyString_by_indexing();
}

int main() {
    test_all_Ctors();
    test_assignment_operators();
    test_adding();
    test_indexing();
    MyString input;
    std::cin >> input;
    std::cout << input << std::endl;


}

