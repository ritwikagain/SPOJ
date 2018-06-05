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
//#include <stdint.h>
using namespace std;

/*
** The aim here is to run Dijkstra on the source node. Maintaining data structures is important.
** The question lets self loops and multiple esdges between two nodes to be entered. I ignored self
** loops. The distance[] array eliminates those edges in multiple edge set which are not smallest.
*/
struct compare
{
	bool operator() (pair<int, int> a, pair<int, int> b)
	{
		return a.second < b.second;
	}
};

int main ()
{
	int N, M, Q;
	cin >> N;
	cin >> M;
	cin >> Q;
	
	vector<vector<pair<int, int> >  > edgeList(N);
	priority_queue<pair<int, int>, vector<pair<int, int> >, compare> pq;
	
	for (int i = 0; i < M; i++)
	{
		int a;
		int b;
		int l;
		cin >> a;
		cin >> b;
		cin >> l;
		
		if (a != b)
		{
			edgeList[a].push_back(make_pair(b, l));
			edgeList[b].push_back(make_pair(a, l));
		}
	}
	
	int source;
	int distance[N];
	bool visited[N];

	while (Q--)
	{
		cin >> source;
		for (int i = 0; i < N; i++)
		{	
			distance[i] = INT_MAX;
		}
		memset (visited, false, sizeof(visited));
		
		pq.push(make_pair(source, 0));
		distance[source] = 0;
    
		while (!pq.empty())
		{
			pair<int, int> temp;
			temp = pq.top();
			pq.pop();
	
			if (visited[temp.first] == false)
			{
				visited[temp.first] = true;
				for (int it = 0; it < edgeList[temp.first].size(); it++)
				{
					
					if (!visited[edgeList[temp.first][it].first] && distance[edgeList[temp.first][it].first] > distance[temp.first] + edgeList[temp.first][it].second)
					{
						distance[edgeList[temp.first][it].first] = distance[temp.first] + edgeList[temp.first][it].second;
						pq.push(make_pair(edgeList[temp.first][it].first, distance[edgeList[temp.first][it].first]));
					}
				}
			}
		}
		
		int highestDistance = -1;
		int count = -1;
		for (int i = 0; i < N; i++)
		{
			if (distance[i] != INT_MAX && distance[i] > highestDistance)
			{
				highestDistance = distance[i];
				count = 0;
			}
			else if (distance[i] == highestDistance)
			{
				count++;
			}
		}
		
		cout << highestDistance << " " << count + 1 << endl;
	}
	
	return 0;
}	
