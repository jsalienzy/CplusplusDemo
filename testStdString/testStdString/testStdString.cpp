// testStdString.cpp : 定义控制台应用程序的入口点。
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
	printf("内存共享:\n");
	printf("\tstr1 的地址: %x\n", (unsigned int)str1.c_str());
	printf("\tstr2 的地址: %x\n", (unsigned int)str2.c_str());
	printf("\tstr3 的地址: %x\n", (unsigned int)str3.c_str());
	system("pause");
    return 0;
}

