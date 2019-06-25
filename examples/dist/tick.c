#include <inform/dist.h>
#include <stdio.h>

int main()
{
    int observations[] = {1,0,1,2,2,1,2,3,2,2};
    inform_dist *dist = inform_dist_alloc(4);
    for (size_t i = 0; i < 10; ++i)
    {
        inform_dist_tick(dist, observations[i]);
    }

    for (size_t i = 0; i < 4; ++i)
    {
        printf("%d ", inform_dist_get(dist, i));
    }
    printf("\n");
    // Output:
    // 1 3 5 1 
    inform_dist_free(dist);
}
