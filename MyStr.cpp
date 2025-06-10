#include "Mystr.h"
#include<iostream>


//All Possible Constructors


int MyStr::length(const char* str) {
    int size = 0;
    for (; str[size] != '\0'; size++) {}
    return size;
}


MyStr::MyStr() {
    Cs = nullptr;
    len = 0;
    cap = 0;
}
MyStr::MyStr(const char* p) {
    len = length(p);
    cap = len + 10;
    Cs = new char[cap];
    for (int i = 0; i < len; i++) {
        Cs[i] = p[i];
    }
}
MyStr::MyStr(char ch, int size) {
    len = size;
    cap = size + 1;
    Cs = new char[cap];
    for (int i = 0; i < len; i++) {
        Cs[i] = ch;
    }
    Cs[len] = '\0';
}
MyStr::MyStr(int num) {
    cap = 20;
    int* tempchar = new int[cap];
    len = 0;


    if (num == 0) {
        Cs = new char[2];
        Cs[0] = '0';
        Cs[1] = '\0';
        len = 1;
        delete[] tempchar;
        return;
    }


    while (num != 0) {
        tempchar[len] = (num % 10) + '0';
        num /= 10;
        len++;
    }


    Cs = new char[len + 1];
    for (int i = 0; i < len; i++) {
        Cs[i] = tempchar[len - i - 1];
    }
    Cs[len] = '\0';


    delete[] tempchar;
}
//Deep Copy
MyStr::MyStr(const MyStr& str) {
    this->len = str.len;
    this->cap = str.cap;
    this->Cs = new char[this->cap];
    for (int i = 0; i < this->len; i++) {
        this->Cs[i] = str.Cs[i];
    }
    this->Cs[len] = '\0';
}


//MyStr to integer
int MyStr::stoi(const MyStr& str) {
    int res = 0;
    for (int i = 0; i < str.len; i++) {
        res = (res * 10) + str.Cs[i] - '0';
    }
    return res;
}
//integer to MyStr;
MyStr MyStr::itos(int num) {
    char* temparr = new char[20];
    int count = 0;


    while (num != 0) {
        temparr[count] = (num % 10) + '0';
        num /= 10;
        count++;
    }


    MyStr res;
    res.len = count;
    res.cap = count + 1;
    res.Cs = new char[res.cap];


    for (int i = 0; i < count; i++) {
        res.Cs[i] = temparr[count - i - 1];
    }
    res.Cs[count] = '\0';
    delete[] temparr;
    return res;
}


//MyStr Comparison
bool MyStr::is_equal(const MyStr& M) const {
    if (this == &M) {
        return true;
    }
    if (this->len != M.len) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (Cs[i] != M.Cs[i]) {
            return false;
        }
    }
    return true;
}
bool MyStr::is_less(const MyStr& M) const {
    int minLen;
    if (len < M.len) {
        minLen = len;
    }
    else {
        minLen = M.len;
    }


    for (int i = 0; i < minLen; i++) {
        if (Cs[i] < M.Cs[i]) {
            return true;
        }
        else if (Cs[i] > M.Cs[i]) {
            return false;
        }
    }


    return len < M.len;


}
bool MyStr::is_greater(const MyStr& M) {
    int minLen;
    if (len < M.len) {
        minLen = len;
    }
    else {
        minLen = M.len;
    }


    for (int i = 0; i < minLen; i++) {
        if (Cs[i] < M.Cs[i]) {
            return false;
        }
        else if (Cs[i] > M.Cs[i]) {
            return true;
        }
    }


    return len > M.len;


}






char& MyStr::operator[](int index) {
    if (index >= 0 && index < len) {
        return Cs[index];
    }
}




const char& MyStr::operator[](int index) const {
    if (index >= 0 && index < len) {
        return Cs[index];
    }
}










