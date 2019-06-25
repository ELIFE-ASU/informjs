#include <assert.h>
#include <inform/utilities.h>
#include <stdio.h>

void print_series(int const *series, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        printf("%d ", series[i]);
    }
    printf("\n");
}

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        int const series[8] = {5,2,2,5,2,5,5,2};
        int coal[8];
        int b = inform_coalesce(series, 8, coal, &err);
        assert(!err);
        assert(b == 2);
        print_series(coal, 8);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int const series[8] = {2,1,0,0,1,2,1,3};
        int coal[8];
        int b = inform_coalesce(series, 8, coal, &err);
        assert(!err);
        assert(b == 4);
        print_series(coal, 8);
    }
}
