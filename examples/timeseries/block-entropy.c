#include <stdio.h>
#include <inform/utilities.h>
#include <inform/block_entropy.h>

void print_h(double h, size_t k)
{
    printf("H(%ld) = %lf\n", k, h);
}

void print_lh(double const *h, size_t n, size_t k)
{
    printf("LH(%ld) = { ", k);
    for (size_t i = 0; i < 5; ++i)
    {
        printf("%6.3lf ", h[i]);
    }
    printf("... ");
    for (size_t i = 0; i < 5; ++i)
    {
        printf("%6.3lf ", h[n-5+i]);
    }
    printf("}\n");
}

int main()
{
    // the length of the time series
    size_t const N = 1000;
    // the base of the time series
    int const base = 2;

    // seed a random number generator
    srand(2017);
    // generate a time series
    int *series = inform_random_series(N, base);
    if (!series)
    {
        fprintf(stderr, "error: cannot allocate time series\n");
        return 1;
    }

    inform_error err = INFORM_SUCCESS;
    // compute and print the block entropy for history lengths 1 to 3.
    printf("H for one time series of length %ld\n", N);
    for (size_t k = 1; k < 4; ++k)
    {
        double h = inform_block_entropy(series, 1, N, base, k, &err);
        if (inform_failed(&err))
        {
            fprintf(stderr, "error: (h(%ld)) - %s\n", k, inform_strerror(&err));
            free(series);
            return 2;
        }
        print_h(h, k);
    }
    printf("\n");

    // compute and print the block entropy for history lengths 1 to 3.
    printf("H for ten time series of length %ld\n", N/10);
    for (size_t k = 1; k < 4; ++k)
    {
        double h = inform_block_entropy(series, 10, N/10, base, k, &err);
        if (inform_failed(&err))
        {
            fprintf(stderr, "error: (h(%ld)) - %s\n", k, inform_strerror(&err));
            free(series);
            return 2;
        }
        print_h(h, k);
    }
    printf("\n");

    // compute and print the local block entropy for history lengths 1 to 3.
    printf("LH for one time series of length %ld\n", N);
    for (size_t k = 1; k < 4; ++k)
    {
        double *h = inform_local_block_entropy(series, 1, N, base, k, NULL, &err);
        if (inform_failed(&err))
        {
            fprintf(stderr, "error: (LH(%ld)) - %s\n", k, inform_strerror(&err));
            free(series);
            return 2;
        }
        print_lh(h, N, k);
        free(h);
    }

    // cleanup the time series
    free(series);
}
