#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>

//https://www.nowcoder.com/practice/abc3fe2ce8e146608e868a70efebf62e?tpId=13&tqId=11154&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking

class Solution {
public:
	bool Find(int vdst, const std::vector<std::vector<int> >& v2Darray)
	{
		if (v2Darray.empty() || v2Darray.front().empty())
			return false;

		auto pBackSmaller = std::lower_bound(v2Darray.cbegin(), v2Darray.cend(), vdst, [](const std::vector<int>& j, int v) {return j.back() < v; });
		if (pBackSmaller == v2Darray.cend())return false;
		if (pBackSmaller->back() == vdst) return true;

		auto pFrontBigger = std::upper_bound(pBackSmaller, v2Darray.cend(), vdst, [](int v, const std::vector<int>& j) {return v < j.front(); });

		while (pBackSmaller != pFrontBigger)
		{
			if (std::binary_search(pBackSmaller->cbegin(), pBackSmaller->cend(), vdst))
				return true;
			pBackSmaller++;
		}
		return false;
	}
};
