// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
const int kDigitNumber = 8;
void printLast8Digit(int number)
{
	long long sum = 0;
	long long a = 0;
	long long b = 1;
	sum = b;
	int count = 1;
	while (count < number)
	{
		std::string b_str = std::to_string(b);
		if (b_str.size() >= kDigitNumber)
		{
			b_str = b_str.substr(b_str.size() - kDigitNumber);
		}
		long long temp = std::stoi(b_str);
		b = temp;
		b = a + b;
		sum = sum + b;
		a = temp;
		++count;
	}
	std::string sum_str = std::to_string(sum);
	if (sum_str.size() > kDigitNumber)
	{
		sum_str = sum_str.substr(sum_str.size() - kDigitNumber);
	}
	else
	{
		int temp = sum_str.size();
		for (int i = 0; i < (kDigitNumber - temp); ++i)
		{
			sum_str.insert(0, "0");
		}
	}
	std::cout << sum_str << std::endl;
}

int main()
{
	printLast8Digit(10000);
	
	system("pause");
    return 0;
}

