#include <assert.h>
#include <inform/dist.h>
#include <inform/shannon.h>
#include <math.h>
#include <stdio.h>

#define N 10
int main()
{
    int obs[N] = {1, 0, 1, 2, 2, 1, 2, 3, 2, 2};
    int max_event = -1;

    // Find the max event
    for (size_t i = 0; i < N; ++i)
    {
        max_event = (obs[i] > max_event) ? obs[i] : max_event;
    }

    // Construct the distribution
    inform_dist *dist = inform_dist_alloc(max_event + 1);
    assert(dist);

    // Make observations
    for (size_t i = 0; i < N; ++i)
    {
        inform_dist_tick(dist, obs[i]);
    }

    // Compute the entropy
    double base = 2.0;
    double entropy = inform_shannon_entropy(dist, base);
    printf("%lf\n", entropy); // 1.685475

    // Clean up
    inform_dist_free(dist);
}
