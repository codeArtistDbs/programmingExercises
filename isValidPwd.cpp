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
����֪���������ʱ��ʹ��������ʽ
while (std::cin.getline(pwd, sizeof(pwd)))
��
while (std::cin >> pwd)
*/

/*
��Ŀ����
����Ҫ��:
1.���ȳ���8λ
2.������Сд��ĸ.����.��������,����������������
3.��������ͬ���ȳ�2���Ӵ��ظ�
˵��:���ȳ���2���Ӵ�
��������:
һ�����鳤�ȳ���2���ӷ�����ÿ��ռһ��

�������:
�������Ҫ�������OK���������NG

ʾ��1
����
����
021Abc9000
021Abc9Abc1
021ABC9000
021$bc9000
���
����
OK
NG
NG
OK
*/