// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/cross_entropy.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(CrossEntropyNULLSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_cross_entropy(NULL, NULL, 3, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_cross_entropy((int[]){0,0,1}, NULL, 3, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(CrossEntropySeriesTooShort)
{
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_cross_entropy(xs, xs, 0, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(CrossEntropyInvalidBase)
{
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_cross_entropy(xs, xs, 8, i, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(CrossEntropyNegativeState)
{
    int const xs[] = {1,1,0,0,-1,0,0,1};
    int const ys[] = {1,1,0,0, 1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_cross_entropy(xs, ys, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_cross_entropy(ys, xs, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(CrossEntropyBadState)
{
    int const xs[] = {1,2,0,0,1,0,0,1};
    int const ys[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_cross_entropy(xs, ys, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_cross_entropy(xs, ys, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(CrossEntropy)
{
    inform_error err = INFORM_SUCCESS;

    double got = inform_cross_entropy((int[]){0,0,1,1,1,1,0,0,0},
        (int[]){1,0,0,1,0,0,1,0,0}, 9, 2, &err);
    ASSERT_DBL_NEAR((log2(3)-5.0/9), got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){1,0,0,1,0,0,1,0,0},
        (int[]){0,0,1,1,1,1,0,0,0}, 9, 2, &err);
    ASSERT_DBL_NEAR(((18*log2(3)-6*log2(5)-6)/9), got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){0,0,0,0,1,1,1,1},
        (int[]){1,1,1,1,0,0,0,0}, 8, 2, &err);
    ASSERT_DBL_NEAR(1.000000, got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){0,0,1,1,1,1,0,0,0},
        (int[]){1,1,0,0,0,0,1,1,1}, 9, 2, &err);
    ASSERT_DBL_NEAR(((18*log2(3)-4*log2(5)-10)/9), got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){1,1,0,1,0,1,1,1,0},
        (int[]){1,1,0,0,0,1,0,1,1}, 9, 2, &err);
    ASSERT_DBL_NEAR(((18*log2(3)-6*log2(5)-6)/9), got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){0,0,0,0,0,0,0,0,0},
        (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, &err);
    ASSERT_DBL_NEAR(log2(3), got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){1,1,1,1,0,0,0,0,1},
        (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, &err);
    ASSERT_DBL_NEAR((log2(3)-5.0/9), got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){1,1,0,0,1,1,0,0,1},
        (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, &err);
    ASSERT_DBL_NEAR((log2(3)-5.0/9), got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){0,1,0,1,0,1,0,1},
        (int[]){0,2,0,2,0,2,0,2}, 8, 3, &err);
    ASSERT_INF(got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){0,0,0,0,0,0,1,1,1,1,1,1},
            (int[]){0,0,0,0,1,1,1,1,2,2,2,2}, 12, 3, &err);
    ASSERT_DBL_NEAR(log2(3), got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){0,0,1,1,2,1,1,0,0},
        (int[]){0,0,0,1,1,1,0,0,0}, 9, 3, &err);
    ASSERT_INF(got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){0,1,0,0,1,0,0,1,0},
        (int[]){1,0,0,1,0,0,1,0,0}, 9, 2, &err);
    ASSERT_DBL_NEAR((log2(3)-6.0/9), got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    got = inform_cross_entropy((int[]){1,0,0,1,0,0,1,0},
        (int[]){2,0,1,2,0,1,2,0}, 8, 3, &err);
    ASSERT_DBL_NEAR(((24 - 5*log2(3) - 3)/8), got);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
}

BEGIN_SUITE(CrossEntropy)
    ADD_UNIT(CrossEntropyNULLSeries)
    ADD_UNIT(CrossEntropySeriesTooShort)
    ADD_UNIT(CrossEntropyInvalidBase)
    ADD_UNIT(CrossEntropyNegativeState)
    ADD_UNIT(CrossEntropyBadState)
    ADD_UNIT(CrossEntropy)
END_SUITE
