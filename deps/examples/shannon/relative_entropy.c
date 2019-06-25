#include <assert.h>
#include <inform/dist.h>
#include <inform/shannon.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define B 2
#define N 10000

int main()
{
    srand(time(NULL));
    inform_dist *p = inform_dist_alloc(B);
    inform_dist *q = inform_dist_alloc(B);
    assert(p && q);

    for (size_t i = 0; i < N; ++i)
    {
        inform_dist_tick(p, rand() % 2);
        inform_dist_tick(q, (((((rand() % 6) % 5) % 4) % 3) % 2));
    }

    printf("%lf\n", inform_shannon_re(q, p, 2.0)); // ~ 0.368494
    printf("%lf\n", inform_shannon_re(p, q, 2.0)); // ~ 0.449499

    inform_dist_free(q);
    inform_dist_free(p);
}
