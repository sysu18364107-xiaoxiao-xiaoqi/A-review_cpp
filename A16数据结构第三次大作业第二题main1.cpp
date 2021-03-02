#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<stdio.h>
#include<cstring>
#include<malloc.h>
#include <iostream.h> 

using namespace std;

class Str {
public:
	Str(); //默认构造函数
	Str(const char* s); //由字符串常量构造的构造函数 ， 如 Str s("aaa") ;
	Str(const Str& s); //拷贝构造函数
	~Str(); //析构函数

	int len()const; //返回字符串长度，即包含了几个有效字符，不包括末尾'\0' .
	bool empty()const; //返回是否为空
	void append(char ch); //向字符串末尾添加字符 , 如 s = "aaa"时 ，s.append('b') 后 , s = "aaab" ; 
	void clear(); // 清空该字符串
	Str substr(int position, int count) const; //返回从pos位置开始，连续count个字符的子串。即 data[pos , pos+count) ，左闭右开区间。

	Str operator+(const Str& s)const; //重载+号运算符, 使得 "aa" + "b" + "cd" = "aabcd" ;
	bool operator==(const Str& s)const; //重载==运算符，判断两个字符串是否相等。 如果s1.data="aba", s2.data="aba" , 那么s1==s2 ; 
	Str operator=(const Str& s); //重载'='赋值运算符,把字符串s的内容赋值给自己.
	char operator[](int index) const; //重载'[]'运算符，返回 data[index] ;

	void print()const {
		for (int i = 0; i < length; i++)
			cout << data[i];
		cout << endl;
	}
private:
	char* data;
	int length;
};

想要考研去北方看雪的日尧 16:56 : 53

Str::Str() {
	data = new char[10000];
	length = 0;//初始化data，同时将length置零
}
Str::Str(const char* s) {
	length = strlen(s);
	data = new char[length + 1];
	strcpy(data, s);
}

Str::Str(const Str& s) {
	length = s.length;
	data = new char[length + 1];
	strcpy(data, s.data);
}

Str::~Str() {
	if (data != NULL)
	{
		delete[]data;
		data = NULL;
		length = 0;
	}
}

int Str::len()const {
	return strlen(data);
}

bool Str::empty()const {
	return length == 0;
}

void Str::append(char ch) {
	if (!data) {
		length = 2;
		data = new char[length];
		data[length - 2] = ch, data[length - 1] = '\0';

	}
	else
	{
		char* tmp = new char[++length];
		strcpy(tmp, data);
		tmp[length - 2] = ch, tmp[length - 1] = '\0';
		delete[]data;
		data = tmp;
	}
}

void Str::clear() {
	delete[]data;
	data = NULL;
	length = 0;
}

Str Str::substr(int position, int count) const {
	if (position + count > length) count = length - position;
	char* tem;
	if (count > 10000) {
		tem = new char[count * 2];
	}
	else {
		tem = new char[10000];
	}
	memcpy(tem, data + position, count * sizeof(char));
	tem[count] = '\0';
	Str temsrt(tem);
	return temsrt;
}

想要考研去北方看雪的日尧 16:57 : 05

Str Str::operator+(const Str& s) const {
	int total = s.length + length;
	char* tem;
	if (total > 10000)
		tem = new char[total * 2];
	else tem = new char[10000];
	memcpy(tem, data, length * sizeof(char));
	memcpy(tem + length, s.data, s.length * sizeof(char));
	tem[total] = '\0';
	Str temstr(tem);
	return temstr;
}

Str Str::operator=(const Str& s) {
	if (s.length > 10000) {
		if (data)
			delete[]data;
		data = new char[s.length * 2];
	}
	length = s.length;
	memcpy(data, s.data, length * sizeof(char));
	data[length] = '\0';
	return *this;
}

bool  Str::operator==(const Str& s)const {
	if (length != s.length) return false;
	else {
		if (data != NULL && s.data != NULL)
			for (int i = 0; i < length; i++) {
				if (data[i] != s.data[i]) return false;
			}
		return true;
	}
}

char Str::operator[](int position)const {
	return data[position];
}

想要考研去北方看雪的日尧 16:57 : 12
int main() {
	int N;
	cin >> N;
	Str s;
	while (N--) {

		char c_str[100];
		scanf_s("%s", c_str);

		int pos, count;
		cin >> pos >> count;

		Str tmp(c_str);    //由字符数组构造一个对象 ， 调用 Str:: Str(const char* s) ;

		tmp.print();    //打印

		Str tmp2 = tmp.substr(pos, count);     //取一段子串
		tmp2.print();     //打印

		Str tmp3;
		for (int i = 0; i < count && i < tmp.len() - pos; i++)
			tmp3.append(tmp[i + pos]);       //在字符串后增添char 

		tmp3.print(); //打印
		cout << (tmp2 == tmp3) << endl;      //判断是否相等

		Str tmp4(tmp);  //拷贝构造函数

		tmp = s + tmp;   //字符串拼接

		s.clear();      //清空s

		for (int i = 0; i < tmp.len(); i++)
			s.append(tmp[i]);       //把tmp添加到s

		s.print();     //打印

		cout << (s == tmp4) << endl;    //判断是否相等

		tmp.clear();    //清空tmp 

		cout << tmp.empty() << endl;    //判断是否为空

		cout << endl;
		for (int i = 0; i < strlen(c_str); i++) {
			cout << c_str[i];
		}
	}
}

