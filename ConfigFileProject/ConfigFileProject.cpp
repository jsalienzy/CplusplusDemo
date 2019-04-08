// ConfigFileProject.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "config_file.h"
//#include "gtest/gtest.h"

//int Sum(int a, int b)
//{
//	return a + b;
//}
//
//TEST(SumFunctionTest, GetSumValueNegative)
//{
//	EXPECT_EQ(Sum(-1, -2), -3);
//	EXPECT_EQ(Sum(-2, -3), -5);
//	EXPECT_EQ(Sum(-3, -2), -5);
//}
//
//TEST(SumFunctionTest, GetSumValueTrivial)
//{
//	EXPECT_EQ(Sum(0, 0), 0);
//	EXPECT_EQ(Sum(1, 4), 5);
//	EXPECT_EQ(Sum(-3, 2), -1);
//}
//
//TEST(SumFunctionTest, GetSumValuePositive)
//{
//	EXPECT_EQ(Sum(3, 2), 5);
//	EXPECT_EQ(Sum(100002, 3), 100005);
//	EXPECT_EQ(Sum(3, 32), 35);
//}


int main()
{
	js::ConfigFile config_file;
	config_file.LoadFile("SynSmbDrv.ini");
	config_file.SaveFileAs("js.ini");
	system("pause");
    return 0;
}

