#include <assert.h>

#include <stdio.h>
#include <inform/predictive_info.h>

void print_pi(double const *pi, size_t n, size_t m)
{
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            printf("%0.3lf ", pi[j + m*i]);
        }
        printf("\n");
    }
}

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        int const series[9] = {0,0,1,1,0,0,1,1,0};
        double pi = inform_predictive_info(series, 1, 9, 2, 1, 2, &err);
        assert(!err);
        printf("%0.6lf\n", pi);
        // pi ~ 0.985228
    }
    {
        inform_error err = INFORM_SUCCESS;
        int const series[18] = {
            0,0,1,1,0,0,1,1,0,
            0,1,0,1,0,1,0,1,0
        };
        double pi = inform_predictive_info(series, 2, 9, 2, 1, 2, &err);
        assert(!err);
        printf("%0.6lf\n", pi);
        // pi ~ 0.244905
    }

    {
        inform_error err = INFORM_SUCCESS;
        int const series[9] = {0,0,1,1,0,0,1,1,0};
        double *pi = inform_local_predictive_info(series, 1, 9, 2, 1, 2, NULL, &err);
        assert(!err);
        print_pi(pi, 1, 7);
        // pi ~ { 0.807 0.807 1.222 1.222 0.807 0.807 1.222 }
        free(pi);
    }
    {
        inform_error err = INFORM_SUCCESS;
        int const series[18] = {
            0,0,1,1,0,0,1,1,0,
            0,1,0,1,0,1,0,1,0
        };
        double *pi = inform_local_predictive_info(series, 2, 9, 2, 1, 2, NULL, &err);
        assert(!err);
        print_pi(pi, 2, 7);
        // pi ~ { -0.515 0.807 -0.363 1.222 -0.515 0.807 -0.363 
        //         0.222 0.485  0.222 0.485  0.222 0.485  0.222 }
        free(pi);
    }
}
