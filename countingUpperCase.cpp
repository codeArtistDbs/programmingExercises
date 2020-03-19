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
��Ŀ����
���������������ж�������̨�������IP��ַ�Ƿ�����ͬһ������ĸ��ݡ�
����������IP��ַ�ṹ��ͬ����32λ������������������Ų���ȫΪ��1���������Ų���ȫΪ��0��������������������ж���̨�����Ƿ���ͬһ�����С�����̨������IP��ַ�ֱ������ǵ����������ࡰ�롱��Ľ����ͬ����˵������̨������ͬһ�����С�

ʾ����
I P ��ַ�� 192.168.0.1
�������롡 255.255.255.0

ת��Ϊ�����ƽ������㣺

I P ��ַ��11010000.10101000.00000000.00000001
�������롡11111111.11111111.11111111.00000000

AND����
��������11000000.10101000.00000000.00000000

	ת��Ϊʮ���ƺ�Ϊ��
	��������192.168.0.0



		I P ��ַ�� 192.168.0.254
		�������롡 255.255.255.0


		ת��Ϊ�����ƽ������㣺

		I P ��ַ��11010000.10101000.00000000.11111110
		�������롡11111111.11111111.11111111.00000000

		AND����
		����������11000000.10101000.00000000.00000000

			 ת��Ϊʮ���ƺ�Ϊ��
			 ����������192.168.0.0

				  ͨ�����϶���̨�����IP��ַ�����������AND��������ǿ��Կ�������������һ���ġ���Ϊ192.168.0.0���������̨���������Ϊ��ͬһ�����硣

				  /*
				  * ����: �ж���̨�����IP��ַ��ͬһ�����硣
				  * ���������    String Mask: �������룬��ʽ����255.255.255.0����
				  *               String ip1: �����1��IP��ַ����ʽ����192.168.0.254����
				  *               String ip2: �����2��IP��ַ����ʽ����192.168.0.1����
				  *

				  * ����ֵ��      0��IP1��IP2����ͬһ�����磻     1��IP��ַ�����������ʽ�Ƿ���    2��IP1��IP2������ͬһ������
				  */
public int checkNetSegment(String mask, String ip1, String ip2)
{
	/*������ʵ�ֹ���*/
	return 0;
}



��������:
�����������롢����ip��ַ

������� :
�õ�������

ʾ��1
����
����
255.255.255.0 192.168.224.256 192.168.10.4
���
����
1

*/