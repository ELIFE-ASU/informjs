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
    inform_dist *d = inform_dist_alloc(B);
    assert(d);
    for (size_t i = 0; i < N; ++i)
    {
        inform_dist_tick(d, rand() % B);
    }

    printf("%lf\n", inform_shannon_entropy(d,  2.0)); // Base-2:  ~ 3.320903
    printf("%lf\n", inform_shannon_entropy(d, 10.0)); // Base-10: ~ 0.999691

    inform_dist_free(d);
}
