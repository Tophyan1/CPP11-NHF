#ifndef CPP11NHF_MYSTRING_H
#define CPP11NHF_MYSTRING_H


#include <string>
#include <iostream>



class StringValue {
public:
    StringValue(const char *str);

    StringValue();

    char *getStr() const;

    unsigned int getRefCount() const;

    void addReference();

    void takeReference();

    virtual ~StringValue();

private:
    char *str;
    unsigned int refCount;
};

class MyString {
public:
    MyString();

    MyString(const MyString & cpy);

    MyString(MyString && cpy) noexcept;

    MyString(const char *str);

    MyString(std::string & str);

    friend std::ostream &operator<<(std::ostream &os, const MyString &string);

    void reset();

    size_t length() const;

    MyString &operator=(const MyString &rhs);

    MyString &operator=(MyString&& rhs) noexcept;

    MyString operator+(const MyString &rhs) const;

    MyString &operator+=(const MyString &rhs);

    MyString operator+(char c) const;

    MyString &operator+=(char c);

    char *c_str();

    char &operator[](size_t idx);

    char operator[](size_t idx) const;

    virtual ~MyString();

private:
    StringValue * reference;

    void leaveValue();
};

std::istream &operator>>(std::istream &is, MyString &string);


#endif //CPP11NHF_MYSTRING_H
