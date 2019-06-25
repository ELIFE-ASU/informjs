// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/entropy_rate.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(EntropyRateNULLSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_entropy_rate(NULL, 1, 8, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(EntropyRateNoInits)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_entropy_rate(series, 0, 8, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(EntropyRateSeriesTooShort)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    
    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_entropy_rate(series, 1, i, 2, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(EntropyRateInvalidBase)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    
    for (int i = 0; i < 2; ++i)
    {
        ASSERT_NAN(inform_entropy_rate(series, 1, 2, i, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(EntropyRateZeroHistory)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    
    ASSERT_NAN(inform_entropy_rate(series, 1, 2, 2, 0, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(EntropyRateHistoryTooLong)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    for (size_t i = 2; i < 4; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_entropy_rate(series, 1, 2, 2, i, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EKLONG, err);
    }
}

UNIT(EntropyRateNegativeState)
{
    int const series[] = {-1,1,0,0,1,0,0,1};
    inform_error err;
    ASSERT_NAN(inform_entropy_rate(series, 1, 8, 3, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(EntropyRateBadState)
{
    int const series[] = {1,2,0,0,1,0,0,1};
    inform_error err;
    ASSERT_NAN(inform_entropy_rate(series, 1, 8, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(EntropyRateSingleSeries_Base2)
{
    ASSERT_DBL_NEAR_TOL(0.000000,
            inform_entropy_rate((int[]){1,1,0,0,1,0,0,1}, 1, 8, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
            inform_entropy_rate((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.679270,
            inform_entropy_rate((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.515663,
            inform_entropy_rate((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.515663,
            inform_entropy_rate((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.463587,
            inform_entropy_rate((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.463587,
            inform_entropy_rate((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.679270,
            inform_entropy_rate((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.679270,
            inform_entropy_rate((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.515663,
            inform_entropy_rate((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, NULL),
            1e-6);
}

UNIT(EntropyRateSingleSeries_Base4)
{
    ASSERT_DBL_NEAR_TOL(0.571428,
            inform_entropy_rate((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.393556,
            inform_entropy_rate((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.515662,
            inform_entropy_rate((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, NULL),
            1e-6);
}

UNIT(EntropyRateEnsemble)
{
    {
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_DBL_NEAR_TOL(0.459148,
                inform_entropy_rate(series, 2, 8, 2, 2, NULL),
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
        ASSERT_DBL_NEAR_TOL(0.610249,
                inform_entropy_rate(series, 9, 9, 2, 2, NULL),
                1e-6);
    }
}

UNIT(EntropyRateEnsemble_Base4)
{
    {
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_DBL_NEAR_TOL(0.544468,
                inform_entropy_rate(series, 4, 9, 4, 2, NULL),
                1e-6);
    }
}

UNIT(LocalEntropyRateNULLSeries)
{
    double er[8];
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_entropy_rate(NULL, 1, 3, 2, 2, er, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(LocalEntropyRateNoInits)
{
    double er[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_entropy_rate(series, 0, 3, 2, 2, er, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(LocalEntropyRateSeriesTooShort)
{
    double er[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_entropy_rate(series, 1, i, 2, 2, er, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(LocalEntropyRateHistoryTooLong)
{
    double er[6];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    for (size_t i = 2; i < 4; ++i)
    {
        ASSERT_NULL(inform_local_entropy_rate(series, 1, 2, 2, 2, er, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EKLONG, err);
    }
}

UNIT(LocalEntropyRateZeroHistory)
{
    double er[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_entropy_rate(series, 1, 2, 2, 0, er, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(LocalEntropyRateInvalidBase)
{
    double er[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_entropy_rate(series, 1, 2, i, 2, er, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(LocalEntropyRateNegativeState)
{
    double er[8];
    int const series[] = {-1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NULL(inform_local_entropy_rate(series, 1, 8, 2, 2, er, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(LocalEntropyRateBadState)
{
    double er[8];
    int const series[] = {2,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NULL(inform_local_entropy_rate(series, 1, 8, 2, 2, er, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}


UNIT(LocalEntropyRateAllocatesOutput)
{
    inform_error err = INFORM_SUCCESS;
    double *er = inform_local_entropy_rate((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, NULL, &err);
    ASSERT_NOT_NULL(er);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    free(er);
}

UNIT(LocalEntropyRateSingleSeries_Base2)
{
    double er[7];
    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(er), 1e-6);

    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.679270, AVERAGE(er), 1e-6);

    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.515663, AVERAGE(er), 1e-6);

    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.515663, AVERAGE(er), 1e-6);

    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.463587, AVERAGE(er), 1e-6);

    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.463587, AVERAGE(er), 1e-6);

    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.679270, AVERAGE(er), 1e-6);

    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.679270, AVERAGE(er), 1e-6);

    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.515663, AVERAGE(er), 1e-6);
}

UNIT(LocalEntropyRateSingleSeries_Base4)
{
    double er[7];

    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.571428, AVERAGE(er), 1e-6);

    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.393556, AVERAGE(er), 1e-6);

    ASSERT_NOT_NULL(inform_local_entropy_rate((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, er, NULL));
    ASSERT_DBL_NEAR_TOL(0.515662, AVERAGE(er), 1e-6);
}

UNIT(LocalEntropyRateEnsemble)
{
    {
        double er[12];
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_NOT_NULL(inform_local_entropy_rate(series, 2, 8, 2, 2, er, NULL));
        ASSERT_DBL_NEAR_TOL(0.459148, AVERAGE(er), 1e-6);
    }

    {
        double er[63];
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
        ASSERT_NOT_NULL(inform_local_entropy_rate(series, 9, 9, 2, 2, er, NULL));
        ASSERT_DBL_NEAR_TOL(0.610249, AVERAGE(er), 1e-6);
    }
}

UNIT(LocalEntropyRateEnsemble_Base4)
{
    {
        double er[28];
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_NOT_NULL(inform_local_entropy_rate(series, 4, 9, 4, 2, er, NULL));
        ASSERT_DBL_NEAR_TOL(0.544468, AVERAGE(er), 1e-6);
    }
}

BEGIN_SUITE(EntropyRate)
    ADD_UNIT(EntropyRateNULLSeries)
    ADD_UNIT(EntropyRateNoInits)
    ADD_UNIT(EntropyRateSeriesTooShort)
    ADD_UNIT(EntropyRateInvalidBase)
    ADD_UNIT(EntropyRateZeroHistory)
    ADD_UNIT(EntropyRateHistoryTooLong)
    ADD_UNIT(EntropyRateNegativeState)
    ADD_UNIT(EntropyRateBadState)
    ADD_UNIT(EntropyRateSingleSeries_Base2)
    ADD_UNIT(EntropyRateSingleSeries_Base4)
    ADD_UNIT(EntropyRateEnsemble)
    ADD_UNIT(EntropyRateEnsemble_Base4)
    ADD_UNIT(LocalEntropyRateNULLSeries)
    ADD_UNIT(LocalEntropyRateNoInits)
    ADD_UNIT(LocalEntropyRateSeriesTooShort)
    ADD_UNIT(LocalEntropyRateInvalidBase)
    ADD_UNIT(LocalEntropyRateZeroHistory)
    ADD_UNIT(LocalEntropyRateHistoryTooLong)
    ADD_UNIT(LocalEntropyRateNegativeState)
    ADD_UNIT(LocalEntropyRateBadState)
    ADD_UNIT(LocalEntropyRateAllocatesOutput)
    ADD_UNIT(LocalEntropyRateSingleSeries_Base2)
    ADD_UNIT(LocalEntropyRateSingleSeries_Base4)
    ADD_UNIT(LocalEntropyRateEnsemble)
    ADD_UNIT(LocalEntropyRateEnsemble_Base4)
END_SUITE
