#include <assert.h>
#include <inform/dist.h>
#include <inform/shannon.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define B 10
#define N 10000

int main()
{
    srand(time(NULL));
    inform_dist *joint = inform_dist_alloc(B * B);
    inform_dist *prev = inform_dist_alloc(B);
    inform_dist *next = inform_dist_alloc(B);
    assert(joint && prev && next);

    int p = rand() % B, n = 0;
    for (size_t i = 0; i < N; ++i)
    {
        n = rand() % B;
        inform_dist_tick(prev, p);
        inform_dist_tick(next, n);
        inform_dist_tick(joint, 10*p + n);
        p = n;
    }

    // Base-2:  ~ 0.006248
    printf("%lf\n", inform_shannon_mi(joint, prev, next,  2.0));
    // Base-10: ~ 0.001881
    printf("%lf\n", inform_shannon_mi(joint, prev, next, 10.0));

    inform_dist_free(next);
    inform_dist_free(prev);
    inform_dist_free(joint);
}
