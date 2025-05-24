#ifndef MYSTR_H
#define MYSTR_H


#include<iostream>
using namespace std;


class MyStr {
    char* Cs;
    int len;
    int cap;


    int length(const char* str);


public:
    //All Possible Constructors
    MyStr();
    MyStr(const char* p);
    MyStr(char ch, int size);
    MyStr(int num);


    //Deep Copy
    MyStr(const MyStr& str);


    //MyStr to integer
    int stoi(const MyStr& str);
    //integer to MyStr;
    MyStr itos(int num);


    //MyStr Comparison
    bool is_equal(const MyStr& M) const;
    bool is_less(const MyStr& M) const;
    bool is_greater(const MyStr& M);




    char& operator[](int index);
    const char& operator[](int index) const;


    //Trim MyStr
    MyStr& trim();
    MyStr trim(const MyStr& str);
    //Tokenize and Split MyStr
    MyStr* split(char delim, int& count) const;
    MyStr* tokenize(char delim, int& count);


    //Joining MyStrs
    MyStr concat(const MyStr& s2)const;
    MyStr& append(const MyStr& s2);
    //Finding functions
    int find_first(char ch);
    int find_first(const MyStr& str) const;
    int find_last(char ch) const;
    int find_last(const MyStr& str) const;
    int* find_all(char ch, int& C);
    int* find_all(const MyStr& str, int& C) const;


    int* subMyStr_search(const MyStr& str, int& count) const;


    //Add and remove functions
    void remove_at(int idx);
    void insert_at(int idx, char ch);
    void insert_at(int idx, const MyStr sub);
    //remove characters
    void remove_first(char ch);
    void remove_last(char ch);
    void remove_all(char ch);
    void clear();


    //Letter Conversion
    void ToUpper();
    void ToLower();



    MyStr& operator=(const MyStr& other);
    MyStr operator+(const MyStr& other);
    friend ostream& operator<<(ostream& os, const MyStr& str);
    friend istream& operator>>(istream& is, MyStr& str);
    ~MyStr();


    const char* fetchstr() const;


};


MyStr operator+(const MyStr& str1, const MyStr& str2);

class MyStrStream {
    MyStr buffer;

public:
    MyStrStream();

    MyStrStream& operator<<(int num);

    MyStrStream& operator<<(char ch);

    MyStrStream& operator<<(const char* str);

    MyStrStream& operator<<(const MyStr& str);

    MyStr str() const;

    void clear();
};





#endif#pragma once




