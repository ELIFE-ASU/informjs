#include <assert.h>
#include <inform/active_info.h>
#include <inform/separable_info.h>
#include <inform/transfer_entropy.h>
#include <stdio.h>

void print_si(double const *si, size_t n, size_t m)
{
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            printf("%0.3lf ", si[j + i*m]);
        }
        printf("\n");
    }
}

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        int const dest[9] = {0,1,1,1,1,0,0,0,0};
        int const srcs[9] = {0,0,1,1,1,1,0,0,0};

        double ai = inform_active_info(dest, 1, 9, 2, 2, &err);
        assert(!err);
        double te = inform_transfer_entropy(srcs, dest, NULL, 0, 1, 9, 2, 2, &err);
        assert(!err);
        double si = inform_separable_info(srcs, dest, 1, 1, 9, 2, 2, &err);
        assert(!err);
        double manual_si = ai + te;
        printf("%.6lf == %.6lf\n", si, manual_si);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int const dest[9] = {0,1,1,1,1,0,0,0,0};
        int const srcs[18] = {
            0,0,1,1,1,1,0,0,0,
            1,1,1,1,0,0,0,0,0,
         };

        double ai = inform_active_info(dest, 1, 9, 2, 2, &err);
        assert(!err);
        double te = 0.0;
        for (size_t i = 0; i < 2; ++i)
        {
            te += inform_transfer_entropy(srcs + 9*i, dest, NULL, 0, 1, 9, 2, 2, &err);
            assert(!err);
        }
        double si = inform_separable_info(srcs, dest, 2, 1, 9, 2, 2, &err);
        assert(!err);
        double manual_si = ai + te;
        printf("%.6lf == %.6lf\n", si, manual_si);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int const dest[18] = {
            0,1,1,1,1,0,0,0,0,
            1,1,0,1,1,0,1,1,0
        };
        int const srcs[36] = {
            0,0,1,1,1,1,0,0,0, 1,1,1,1,1,0,1,1,0,
            1,1,1,1,0,0,0,0,0, 0,0,0,0,1,1,1,1,0,
        };

        double ai = inform_active_info(dest, 2, 9, 2, 2, &err);
        assert(!err);
        double te = 0.0;
        for (size_t i = 0; i < 2; ++i)
        {
            te += inform_transfer_entropy(srcs + 18*i, dest, NULL, 0, 2, 9, 2, 2, &err);
            assert(!err);
        }
        double si = inform_separable_info(srcs, dest, 2, 2, 9, 2, 2, &err);
        assert(!err);
        double manual_si = ai + te;
        printf("%.6lf == %.6lf\n", si, manual_si);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int const dest[9] = {0,1,1,1,1,0,0,0,0};
        int const srcs[9] = {0,0,1,1,1,1,0,0,0};

        double *si = inform_local_separable_info(srcs, dest, 1, 1, 9, 2, 2, NULL, &err);
        assert(!err);
        print_si(si, 1, 7);
        free(si);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int const dest[9] = {0,1,1,1,1,0,0,0,0};
        int const srcs[18] = {
            0,0,1,1,1,1,0,0,0,
            1,1,1,1,0,0,0,0,0,
        };

        double *si = inform_local_separable_info(srcs, dest, 2, 1, 9, 2, 2, NULL, &err);
        assert(!err);
        print_si(si, 1, 7);
        free(si);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int const dest[18] = {
            0,1,1,1,1,0,0,0,0,
            1,1,0,1,1,0,1,1,0
        };
        int const srcs[36] = {
            0,0,1,1,1,1,0,0,0, 1,1,1,1,1,0,1,1,0,
            1,1,1,1,0,0,0,0,0, 0,0,0,0,1,1,1,1,0,
        };

        double *si = inform_local_separable_info(srcs, dest, 2, 2, 9, 2, 2, NULL, &err);
        assert(!err);
        print_si(si, 2, 7);
        free(si);
    }
}
