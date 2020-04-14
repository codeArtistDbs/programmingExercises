#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <string>
#include <string.h>

int getWordLen(char* vp)
{
	char* p = vp;
	while (*p >= 'A' && *p <= 'Z' || *p >= 'a' && *p <= 'z')
		p++;

	return p - vp;
}

char* getNext(char* p)
{
	while (*p)
	{
		if (*p >= 'A' && *p <= 'Z' || *p >= 'a' && *p <= 'z')
			break;
		p++;
	}
	return p;
}

int main()
{
	std::vector<char> cs(1 << 22);
	while (std::cin.getline(cs.data(), cs.size()))
	{
		int n = strlen(cs.data());
		std::reverse(cs.begin(), cs.begin() + n);
		char word[21];
		char* p0 = cs.data(), *p1 = p0 + n, *pend = p0;
		while (p0 < p1)
		{
			char* p = getNext(p0);
			if (p >= p1) break;
			int m = getWordLen(p);
			memcpy(word, p, m);
			std::reverse(word, word + m);
			memcpy(pend, word, m);
			pend += m;
			*pend = ' ';
			p0 = p + m + 1;
			pend++;
		}
		pend--;
		*pend = 0;

		std::cout << cs.data() << std::endl;
	}



	return 0;
}

/*
//https://www.nowcoder.com/practice/81544a4989df4109b33c2d65037c5836?tpId=37&tqId=21254&tPage=1&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking
//字符串倒排：注意排查细节getWordLen容易出错
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <string>
#include <string.h>

int getWordLen(char* vp)
{
char* p = vp;
while(*p>='A' && *p<='Z' || *p>='a' && *p<='z')
p++;

return p - vp;
}

char* getNext(char* p)
{
while(*p)
{   if (*p>='A' && *p<='Z' || *p>='a' && *p<='z')
break;
p++;
}
return p;
}

int main()
{
std::vector<char> cs(1<<22);
while(std::cin.getline(cs.data(), cs.size()))
{
int n = strlen(cs.data());
std::reverse(cs.begin(), cs.begin()+n);
char word[21];
char* p0 = cs.data(), *p1=p0+n,*pend=p0;
while(p0<p1)
{
char* p = getNext(p0);
if (p>=p1) break;
int m = getWordLen(p);
memcpy(word, p, m);
std::reverse(word, word+m);
memcpy(pend, word, m);
pend += m;
*pend = ' ';
p0 = p+m+1;
pend++;
}
pend--;
*pend = 0;

std::cout << cs.data() << std::endl;
}



return 0;
}
*/

/*
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <string>
#include <string.h>
//01背包为题的变种
//https://www.nowcoder.com/practice/f9c6f980eeec43ef85be20755ddbeaf4?tpId=37&tqId=21239&tPage=1&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking
struct SProduct
{
std::vector<std::pair<int,int>> ppws;
void setValue(int p, int w){ppws.front().first=p; ppws.front().second=p*w;}
void appandValue(int p, int w){ppws.emplace_back(p, p*w);}
int getSum()
{
int s = 0;
s = std::accumulate(ppws.cbegin(), ppws.cend(), s, [](int v, const std::pair<int,int>& a){return a.second+v;});
return s;
}
int getPrice()
{
int p = 0;
p = std::accumulate(ppws.cbegin(), ppws.cend(), p, [](int v, const std::pair<int,int>& a){return a.first+v;});
return p;
}
SProduct(){ppws.resize(1);ppws.front().first=0; ppws.front().second=0;}
SProduct(int p, int w){ppws.resize(1);ppws.front().first=p; ppws.front().second=p*w;}
};

int getHistory(std::vector<std::pair<int, int>>& vh, int money)
{
if (money>= vh.front().first)
return vh.front().second;
auto p0 = std::lower_bound(vh.cbegin(), vh.cend(), money,  [=](const std::pair<int, int>& h, int m){return h.first>m;});
if (p0==vh.cend()) return -1;
if (p0->first==money || (p0->second==(p0-1)->second))
return p0->second;
return -1;
}

void setHistory(std::vector<std::pair<int, int>>& vh, int money, int vmax)
{
auto p0 = std::lower_bound(vh.begin(), vh.end(), money, [=](std::pair<int, int>& h, int m){return h.first>m;});
if (p0-2>=vh.begin() && (p0-1)->second==vmax && (p0-2)->second==vmax)
(p0-1)->first=money;
else if (p0+2<vh.end() && (p0+1)->second==vmax && (p0+2)->second==vmax)
(p0+1)->first=money;
else  vh.insert(p0, std::make_pair(money, vmax));
}

std::vector<std::vector<std::pair<int, int>>> g_sum;
int getMax(const std::vector<SProduct>& vps, int n, int b0, int b1)
{
if (b0>=vps.size()) return 0;

auto& h = g_sum[b0];
int s0 = (b1==0? getHistory(h, n): -1);
if (s0>=0) return s0;

const auto& ppws = vps[b0].ppws;
bool nflag = (ppws.size()==1 || ppws.size()==b1+1 || b1==0);
int nb0=b0+nflag, nb1 = (nflag? 0 : b1+1);
s0 = getMax(vps, n,nb0, nb1);


const auto& ppw = ppws[b1];
nflag = (ppws.size()==1 || ppws.size()==b1+1);
nb0=b0+nflag, nb1 = (nflag? 0 : b1+1);
int s1 = (ppw.first>n?  s0 :  ppw.second+getMax(vps, n-ppw.first,  nb0, nb1));
if (s1>s0) s0 = s1;
if (b1==0)
setHistory(h, n, s0);
return s0;
}

int main()
{
int N,m;
std::cin >> N >> m;

int p, w, id;
std::vector<SProduct> ps(m);
for (int i=0; i<m; ++i)
{
std::cin >> p >> w >> id;
if(id==0) ps[i].setValue(p,w);
else ps[id-1].appandValue(p,w);
}
auto pend = std::remove_if(ps.begin(),ps.end(), [](const SProduct& p){return p.ppws.front().first==0;} );
ps.resize(pend-ps.begin());

m = ps.size();
g_sum.resize(m);
for (int i=m-1; i>=0; --i)
{
auto& s = g_sum[i];
s.emplace_back(ps[i].getPrice(), ps[i].getSum());
if (i<m-1)
{
auto& la = g_sum[i+1].front();
s.front().first += la.first;
s.front().second+= la.second;
}
}

N = getMax(ps, N, 0, 0);

std::cout << N << std::endl;
return 0;
}

*/

