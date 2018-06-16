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
#include <bitset>

using namespace std;

#define length 100005

/*
** This is a DP + bitmap problem. This is a corollary of subset sum problem.
** Here the aim is to store all sum values possible in a bitmap. The implementation is to
** take every input i and add all available sum to that value (i.e. shifting all sum values i times left in the bitmap)
** Then we populate count[i] to store all sum values in the range 0 to i.
*/

int main ()
{
	int N, Q;
	scanf("%d%d", &N, &Q);
	
	int coin_denomination[N];
	
	bitset<length> bs_prev;
	bitset<length> bs_current;
	
	bs_prev[0] = 1;
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &coin_denomination[i]);
		
		bs_current = bs_prev | (bs_prev << coin_denomination[i]);
		bs_prev = bs_current;
	}

	int count[length];
	memset (count, 0, sizeof(count));
	
	count[0] = 1;
	for (int i = 1; i < length; i++)
	{
		if (bs_current[i] == 1)
		{
			count[i] = count[i - 1] + 1;
		}
		else
		{
			count[i] = count[i - 1];
		}
	}
	
	while (Q--)
	{
		int start, end;
		scanf("%d%d", &start, &end);
		printf("%d\n", count[end] - count[start - 1]);
		
	}
	return 0;
}