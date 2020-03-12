#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
int calcuPation(int* vparray, int vn)
{
	if (vn < 2) return 0;
	int key = *vparray;
	int leftBord = 0;
	for (int i = 1; i < vn; ++i)
	{
		if (vparray[i] <= key)
		{
			leftBord++;
			if (leftBord != i)
				std::swap(vparray[leftBord], vparray[i]);
		}
	}
	if (leftBord > 0)
		std::swap(vparray[0], vparray[leftBord]);
	return leftBord;
}

void quickSort(int* vparray, unsigned int vn)
{
	if (vn > 1)
	{
		int part = calcuPation(vparray, vn);
		quickSort(vparray, part);
		quickSort(vparray + part + 1, vn - part -1);
	}
}

int main()
{
	int a[] = { 3, 0, 8,7, 2,-1 };
	quickSort(a, sizeof(a) / 4);
	//system("pause");
	return 0;
}