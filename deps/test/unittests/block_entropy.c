// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/block_entropy.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(BlockEntropyNULLSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_block_entropy(NULL, 1, 3, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(BlockEntropyNoInits)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_block_entropy(series, 0, 3, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(BlockEntropySeriesTooShort)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_block_entropy(series, 1, i, 2, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(BlockEntropyHistoryTooLong)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 2; i < 4; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_block_entropy(series, 1, 2, 2, i, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EKLONG, err);
    }
}

UNIT(BlockEntropyZeroHistory)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_block_entropy(series, 1, 2, 2, 0, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(BlockEntropyInvalidBase)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_block_entropy(series, 1, 2, i, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(BlockEntropyNegativeState)
{
    int const series[] = {-1,1,0,0,1,0,0,1};
    inform_error err;
    ASSERT_NAN(inform_block_entropy(series, 1, 8, 3, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(BlockEntropyBadState)
{
    int const series[] = {1,2,0,0,1,0,0,1};
    inform_error err;
    ASSERT_NAN(inform_block_entropy(series, 1, 8, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(BlockEntropySingleSeries_Base2)
{
    ASSERT_DBL_NEAR_TOL(1.950212,
            inform_block_entropy((int[]){1,1,0,0,1,0,0,1}, 1, 8, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.543564,
            inform_block_entropy((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(1.811278,
            inform_block_entropy((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(1.548795,
            inform_block_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(1.548795,
            inform_block_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(1.548795,
            inform_block_entropy((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(1.548795,
            inform_block_entropy((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(1.811278,
            inform_block_entropy((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(1.811278,
            inform_block_entropy((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(1.548795,
            inform_block_entropy((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, NULL),
            1e-6);
}

UNIT(BlockEntropySingleSeries_Base4)
{
    ASSERT_DBL_NEAR_TOL(2.50000,
            inform_block_entropy((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(2.40564,
            inform_block_entropy((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(1.298794,
            inform_block_entropy((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, NULL),
            1e-6);
}

UNIT(BlockEntropyEnsemble)
{
    {
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_DBL_NEAR_TOL(1.788450,
                inform_block_entropy(series, 2, 8, 2, 2, NULL),
                1e-6);
    }

    {
        int series[81] = {
            1,0,0,0,0,0,0,0,0,
            0,0,1,1,1,1,0,0,0,
            1,0,0,0,0,0,0,1,1,
            1,0,0,0,0,0,0,1,1,
            0,0,0,0,0,1,1,0,0,
            0,0,0,0,1,1,0,0,0,
            1,1,1,0,0,0,0,1,1,
            0,0,0,1,1,1,1,0,0,
            0,0,0,0,0,0,1,1,0,
        };
        ASSERT_DBL_NEAR_TOL(1.649204,
                inform_block_entropy(series, 9, 9, 2, 2, NULL),
                1e-6);
    }
}

UNIT(BlockEntropyEnsemble_Base4)
{
    {
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_DBL_NEAR_TOL(3.010976,
                inform_block_entropy(series, 4, 9, 4, 2, NULL),
                1e-6);
    }
}

UNIT(LocalBlockEntropyNULLSeries)
{
    double be[8];
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_block_entropy(NULL, 1, 3, 2, 2, be, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(LocalBlockEntropyNoInits)
{
    double be[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_block_entropy(series, 0, 3, 2, 2, be, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(LocalBlockEntropySeriesTooShort)
{
    double be[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_block_entropy(series, 1, i, 2, 2, be, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(LocalBlockEntropyHistoryTooLong)
{
    double be[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    for (size_t i = 2; i < 4; ++i)
    {
        ASSERT_NULL(inform_local_block_entropy(series, 1, 2, 2, 2, be, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EKLONG, err);
    }
}

UNIT(LocalBlockEntropyZeroHistory)
{
    double be[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_block_entropy(series, 1, 2, 2, 0, be, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(LocalBlockEntropyInvalidBase)
{
    double be[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_block_entropy(series, 1, 2, i, 2, be, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(LocalBlockEntropyNegativeState)
{
    double be[8];
    int const series[] = {-1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NULL(inform_local_block_entropy(series, 1, 8, 2, 2, be, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(LocalBlockEntropyBadState)
{
    double be[8];
    int const series[] = {2,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NULL(inform_local_block_entropy(series, 1, 8, 2, 2, be, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(LocalBlockEntropyAllocatesOutput)
{
    inform_error err = INFORM_SUCCESS;
    double *be = inform_local_block_entropy((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, NULL, &err);
    ASSERT_NOT_NULL(be);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    free(be);
}

UNIT(LocalBlockEntropySingleSeries_Base2)
{
    double be[8] = {0, 0, 0, 0, 0, 0, 0};

    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(0.543564, AVERAGE(be), 1e-6);

    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(1.811278, AVERAGE(be), 1e-6);

    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(1.548795, AVERAGE(be), 1e-6);

    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(1.548795, AVERAGE(be), 1e-6);

    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(1.548795, AVERAGE(be), 1e-6);

    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(1.548795, AVERAGE(be), 1e-6);

    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(1.811278, AVERAGE(be), 1e-6);

    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(1.811278, AVERAGE(be), 1e-6);

    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(1.548795, AVERAGE(be), 1e-6);
}

UNIT(LocalBlockEntropySingleSeries_Base4)
{
    double be[8];
    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(2.5, AVERAGE(be), 1e-6);

    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(2.40564, AVERAGE(be), 1e-6);

    ASSERT_NOT_NULL(inform_local_block_entropy((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, be, NULL));
    ASSERT_DBL_NEAR_TOL(1.298794, AVERAGE(be), 1e-6);
}

UNIT(LocalBlockEntropyEnsemble)
{
    {
        double be[14];
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_NOT_NULL(inform_local_block_entropy(series, 2, 8, 2, 2, be, NULL));
        ASSERT_DBL_NEAR_TOL(1.788450, AVERAGE(be), 1e-6);
    }

    {
        double be[72];
        int series[81] = {
            1,0,0,0,0,0,0,0,0,
            0,0,1,1,1,1,0,0,0,
            1,0,0,0,0,0,0,1,1,
            1,0,0,0,0,0,0,1,1,
            0,0,0,0,0,1,1,0,0,
            0,0,0,0,1,1,0,0,0,
            1,1,1,0,0,0,0,1,1,
            0,0,0,1,1,1,1,0,0,
            0,0,0,0,0,0,1,1,0,
        };
        ASSERT_NOT_NULL(inform_local_block_entropy(series, 9, 9, 2, 2, be, NULL));
        ASSERT_DBL_NEAR_TOL(1.649204, AVERAGE(be), 1e-6);
    }
}

UNIT(LocalBlockEntropyEnsemble_Base4)
{
    {
        double be[32];
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_NOT_NULL(inform_local_block_entropy(series, 4, 9, 4, 2, be, NULL));
        ASSERT_DBL_NEAR_TOL(3.010976, AVERAGE(be), 1e-6);
    }
}

BEGIN_SUITE(BlockEntropy)
    ADD_UNIT(BlockEntropyNULLSeries)
    ADD_UNIT(BlockEntropyNoInits)
    ADD_UNIT(BlockEntropySeriesTooShort)
    ADD_UNIT(BlockEntropyHistoryTooLong)
    ADD_UNIT(BlockEntropyZeroHistory)
    ADD_UNIT(BlockEntropyInvalidBase)
    ADD_UNIT(BlockEntropyNegativeState)
    ADD_UNIT(BlockEntropyBadState)
    ADD_UNIT(BlockEntropySingleSeries_Base2)
    ADD_UNIT(BlockEntropySingleSeries_Base4)
    ADD_UNIT(BlockEntropyEnsemble)
    ADD_UNIT(BlockEntropyEnsemble_Base4)
    ADD_UNIT(LocalBlockEntropyNULLSeries)
    ADD_UNIT(LocalBlockEntropyNoInits)
    ADD_UNIT(LocalBlockEntropySeriesTooShort)
    ADD_UNIT(LocalBlockEntropyHistoryTooLong)
    ADD_UNIT(LocalBlockEntropyZeroHistory)
    ADD_UNIT(LocalBlockEntropyInvalidBase)
    ADD_UNIT(LocalBlockEntropyNegativeState)
    ADD_UNIT(LocalBlockEntropyBadState)
    ADD_UNIT(LocalBlockEntropyAllocatesOutput)
    ADD_UNIT(LocalBlockEntropySingleSeries_Base2)
    ADD_UNIT(LocalBlockEntropySingleSeries_Base4)
    ADD_UNIT(LocalBlockEntropyEnsemble)
    ADD_UNIT(LocalBlockEntropyEnsemble_Base4)
END_SUITE
