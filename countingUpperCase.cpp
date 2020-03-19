#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
// #include "FileFunction.h"
template<typename T>
inline void splitStringAndConvert(std::string vSrc, std::vector<T>& voDst, const char vSeparator, char vIgnoring = ' ', bool vClearBeforAppanding = true)
{
	if (vClearBeforAppanding) voDst.resize(0);
	std::stringstream SS(vSrc);
	T temp;
	char sep;
	while (SS >> temp)
	{
		voDst.push_back(temp);
		SS >> sep;
	}
}

bool isValidChar(const std::string& v, std::vector<int>& vo)
{
	for (char c : v)
	{
		if (false == (c == '.' || (c >= '0' && c <= '9')))
			return false;
	}
	if (v.front() == '.' || v.back() == '.') return false;
	if (std::count(v.cbegin(), v.cend(), '.') != 3) return false;
	if (v.find("..") < v.size()) return false;
	splitStringAndConvert(v, vo, '.');
	bool flag = (vo.size() == 4);
	for (int i = 0; i < 4; ++i)
		flag &= (vo[i] < 256);
	return flag;
}

void fun()
{
	std::string strMsk, strIp0, strIp1;
	std::vector<int> msk, ip0, ip1;
	while (std::cin >> strMsk >> strIp0 >> strIp1)
	{
		int flag = 0;
		if (!isValidChar(strMsk, msk) || !isValidChar(strIp1, ip1) || !isValidChar(strIp0, ip0))
			flag = 1;
		else
		{
			bool flagSame = true;
			for (int i = 0; i < 4; ++i)
			{
				flagSame &= ((ip0[i] & msk[i]) == (ip1[i] & msk[i]));
			}
			if (!flagSame) flag = 2;

		}
		std::cout << flag << std::endl;
	}
}

int main()
{
	fun();
	//system("pause");
	return 0;
}

/*
题目描述
子网掩码是用来判断任意两台计算机的IP地址是否属于同一子网络的根据。
子网掩码与IP地址结构相同，是32位二进制数，其中网络号部分全为“1”和主机号部分全为“0”。利用子网掩码可以判断两台主机是否中同一子网中。若两台主机的IP地址分别与它们的子网掩码相“与”后的结果相同，则说明这两台主机在同一子网中。

示例：
I P 地址　 192.168.0.1
子网掩码　 255.255.255.0

转化为二进制进行运算：

I P 地址　11010000.10101000.00000000.00000001
子网掩码　11111111.11111111.11111111.00000000

AND运算
　　　　11000000.10101000.00000000.00000000

	转化为十进制后为：
	　　　　192.168.0.0



		I P 地址　 192.168.0.254
		子网掩码　 255.255.255.0


		转化为二进制进行运算：

		I P 地址　11010000.10101000.00000000.11111110
		子网掩码　11111111.11111111.11111111.00000000

		AND运算
		　　　　　11000000.10101000.00000000.00000000

			 转化为十进制后为：
			 　　　　　192.168.0.0

				  通过以上对两台计算机IP地址与子网掩码的AND运算后，我们可以看到它运算结果是一样的。均为192.168.0.0，所以这二台计算机可视为是同一子网络。

				  /*
				  * 功能: 判断两台计算机IP地址是同一子网络。
				  * 输入参数：    String Mask: 子网掩码，格式：“255.255.255.0”；
				  *               String ip1: 计算机1的IP地址，格式：“192.168.0.254”；
				  *               String ip2: 计算机2的IP地址，格式：“192.168.0.1”；
				  *

				  * 返回值：      0：IP1与IP2属于同一子网络；     1：IP地址或子网掩码格式非法；    2：IP1与IP2不属于同一子网络
				  */
public int checkNetSegment(String mask, String ip1, String ip2)
{
	/*在这里实现功能*/
	return 0;
}



输入描述:
输入子网掩码、两个ip地址

输出描述 :
得到计算结果

示例1
输入
复制
255.255.255.0 192.168.224.256 192.168.10.4
输出
复制
1

*/