/*
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <string>
#include <string.h>
struct SProduct
{
int price, pw;
std::vector<SProduct> vice;
void setValue(int p, int w){price=p; pw=p*w;}
SProduct():price(0), pw(0){}
SProduct(int p, int w): price(p), pw(p*w){vice.resize(0);}
};
//https://www.nowcoder.com/practice/f9c6f980eeec43ef85be20755ddbeaf4?tpId=37&tqId=21239&tPage=1&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking
//动态规划：

int getMax(const std::vector<SProduct>& vps, int n, int b0, int b1)
{
if (b0>=vps.size()) return 0;

int s0 = getMax(vps, n, b0+1 , 0);

const auto& p0 = vps[b0];
int p0s = p0.vice.size();
bool mainFull = (p0s==0 || p0s==b1);
int nb0=b0+mainFull, nb1 = mainFull?0:b1+1;
const SProduct& p = ((b1==0)?p0:p0.vice[b1-1]);
int s1 = (p.price>n? getMax(vps, n,  nb0, nb1) :  p.pw+getMax(vps, n-p.price,  nb0, nb1));
if (s1>s0) s0 = s1;
return s0;
}

int main()
{
int N,m;
std::cin >> N >> m;

std::vector<SProduct> ps(m);
int p, w, id;
for (int i=0; i<m; ++i)
{
std::cin >> p >> w >> id;
if(id==0) ps[i].setValue(p,w);
else ps[id-1].vice.emplace_back(p,w);
}

N = getMax(ps, N, 0, 0);

std::cout << N << std::endl;
return 0;
}

*/

/*
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <string>
#include <string.h>
//数字颠倒https://www.nowcoder.com/practice/ae809795fca34687a48b172186e3dafe?tpId=37&tqId=21234&tPage=1&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking
//可见用cin cout 输入输出不能判断数据类型
int main()
{
int n;
std::cin >> n;
while(n)
{
std::cout << n%10;
n /=10;
}
std::cout << std::endl;
return 0;
}

*/

/*
#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>

//https://www.nowcoder.com/practice/48b3cb4e3c694d9da5526e6255bb73c3?tpId=37&tqId=21236&tPage=1&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking
//使用<string.h> 比 <string>可调用更多函数

char* getWordEnd(char* v)
{
while(*++v!=' ' && *v);
return v;
}

int main()
{
std::vector<char> sen(1<<20);
std::cin.getline(sen.data(), sen.size());
int n = strlen(sen.data());
std::reverse(sen.begin(), sen.begin()+n);

for (auto p0=sen.data(), p1=p0+n; p0<p1;)
{
char* p = getWordEnd(p0);
std::reverse(p0, p);
p0=p+1;
}

std::cout << sen.data() << std::endl;
return 0;
}


*/


/*
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
//https://www.nowcoder.com/practice/5af18ba2eb45443aa91a11e848aa6723?tpId=37&tqId=21237&tPage=1&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking
//机考可以先考虑简单大部分情况，先易后难，先及格再满分
int main()
{
int n;
std::cin >> n;
std::vector<std::string> ss(n);
for (int i = 0; i < n; ++i)
{
std::cin >> ss[i];
}
std::sort(ss.begin(), ss.end());

for (int i = 0; i < n; ++i)
std::cout << ss[i] << std::endl;
return 0;
}

*/


/*
//https://www.nowcoder.com/practice/2baa6aba39214d6ea91a2e03dff3fbeb?tpId=37&tqId=21242&tPage=1&rp=&ru=/ta/huawei&qru=/ta/huawei/question-ranking
//理解题意，首先向简单方向想
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

struct SError
{
std::string fileName;
int rowNO,count;
SError(std::string vfileName, int vrowNO): rowNO(vrowNO), count(1)
{
if (vfileName.size()>16)
vfileName = vfileName.substr(vfileName.size()-16);
int offset = vfileName.rfind('\\');
if (offset>=0 && offset<vfileName.size())
vfileName = vfileName.substr(offset+1);
fileName = vfileName;
}
bool operator ==(const SError& verr)
{
return verr.fileName ==  fileName && verr.rowNO==rowNO;
}
};

int main()
{
int rowNO;
std::string file;
std::vector<SError> errs;
while(std::cin >> file >> rowNO)
{
bool sameFlag = false;
SError err(file, rowNO);
for (auto& e : errs)
{
if (e==err)
{
e.count++;
sameFlag = true;
break;
}
}
if (!sameFlag)errs.push_back(err);

}

int i=0;
if (errs.size()>8)
i=errs.size()-8;
for (;i<errs.size(); ++i)
{
const auto& e = errs[i];
std::cout << e.fileName << " " << e.rowNO  << " "<< e.count << std::endl;
}
return 0;
}
*/
