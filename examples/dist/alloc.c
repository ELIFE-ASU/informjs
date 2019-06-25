#include <assert.h>
#include <inform/dist.h>

int main()
{
    inform_dist *dist = inform_dist_alloc(5);
    assert(dist != NULL);
    assert(inform_dist_is_valid(dist) == 0);
    assert(inform_dist_size(dist) == 5);
    assert(inform_dist_counts(dist) == 0);
    inform_dist_free(dist);
}
