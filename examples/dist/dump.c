#include <assert.h>
#include <inform/dist.h>
#include <math.h>
#include <stdio.h>

int main()
{
    inform_dist *dist = inform_dist_create((uint32_t[4]){3, 0, 1, 2}, 4);
    double probs[4];
    inform_dist_dump(dist, probs, 4);
    for (size_t i = 0; i < 4; ++i)
    {
        printf("%0.2lf ", probs[i]);
    }
    printf("\n");
    // Outputs:
    // 0.50 0.00 0.17 0.33
    inform_dist_free(dist);
}
