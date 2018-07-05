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
//#include <stdint.h>
using namespace std;

/*
** This is a pure mathematical problem and a marvel application of bitset. At first we want to compute all possible cherry counts and then we will
** remove them which are triangles. If a node has degree n, then it can form at max nC2 cherries, i.e. it can select any 2 edges from all incidet edges.
** Now we need to remove all bad ones. During preparartion, we create a bitset of NODE_MAX size for all the nodes identifying its neighbours. Now for 
** edge, we will see how many nodes are common as neighbours with both nodes of that edge. Every instance of such creates a triangle => bad cherry.
*/
#define NODE_MAX 100002

int main ()
{
	int N, M;
	scanf("%d%d", &N, &M);
	
	vector<pair<int, int> > edgeList;
	vector<bitset<NODE_MAX> > bs(NODE_MAX);
	vector<int> degree(NODE_MAX);
	
	for(int i = 0; i < NODE_MAX; i++)
	{
		degree[i] = 0;
	}
	for (int i = 0; i < M; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		edgeList.push_back(make_pair(a, b));
		degree[a]++;
		degree[b]++;
		bs[a][b] = 1;
		bs[b][a] = 1;
	}
	
	long long all_cherries = 0;
	for (int i = 0; i < N; i++)
	{
		if (degree[i] > 0)
		{
			all_cherries += (degree[i]*(degree[i] - 1))/2; //nC2
		}
	}
	
	long long bad_cherries = 0;
	int size = edgeList.size();
	for (int i = 0; i < size; i++)
	{
		bad_cherries += (bs[edgeList[i].first] & bs[edgeList[i].second]).count();
	}
	
	printf("%lld\n", all_cherries - bad_cherries);
	
	return 0;
}