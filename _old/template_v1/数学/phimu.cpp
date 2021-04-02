bool isNotPrime[MAXN + 1];
int mu[MAXN + 1], phi[MAXN + 1], primes[MAXN + 1], cnt;
inline void euler()
{
    isNotPrime[0] = isNotPrime[1] = true;
    mu[1] = 1;
    phi[1] = 1;
    for (int i = 2; i <= MAXN; i++)
    {
        if (!isNotPrime[i])
        {
            primes[++cnt] = i;
            mu[i] = -1;
            phi[i] = i - 1;
        }

        for (int j = 1; j <= cnt; j++)
        {
            int t = i * primes[j];
            if (t > MAXN) break;

            isNotPrime[t] = true;

            if (i % primes[j] == 0)
            {
                mu[t] = 0;
                phi[t] = phi[i] * primes[j];
                break;
            }
            else
            {
                mu[t] = -mu[i];
                phi[t] = phi[i] * (primes[j] - 1);
            }
        }
    }
}
