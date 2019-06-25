#include <assert.h>
#include <inform/utilities.h>
#include <stdio.h>

int main()
{
    inform_random_seed();

    {
        srand(2018);
        for (size_t i = 0; i < 10; ++i)
        {
            printf("%d ", inform_random_int(0, 2));
        }
        printf("\n");
    }

    {
        srand(2018);
        int *arr = inform_random_ints(0, 2, 10);
        assert(arr);
        for (size_t i = 0; i < 10; ++i)
        {
            printf("%d ", arr[i]);
        }
        printf("\n");
        free(arr);
    }

    {
        srand(2018);
        int *series = inform_random_series(10, 2);
        assert(series);
        for (size_t i = 0; i < 10; ++i)
        {
            printf("%d ", series[i]);
        }
        printf("\n");
        free(series);
    }
}
