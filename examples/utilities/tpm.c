#include <assert.h>
#include <inform/utilities.h>
#include <stdio.h>

void print_tpm(double const *tpm, size_t b)
{
    for (size_t i = 0; i < b; ++i)
    {
        for (size_t j = 0; j < b; ++j)
        {
            printf("%0.3lf ", tpm[j + i*b]);
        }
        printf("\n");
    }
}

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        int const series[15] = {0,2,1,0,1,2,0,1,2,1,0,0,2,1,1};
        double *tpm = inform_tpm(series, 1, 15, 3, NULL, &err);
        assert(!err);
        print_tpm(tpm, 3);
        free(tpm);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int const series[14] = {
            0,0,
            0,1,
            0,1,
            0,1,
            1,0,
            1,1,
            2,2,
        };
        double *tpm = inform_tpm(series, 7, 2, 3, NULL, &err);
        assert(!err);
        print_tpm(tpm, 3);
        free(tpm);
    }
}
