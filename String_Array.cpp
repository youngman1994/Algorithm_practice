// String_Array.cpp : 定义控制台应用程序的入口点。
//
#pragma  warning (disable:4996) 
#include "stdafx.h"
#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<bitset>
using namespace std;
//第一题查找字符串
int strStr(string source, string target);
const char* strStr2_0(const char* s,const char* t);
//第二例子：判断字符串中所有字符是否的唯一的
//考虑用hash table 和bitset
void JudegeStr();

int main()
{
	string A, B;
	A = "sadgads";
	B = "ds";
	int r = strStr(A,B);
	cout << r << endl;
	cout << "A的大小：" << A.size() << " "
		<< "A的长度：" << A.length() << endl
		<< "B的大小：" << B.size() << " "
		<< "BB的长度：" << B.length() << endl;//string的size()和length()方法没有差别
	JudegeStr();
	const char* a = "abcd";
	const char* b = "";
	const char* result = strStr2_0(a, b);
	cout << "result=" << result << endl;
    return 0;
}
//用char*实现
const char* strStr2_0(const char* s, const char* t) {
	if (!*t) return s;
	const char* p1 = s;
	while (*p1) {
		const char* p1Begin = p1, *p2 = t;//初始化位置
		while (*p1 && *p2 && *p1 == *p2) {
			p1++;
			p2++;
		}
		if (!*p2) return p1Begin;
		p1 = p1Begin + 1;
	}
	return NULL;
}

//用string没实现,第二次实现
int strStr(string source, string target) {
	if (source.size() < target.size() || target.size() == 0)
		return -1;
	int length = source.size() - target.size();//移动的长度
	string::iterator it = source.begin();
	int i,j;
	for (i = 0; i <= length; i++, it++) {
		string::iterator temp = it;
		for (j = 0; j < target.size(); j++, temp++) {//注意这里结束的时候j和temp还要加一
			if (*temp != target[j]) break;
		}
		if (j>1 && *(temp-1) == target[j-1] && j == target.size())
				return 1;
	}
	return -1;
}

void JudegeStr(){
	char* str = new char[20];
	cin.get(str, 20).get();//传入字符串
	map<char, int> hashTable;//用哈希表实现统计一个元素集中元素出现的次数
	bitset<256> *BitSet = new bitset<256>;//用位集实现
	BitSet->reset();
	for (int i = 0; i < strlen(str); i++) {
		hashTable[str[i]] += 1;
		if ((*BitSet)[int(str[i])]==0)//bitset迭代器没有*重载，即不能直接用迭代器索引，可以用引用重载了[]
			(*BitSet)[int(str[i])] = 1;
	}
	map<char, int>::iterator it = hashTable.begin();//关联容器有迭代器，已经排好序
	for (; it != hashTable.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
	for (int i = 0; i < 256; i++) {
		if ((*BitSet)[i]==1)
			cout << char(i) << endl;
	}

}
