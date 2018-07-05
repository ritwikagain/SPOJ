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
** Simple application of trie to find the the number of words who have given word as their prefix.
** We will keep a member count in each node and whenever a node is visited, we will increment count.
** That way whenever a given word will finish traveral in te trie, the count of the last node will tell
** you that how many actual words have followed the same trie path.
*/

#define CHILDREN_SIZE 26
#define WORD_SIZE 1000002
struct Node
{
	int count;
	struct Node *children[CHILDREN_SIZE];
};

struct Node *newNode()
{
	Node *n = (Node *)malloc(sizeof(Node));
	n->count = 0;
	for (int i = 0; i < CHILDREN_SIZE; i++)
	{
		n->children[i] = NULL;
	}
	return n;
}

void insert (Node *root, char *x)
{
	int length = strlen(x);
	for (int i = 0; i < length; i++)
	{
		if (root->children[x[i] - 'a'] == NULL)
		{
			root->children[x[i] - 'a'] = newNode();
		}
		root = root->children[x[i] - 'a'];
		root->count++;
	}
}
int find (Node *root, char *x)
{
	int length = strlen(x);
	for (int i = 0; i < length; i++)
	{
		if (root->children[x[i] - 'a'] == NULL)
		{
			return 0;
		}
		root = root->children[x[i] - 'a'];
	}
	return root->count;
}
int main ()
{
	int N, Q;
	scanf("%d%d", &N, &Q);
	
	Node *root = newNode();
	
	char x[WORD_SIZE];
	for (int i = 0; i < N; i++)
	{
		scanf("%s", x);
		insert(root, x);
	}
	
	for (int i = 0; i < Q; i++)
	{
		scanf("%s", x);
		printf("%d\n", find(root, x));
	}
}