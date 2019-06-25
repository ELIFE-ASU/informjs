#include <assert.h>
#include <inform/dist.h>
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

    // Get the probabilities
    double *probs = malloc((max_event + 1) * sizeof(double));
    assert(probs);
    inform_dist_dump(dist, probs, max_event + 1);

    // Compute the entropy
    double entropy = 0.0;
    for (size_t i = 0; i < inform_dist_size(dist); ++i)
    {
        entropy -= probs[i] * log2(probs[i]);
    }
    printf("%lf\n", entropy); // 1.685475

    // Clean up
    free(probs);
    inform_dist_free(dist);
}
