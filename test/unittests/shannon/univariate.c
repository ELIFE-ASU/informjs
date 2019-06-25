// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <ginger/unit.h>

#include <inform/shannon.h>
#include <inform/utilities/random.h>
#include "../util.h"

UNIT(ShannonUniInvalidDistribution)
{
    inform_dist *dist = NULL;
    ASSERT_NAN(inform_shannon_entropy(dist, 2));

    dist = inform_dist_alloc(5);
    ASSERT_NAN(inform_shannon_entropy(dist, 2));
    inform_dist_free(dist);
}

UNIT(ShannonUniDeltaFunction)
{
    inform_dist *dist = inform_dist_alloc(5);
    inform_dist_fill(dist, 0, 1, 0, 0, 0);
    ASSERT_NAN(inform_shannon_entropy(dist, -1.0));
    ASSERT_NAN(inform_shannon_entropy(dist, -0.5));
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_entropy(dist, 0.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_entropy(dist, 0.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_entropy(dist, 1.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_entropy(dist, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_entropy(dist, 3), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_entropy(dist, 4), 1e-6);
    inform_dist_free(dist);
}

UNIT(ShannonUniUniform)
{
    inform_dist *dist = inform_dist_alloc(5);
    inform_dist_fill(dist, 1, 1, 1, 1, 1);

    ASSERT_NAN(inform_shannon_entropy(dist, -1.0));
    ASSERT_NAN(inform_shannon_entropy(dist, -0.5));
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_entropy(dist, 0.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(-2.321928, inform_shannon_entropy(dist, 0.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(3.969362, inform_shannon_entropy(dist, 1.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(2.321928, inform_shannon_entropy(dist, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(1.464973, inform_shannon_entropy(dist, 3), 1e-6);
    ASSERT_DBL_NEAR_TOL(1.160964, inform_shannon_entropy(dist, 4), 1e-6);
    inform_dist_free(dist);
}

UNIT(ShannonUniNonUniform)
{
    inform_dist *dist = inform_dist_alloc(2);
    inform_dist_fill(dist, 2, 1);

    ASSERT_NAN(inform_shannon_entropy(dist, -1.0));
    ASSERT_NAN(inform_shannon_entropy(dist, -0.5));
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_entropy(dist, 0.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(-0.918295, inform_shannon_entropy(dist, 0.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(1.569837, inform_shannon_entropy(dist, 1.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.918295, inform_shannon_entropy(dist, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.579380, inform_shannon_entropy(dist, 3), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.459148, inform_shannon_entropy(dist, 4), 1e-6);

    dist = inform_dist_realloc(dist, 3);
    inform_dist_fill(dist, 1, 1, 0);

    ASSERT_NAN(inform_shannon_entropy(dist, -1.0));
    ASSERT_NAN(inform_shannon_entropy(dist, -0.5));
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_entropy(dist, 0.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(-1.000000, inform_shannon_entropy(dist, 0.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(1.709511, inform_shannon_entropy(dist, 1.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(1.000000, inform_shannon_entropy(dist, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.630930, inform_shannon_entropy(dist, 3), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.500000, inform_shannon_entropy(dist, 4), 1e-6);

    inform_dist_fill(dist, 2, 2, 1);
    ASSERT_DBL_NEAR_TOL(1.521928, inform_shannon_entropy(dist, 2), 1e-6);

    ASSERT_NAN(inform_shannon_entropy(dist, -1.0));
    ASSERT_NAN(inform_shannon_entropy(dist, -0.5));
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_entropy(dist, 0.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(-1.521928, inform_shannon_entropy(dist, 0.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(2.601753, inform_shannon_entropy(dist, 1.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(1.521928, inform_shannon_entropy(dist, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.960230, inform_shannon_entropy(dist, 3), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.760964, inform_shannon_entropy(dist, 4), 1e-6);

    inform_dist_free(dist);
}

UNIT(ShannonUniMutualInformationIndependent)
{

    inform_dist *xs = inform_dist_alloc(12);
    inform_dist_fill(xs, 5, 2, 3, 5, 1, 4, 6, 2, 1, 4, 2, 4);

    inform_dist *ys = inform_dist_alloc(12);
    inform_dist_fill(ys, 2, 4, 5, 2, 7, 3, 9, 8, 8, 7, 2, 3);

    inform_dist *dist = inform_dist_alloc(144);
    for (size_t i = 0; i < inform_dist_size(xs); ++i)
    {
        for (size_t j = 0; j < inform_dist_size(ys); ++j)
        {
            inform_dist_set(dist, j+i*12,
                    inform_dist_get(xs, i) * inform_dist_get(ys, j));
        }
    }
    ASSERT_NAN(inform_shannon_mi(dist, xs, ys, -1.0));
    ASSERT_NAN(inform_shannon_mi(dist, xs, ys, -0.5));
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_mi(dist, xs, ys, 0.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_mi(dist, xs, ys, 0.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_mi(dist, xs, ys, 1.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_mi(dist, xs, ys, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_mi(dist, xs, ys, 3), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_mi(dist, xs, ys, 4), 1e-6);
    inform_dist_free(dist);
    inform_dist_free(ys);
    inform_dist_free(xs);
}

UNIT(ShannonUniMutualInformationDependent)
{
    inform_dist *dist = inform_dist_alloc(4);
    inform_dist_fill(dist, 10, 70, 15, 5);

    inform_dist *xs = inform_dist_alloc(2);
    inform_dist_fill(xs, 80, 20);

    inform_dist *ys = inform_dist_alloc(2);
    inform_dist_fill(ys, 25, 75);

    ASSERT_NAN(inform_shannon_mi(dist, xs, ys, -1.0));
    ASSERT_NAN(inform_shannon_mi(dist, xs, ys, -0.5));
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_mi(dist, xs, ys, 0.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(-0.214171, inform_shannon_mi(dist, xs, ys, 0.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.366128, inform_shannon_mi(dist, xs, ys, 1.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.214171, inform_shannon_mi(dist, xs, ys, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.135127, inform_shannon_mi(dist, xs, ys, 3), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.107086, inform_shannon_mi(dist, xs, ys, 4), 1e-6);
    inform_dist_free(ys);
    inform_dist_free(xs);
    inform_dist_free(dist);
}

UNIT(ShannonUniSelfInformationInvalidDist)
{
    inform_dist *dist = NULL;
    ASSERT_NAN(inform_shannon_si(dist, 0, 2));
}

UNIT(ShannonUniSelfInformationImposibleEvent)
{
    inform_dist *dist = inform_dist_alloc(2);
    inform_dist_fill(dist, 1, 0);
    ASSERT_NOT_INF(inform_shannon_si(dist, 0, 2));
    ASSERT_INF(inform_shannon_si(dist, 2, 2));
    inform_dist_free(dist);
}

UNIT(ShannonUniSelfInformationBase2)
{
    inform_dist *dist = inform_dist_alloc(2);
    inform_dist_fill(dist, 1, 1);
    ASSERT_DBL_NEAR_TOL(1.000000, inform_shannon_si(dist, 0, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(1.000000, inform_shannon_si(dist, 1, 2), 1e-6);

    inform_dist_fill(dist, 2, 1);
    ASSERT_DBL_NEAR_TOL(0.584963, inform_shannon_si(dist, 0, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(1.584963, inform_shannon_si(dist, 1, 2), 1e-6);

    inform_dist_fill(dist, 2, 0);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_si(dist, 0, 2), 1e-6);
    ASSERT_INF(inform_shannon_si(dist, 1, 2));

    inform_dist_free(dist);
}

UNIT(ShannonUniSelfInformationBase3)
{
    inform_dist *dist = inform_dist_alloc(3);
    inform_dist_fill(dist, 1, 2, 3);
    ASSERT_DBL_NEAR_TOL(1.630930, inform_shannon_si(dist, 0, 3), 1e-6);
    ASSERT_DBL_NEAR_TOL(1.000000, inform_shannon_si(dist, 1, 3), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.630930, inform_shannon_si(dist, 2, 3), 1e-6);
    inform_dist_free(dist);
}

UNIT(ShannonUniPointwiseMutualInformationIndependent)
{

    inform_dist *xs = inform_dist_alloc(12);
    inform_dist_fill(xs, 5, 2, 3, 5, 1, 4, 6, 2, 1, 4, 2, 4);

    inform_dist *ys = inform_dist_alloc(12);
    inform_dist_fill(ys, 2, 4, 5, 2, 7, 3, 9, 8, 8, 7, 2, 3);

    inform_dist *dist = inform_dist_alloc(144);
    for (size_t i = 0; i < inform_dist_size(xs); ++i)
    {
        for (size_t j = 0; j < inform_dist_size(ys); ++j)
        {
            inform_dist_set(dist, j+i*12,
                    inform_dist_get(xs, i) * inform_dist_get(ys, j));
        }
    }

    for (size_t i = 0; i < inform_dist_size(xs); ++i)
    {
        for (size_t j = 0; j < inform_dist_size(ys); ++j)
        {
            ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_pmi(dist, xs, ys, j+i*12, i, j, 0.5), 1e-6);
            ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_pmi(dist, xs, ys, j+i*12, i, j, 2), 1e-6);
            ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_pmi(dist, xs, ys, j+i*12, i, j, 3), 1e-6);
        }
    }

    inform_dist_free(dist);
    inform_dist_free(ys);
    inform_dist_free(xs);
}

UNIT(ShannonUniPointwiseMutualInformationDependent)
{
    inform_dist *dist = inform_dist_alloc(4);
    inform_dist_fill(dist, 10, 70, 15, 5);

    inform_dist *xs = inform_dist_alloc(2);
    inform_dist_fill(xs, 80, 20);

    inform_dist *ys = inform_dist_alloc(2);
    inform_dist_fill(ys, 25, 75);

    ASSERT_DBL_NEAR_TOL(-1.000000, inform_shannon_pmi(dist, xs, ys, 0, 0, 0, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL( 0.222392, inform_shannon_pmi(dist, xs, ys, 1, 0, 1, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL( 1.584963, inform_shannon_pmi(dist, xs, ys, 2, 1, 0, 2), 1e-6);
    ASSERT_DBL_NEAR_TOL(-1.584963, inform_shannon_pmi(dist, xs, ys, 3, 1, 1, 2), 1e-6);

    inform_dist_free(ys);
    inform_dist_free(xs);
    inform_dist_free(dist);
}

UNIT(ShannonUniRelativeEntropyInvalidDistributions)
{
    inform_dist *p = NULL, *q = NULL;
    ASSERT_NAN(inform_shannon_re(p, q, 2));

    p = inform_dist_alloc(5);
    ASSERT_NAN(inform_shannon_re(p, q, 2));
    ASSERT_NAN(inform_shannon_re(q, p, 2));

    inform_dist_tick(p, 0);
    ASSERT_NAN(inform_shannon_re(p, q, 2));
    ASSERT_NAN(inform_shannon_re(q, p, 2));

    q = inform_dist_alloc(5);
    ASSERT_NAN(inform_shannon_re(p, q, 2));
    ASSERT_NAN(inform_shannon_re(q, p, 2));

    inform_dist_free(q);
    inform_dist_free(p);
}

UNIT(ShannonUniRelativeEntropyIncompatibleSizes)
{
    inform_dist *p = inform_dist_alloc(5);
    inform_dist *q = inform_dist_alloc(4);

    inform_dist_tick(p, 0);
    inform_dist_tick(q, 1);

    ASSERT_NAN(inform_shannon_re(p, q, 2));
    ASSERT_NAN(inform_shannon_re(q, p, 2));

    inform_dist_free(q);
    inform_dist_free(p);
}

UNIT(ShannonUniRelativeEntropyUndefined)
{
    inform_dist *p = inform_dist_alloc(5);
    inform_dist *q = inform_dist_alloc(5);
    inform_dist_fill(p, 1, 1, 1, 1, 1);
    inform_dist_fill(q, 1, 1, 1, 2, 0);

    ASSERT_NAN(inform_shannon_re(p, q, 2));
    ASSERT_NOT_NAN(inform_shannon_re(q, p, 2));

    inform_dist_free(q);
    inform_dist_free(p);
}

UNIT(ShannonUniRelativeEntropySameDist)
{
    inform_dist *p = inform_dist_alloc(20);
    for (size_t i = 0; i < inform_dist_size(p); ++i)
        inform_dist_set(p, i, inform_random_int(0, 100));
    ASSERT_NAN(inform_shannon_re(p, p, -1.0));
    ASSERT_NAN(inform_shannon_re(p, p, -0.5));
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_re(p, p, 0.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_re(p, p, 0.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_re(p, p, 1.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_re(p, p, 2.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_re(p, p, 3.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(0.000000, inform_shannon_re(p, p, 4.0), 1e-6);
    inform_dist_free(p);
}

UNIT(ShannonUniRelativeEntropyDefined)
{
    inform_dist *p = inform_dist_alloc(3);
    inform_dist *q = inform_dist_alloc(3);

    inform_dist_fill(p, 1, 0, 0);
    inform_dist_fill(q, 1, 1, 1);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        ASSERT_DBL_NEAR(log2(3)/log2(b), inform_shannon_re(p, q, b));
    }

    inform_dist_fill(p, 1, 1, 0);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        ASSERT_DBL_NEAR(log2(3.0/2.0)/log2(b), inform_shannon_re(p, q, b));
    }

    inform_dist_fill(p, 2, 2, 1);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        ASSERT_DBL_NEAR_TOL((4*log2(6./5.) + log2(3./5.))/(5 * log2(b)), inform_shannon_re(p, q, b), 5e-16);
    }

    inform_dist_fill(q, 1, 2, 2);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        ASSERT_DBL_NEAR(1.0/(5.0*log2(b)), inform_shannon_re(p, q, b));
    }

    inform_dist_fill(p, 1, 0, 1);
    inform_dist_fill(q, 2, 1, 2);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        ASSERT_DBL_NEAR(log2(5.0/4.0)/log2(b), inform_shannon_re(p, q, b));
    }

    inform_dist_fill(p, 1, 0, 0);
    inform_dist_fill(q, 4, 1, 0);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        ASSERT_DBL_NEAR(log2(5.0/4.0)/log2(b), inform_shannon_re(p, q, b));
    }

    inform_dist_fill(p, 1, 0, 0);
    inform_dist_fill(q, 1, 4, 0);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        ASSERT_DBL_NEAR(log2(5.0)/log2(b), inform_shannon_re(p, q, b));
    }

    inform_dist_free(q);
    inform_dist_free(p);
}

UNIT(ShannonUniCrossEntropyInvalidDistributions)
{
    inform_dist *p = NULL, *q = NULL;
    ASSERT_NAN(inform_shannon_cross(p, q, 2));

    p = inform_dist_alloc(5);
    ASSERT_NAN(inform_shannon_cross(p, q, 2));
    ASSERT_NAN(inform_shannon_cross(q, p, 2));

    inform_dist_tick(p, 0);
    ASSERT_NAN(inform_shannon_cross(p, q, 2));
    ASSERT_NAN(inform_shannon_cross(q, p, 2));

    q = inform_dist_alloc(5);
    ASSERT_NAN(inform_shannon_cross(p, q, 2));
    ASSERT_NAN(inform_shannon_cross(q, p, 2));

    inform_dist_free(q);
    inform_dist_free(p);
}

UNIT(ShannonUniCrossEntropyIncompatibleSizes)
{
    inform_dist *p = inform_dist_alloc(5);
    inform_dist *q = inform_dist_alloc(4);

    inform_dist_tick(p, 0);
    inform_dist_tick(q, 1);

    ASSERT_NAN(inform_shannon_cross(p, q, 2));
    ASSERT_NAN(inform_shannon_cross(q, p, 2));

    inform_dist_free(q);
    inform_dist_free(p);
}

UNIT(ShannonUniCrossEntropyUndefined)
{
    inform_dist *p = inform_dist_alloc(5);
    inform_dist *q = inform_dist_alloc(5);
    inform_dist_fill(p, 1, 1, 1, 1, 1);
    inform_dist_fill(q, 1, 1, 1, 2, 0);

    ASSERT_INF(inform_shannon_cross(p, q, 2));
    ASSERT_NOT_NAN(inform_shannon_cross(q, p, 2));
    ASSERT_NOT_INF(inform_shannon_cross(q, p, 2));

    inform_dist_free(q);
    inform_dist_free(p);
}

UNIT(ShannonUniCrossEntropySameDist)
{
    inform_dist *p = inform_dist_alloc(20);
    for (size_t i = 0; i < inform_dist_size(p); ++i)
        inform_dist_set(p, i, inform_random_int(0, 100));
    ASSERT_NAN(inform_shannon_cross(p, p, -1.0));
    ASSERT_NAN(inform_shannon_cross(p, p, -0.5));
    ASSERT_DBL_NEAR_TOL(inform_shannon_entropy(p, 0.0), inform_shannon_cross(p, p, 0.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(inform_shannon_entropy(p, 0.5), inform_shannon_cross(p, p, 0.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(inform_shannon_entropy(p, 1.5), inform_shannon_cross(p, p, 1.5), 1e-6);
    ASSERT_DBL_NEAR_TOL(inform_shannon_entropy(p, 2.0), inform_shannon_cross(p, p, 2.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(inform_shannon_entropy(p, 3.0), inform_shannon_cross(p, p, 3.0), 1e-6);
    ASSERT_DBL_NEAR_TOL(inform_shannon_entropy(p, 4.0), inform_shannon_cross(p, p, 4.0), 1e-6);
    inform_dist_free(p);
}

UNIT(ShannonUniCrossEntropyDefined)
{
    inform_dist *p = inform_dist_alloc(3);
    inform_dist *q = inform_dist_alloc(3);

    inform_dist_fill(p, 1, 0, 0);
    inform_dist_fill(q, 2, 1, 1);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        double got = inform_shannon_cross(p, q, b);
        ASSERT_NOT_NAN(got);
        ASSERT_DBL_NEAR(1/log2(b), got);
    }

    inform_dist_fill(p, 1, 1, 0);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        double got = inform_shannon_cross(p, q, b);
        ASSERT_NOT_NAN(got);
        ASSERT_DBL_NEAR(3/(2*log2(b)), got);
    }

    inform_dist_fill(p, 2, 2, 1);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        double got = inform_shannon_cross(p, q, b);
        ASSERT_NOT_NAN(got);
        ASSERT_DBL_NEAR(8/(5*log2(b)), got);
    }

    inform_dist_fill(q, 1, 2, 2);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        double got = inform_shannon_cross(p, q, b);
        ASSERT_NOT_NAN(got);
        ASSERT_DBL_NEAR(((5*log2(5)-3)/(5*log2(b))), got);
    }

    inform_dist_fill(p, 1, 0, 1);
    inform_dist_fill(q, 2, 1, 2);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        double got = inform_shannon_cross(p, q, b);
        ASSERT_NOT_NAN(got);
        ASSERT_DBL_NEAR((log2(5)-1)/log2(b), got);
    }

    inform_dist_fill(p, 1, 0, 0);
    inform_dist_fill(q, 4, 1, 0);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        double got = inform_shannon_cross(p, q, b);
        ASSERT_NOT_NAN(got);
        ASSERT_DBL_NEAR((log2(5)-2)/log2(b), got);
    }

    inform_dist_fill(p, 1, 0, 0);
    inform_dist_fill(q, 1, 4, 0);
    for (double b = 0.0; b <= 4.0; b += 0.5)
    {
        double got = inform_shannon_cross(p, q, b);
        ASSERT_NOT_NAN(got);
        ASSERT_DBL_NEAR(log2(5.0)/log2(b), got);
    }

    inform_dist_free(q);
    inform_dist_free(p);
}

BEGIN_SUITE(ShannonUni)
    ADD_UNIT(ShannonUniInvalidDistribution)
    ADD_UNIT(ShannonUniDeltaFunction)
    ADD_UNIT(ShannonUniUniform)
    ADD_UNIT(ShannonUniNonUniform)

    ADD_UNIT(ShannonUniMutualInformationIndependent)
    ADD_UNIT(ShannonUniMutualInformationDependent)

    ADD_UNIT(ShannonUniSelfInformationInvalidDist)
    ADD_UNIT(ShannonUniSelfInformationImposibleEvent)
    ADD_UNIT(ShannonUniSelfInformationBase2)
    ADD_UNIT(ShannonUniSelfInformationBase3)

    ADD_UNIT(ShannonUniPointwiseMutualInformationIndependent)
    ADD_UNIT(ShannonUniPointwiseMutualInformationDependent)

    ADD_UNIT(ShannonUniRelativeEntropyInvalidDistributions)
    ADD_UNIT(ShannonUniRelativeEntropyIncompatibleSizes)
    ADD_UNIT(ShannonUniRelativeEntropyUndefined)
    ADD_UNIT(ShannonUniRelativeEntropySameDist)
    ADD_UNIT(ShannonUniRelativeEntropyDefined)

    ADD_UNIT(ShannonUniCrossEntropyInvalidDistributions)
    ADD_UNIT(ShannonUniCrossEntropyIncompatibleSizes)
    ADD_UNIT(ShannonUniCrossEntropyUndefined)
    ADD_UNIT(ShannonUniCrossEntropySameDist)
    ADD_UNIT(ShannonUniCrossEntropyDefined)
END_SUITE
