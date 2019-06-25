#include <stdio.h>
#include <inform/utilities.h>
#include <inform/active_info.h>

void print_ai(double ai, size_t k)
{
    printf("AI(%ld) = %lf\n", k, ai);
}

void print_lai(double const *ai, size_t n, size_t k)
{
    printf("LAI(%ld) = { ", k);
    for (size_t i = 0; i < 5; ++i)
    {
        printf("%6.3lf ", ai[i]);
    }
    printf("... ");
    for (size_t i = 0; i < 5; ++i)
    {
        printf("%6.3lf ", ai[n-5+i]);
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
    // compute and print the active information for history lengths 1 to 3.
    printf("AI for one time series of length %ld\n", N);
    for (size_t k = 1; k < 4; ++k)
    {
        double ai = inform_active_info(series, 1, N, base, k, &err);
        if (inform_failed(&err))
        {
            fprintf(stderr, "error: (ai(%ld)) - %s\n", k, inform_strerror(&err));
            free(series);
            return 2;
        }
        print_ai(ai, k);
    }
    printf("\n");

    // compute and print the active information for history lengths 1 to 3.
    printf("AI for ten time series of length %ld\n", N/10);
    for (size_t k = 1; k < 4; ++k)
    {
        double ai = inform_active_info(series, 10, N/10, base, k, &err);
        if (inform_failed(&err))
        {
            fprintf(stderr, "error: (ai(%ld)) - %s\n", k, inform_strerror(&err));
            free(series);
            return 2;
        }
        print_ai(ai, k);
    }
    printf("\n");

    // compute and print the local active information for history lengths 1 to 3.
    printf("LAI for one time series of length %ld\n", N);
    for (size_t k = 1; k < 4; ++k)
    {
        double *ai = inform_local_active_info(series, 1, N, base, k, NULL, &err);
        if (inform_failed(&err))
        {
            fprintf(stderr, "error: (LAI(%ld)) - %s\n", k, inform_strerror(&err));
            free(series);
            return 2;
        }
        print_lai(ai, N, k);
        free(ai);
    }

    // cleanup the time series
    free(series);
}
