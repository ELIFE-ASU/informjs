#include <stdio.h>
#include <inform/utilities.h>
#include <inform/conditional_entropy.h>

void print_ce(double ce)
{
    printf("CE = %lf\n", ce);
}

void print_lce(double const *ce, size_t n)
{
    printf("LCE = { ");
    for (size_t i = 0; i < 5; ++i)
    {
        printf("%6.3lf ", ce[i]);
    }
    printf("... ");
    for (size_t i = 0; i < 5; ++i)
    {
        printf("%6.3lf ", ce[n-5+i]);
    }
    printf("}\n");
}

int main()
{
    // the length of the time series
    size_t const N = 1000;
    // the base of the X time series
    int const base_x = 2;
    // the base of the Y time series
    int const base_y = 3;

    // seed a random number generator
    srand(2017);
    // generate the X and Y time series
    int *series_x = inform_random_series(N, base_x);
    if (!series_x)
    {
        fprintf(stderr, "error: cannot allocate the X time series\n");
        return 1;
    }
    int *series_y = inform_random_series(N, base_y);
    if (!series_y)
    {
        fprintf(stderr, "error: cannot allocate the Y time series\n");
        return 1;
    }

    inform_error err = INFORM_SUCCESS;
    printf("The entropy of Y conditioned on X:\n");
    double ce = inform_conditional_entropy(series_x, series_y, N, base_x, base_y, &err);
    if (inform_failed(&err))
    {
        fprintf(stderr, "error: %s\n", inform_strerror(&err));
        free(series_y);
        free(series_x);
        return 2;
    }
    print_ce(ce);
    printf("\n");

    printf("The entropy of X conditioned on Y:\n");
    ce = inform_conditional_entropy(series_y, series_x, N, base_y, base_x, &err);
    if (inform_failed(&err))
    {
        fprintf(stderr, "error: %s\n", inform_strerror(&err));
        free(series_y);
        free(series_x);
        return 2;
    }
    print_ce(ce);
    printf("\n");

    printf("The local entropy of Y conditioned on X:\n");
    double *lce =
        inform_local_conditional_entropy(series_x, series_y, N, base_x, base_y, NULL, &err);
    if (inform_failed(&err))
    {
        fprintf(stderr, "error: %s\n", inform_strerror(&err));
        free(series_y);
        free(series_x);
        return 2;
    }
    print_lce(lce, N);
    free(lce);

    // cleanup the time series
    free(series_x);
    free(series_y);
}
