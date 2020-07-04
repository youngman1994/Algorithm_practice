// String_Array.cpp : �������̨Ӧ�ó������ڵ㡣
//
#pragma  warning (disable:4996) 
#include "stdafx.h"
#include<iostream>
#include<string>
#include<algorithm>
#include<map>
#include<bitset>
using namespace std;
//��һ������ַ���
int strStr(string source, string target);
const char* strStr2_0(const char* s,const char* t);
//�ڶ����ӣ��ж��ַ����������ַ��Ƿ��Ψһ��
//������hash table ��bitset
void JudegeStr();

int main()
{
	string A, B;
	A = "sadgads";
	B = "ds";
	int r = strStr(A,B);
	cout << r << endl;
	cout << "A�Ĵ�С��" << A.size() << " "
		<< "A�ĳ��ȣ�" << A.length() << endl
		<< "B�Ĵ�С��" << B.size() << " "
		<< "BB�ĳ��ȣ�" << B.length() << endl;//string��size()��length()����û�в��
	JudegeStr();
	const char* a = "abcd";
	const char* b = "";
	const char* result = strStr2_0(a, b);
	cout << "result=" << result << endl;
    return 0;
}
//��char*ʵ��
const char* strStr2_0(const char* s, const char* t) {
	if (!*t) return s;
	const char* p1 = s;
	while (*p1) {
		const char* p1Begin = p1, *p2 = t;//��ʼ��λ��
		while (*p1 && *p2 && *p1 == *p2) {
			p1++;
			p2++;
		}
		if (!*p2) return p1Begin;
		p1 = p1Begin + 1;
	}
	return NULL;
}

//��stringûʵ��,�ڶ���ʵ��
int strStr(string source, string target) {
	if (source.size() < target.size() || target.size() == 0)
		return -1;
	int length = source.size() - target.size();//�ƶ��ĳ���
	string::iterator it = source.begin();
	int i,j;
	for (i = 0; i <= length; i++, it++) {
		string::iterator temp = it;
		for (j = 0; j < target.size(); j++, temp++) {//ע�����������ʱ��j��temp��Ҫ��һ
			if (*temp != target[j]) break;
		}
		if (j>1 && *(temp-1) == target[j-1] && j == target.size())
				return 1;
	}
	return -1;
}

void JudegeStr(){
	char* str = new char[20];
	cin.get(str, 20).get();//�����ַ���
	map<char, int> hashTable;//�ù�ϣ��ʵ��
	bitset<256> *BitSet = new bitset<256>;//��λ��ʵ��
	BitSet->reset();
	for (int i = 0; i < strlen(str); i++) {
		hashTable[str[i]] += 1;
		if ((*BitSet)[int(str[i])]==0)//bitset������û��*���أ�������ֱ���õ���������������������������[]
			(*BitSet)[int(str[i])] = 1;
	}
	map<char, int>::iterator it = hashTable.begin();//���������е��������Ѿ��ź���
	for (; it != hashTable.end(); it++) {
		cout << it->first << " " << it->second << endl;
	}
	for (int i = 0; i < 256; i++) {
		if ((*BitSet)[i]==1)
			cout << char(i) << endl;
	}

}