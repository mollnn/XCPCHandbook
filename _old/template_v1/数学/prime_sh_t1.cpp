/*
POJ 2689 Prime Distance
Give an interval [L, U], find out the interval content, the nearest two prime numbers and
The two prime numbers farthest away.
1<=L<U<=2,147,483,647 Interval length not exceeding 1,000,000
Is to filter out the prime numbers between [L, U]
It is necessary to know the prime factors of all non-prime numbers in the [L, U] interval (because a non-prime number is screened out by its smallest prime factor). 2 147 483 The number in 647 or the prime number can be divisible by the prime number in the root number 2 147 483 647, that is to say, all non-prime prime factors in the [L, U] interval are within the root number 2 147 483 647 .
You can find all the prime numbers in the root number 2 147 483 647 in advance, and then use these prime numbers to screen out all non-prime numbers in the specified interval.
*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100010;
int prime[MAXN + 1];
void getPrime()
{
	memset(prime, 0, sizeof(prime));
	for (int i = 2; i <= MAXN; i++)
	{
		if (!prime[i])prime[++prime[0]] = i;
		for (int j = 1; j <= prime[0] && prime[j] <= MAXN / i; j++)
		{
			prime[prime[j] * i] = 1;
			if (i % prime[j] == 0)break;
		}
	}
}
bool notprime[1000010];
int prime2[1000010];
void getPrime2(int L, int R)
{
	memset(notprime, false, sizeof(notprime));
	if (L < 2)L = 2;
	for (int i = 1; i <= prime[0] && (long long)prime[i] * prime[i] <= R; i++)
	{
		int s = L / prime[i] + (L % prime[i] > 0);
		if (s == 1)s = 2;
		for (int j = s; (long long)j * prime[i] <= R; j++)
			if ((long long)j * prime[i] >= L)
				notprime[j * prime[i] - L] = true;
	}
	prime2[0] = 0;
	for (int i = 0; i <= R - L; i++)
		if (!notprime[i])
			prime2[++prime2[0]] = i + L;
}
int main()
{
	getPrime();
	int L, U;
	while (scanf("%d%d", &L, &U) == 2)
	{
		getPrime2(L, U);
		if (prime2[0] < 2) printf("There are no adjacent primes.\n");
		else
		{
			int X1 = 0, X2 = 100000000, Y1 = 0, Y2 = 0;
			for (int i = 1; i < prime2[0]; i++)
			{
				if (prime2[i + 1] - prime2[i] < X2 - X1){
					X1 = prime2[i];
                    X2 = prime2[i + 1];
                }
                if (prime2[i + 1] - prime2[i] > Y2 - Y1){
                    Y1 = prime2[i];
                    Y2 = prime2[i + 1];
                }
            }
            printf("%d,%d are closest, %d,%d are most distant.\n", X1, X2, Y1, Y2);
		}
	}
}

