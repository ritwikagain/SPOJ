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
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <utility>
#include <limits.h>
using namespace std;

/*
** This is application of binary search where we are searching for the distance between two cows between 0 and INT_MAX.
** For every distance, we are checking if all the cows can be placed maintaining that distance. 
**	1. If Yes, it may happen that the distance can be increased more.
**	2. If No, it may happen that we may get a lesser distance afterwards.
*/
bool check (int *a, int N, int C, int distance)
{
	int last = a[0];
	int cowsPlaced = 1;
	for (int i = 1; i < N; i++)
	{
		if (a[i] - last >= distance)
		{
			if (cowsPlaced < C)
			{
				cowsPlaced++;
				if (cowsPlaced == C)
				{
					return true;
				}
			}	
			last = a[i];
		}
	}
	
	return false;
}

int main ()
{
	int T;
	cin >> T;
	
	while (T--)
	{
		int N, C;
		int longestDistance = 0;
		cin >> N;
		cin >> C;
		
		int *a = (int *) malloc (sizeof(int) * N);

		for (int i = 0; i < N; i++)
		{
			cin >> a[i];
		}

		sort (a, a + N);
		
		int mindiff = 0;
		int maxdiff = INT_MAX;
		
		while (mindiff <= maxdiff)
		{
			//cout << "mindiff: " << mindiff << " maxdiff: " << maxdiff << endl;
			int middiff = (mindiff + maxdiff)/2;
			//cout << "middiff: " << middiff << endl;
			if (check (a, N, C, middiff))
			{
				longestDistance = max (longestDistance, middiff);
				//cout << "longestDistance: " << longestDistance << endl;
				mindiff = middiff + 1;
			}
			else
			{
				maxdiff = middiff - 1;
			}
		}
		
		free (a);
		
		cout << longestDistance << endl;
	}
	return 0;
}