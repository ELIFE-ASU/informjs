// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <ginger/unit.h>

#include <inform/shannon.h>
#include <inform/utilities/random.h>
#include "../util.h"

UNIT(ShannonMultiPointwiseMutualInformationIndependent)
{
    inform_dist *xs = inform_dist_alloc(12);
    inform_dist_fill(xs, 5, 2, 3, 5, 1, 4, 6, 2, 1, 4, 2, 4);

    inform_dist *ys = inform_dist_alloc(12);
    inform_dist_fill(ys, 2, 4, 5, 2, 7, 3, 9, 8, 8, 7, 2, 3);

    inform_dist *zs = inform_dist_alloc(12);
    inform_dist_fill(zs, 3, 8, 1, 4, 5, 8, 8, 8, 2, 1, 1, 0);

    inform_dist *dist = inform_dist_alloc(1728);
    for (size_t i = 0; i < inform_dist_size(xs); ++i)
    {
        for (size_t j = 0; j < inform_dist_size(ys); ++j)
        {
            for (size_t k = 0; k < inform_dist_size(zs); ++k)
            {
                inform_dist_set(dist, k + 12 * (j + 12 * i),
                    inform_dist_get(xs, i) * inform_dist_get(ys, j) * inform_dist_get(zs, k));
            }
        }
    }

    for (size_t i = 0; i < inform_dist_size(xs); ++i)
    {
        for (size_t j = 0; j < inform_dist_size(ys); ++j)
        {
            for (size_t k = 0; k < inform_dist_size(zs); ++k)
            {
                size_t joint_event = k+12*(j+12*i);
                double expect = inform_dist_prob(dist, joint_event) ? 0 : NAN;
                ASSERT_DBL_NEAR_TOL(expect,
                    inform_shannon_multi_pmi(dist,
                        (inform_dist const *[3]){xs, ys, zs}, 3,
                        joint_event, (size_t[3]){i, j, k}, 0.5),
                    1e-6);
                ASSERT_DBL_NEAR_TOL(expect,
                    inform_shannon_multi_pmi(dist,
                        (inform_dist const *[3]){xs, ys, zs}, 3,
                        joint_event, (size_t[3]){i, j, k}, 2),
                    1e-6);
                ASSERT_DBL_NEAR_TOL(expect,
                    inform_shannon_multi_pmi(dist,
                        (inform_dist const *[3]){xs, ys, zs}, 3,
                        joint_event, (size_t[3]){i, j, k}, 3),
                    1e-6);
            }
        }
    }

    inform_dist_free(dist);
    inform_dist_free(zs);
    inform_dist_free(ys);
    inform_dist_free(xs);
}

UNIT(ShannonMultiPointwiseMutualInformationDependent)
{
    inform_dist *dist = inform_dist_alloc(8);
    inform_dist_fill(dist, 4, 6, 28, 42, 6, 9, 2, 3);

    inform_dist *xs = inform_dist_alloc(2);
    inform_dist_fill(xs, 80, 20);

    inform_dist *ys = inform_dist_alloc(2);
    inform_dist_fill(ys, 25, 75);

    inform_dist *zs = inform_dist_alloc(2);
    inform_dist_fill(zs, 40, 60);

    inform_dist const *marginals[3] = {xs, ys, zs};

    ASSERT_DBL_NEAR_TOL(-1.000000,
        inform_shannon_multi_pmi(dist, marginals, 3, 0, (size_t[]){0, 0, 0}, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(-1.000000,
        inform_shannon_multi_pmi(dist, marginals, 3, 1, (size_t[]){0, 0, 1}, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.222392,
        inform_shannon_multi_pmi(dist, marginals, 3, 2, (size_t[]){0, 1, 0}, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.222392,
        inform_shannon_multi_pmi(dist, marginals, 3, 3, (size_t[]){0, 1, 1}, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(1.584963,
        inform_shannon_multi_pmi(dist, marginals, 3, 4, (size_t[]){1, 0, 0}, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(1.584963,
        inform_shannon_multi_pmi(dist, marginals, 3, 5, (size_t[]){1, 0, 1}, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(-1.584963,
        inform_shannon_multi_pmi(dist, marginals, 3, 6, (size_t[]){1, 1, 0}, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(-1.584963,
        inform_shannon_multi_pmi(dist, marginals, 3, 7, (size_t[]){1, 1, 1}, 2), 1e-6);

    inform_dist_free(zs);
    inform_dist_free(ys);
    inform_dist_free(xs);
    inform_dist_free(dist);
}

UNIT(ShannonMultiMutualInformationIndependent)
{
    inform_dist *xs = inform_dist_alloc(12);
    inform_dist_fill(xs, 5, 2, 3, 5, 1, 4, 6, 2, 1, 4, 2, 4);

    inform_dist *ys = inform_dist_alloc(12);
    inform_dist_fill(ys, 2, 4, 5, 2, 7, 3, 9, 8, 8, 7, 2, 3);

    inform_dist *zs = inform_dist_alloc(12);
    inform_dist_fill(zs, 3, 8, 1, 4, 5, 8, 8, 8, 2, 1, 1, 0);

    inform_dist *dist = inform_dist_alloc(1728);
    for (size_t i = 0; i < inform_dist_size(xs); ++i)
    {
        for (size_t j = 0; j < inform_dist_size(ys); ++j)
        {
            for (size_t k = 0; k < inform_dist_size(zs); ++k)
            {
                inform_dist_set(dist, k + 12 * (j + 12 * i),
                    inform_dist_get(xs, i) * inform_dist_get(ys, j) * inform_dist_get(zs, k));
            }
        }
    }

    inform_dist const *marginals[] = {xs, ys, zs};
    ASSERT_DBL_NEAR_TOL(0.0, inform_shannon_multi_mi(dist, marginals, 3, 0.5), 1e-10);
    ASSERT_DBL_NEAR_TOL(0.0, inform_shannon_multi_mi(dist, marginals, 3, 2), 1e-10);
    ASSERT_DBL_NEAR_TOL(0.0, inform_shannon_multi_mi(dist, marginals, 3, 3), 1e-10);

    inform_dist_free(dist);
    inform_dist_free(zs);
    inform_dist_free(ys);
    inform_dist_free(xs);
}

UNIT(ShannonMultiMutualInformationDependent)
{
    inform_dist *dist = inform_dist_alloc(8);
    inform_dist_fill(dist, 4, 6, 28, 42, 6, 9, 2, 3);

    inform_dist *xs = inform_dist_alloc(2);
    inform_dist_fill(xs, 80, 20);

    inform_dist *ys = inform_dist_alloc(2);
    inform_dist_fill(ys, 25, 75);

    inform_dist *zs = inform_dist_alloc(2);
    inform_dist_fill(zs, 40, 60);

    inform_dist const *marginals[3] = {xs, ys, zs};
    ASSERT_DBL_NEAR_TOL(0.214170, inform_shannon_multi_mi(dist, marginals, 3, 2), 1e-6);

    inform_dist_free(zs);
    inform_dist_free(ys);
    inform_dist_free(xs);
    inform_dist_free(dist);
}

BEGIN_SUITE(ShannonMulti)
    ADD_UNIT(ShannonMultiPointwiseMutualInformationIndependent)
    ADD_UNIT(ShannonMultiPointwiseMutualInformationDependent)
    ADD_UNIT(ShannonMultiMutualInformationIndependent)
    ADD_UNIT(ShannonMultiMutualInformationDependent)
END_SUITE
