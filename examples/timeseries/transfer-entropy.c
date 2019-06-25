#include <assert.h>
#include <stdio.h>
#include <inform/transfer_entropy.h>

// void print_ai(double ai, size_t k)
// {
//     printf("AI(%ld) = %lf\n", k, ai);
// }

void print_lte(double const *te, size_t n, size_t k)
{
    printf("LAI(%ld) = { ", k);
    for (size_t i = 0; i < n; ++i)
    {
        printf("%6.3lf ", te[i]);
    }
    printf("}\n");
}

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        int const xs[9] = {0,1,1,1,1,0,0,0,0};
        int const ys[9] = {0,0,1,1,1,1,0,0,0};
        double te = inform_transfer_entropy(xs, ys, NULL, 0, 1, 9, 2, 2, &err);
        assert(inform_succeeded(&err));
        printf("%0.6lf\n", te);
        double *lte = inform_local_transfer_entropy(xs, ys, NULL, 0, 1, 9, 2, 2, NULL, &err);
        assert(inform_succeeded(&err));
        print_lte(lte, 7, 2);
        free(lte);
    }
    {
        inform_error err = INFORM_SUCCESS;
        int const xs[18] = {1,0,0,0,0,1,1,1,1,
                            1,1,1,1,0,0,0,1,1};
        int const ys[18] = {0,0,1,1,1,1,0,0,0,
                            1,0,0,0,0,1,1,1,0};
        double te = inform_transfer_entropy(xs, ys, NULL, 0, 2, 9, 2, 2, &err);
        assert(inform_succeeded(&err));
        printf("%0.6lf\n", te);
        double *lte = inform_local_transfer_entropy(xs, ys, NULL, 0, 2, 9, 2, 2, NULL, &err);
        assert(inform_succeeded(&err));
        print_lte(lte, 14, 2);
        free(lte);
    }
    {
        inform_error err = INFORM_SUCCESS;
        int const xs[9] = {0,1,1,1,1,0,0,0,0};
        int const ys[9] = {0,0,1,1,1,1,0,0,0};
        int const ws[9] = {0,1,1,1,1,0,1,1,1};
        double te = inform_transfer_entropy(xs, ys, ws, 1, 1, 9, 2, 2, &err);
        assert(inform_succeeded(&err));
        printf("%0.6lf\n", te);
        double *lte = inform_local_transfer_entropy(xs, ys, ws, 1, 1, 9, 2, 2, NULL, &err);
        assert(inform_succeeded(&err));
        print_lte(lte, 7, 2);
        free(lte);
    }
    {
        inform_error err = INFORM_SUCCESS;
        int const xs[9]  = {0,1,1,1,1,0,0,0,0};
        int const ys[9]  = {0,0,1,1,1,1,0,0,0};
        int const ws[18] = {1,0,1,0,1,1,1,1,1,
                            1,1,0,1,0,1,1,1,1};
        double te = inform_transfer_entropy(xs, ys, ws, 2, 1, 9, 2, 2, &err);
        assert(inform_succeeded(&err));
        printf("%0.6lf\n", te);
        double *lte = inform_local_transfer_entropy(xs, ys, ws, 2, 1, 9, 2, 2, NULL, &err);
        assert(inform_succeeded(&err));
        print_lte(lte, 7, 2);
        free(lte);
    }
}
