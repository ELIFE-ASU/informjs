#include <assert.h>
#include <inform/integration.h>
#include <stdio.h>

void print_evidence(double const *evidence, size_t n)
{
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            printf("%0.3lf ", evidence[j + i*n]);
        }
        printf("\n");
    }
}

void print_evidence_part(double const *evidence, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        printf("%0.3lf ", evidence[i]);
    }
    printf("\n");
}

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        int const series[30] = {
            0, 1, 0, 1, 1, 1, 0, 0, 1, 0,
            0, 1, 0, 1, 1, 1, 0, 0, 1, 0,
            1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
        };
        double *evidence =
            inform_integration_evidence(series, 3, 10, (int[3]){2,2,2}, NULL, &err);
        assert(!err);
        print_evidence(evidence, 10);
    }
    {
        inform_error err = INFORM_SUCCESS;
        int const series[30] = {
            0, 1, 0, 1, 1, 1, 0, 0, 1, 0, // X_1
            0, 1, 0, 1, 1, 1, 0, 0, 1, 0, // X_2
            1, 1, 1, 1, 1, 0, 0, 0, 0, 0, // X_3
        };
        size_t partitions[3] = {0,0,1}; // Partition as {{X_1, X_2}, {X_3}} (2 partitions)
        double *evidence = inform_integration_evidence_part(series, 3, 10,
                (int[3]){2,2,2}, partitions, 2, NULL, &err);
        assert(!err);
        print_evidence_part(evidence, 10);
        free(evidence);
    }
}
