// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/conditional_entropy.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(ConditionalEntropyNULLSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_conditional_entropy(NULL, NULL, 3, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_conditional_entropy((int[]){0,0,1}, NULL, 3, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(ConditionalEntropySeriesTooShort)
{
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_conditional_entropy(xs, xs, 0, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(ConditionalEntropyInvalidBase)
{
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_conditional_entropy(xs, xs, 8, i, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);

        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_conditional_entropy(xs, xs, 8, 2, i, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(ConditionalEntropyNegativeState)
{
    int const xs[] = {1,1,0,0,-1,0,0,1};
    int const ys[] = {1,1,0,0, 1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_conditional_entropy(xs, ys, 8, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_conditional_entropy(ys, xs, 8, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(ConditionalEntropyBadState)
{
    int const xs[] = {1,2,0,0,1,0,0,1};
    int const ys[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_conditional_entropy(xs, ys, 8, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_conditional_entropy(xs, ys, 8, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(ConditionalEntropy)
{
    inform_error err = INFORM_SUCCESS;

    ASSERT_DBL_NEAR_TOL(0.899985, inform_conditional_entropy((int[]){0,0,1,1,1,1,0,0,0},
        (int[]){1,0,0,1,0,0,1,0,0}, 9, 2, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.972765, inform_conditional_entropy((int[]){1,0,0,1,0,0,1,0,0},
        (int[]){0,0,1,1,1,1,0,0,0}, 9, 2, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.000000, inform_conditional_entropy((int[]){0,0,0,0,1,1,1,1},
        (int[]){1,1,1,1,0,0,0,0}, 8, 2, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.000000, inform_conditional_entropy((int[]){0,0,1,1,1,1,0,0,0},
        (int[]){1,1,0,0,0,0,1,1,1}, 9, 2, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.918296, inform_conditional_entropy((int[]){1,1,0,1,0,1,1,1,0},
        (int[]){1,1,0,0,0,1,0,1,1}, 9, 2, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.918296, inform_conditional_entropy((int[]){0,0,0,0,0,0,0,0,0},
        (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.845516, inform_conditional_entropy((int[]){1,1,1,1,0,0,0,0,1},
        (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.899985, inform_conditional_entropy((int[]){1,1,0,0,1,1,0,0,1},
        (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.000000, inform_conditional_entropy((int[]){0,1,0,1,0,1,0,1},
        (int[]){0,2,0,2,0,2,0,2}, 8, 2, 3, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.918296,
        inform_conditional_entropy((int[]){0,0,0,0,0,0,1,1,1,1,1,1},
            (int[]){0,0,0,0,1,1,1,1,2,2,2,2}, 12, 2, 3, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.444444, inform_conditional_entropy((int[]){0,0,1,1,2,1,1,0,0},
        (int[]){0,0,0,1,1,1,0,0,0}, 9, 3, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.666667, inform_conditional_entropy((int[]){0,1,0,0,1,0,0,1,0},
        (int[]){1,0,0,1,0,0,1,0,0}, 9, 2, 2, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    ASSERT_DBL_NEAR_TOL(0.606844, inform_conditional_entropy((int[]){1,0,0,1,0,0,1,0},
        (int[]){2,0,1,2,0,1,2,0}, 8, 2, 3, &err), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
}

UNIT(LocalConditionalEntropyNULLSeries)
{
    double ce[8];
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_conditional_entropy(NULL, NULL, 3, 2, 2, ce, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_conditional_entropy((int[]){0,0,1}, NULL, 3, 2, 2, ce, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(LocalConditionalEntropySeriesTooShort)
{
    double ce[8];
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_conditional_entropy(xs, xs, 0, 2, 2, ce, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(LocalConditionalEntropyInvalidBase)
{
    double ce[8];
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_conditional_entropy(xs, xs, 8, i, 2, ce, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);

        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_conditional_entropy(xs, xs, 8, 2, i, ce, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(LocalConditionalEntropyNegativeState)
{
    double ce[8];
    int const xs[] = {1,1,0,0,-1,0,0,1};
    int const ys[] = {1,1,0,0, 1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_conditional_entropy(xs, ys, 8, 2, 2, ce, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_conditional_entropy(ys, xs, 8, 2, 2, ce, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(LocalConditionalEntropyBadState)
{
    double ce[8];
    int const xs[] = {1,2,0,0,1,0,0,1};
    int const ys[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_conditional_entropy(xs, ys, 8, 2, 2, ce, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_conditional_entropy(xs, ys, 8, 2, 2, ce, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(LocalConditionalEntropyAllocatesOutput)
{
    int const xs[] = {0,0,1,1,1,1,0,0,0};
    int const ys[] = {1,1,0,0,0,0,1,1,1};
    inform_error err = INFORM_SUCCESS;
    double *ce = inform_local_conditional_entropy(xs, ys, 9, 2, 2, NULL, &err);
    ASSERT_NOT_NULL(ce);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    free(ce);
}

UNIT(LocalConditionalEntropy)
{
    inform_error err = INFORM_SUCCESS;
    double ce_8[8];
    double ce_9[9];
    double ce_12[12];

    inform_local_conditional_entropy((int[]){0,0,1,1,1,1,0,0,0}, (int[]){1,0,0,1,0,0,1,0,0}, 9, 2, 2, ce_9, &err);
    ASSERT_DBL_NEAR_TOL(0.899985, AVERAGE(ce_9), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_conditional_entropy((int[]){1,0,0,1,0,0,1,0,0}, (int[]){0,0,1,1,1,1,0,0,0}, 9, 2, 2, ce_9, &err);
    ASSERT_DBL_NEAR_TOL(0.972765, AVERAGE(ce_9), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_conditional_entropy((int[]){0,0,0,0,1,1,1,1}, (int[]){1,1,1,1,0,0,0,0}, 8, 2, 2, ce_8, &err);
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(ce_8), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_conditional_entropy((int[]){0,0,1,1,1,1,0,0,0}, (int[]){1,1,0,0,0,0,1,1,1}, 9, 2, 2, ce_9, &err);
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(ce_9), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_conditional_entropy((int[]){1,1,0,1,0,1,1,1,0}, (int[]){1,1,0,0,0,1,0,1,1}, 9, 2, 2, ce_9, &err);
    ASSERT_DBL_NEAR_TOL(0.918296, AVERAGE(ce_9), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_conditional_entropy((int[]){0,0,0,0,0,0,0,0,0}, (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, 2, ce_9, &err);
    ASSERT_DBL_NEAR_TOL(0.918296, AVERAGE(ce_9), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_conditional_entropy((int[]){1,1,1,1,0,0,0,0,1}, (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, 2, ce_9, &err);
    ASSERT_DBL_NEAR_TOL(0.845516, AVERAGE(ce_9), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_conditional_entropy((int[]){1,1,0,0,1,1,0,0,1}, (int[]){1,1,1,0,0,0,1,1,1}, 9, 2, 2, ce_9, &err);
    ASSERT_DBL_NEAR_TOL(0.899985, AVERAGE(ce_9), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_conditional_entropy((int[]){0,1,0,1,0,1,0,1}, (int[]){0,2,0,2,0,2,0,2}, 8, 2, 3, ce_8, &err);
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(ce_8), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_conditional_entropy((int[]){0,0,0,0,0,0,1,1,1,1,1,1}, (int[]){0,0,0,0,1,1,1,1,2,2,2,2}, 12, 2, 3, ce_12, &err);
    ASSERT_DBL_NEAR_TOL(0.918296, AVERAGE(ce_12), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_conditional_entropy((int[]){0,0,1,1,2,1,1,0,0}, (int[]){0,0,0,1,1,1,0,0,0}, 9, 3, 2, ce_9, &err);
    ASSERT_DBL_NEAR_TOL(0.444444, AVERAGE(ce_9), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    
    inform_local_conditional_entropy((int[]){0,1,0,0,1,0,0,1,0}, (int[]){1,0,0,1,0,0,1,0,0}, 9, 2, 2, ce_9, &err);
    ASSERT_DBL_NEAR_TOL(0.666667, AVERAGE(ce_9), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);

    inform_local_conditional_entropy((int[]){1,0,0,1,0,0,1,0}, (int[]){2,0,1,2,0,1,2,0}, 8, 2, 3, ce_8, &err);
    ASSERT_DBL_NEAR_TOL(0.606844, AVERAGE(ce_8), 1e-6);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
}

BEGIN_SUITE(ConditionalEntropy)
    ADD_UNIT(ConditionalEntropyNULLSeries)
    ADD_UNIT(ConditionalEntropySeriesTooShort)
    ADD_UNIT(ConditionalEntropyInvalidBase)
    ADD_UNIT(ConditionalEntropyNegativeState)
    ADD_UNIT(ConditionalEntropyBadState)
    ADD_UNIT(ConditionalEntropy)
    ADD_UNIT(LocalConditionalEntropyNULLSeries)
    ADD_UNIT(LocalConditionalEntropySeriesTooShort)
    ADD_UNIT(LocalConditionalEntropyInvalidBase)
    ADD_UNIT(LocalConditionalEntropyNegativeState)
    ADD_UNIT(LocalConditionalEntropyBadState)
    ADD_UNIT(LocalConditionalEntropyAllocatesOutput)
    ADD_UNIT(LocalConditionalEntropy)
END_SUITE
