
struct sieve_t {
    int n;
    unsigned char *mod1;
    unsigned char *mod5;
};
int get(struct sieve_t *, int, int);
void set(struct sieve_t *, int, int);

void fill_sieve(struct sieve_t *);

int is_prime(struct sieve_t *, unsigned);