//Trim MyStr
MyStr& MyStr::trim() {
    int startidx = 0;
    for (int i = 0; i < len; i++) {
        if (Cs[i] != ' ' && Cs[i] != '\n' && Cs[i] != '\t') {
            startidx = i;
            break;
        }
    }
    int lastidx = len - 1;
    for (int i = len - 1; i >= 0; i--) { // Fix: `i >= 0`
        if (Cs[i] != ' ' && Cs[i] != '\n' && Cs[i] != '\t') {
            lastidx = i;
            break;
        }
    }


    int newLen = lastidx - startidx + 1;
    char* newCs = new char[newLen + 1];


    for (int i = 0; i < newLen; i++) {
        newCs[i] = Cs[startidx + i];
    }


    newCs[newLen] = '\0';


    delete[] Cs;
    Cs = newCs;
    len = newLen;
    cap = newLen + 1;


    return *this;
}
MyStr MyStr::trim(const MyStr& str) {
    int startidx = 0;
    for (int i = 0; i < str.len; i++) {
        if (str.Cs[i] != ' ' && str.Cs[i] != '\n' && str.Cs[i] != '\t') {
            startidx = i;
            break;
        }
    }
    int lastidx = str.len - 1;
    for (int i = str.len - 1; i >= 0; i--) {
        if (str.Cs[i] != ' ' && str.Cs[i] != '\n' && str.Cs[i] != '\t') {
            lastidx = i;
            break;
        }
    }


    int newLen = lastidx - startidx + 1;
    char* newCs = new char[newLen + 1];


    for (int i = 0; i < newLen; i++) {
        newCs[i] = str.Cs[startidx + i];
    }
    newCs[newLen] = '\0';


    return newCs;
}


//Tokenize and Split MyStr
MyStr* MyStr::split(char delim, int& count) const {


    for (int i = 0; i < len; i++) {
        if (Cs[i] == delim) {
            count++;
        }
    }


    MyStr* split_MyStrs = new MyStr[count + 1];
    int idx = 0;


    int start_idx = 0;
    for (int i = 0; Cs[i] != '\0'; i++) {
        if (Cs[i] == delim) {
            int sub_len = i - start_idx;
            char* temp = new char[sub_len + 1];
            for (int j = 0; j < sub_len; j++) {
                temp[j] = Cs[start_idx + j];
            }
            temp[sub_len] = '\0';
            split_MyStrs[idx] = temp;
            idx++;


            delete[] temp;
            start_idx = i + 1;
        }
    }


    return split_MyStrs;
}
MyStr* MyStr::tokenize(char delim, int& count) {
    for (int i = 0; i < len; i++) {
        if (Cs[i] == delim) {
            count++;
        }
    }


    MyStr* split_MyStrs = new MyStr[count + 1];
    int idx = 0;


    int start_idx = 0;
    for (int i = 0; Cs[i] != '\0'; i++) {
        if (Cs[i] == delim) {
            int sub_len = i - start_idx;
            char* temp = new char[sub_len + 1];
            for (int j = 0; j < sub_len; j++) {
                temp[j] = Cs[start_idx + j];
            }
            temp[sub_len] = '\0';
            split_MyStrs[idx] = temp;
            idx++;


            delete[] temp;
            start_idx = i + 1;
        }
    }


    return split_MyStrs;
}


//Joining MyStrs
MyStr MyStr::concat(const MyStr& s2)const {
    MyStr res;


    res.len = len + s2.len;
    res.cap = cap + s2.cap;
    res.Cs = new char[res.cap];


    for (int i = 0; i < len; i++) {
        res.Cs[i] = Cs[i];
    }
    for (int i = 0; i < s2.len; i++) {
        res.Cs[i + len] = s2.Cs[i];
    }


    res.Cs[res.len] = '\0';
    return res;


}
MyStr& MyStr::append(const MyStr& s2) {
    char* res = new char[len + s2.len + 1];


    for (int i = 0; i < len; i++) {
        res[i] = Cs[i];
    }
    for (int i = 0; i < s2.len; i++) {
        res[i + len] = s2.Cs[i];
    }


    res[len + s2.len] = '\0';


    delete[] Cs;
    Cs = res;
    len += s2.len;
    cap = len + 1;


    return *this;
}


