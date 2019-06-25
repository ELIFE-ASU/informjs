#include <assert.h>
#include <inform/dist.h>

int main()
{
    uint32_t observations[7] = {0, 0, 1, 2, 1, 0, 0};
    inform_dist *dist = inform_dist_create(observations, 7);
    assert(dist != NULL);
    assert(inform_dist_is_valid(dist) == 1);
    assert(inform_dist_size(dist) == 7);
    assert(inform_dist_counts(dist) == 4);
    inform_dist_free(dist);
}
