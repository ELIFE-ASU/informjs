#include <assert.h>
#include <stdio.h>
#include <inform/dist.h>

int main()
{
    inform_dist *dist = inform_dist_alloc(5);
    for (uint32_t i = 0; i < 5; ++i)
    {
        uint32_t x = inform_dist_set(dist, i, i*i);
        assert(x == i * i);
        assert(inform_dist_get(dist, i) == i * i);
        printf("%d ", x);
    }
    printf("\n");
    inform_dist_free(dist);
}
