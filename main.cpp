#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <unordered_map>
//https://leetcode-cn.com/problems/maximum-profit-in-job-scheduling/

using namespace std;
class Solution {
public:
	int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
		int n = startTime.size();
		std::vector<int> ids(n);
		for (int i = 0; i < n; ++i) ids[i] = i;
		std::sort(ids.begin(), ids.end(), [&](int a, int b) {return startTime[a] < startTime[b]; });
		std::sort(startTime.begin(), startTime.end());


		std::vector<int> moneyList(n);
		_sortByKey(endTime, ids, moneyList);
		_sortByKey(profit, ids, moneyList);
		moneyList = profit;
		for (int i = n - 2; i >= 0; --i)
		{
			int time = endTime[i];
			int& money = moneyList[i];
			for (int k = i + 1; k < n; ++k)
			{
				if (startTime[k] >= time)
				{
					money += moneyList[k];
					break;
				}
			}
			if (money < moneyList[i + 1])
				money = moneyList[i + 1];
		}

		return moneyList.front();
	}
private: 
	void _sortByKey(vector<int>& vdata, vector<int>& vkey, vector<int>& vbuffer)
	{
		for (int i = 0; i < vkey.size(); ++i)
		{
			vbuffer[i] = vdata[vkey[i]];
		}
		vdata = vbuffer;
	}
};
