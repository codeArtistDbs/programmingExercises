#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <numeric>

bool isValid(const char* pwd, int n)
{
	if (n < 9) return false;

	char flags[4] = { 0 };
	for (int i = 0; i < n; ++i)
	{
		char c = pwd[i];
		if (c <= 'Z' && c >= 'A')
			flags[0] = 1;
		else if (c <= 'z' && c >= 'a')
			flags[1] = 1;
		else if (c <= '9' && c >= '0')
			flags[2] = 1;
		else flags[3] = 1;
	}
	if (std::accumulate(flags, flags + 4, 0) < 3)
		return false;

	for (int i = 0; i < n; ++i)
	{
		std::string src(pwd + i, 3);
		for (int k=i+3; k<n; ++k)
		{
			std::string dst(pwd + k, 3);
			if (dst == src)
				return false;
		}
	}
	return true;
}

int main()
{
	char pwd[4096];
	while (std::cin.getline(pwd, sizeof(pwd)))
	{
		if (isValid(pwd, strlen(pwd)))
			std::cout << "OK";
		else std::cout << "NG";
		std::cout << std::endl;
	};

	//system("pause");
	return 0;
}

/*
当不知道输入个数时，使用如下形式
while (std::cin.getline(pwd, sizeof(pwd)))
或
while (std::cin >> pwd)
*/

/*
题目描述
密码要求:
1.长度超过8位
2.包括大小写字母.数字.其它符号,以上四种至少三种
3.不能有相同长度超2的子串重复
说明:长度超过2的子串
输入描述:
一组或多组长度超过2的子符串。每组占一行

输出描述:
如果符合要求输出：OK，否则输出NG

示例1
输入
复制
021Abc9000
021Abc9Abc1
021ABC9000
021$bc9000
输出
复制
OK
NG
NG
OK
*/