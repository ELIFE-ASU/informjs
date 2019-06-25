#include <assert.h>
#include <inform/dist.h>
#include <math.h>
#include <stdio.h>

int main()
{
    inform_dist *dist = inform_dist_create((uint32_t[4]){3, 0, 1, 2}, 4);
    assert(fabs(inform_dist_prob(dist, 0) -    0.5) < 1e-6);
    assert(fabs(inform_dist_prob(dist, 1) -    0.0) < 1e-6);
    assert(fabs(inform_dist_prob(dist, 2) - 0.1666) < 1e-6);
    assert(fabs(inform_dist_prob(dist, 3) - 0.3333) < 1e-6);
    for (size_t i = 0; i < 4; ++i)
    {
        printf("%lf  ", inform_dist_prob(dist, i));
    }
    printf("\n");
    inform_dist_free(dist);
}
