#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
struct sieve_t {
    int n;
    unsigned char *mod1;
    unsigned char *mod5;
};
void fill_sieve(struct sieve_t *sv)
{
    unsigned long long k, m, x;
    int val;
    sv->mod1[0] = sv->mod1[0] | (1u << 0);

    for (k = 1; k + 1 <= (sv->n) * 8; k++) {
        val = (sv->mod1[k / 8] >> (k % 8)) & 1u;
        if (val == 0) {
            for (m = k; m + 1 <= (sv->n) * 8; m += 1) {
                x = (6 * m + 1) * k + (6 * m + 1) / 6;
                if (x + 1 <= (sv->n) * 8)
                    sv->mod1[x / 8] = sv->mod1[x / 8] | (1u << (x % 8));

                x = (6 * m + 5) * k + (6 * m + 5) / 6;
                if (x + 1 <= (sv->n) * 8)
                    sv->mod5[x / 8] = sv->mod5[x / 8] | (1u << (x % 8));
            }
        }
    }
    for (k = 0; k + 1 <= (sv->n) * 8; k++) {
        val = (sv->mod5[k / 8] >> (k % 8)) & 1u;
        if (val == 0) {
            for (m = k + 1; m + 1 <= (sv->n) * 8; m += 1) {
                x = (6 * m + 1) * k + (5 * (6 * m + 1)) / 6;
                if (x + 1 <= (sv->n) * 8)
                    sv->mod5[x / 8] = sv->mod5[x / 8] | (1u << (x % 8));
            }
            for (m = k; m + 1 <= (sv->n) * 8; m += 1) {
                x = (6 * m + 5) * k + (5 * (6 * m + 5)) / 6;
                if (x + 1 <= (sv->n) * 8)
                    sv->mod1[x / 8] = sv->mod1[x / 8] | (1u << (x % 8));
            }
        }
    }
    printf("%d %d\n", sv->mod1[1], sv->mod5[1]);
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
