#include <assert.h>

#include <stdio.h>
#include <inform/excess_entropy.h>

void print_ee(double const *ee, size_t n, size_t m)
{
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            printf("%0.3lf ", ee[j + m*i]);
        }
        printf("\n");
    }
}

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        int const series[9] = {0,0,1,1,0,0,1,1,0};
        double ee = inform_excess_entropy(series, 1, 9, 2, 2, &err);
        assert(!err);
        printf("%0.6lf\n", ee);
        // ee ~ 1.918296
    }
    {
        inform_error err = INFORM_SUCCESS;
        int const series[18] = {
            0,0,1,1,0,0,1,1,0,
            0,1,0,1,0,1,0,1,0
        };
        double ee = inform_excess_entropy(series, 2, 9, 2, 2, &err);
        assert(!err);
        printf("%0.6lf\n", ee);
        // ee ~ 1.109170
    }

    {
        inform_error err = INFORM_SUCCESS;
        int const series[9] = {0,0,1,1,0,0,1,1,0};
        double *ee = inform_local_excess_entropy(series, 1, 9, 2, 2, NULL, &err);
        assert(!err);
        print_ee(ee, 1, 6);
        // ee ~ { 1.585 1.585 2.585 2.585 1.585 1.585 }
        free(ee);
    }
    {
        inform_error err = INFORM_SUCCESS;
        int const series[18] = {
            0,0,1,1,0,0,1,1,0,
            0,1,0,1,0,1,0,1,0
        };
        double *ee = inform_local_excess_entropy(series, 2, 9, 2, 2, NULL, &err);
        assert(!err);
        print_ee(ee, 2, 6);
        // ee ~ { 2.585 -0.059 3.585 -0.415 2.585 -0.059 
        //        0.848  0.848 0.848  0.848 0.848  0.848 }
        free(ee);
    }
}
