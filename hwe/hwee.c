#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "primes.h"


int main()
{
    int n = 10;
    int otv;
    int ch;
    scanf("%d", &ch);
    unsigned char *sieve1 = calloc(n, sizeof(unsigned char));
    unsigned char *sieve5 = calloc(n, sizeof(unsigned char));
    struct sieve_t res;
    res.n = n;
    res.mod1 = sieve1;
    res.mod5 = sieve5;
    for (int i = 0; i <= n; i++)
        res.mod1[i] = 0u;
    for (int i = 0; i <= n; i++)
        res.mod5[i] = 0u;
    fill_sieve(&res);
    otv = is_prime(&res, ch);
    printf("%d\n", otv);
    return 0;
}
