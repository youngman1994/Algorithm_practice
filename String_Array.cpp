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
//第三个例子：求一个数组中连续数字的最大长度
int MaxStrLen(int* arr,int n);//要加入数组的长度
//第四个例子：reverse，将字符串中每个单词反转
void StrReverse(const string&);

int main()
{
	string SReverse = "I have 36 books,40 pens 2.";
	StrReverse(SReverse);
	int array[] = { 31,6,32,1,3,2 };
	int nums = MaxStrLen(array,7);
	cout << "最大连续长度为：" << nums << endl;
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
int MaxStrLen(int* arr,int n) {
	vector<int> temp(arr,arr+n);
	sort(temp.begin(), temp.end());//这里通过迭代器使得容器与算法进行沟通，排序
	vector<int>::iterator it = temp.begin();
	it++;//后一个数与前一个数比较
	int num = 1, max_num = 0;
	for (; it != temp.end(); it++) {
		if ((*it)-1 == *(it - 1))
			num++;
		else {
			max_num = (max_num > num) ? max_num : num;
			num = 1;
		}
	}
	return max_num;
}
void StrReverse(const string& s) {
	string str(s);//因为输入不可变，所以深拷贝一个对象
	string::iterator it = str.begin();
	for (int i = 0; it != str.end();i++, it++) {
		if (isdigit(*it) != 0)
			i = 0;
		else if ((*it)==' ' || (*it) == ',' || (*it) == '.') {//string中的空格怎么表示，
			if (i > 1) {
					string temp(it - i, it);
					auto it1 = temp.begin();
					for (int j = 1; it1 != temp.end() && j <= i; it1++, j++) {
						*(it - j) = *it1;
				}
			}
			i = 0;
		}
	}
	for (auto elem : str)//如何判断纯数字，isdigit()不为0就是数字,同理isalpha()判断字母，不为0就是字母。
		cout << elem;
	cout << endl;

}
/*String相关问题的一些处理技巧
通常，纯粹字符串操作难度不大，但是实现起来可能比较麻烦，edge case比较多。例如把字符变成数字，把数字变成字符等等。
*/
