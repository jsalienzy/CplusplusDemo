// testStdString.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <string>

int main()
{
	std::string str1 = "hello world";
	std::string str2 = str1;
	std::string str3 = str2;
	std::string str4;
	const char *temp = str4.c_str();
	printf("�ڴ湲��:\n");
	printf("\tstr1 �ĵ�ַ: %x\n", (unsigned int)str1.c_str());
	printf("\tstr2 �ĵ�ַ: %x\n", (unsigned int)str2.c_str());
	printf("\tstr3 �ĵ�ַ: %x\n", (unsigned int)str3.c_str());
	system("pause");
    return 0;
}