//Finding functions
int MyStr::find_first(char ch) {
    for (int i = 0; i < len; i++) {
        if (Cs[i] == ch) {
            return i;
        }
    }
}
int MyStr::find_first(const MyStr& str) const {
    for (int i = 0; i <= len - str.len; i++) {
        bool match = true;
        for (int j = 0; j < str.len; j++) {
            if (Cs[i + j] != str.Cs[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return i;
        }
    }


    return -1;
}
int MyStr::find_last(char ch) const {
    for (int i = len - 1; i >= 0; i--) {
        if (Cs[i] == ch) {
            return i;
        }
    }
    return -1;
}
int MyStr::find_last(const MyStr& str) const {
    for (int i = len - str.len; i >= 0; i--) {
        bool match = true;
        for (int j = 0; j < str.len; j++) {
            if (Cs[i + j] != str.Cs[j]) {
                match = false;
                break;
            }
        }


        if (match) {
            return i;
        }
    }


    return -1;
}
int* MyStr::find_all(char ch, int& C) {
    int* temp = new int[len];
    for (int i = 0; i < len; i++) {
        if (ch == Cs[i]) {
            temp[C] = i;
            C++;
        }
    }


    int* idx = new int[C];
    for (int i = 0; i < C; i++) {
        idx[i] = temp[i];
    }
    delete[] temp;
    return idx;
}
int* MyStr::find_all(const MyStr& str, int& C) const {
    int* temp = new int[len];
    for (int i = 0; i <= len - str.len; i++) {
        bool match = true;
        for (int j = 0; j < str.len; j++) {
            if (Cs[i + j] != str.Cs[j]) {
                match = false;
            }
        }
        if (match) {
            temp[C] = i;
            C++;
        }
    }


    int* idx = new int[C];
    for (int i = 0; i < C; i++) {
        idx[i] = temp[i];
    }
    delete[] temp;
    return idx;
}


int* MyStr::subMyStr_search(const MyStr& str, int& count) const {
    int* temp = new int[len];


    for (int i = 0; i <= len - str.len; i++) {
        bool match = true;
        for (int j = 0; j < str.len; j++) {
            if (Cs[i + j] != str.Cs[j]) {
                match = false;
                break;
            }
        }


        if (match) {
            temp[count] = i;
            count++;
        }
    }


    int* res = new int[count + 1];
    for (int i = 0; i < count; i++) {
        res[i] = temp[i];
    }
    res[count] = -1;


    return res;
}


//Add and remove functions
void MyStr::remove_at(int idx) {
    if (idx < 0 || idx >= len) {
        return;
    }
    for (int i = idx; i < len - 1; i++) {
        Cs[i] = Cs[i + 1];
    }
    len--;
    Cs[len] = '\0';
}
void MyStr::insert_at(int idx, char ch) {


    if (len + 1 >= cap) {
        cap = len + 10;
        char* newCs = new char[cap];
        for (int i = 0; i < len; i++) {
            newCs[i] = Cs[i];
        }
        delete[] Cs;
        Cs = newCs;
    }


    for (int i = len; i >= idx - 1; i--) {
        Cs[i + 1] = Cs[i];
    }


    Cs[idx - 1] = ch;


    len++;
    Cs[len] = '\0';
}
void MyStr::insert_at(int idx, const MyStr sub) {


    if (len + 1 >= cap) {
        cap = len + sub.len;
        char* newCs = new char[cap];
        for (int i = 0; i < len; i++) {
            newCs[i] = Cs[i];
        }
        delete[] Cs;
        Cs = newCs;
    }


    for (int i = len; i >= idx; i--) {
        Cs[i + sub.len] = Cs[i];
    }


    for (int i = 0; i < sub.len; i++) {
        Cs[idx + i] = sub.Cs[i];
    }


    len += sub.len;




}


//remove characters
void MyStr::remove_first(char ch) {
    for (int i = 0; i < len; i++) {
        if (Cs[i] == ch) {
            for (int j = i; j < len - 1; j++) {
                Cs[j] = Cs[j + 1];
            }
            break;
        }
    }
    len--;
    Cs[len] = '\0';
}
void MyStr::remove_last(char ch) {
    for (int i = len; i > 0; i--) {
        if (Cs[i] == ch) {
            for (int j = i; j < len - 1; j++) {
                Cs[j] = Cs[j + 1];
            }
            break;
        }
    }
    len--;
    Cs[len] = '\0';
}
void MyStr::remove_all(char ch) {
    for (int i = 0; i < len; i++) {
        if (Cs[i] == ch) {
            for (int j = i; j < len - 1; j++) {
                Cs[j] = Cs[j + 1];
                len--;
            }
        }
    }
    len--;
    Cs[len] = '\0';
}
void MyStr::clear() {
    for (int i = 0; i < len; i++) {
        Cs[i] = '\0';
    }
    len = 0;
    cap = 0;
}


//Letter Conversion
void MyStr::ToUpper() {
    for (int i = 0; i < len; i++) {
        if (Cs[i] >= 'a' && Cs[i] <= 'z') {
            Cs[i] -= 32;
        }
    }
}
void MyStr::ToLower() {
    for (int i = 0; i < len; i++) {
        if (Cs[i] >= 'A' && Cs[i] <= 'Z') {
            Cs[i] += 32;
        }
    }
}

//Operator overloads
MyStr& MyStr::operator=(const MyStr& other) {
    delete[]this->Cs;
    len = other.len;
    cap = other.cap;
    Cs = new char[cap];
    for (int i = 0; i < len; i++) {
        Cs[i] = other.Cs[i];
    }
    return *this;
}
MyStr MyStr::operator+(const MyStr& other) {
    MyStr res;


    res.len = len + other.len;
    res.cap = cap + other.cap;
    res.Cs = new char[res.cap];


    for (int i = 0; i < len; i++) {
        res.Cs[i] = Cs[i];
    }
    for (int i = 0; i < other.len; i++) {
        res.Cs[i + len] = other.Cs[i];
    }


    res.Cs[res.len] = '\0';
    return res;
}
MyStr& MyStr::operator+=(const char ch) {  
    this->push_back(ch);  
    return *this;  
}
ostream& operator<<(ostream& os, const MyStr& str) {
    for (int i = 0; i < str.len; i++) {
        os << str.Cs[i];
    }
    return os;
}
MyStr::~MyStr() {
    delete[] Cs;
}
MyStr operator+(const MyStr& str1, const MyStr& str2) {
    return str1.concat(str2);
}
istream& operator>>(istream& is, MyStr& str) {
    char temp[1024];
    is.getline(temp, 1024, ',');
    str = MyStr(temp);
    return is;
}


const char* MyStr::fetchstr() const {
    return Cs;
}

void MyStr::pop_back() {
    if (len > 0) {
        Cs[--len] = '\0';
    }
}


void MyStr::push_back(char ch) {
    if (len + 1 >= cap) {
        cap = len + 10;
        char* newCs = new char[cap];
        for (int i = 0; i < len; ++i) { newCs[i] = Cs[i]; }
        delete[] Cs;
        Cs = newCs;
    }
    Cs[len++] = ch;
    Cs[len] = '\0';
}

bool MyStr::empty() const {
    if (len == 0) {
        return true;
    }
    else {
        return false;
    }
}









MyStrStream::MyStrStream() {}

MyStrStream& MyStrStream::operator<<(int num) {
    MyStr temp(num);
    buffer.append(temp);
    return *this;
}

MyStrStream& MyStrStream::operator<<(char ch) {
    MyStr temp(ch, 1);
    buffer.append(temp);
    return *this;
}

MyStrStream& MyStrStream::operator<<(const char* str) {
    MyStr temp(str);
    buffer.append(temp);
    return *this;
}

MyStrStream& MyStrStream::operator<<(const MyStr& str) {
    buffer.append(str);
    return *this;
}

MyStr MyStrStream::str() const {
    return buffer;
}

void MyStrStream::clear() {
    buffer.clear();
}