#include <cstring>
#include <iostream>
#include <stdexcept>
#include "MyString.h"


StringValue::StringValue(const char *str) {
    this->str = new char[strlen(str)+1];
    strcpy(this->str, str);
    this->str[strlen(str)] = '\0';
    this->refCount = 1;
}

StringValue::StringValue(char *str, Adopt adopt) {
    this->str = str;
    this->refCount = 1;
}

char *StringValue::getStr() const {
    return str;
}

unsigned int StringValue::getRefCount() const {
    return refCount;
}

void StringValue::addReference() {
    refCount++;
}

void StringValue::takeReference() {
    if (this->refCount == 0)
        throw std::underflow_error("Reference count underflown zero");
    refCount--;
}

StringValue::~StringValue() {
    delete[] this->str;
}

StringValue::StringValue() {
    this->str = new char[1];
    this->str[0] = '\0';
    this->refCount = 1;
}

MyString::MyString() {
    this->stringVal = new StringValue();
}

MyString::MyString(const MyString & cpy) {
    this->stringVal = cpy.stringVal;
    this->stringVal->addReference();
}

MyString::MyString(MyString && cpy) noexcept {
    this->stringVal = cpy.stringVal;
    cpy.stringVal = nullptr;
}

MyString::MyString(const char *str) {
    this->stringVal = new StringValue(str);
}

MyString::MyString(char *str, Adopt adopt) {
    this->stringVal = new StringValue(str, adopt);
}

MyString::MyString(const std::string &str) {
    this->stringVal = new StringValue(str.c_str());
}

std::ostream &operator<<(std::ostream &os, const MyString &string) {
    os << string.stringVal->getStr();
    return os;
}

void MyString::dropValue() {
    this->stringVal->takeReference();
    if (this->stringVal->getRefCount() == 0)
        delete this->stringVal;
    this->stringVal = nullptr;
}

void MyString::reset() {
    this->dropValue();
    this->stringVal = new StringValue();
}

size_t MyString::length() const {
    return strlen(this->stringVal->getStr());
}

MyString &MyString::operator=(const MyString &rhs) {
    if (this != &rhs) {
        this->dropValue();
        this->stringVal = rhs.stringVal;
        this->stringVal->addReference();
    }
    return *this;
}

MyString &MyString::operator=(MyString &&rhs) noexcept {
    if (&rhs != this) {
        this->dropValue();
        this->stringVal = rhs.stringVal;
        rhs.stringVal = nullptr;
    }
    return *this;
}

MyString MyString::operator+(const MyString &rhs) const {
    size_t size = this->length() + rhs.length() + 1;
    char *tmp = new char[size];
    strcpy(tmp, this->stringVal->getStr());
    strcat(tmp, rhs.stringVal->getStr());
    auto ret = MyString(tmp);
    delete[] tmp;
    return ret;
}

MyString &MyString::operator+=(const MyString &rhs) {
    *this = *this + rhs;
    return *this;
}

MyString MyString::operator+(char c) const {
    char *tmp = new char[this->length() + 2];
    strcpy(tmp, this->stringVal->getStr());
    tmp[this->length()] = c;
    tmp[this->length() + 1] = '\0';
    auto ret = MyString(tmp);
    delete[] tmp;
    return ret;
}

MyString &MyString::operator+=(char c) {
    *this = *this + c;
    return *this;
}

std::istream &operator>>(std::istream &is, MyString &string) {
    string.reset();
    char c = 0;
    while (c != '\n') {
        c = is.get();
        string += c;
    }
    string += '\0';
    return is;
}

char &MyString::operator[](size_t idx) {
    if (this->stringVal->getRefCount() > 1) {
        MyString temp(this->stringVal->getStr());
        this->dropValue();
        this->stringVal = temp.stringVal;
        this->stringVal->addReference();
    }
    return this->stringVal->getStr()[idx];
}

char MyString::operator[](size_t idx) const {
    return this->stringVal->getStr()[idx];
}

char *MyString::c_str() {
    if (this->stringVal == nullptr)
        throw std::range_error("No string :c");
    return this->stringVal->getStr();
}

MyString::~MyString() {
    if (this->stringVal != nullptr)
        this->dropValue();
}
