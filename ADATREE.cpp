#include <bits/stdc++.h>
using namespace std;

/*
** Application of segment tree.
**
** The aim is to find the lower bound of a given value within a segment. As it's a range problem, we need to
** use segment tree and as we need to take a decision depending on the value of nodes, we need sorted segments.
** So for each internal node of the tree, we keep a sorted segment of values which that internal node is representing.
** The trick here is: we need to do binary search on the sorted segment to get an AC. 
*/

#define SIZE 300002

int input[SIZE];
vector<vector<int> >  st(SIZE << 2);

void merge (int left, int right, int si)
{
	int l_count = st[left].size();
	int r_count = st[right].size();
	int i = 0, j = 0;
	for (; i < l_count && j < r_count;)
	{
		if (st[left][i] <= st[right][j])
		{
			st[si].push_back(st[left][i]);
			i++;
		}
		else
		{
			st[si].push_back(st[right][j]);
			j++;
		}
	}
	
	while (i < l_count)
	{
		st[si].push_back(st[left][i]);
		i++;
	}
	
	while (j < r_count)
	{
		st[si].push_back(st[right][j]);
		j++;
	}
}
void constructST (int si, int ss, int se)
{
	if (ss == se)
	{
		st[si].push_back(input[ss]);
		return;
	}
	
	int mid = (ss + se) / 2;
	constructST (si * 2 + 1, ss, mid);
	constructST (si * 2 + 2, mid + 1, se);
	merge (si * 2 + 1, si * 2 + 2, si);
}
int get (int ss, int se, int qs, int qe, int si, int H)
{
	if (qe < ss || qs > se)
	{
		return 0;
	}
	
	int greatest = INT_MIN;
	if (qs <= ss && se <= qe)
	{
		/*for (int i = 0; i < st[si].size(); i++)
		{
			if (st[si][i] <= H)
			{
				if (st[si][i] > greatest)
				{
					greatest = st[si][i];
				}
			}
		}
		if (greatest == INT_MIN)
		{
			greatest = 0;
		}
		return greatest;*/
		vector<int>::iterator it = --lower_bound(st[si].begin(), st[si].end(), H + 1);
		/*for (int i = 0; i < st[si].size(); i++)
			printf("%d ", st[si][i]);
		printf("\n");*/
		//vector<int>::iterator it = lower_bound(st[si].begin(), st[si].end(), H);
		//printf("H: %d\t*it: %d\n", H, *it);
        if (*it > H) {
            return 0;
        }
        return *it;
	}
	
	int mid = (ss + se) / 2;
	greatest = max (get (ss, mid, qs, qe, si * 2 + 1, H), get (mid + 1, se, qs, qe, si * 2 + 2, H));
	return greatest;
}
int main ()
{
	int N, Q;
	scanf("%d%d", &N, &Q);

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &input[i]);
	}
	
	constructST(0, 0, N - 1);
	/*for (int i = 0; i < (N+1) << 1; i++)
	{
		for (int j = 0; j < st[i].size(); j++)
			printf("%d ", st[i][j]);
		printf("\n");
	}
	printf("\n");*/
	for (int i = 0; i < Q; i++)
	{
		int l, r, H;
		scanf("%d%d%d", &l, &r, &H);
		printf ("%d\n", get (0, N - 1, l, r, 0, H));
		//printf ("\nAns: %d\n", get (0, N - 1, l, r, 0, H));
	}
	return 0;
}