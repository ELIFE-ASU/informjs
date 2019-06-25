#include <assert.h>
#include <inform/active_info.h>
#include <inform/mutual_info.h>
#include <inform/utilities.h>
#include <stdio.h>
#include <string.h>

void print_series(int const *series, size_t n, size_t m)
{
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            printf("%d ", series[j + i*m]);
        }
        printf("\n");
    }
}

int main()
{
    {
        inform_error err = INFORM_SUCCESS;
        int const series[16] = {
            0,1,1,0,1,0,0,1,
            1,0,0,1,1,0,1,0,
        };
        int b[2] = {2,2};

        int box[8];
        inform_black_box(series, 2, 1, 8, b, NULL, NULL, box, &err);
        assert(!err);
        print_series(box, 1, 8);
        // 1 2 2 1 3 0 1 2 
    }
    printf("\n");

    {
        inform_error err = INFORM_SUCCESS;
        int const series[8] = {
            0,1,1,0,1,0,0,1,
        };
        int b = 2;

        size_t r = 2;
        int box[7];
        inform_black_box(series, 1, 1, 8, &b, &r, NULL, box, &err);
        assert(!err);
        print_series(box, 1, 7);
        // 1 3 2 1 2 0 1 
    }
    printf("\n");

    {
        inform_error err = INFORM_SUCCESS;
        int const series[16] = {
            0,1,1,0,1,0,0,1,
            1,0,0,1,1,0,1,0,
        };
        int b[2] = {2,2};

        size_t r[2] = {2,1};
        size_t s[2] = {0,1};
        int box[6];
        inform_black_box(series, 2, 1, 8, b, r, s, box, &err);
        assert(!err);
        print_series(box, 1, 6);
        // 4 13 11 6 9 2 
    }
    printf("\n");

    {
        inform_error err = INFORM_SUCCESS;
        int const series[32] = {
            0,1,1,0,1,0,0,1,
            1,0,0,1,1,0,1,0,
            0,0,0,1,1,1,0,0,
            1,0,1,0,1,1,1,0,
        };
        int b[4] = {2,2,2,2};

        size_t parts[4] = {0,0,0,0};
        size_t nparts = 1; // max(parts) + 1
        int *box = inform_black_box_parts(series, 4, 8, b, parts, nparts, NULL, &err);
        assert(!err);
        print_series(box, nparts, 8);
        // 5 8 9 6 15 3 5 8
        print_series(box + 8, nparts, nparts);
        // 16
        free(box);
    }
    printf("\n");

    {
        inform_error err = INFORM_SUCCESS;
        int const series[32] = {
            0,1,1,0,1,0,0,1,
            1,0,0,1,1,0,1,0,
            0,0,0,1,1,1,0,0,
            1,0,1,0,1,1,1,0,
        };
        int b[4] = {2,2,2,2};

        size_t parts[4] = {0,1,1,0};
        size_t nparts = 2; // max(parts) + 1
        int *box = inform_black_box_parts(series, 4, 8, b, parts, nparts, NULL, &err);
        assert(!err);
        print_series(box, nparts, 8);
        // 1 2 3 0 3 1 1 2
        // 2 0 0 3 3 1 2 0 
        print_series(box+16, 1, nparts);
        // 4 4
        free(box);
    }
    printf("\n");

    {
        #define L 4
        #define N 8

        inform_error err = INFORM_SUCCESS;
        int const series[L*N] = {
            0,1,1,0,1,0,0,1,
            1,0,0,1,1,0,1,0,
            0,0,0,1,1,1,0,0,
            1,0,1,0,1,1,1,0,
        };
        int b[L] = {2,2,2,2};

        int box[L + L*N];

        size_t *parts = inform_first_partitioning(L);
        size_t nparts = 1;
        while((nparts = inform_next_partitioning(parts, L)))
        {
            inform_black_box_parts(series, L, N, b, parts, nparts, box, &err);
            assert(!err);

            int *bases = box + N*nparts;
            double mi = inform_mutual_info(box, nparts, N, bases, &err);
            assert(!err);
            printf("%0.3lf ", mi);
        }
        printf("\n");
    }
    printf("\n");
}
