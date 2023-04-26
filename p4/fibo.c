#include <stdio.h>
#include <gmp.h>

int main()
{
    mpz_t a, b, c;
    mpz_init(a);
    mpz_init(b);
    mpz_init(c);

    mpz_set_ui(a, 0);
    mpz_set_ui(b, 1);

    for (int i = 2; i <= 1000; i++)
    {
        mpz_add(c, a, b);
        gmp_printf("%Zd\n", a);
        mpz_set(a, b);
        mpz_set(b, c);
        
    }

    gmp_printf("%Zd\n", b);

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(c);

    return 0;
}
