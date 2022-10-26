#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "primes.h"

int get(struct sieve_t *sv, int k, int num)
{
    int val=0;
    if (num == 1)
        val = (sv->mod1[k / 8] >> (k % 8)) & 1u;

    if (num == 5)
        val = (sv->mod5[k / 8] >> (k % 8)) & 1u;

    if (val == 0)
        return 1;
    else
        return 0;
}

void set(struct sieve_t *sv, int x, int num)
{
    x = x / 6;
    if (num == 1)
        sv->mod1[x / 8] = sv->mod1[x / 8] | (1u << (x % 8));
    else
        sv->mod5[x / 8] = sv->mod5[x / 8] | (1u << (x % 8));

}



void fill_sieve(struct sieve_t *sv)
{
    long long k;
    unsigned long long ch;
    sv->mod1[0] = sv->mod1[0] | (1u << 0);
    for (k = 0; k + 1 <= (sv->n) * 8; k++) {
        if ((k != 0) && get(sv, k, 1)) {
            for (ch = (6 * k + 1) * (6 * k + 1);
                 ch <= (6 * ((sv->n) * 8 - 1) + 1); ch += (6 * k + 1))
                if ((ch % 6) == 1)
                    set(sv, ch, 1);
            for (ch = (6 * k + 1) * (6 * k + 5);
                 ch <= (6 * ((sv->n) * 8 - 1) + 5); ch += (6 * k + 1))
                if ((ch % 6) == 5)
                    set(sv, ch, 5);
        }
        if (get(sv, k, 5)) {
            for (ch = (6 * k + 5) * (6 * k + 5);
                 ch <= (6 * ((sv->n) * 8 - 1) + 1); ch += (6 * k + 5))
                if ((ch % 6) == 1)
                    set(sv, ch, 1);
            for (ch = (6 * (k + 1) + 1) * (6 * k + 5);
                 ch <= (6 * ((sv->n) * 8 - 1) + 5); ch += (6 * k + 5))
                if ((ch % 6) == 5)
                    set(sv, ch, 5);
        }
    }
}

int is_prime(struct sieve_t *sv, unsigned n)
{
    int val;
    if ((n == 2) || (n == 3))
        return 1;

    else if (n % 6 == 1) {
        val = ((sv->mod1[(n / 6) / 8]) >> ((n / 6) % 8)) & 1u;
        if (val == 1)
            return 0;

        else
            return 1;
    } else if (n % 6 == 5) {
        val = ((sv->mod5[(n / 6) / 8]) >> ((n / 6) % 8)) & 1u;
        if (val == 1)
            return 0;

        else
            return 1;
    }

    else
        return 0;
}
