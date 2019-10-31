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
    this->reference = new StringValue();
}

MyString::MyString(const MyString & cpy) {
    this->reference = cpy.reference;
    this->reference->addReference();
}

MyString::MyString(MyString && cpy) noexcept {
    this->reference = cpy.reference;
    cpy.reference = nullptr;
}

MyString::MyString(const char *str) {
    this->reference = new StringValue(str);
}

MyString::MyString(std::string &str) {
    this->reference = new StringValue(str.c_str());
}

std::ostream &operator<<(std::ostream &os, const MyString &string) {
    os << string.reference->getStr();
    return os;
}

void MyString::leaveValue() {
    this->reference->takeReference();
    if (this->reference->getRefCount() == 0)
        delete this->reference;
    this->reference = nullptr;
}

void MyString::reset() {
    this->leaveValue();
    this->reference = new StringValue();
}

size_t MyString::length() const {
    return strlen(this->reference->getStr());
}

MyString &MyString::operator=(const MyString &rhs) {
    if (this != &rhs) {
        this->leaveValue();
        this->reference = rhs.reference;
        this->reference->addReference();
    }
    return *this;
}

MyString &MyString::operator=(MyString &&rhs) noexcept {
    if (&rhs != this) {
        this->leaveValue();
        this->reference = rhs.reference;
        rhs.reference = nullptr;
    }
    return *this;
}

MyString MyString::operator+(const MyString &rhs) const {
    size_t size = this->length() + rhs.length() + 1;
    char *tmp = new char[size];
    strcpy(tmp, this->reference->getStr());
    strcat(tmp, rhs.reference->getStr());
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
    strcpy(tmp, this->reference->getStr());
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
    if (this->reference->getRefCount() > 1) {
        MyString temp(this->reference->getStr());
        this->leaveValue();
        this->reference = temp.reference;
        this->reference->addReference();
    }
    return this->reference->getStr()[idx];
}

char MyString::operator[](size_t idx) const {
    return this->reference->getStr()[idx];
}

char *MyString::c_str() {
    if (this->reference == nullptr)
        throw std::range_error("No string :c");
    return this->reference->getStr();
}

MyString::~MyString() {
    if (this->reference != nullptr)
        this->leaveValue();
}
