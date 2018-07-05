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
** This is a classical problem of finding MST. I chose Kruskal because of the forest nature of the input graph.
** I chose UNION FIND with rank and path compression to improve runtime, but it's not essential to get an AC.
** The trick lies in the fact that I am sorting all the input edges and queries in decreasing order and then I am running UNION FIND
** because if I would have created the MST before the queries, I would have to again traverse a particular tree to know
** which edges bear Ada'a weight. But if I do UNION FIND on a overall sorted sequence in decreasing order, then I am saving myself an extra 
** traversal with each query.
*/
struct subset
{
	int parent;
	int rank;
	int size;
};

struct operation
{
	int op_type;
	int query_index; // needed to print result in order 
	int src_node;
	int dest_node;
	int weight;
};

int mycompare (operation& a, operation& b)
{
	if (a.weight != b.weight)
	{
		return a.weight > b.weight;
	}
	else
	{
		return a.op_type < b.op_type;
	}
}

vector<subset> subsets;
int find_root (int a)
{
	if (subsets[a].parent != a)
	{
		subsets[a].parent = find_root(subsets[a].parent);
	}
	return subsets[a].parent;
}

void union_set (int a, int b)
{
	int a_set = find_root(a);
	int b_set = find_root(b);
	
	if (a_set == b_set)
	{
		return;
	}
	else
	{
		if (subsets[a_set].rank < subsets[b_set].rank)
		{
			subsets[a_set].parent = b_set;
			subsets[b_set].size += subsets[a_set].size;
		}
		else if (subsets[a_set].rank > subsets[b_set].rank)
		{
			subsets[b_set].parent = a_set;
			subsets[a_set].size += subsets[b_set].size;
		}
		else
		{
			subsets[b_set].parent = a_set;
			subsets[a_set].size += subsets[b_set].size;
			subsets[a_set].rank += 1;
		}
	}
}

int main ()
{
	int N, M, Q;
	scanf("%d%d%d", &N, &M, &Q);
	
	for (int i = 0; i < N; i++)
	{
		subset s;
		s.parent = i;
		s.rank = 0;
		s.size = 1;
		subsets.push_back(s);
	}
	
	vector<operation> operations;
	for (int i = 0; i < M; i++)
	{
		int a, b, w;
		scanf("%d%d%d", &a, &b, &w);
		operation o;
		o.op_type = 0;
		o.query_index = -1;
		o.src_node = a;
		o.dest_node = b;
		o.weight = w;
		operations.push_back(o);
	}
	
	for (int i = 0; i < Q; i++)
	{
		int a, w;
		scanf("%d%d", &a, &w);
		operation o;
		o.op_type = 1;
		o.query_index = i;
		o.src_node = a;
		o.dest_node = -1;
		o.weight = w;
		operations.push_back(o);
	}
	
	sort(operations.begin(), operations.end(), mycompare);
	
	int size = operations.size();
	int result[Q];
	for (int i = 0; i < size; i++)
	{
		operation op = operations[i];
		if (op.op_type == 0) // add edge
		{
			union_set(op.src_node, op.dest_node);
		}
		else  // query 
		{
			result[op.query_index] = subsets[find_root(op.src_node)].size;
			
		}
	}
	
	for (int i = 0; i < Q; i++)
	{
		printf("%d\n", result[i]);
	}
	return 0;
}