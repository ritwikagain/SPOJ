#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include <limits.h>
//#include <stdint.h> // only for bcc32 compiler to include long long!

using namespace std;

/*
** The aim is to maintain the length of all rectangles formed in xd and the width in yd, so that
** we can pick the largest one from them and return their multiplication(area). Now we need to keep them sorted 
** to find one of them in O(log n) time. So we use multi-set. Why multi-set ? because there can be multiple rectangles
** whose length/width are same and we need to keep them all.
**
** xc and yc are just to keep the x and y cordinates sorted. Whenever we get a new vertical/horizontal line, we use xc/yc to find
** out which rectangle the line  is intersecting in xd/yd. Likewise we remove the rectangle, split it and insert the split sections
** in xd/yd.
**
** Basically we are maintaining four balanced BSTs at one go!
*/
int main ()
{
	int T;
	cin >> T;
	
	multiset<long long> xc, yc, xd, yd; // xc, yc can be used as ordered set as well.
	multiset<long long>:: iterator it;
	
	while (T--)
	{
		long long N, M, Q;
		cin >> N;
		cin >> M;
		cin >> Q;
		
		xc.clear();
		xd.clear();
		yc.clear();
		yd.clear();
		
		xc.insert(0);
		xc.insert(N);
		xd.insert(N);
		yc.insert(0);
		yc.insert(M);
		yd.insert(M);
		
		for (long long i = 0; i < Q; i++)
		{
			int which_axis;
			int coordinate;
			cin >> which_axis;
			cin >> coordinate;
			if (which_axis == 0)
			{
				if (xc.find(coordinate) == xc.end())
				{	
					xc.insert(coordinate);
					it = xc.find(coordinate);
					it++;
					long long high = *(it);
					advance(it, -2);   // advance() is used to increment/drcrement STL iterator for any random step, (it+x) won't work!
					long long low = *(it);
					
					it = xd.find(high - low);
					xd.erase(it);
					xd.insert(high - coordinate);
					xd.insert(coordinate - low);
				}
			}
			else
			{
				if (yc.find(coordinate) == yc.end())
				{
					yc.insert(coordinate);
					it = yc.find(coordinate);
					it++;
					long long high = *(it);
					advance(it, -2);
					long long low = *(it);
					
					it = yd.find(high - low);
					yd.erase(it);
					yd.insert(high - coordinate);
					yd.insert(coordinate - low);					
				}
			}
			
			it = xd.end();
			it--;
			long long max_xpiece = *(it);
			it = yd.end();
			it--;
			long long max_ypiece = *(it);
			cout << max_xpiece * max_ypiece << endl;
		}
	}
	return 0;
}