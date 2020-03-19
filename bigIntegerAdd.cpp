#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>

//https://www.nowcoder.com/practice/5821836e0ec140c1aa29510fd05f45fc?tpId=37&tqId=21301&tPage=5&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking
char popAndCalcu(std::string& v)
{
	char c = 0;
	if (v.size())
	{
		c = v.back()-'0';
		v.pop_back();
	}
	return c;
}

void fun()
{
	char a, b, c;
	std::string A,B;
	std::vector<char> C;
	while (std::cin >> A>>B)
	{
		c = 0;
		C.resize(0);
		while (A.size() || B.size())
		{
			a = popAndCalcu(A);
			b = popAndCalcu(B);
			c += a + b;
			C.push_back('0' + c % 10);
			if (c > 9)c = 1;
			else c = 0;
		}
		if (c) C.push_back('1');
		std::reverse(C.begin(), C.end());
		C.push_back(0);
		std::cout << C.data() << std::endl;
	}
}

int main()
{
	fun();
	//system("pause");
	return 0;
}

