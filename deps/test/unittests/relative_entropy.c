// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/relative_entropy.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(RelativeEntropyNULLSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_relative_entropy(NULL, NULL, 3, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_relative_entropy((int[]){0,0,1}, NULL, 3, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(RelativeEntropySeriesTooShort)
{
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_relative_entropy(xs, xs, 0, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(RelativeEntropyInvalidBase)
{
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_relative_entropy(xs, xs, 8, i, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(RelativeEntropyNegativeState)
{
    int const xs[] = {1,1,0,0,-1,0,0,1};
    int const ys[] = {1,1,0,0, 1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_relative_entropy(xs, ys, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_relative_entropy(ys, xs, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(RelativeEntropyBadState)
{
    int const xs[] = {1,2,0,0,1,0,0,1};
    int const ys[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_relative_entropy(xs, ys, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_relative_entropy(xs, ys, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(RelativeEntropy)
{
    inform_error err = INFORM_SUCCESS;

    ASSERT_DBL_NEAR_TOL(0.038330, inform_relative_entropy((int[]){0,0,1,1,1,1,0,0,0},
        (int[]){1,0,0,1,0,0,1,0,0}, 9, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.037010, inform_relative_entropy((int[]){1,0,0,1,0,0,1,0,0},
        (int[]){0,0,1,1,1,1,0,0,0}, 9, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.000000, inform_relative_entropy((int[]){0,0,0,0,1,1,1,1},
        (int[]){1,1,1,1,0,0,0,0}, 8, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.035770, inform_relative_entropy((int[]){0,0,1,1,1,1,0,0,0},
        (int[]){1,1,0,0,0,0,1,1,1}, 9, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.037010, inform_relative_entropy((int[]){1,1,0,1,0,1,1,1,0},
        (int[]){1,1,0,0,0,1,0,1,1}, 9, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(1.584963, inform_relative_entropy((int[]){0,0,0,0,0,0,0,0,0},
        (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.038331, inform_relative_entropy((int[]){1,1,1,1,0,0,0,0,1},
        (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.038331, inform_relative_entropy((int[]){1,1,0,0,1,1,0,0,1},
        (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_NAN(inform_relative_entropy((int[]){0,1,0,1,0,1,0,1},
        (int[]){0,2,0,2,0,2,0,2}, 8, 3, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.584963,
        inform_relative_entropy((int[]){0,0,0,0,0,0,1,1,1,1,1,1},
            (int[]){0,0,0,0,1,1,1,1,2,2,2,2}, 12, 3, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_NAN(inform_relative_entropy((int[]){0,0,1,1,2,1,1,0,0},
        (int[]){0,0,0,1,1,1,0,0,0}, 9, 3, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.000000, inform_relative_entropy((int[]){0,1,0,0,1,0,0,1,0},
        (int[]){1,0,0,1,0,0,1,0,0}, 9, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.679964, inform_relative_entropy((int[]){1,0,0,1,0,0,1,0},
        (int[]){2,0,1,2,0,1,2,0}, 8, 3, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
}

UNIT(LocalRelativeEntropyNULLSeries)
{
    double re[8];
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_relative_entropy(NULL, NULL, 3, 2, re, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_relative_entropy((int[]){0,0,1}, NULL, 3, 2, re, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(LocalRelativeEntropySeriesTooShort)
{
    double re[8];
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_relative_entropy(xs, xs, 0, 2, re, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(LocalRelativeEntropyInvalidBase)
{
    double re[8];
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_relative_entropy(xs, xs, 8, i, re, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(LocalRelativeEntropyNegativeState)
{
    double re[8];
    int const xs[] = {1,1,0,0,-1,0,0,1};
    int const ys[] = {1,1,0,0, 1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_relative_entropy(xs, ys, 8, 2, re, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_relative_entropy(ys, xs, 8, 2, re, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(LocalRelativeEntropyBadState)
{
    double re[8];
    int const xs[] = {1,2,0,0,1,0,0,1};
    int const ys[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_relative_entropy(xs, ys, 8, 2, re, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_relative_entropy(xs, ys, 8, 2, re, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(LocalRelativeEntropyAllocatesOutput)
{
    int const xs[] = {0,0,1,1,1,1,0,0,0};
    int const ys[] = {1,1,0,0,0,0,1,1,1};
    inform_error err = INFORM_SUCCESS;
    double *re = inform_local_relative_entropy(xs, ys, 9, 2, NULL, &err);
    ASSERT_NOT_NULL(re);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    free(re);
}

UNIT(LocalRelativeEntropy)
{
    inform_error err = INFORM_SUCCESS;
    double re_2[2];
    double re_3[3];

    inform_local_relative_entropy((int[]){0,0,1,1,1,1,0,0,0}, (int[]){1,0,0,1,0,0,1,0,0}, 9, 2, re_2, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){-0.263034, 0.415037}), re_2, 2, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){1,0,0,1,0,0,1,0,0}, (int[]){0,0,1,1,1,1,0,0,0}, 9, 2, re_2, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){0.263034, -0.415037}), re_2, 2, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){0,0,0,0,1,1,1,1}, (int[]){1,1,1,1,0,0,0,0}, 8, 2, re_2, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){0.000000, 0.000000}), re_2, 2, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){0,0,1,1,1,1,0,0,0}, (int[]){1,1,0,0,0,0,1,1,1}, 9, 2, re_2, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){0.321928, -0.321928}), re_2, 2, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){1,1,0,1,0,1,1,1,0}, (int[]){1,1,0,0,0,1,0,1,1}, 9, 2, re_2, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){-0.415037, 0.263034}), re_2, 2, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){0,0,0,0,0,0,0,0,0}, (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, re_2, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){1.584963, -INFINITY}), re_2, 2, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){1,1,1,1,0,0,0,0,1}, (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, re_2, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){0.415037, -0.263034}), re_2, 2, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){1,1,0,0,1,1,0,0,1}, (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, re_2, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){0.415037, -0.263034}), re_2, 2, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){0,1,0,1,0,1,0,1}, (int[]){0,2,0,2,0,2,0,2}, 8, 3, re_3, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){0.000000, INFINITY, -INFINITY}), re_3, 3, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){0,0,0,0,0,0,1,1,1,1,1,1}, (int[]){0,0,0,0,1,1,1,1,2,2,2,2}, 12, 3, re_3, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){0.584963, 0.584963, -INFINITY}), re_3, 3, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){0,0,1,1,2,1,1,0,0}, (int[]){0,0,0,1,1,1,0,0,0}, 9, 3, re_3, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){-0.584963, 0.415037, INFINITY}), re_3, 3, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){0,1,0,0,1,0,0,1,0}, (int[]){1,0,0,1,0,0,1,0,0}, 9, 2, re_2, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){0.000000, 0.000000, -INFINITY}), re_2, 2, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_relative_entropy((int[]){1,0,0,1,0,0,1,0}, (int[]){2,0,1,2,0,1,2,0}, 8, 3, re_3, &err);
    ASSERT_DBL_ARRAY_NEAR_TOL(((double[]){0.736966, 0.584963, -INFINITY}), re_3, 3, 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
}

BEGIN_SUITE(RelativeEntropy)
    ADD_UNIT(RelativeEntropyNULLSeries)
    ADD_UNIT(RelativeEntropySeriesTooShort)
    ADD_UNIT(RelativeEntropyInvalidBase)
    ADD_UNIT(RelativeEntropyNegativeState)
    ADD_UNIT(RelativeEntropyBadState)
    ADD_UNIT(RelativeEntropy)
    ADD_UNIT(LocalRelativeEntropyNULLSeries)
    ADD_UNIT(LocalRelativeEntropySeriesTooShort)
    ADD_UNIT(LocalRelativeEntropyInvalidBase)
    ADD_UNIT(LocalRelativeEntropyNegativeState)
    ADD_UNIT(LocalRelativeEntropyBadState)
    ADD_UNIT(LocalRelativeEntropyAllocatesOutput)
    ADD_UNIT(LocalRelativeEntropy)
END_SUITE
