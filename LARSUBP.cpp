#include <iostream>
#include <string.h>
#include <time.h>

using namespace std;

/*
**	DP
**
**	This is improvement on basic LIS. You can solve the problem using basic LIS but will end up having TLE.
**	Fo basic LIS, you will take dp[size_of_input] and for a particular digit i, you need to check from dp[0] to dp[i-1] to populate dp[i].
**	This leads to O(n^2) algo which gives TLE here. Here we bring the complexity down to O(n) by having dp[] of constant size(no of digits possible).
**
**	We will traverse the input from left to right, and for every input digit i, we will check all dp[j] from 0 to i and add to dp[i]. Because to make_heap
**	an increasing subsequence, we want to add all dp[j] where j < i from the currently traversed string and the values of i or j can be only of 10 types (0 ... 9).
**	So having a dp[] of 10 size is enough.
*/

#define MAX_CHAR 10010
#define MOD 1000000007
#define MAX_DIGITS 10

char s[MAX_CHAR];
int dp[MAX_DIGITS];

int main ()
{
	int T;
	cin >> T;
	int c = 0;
	while(c < T)
	{
		cin >> s;
		int len = strlen(s);
		memset (dp, 0, sizeof(dp));
		
		for (int i = 0; i < len; i++)  //O(n)
		{
			int digit = s[i] - '0';
			int count = digit;
			while (count--) 			// O(1)
			{
				dp[digit] = (dp[digit] + dp[count]) % MOD;
			}
			dp[digit]++; // a subsequence having a single digit s[i]
		}
		
		int sum = 0;
		for (int i = 0; i < MAX_DIGITS; i++)
		{
			sum = (sum + dp[i]) % MOD;
		}
		
		cout << "Case " << c + 1 << ": " << sum << endl;
		c++;
	}
	return 0;
}
