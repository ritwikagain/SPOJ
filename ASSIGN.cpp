#include <iostream>

using namespace std;

/*
** DP + bitmask.
**
** As you see (1 << no_of_students) is actually denoting all the subsets that form the superset of students(or subjects as no of students = no of subjects).
**
** Here for every student, we have a 1D dp array where for every choice of a student's subject, we store how many ways all other objects can be assigned to other students.
** So, if a[i][j] == 1, then for all k where jth bit is 1, dp[i][k] => total number of ways of assigning i subjects to i students where ith student gets jth subject of his choice.
**	   else, 											   dp[i][k] = 0.
**
** Now the question becomes how to populate dp[i][k]. dp[i][k] will take values from all dp[i-1][k ^ (1 << j)] where the jth bit is 0, meaning the jth subject is not yet taken. 	
** If there are n subjects, then there will 2^(n-1) cases where jth subject will be 1, 2^(n-1) cases where jth subject will be 0. So for each population of dp[i][k], it will take
** O(2^(n-1)). Overall the complexity is O(n^2 * 2^n).
*/

const int MAX_CHAR = 20;

int T, N;
int a[MAX_CHAR][MAX_CHAR];
long int dp[MAX_CHAR][1 << MAX_CHAR];

int main ()
{
	int T;
	cin >> T;
	
	while(T--)
	{
		int no_of_students;
		long int result = 0;
		cin >> no_of_students;
		
		for (int i = 0; i < no_of_students; i++)
		{
			for (int j = 0; j < no_of_students; j++)
			{
				cin >> a[i][j];
			}
		}
		
		for (int i = 0; i < no_of_students; i++)
		{
			for (int j = 0; j < (1 << no_of_students); j++)
			{
				dp[i][j] = 0;
			}
		}
		
		for (int j = 0; j < no_of_students; j++)
		{
			if (a[0][j] == 1)
			{
				dp[0][1 << j] = 1;
			}
		}
		
		for (int i = 1; i < no_of_students; i++)
		{
			for (int j = 0; j < no_of_students; j++)
			{
				if (a[i][j])
				{
					for (int k = 0; k < (1 << no_of_students); k++)
					{
						if ((k >> j) & 1)
						{
							dp[i][k] += dp[i - 1][k ^ (1 << j)];
						}
					}
				}
			}
		}
		
		for (int j = 0; j < (1 << no_of_students); j++)
		{
			result += dp[no_of_students - 1][j];
		}
		
		cout << result << endl;
	}
	return 0;
}
