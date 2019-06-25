// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/active_info.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(ActiveInfoSeriesNULLSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_active_info(NULL, 1, 3, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(ActiveInfoSeriesNoInits)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_active_info(series, 0, 3, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(ActiveInfoSeriesTooShort)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_active_info(series, 1, i, 2, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(ActiveInfoHistoryTooLong)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 2; i < 4; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_active_info(series, 1, 2, 2, i, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EKLONG, err);
    }
}

UNIT(ActiveInfoZeroHistory)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_active_info(series, 1, 2, 2, 0, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(ActiveInfoInvalidBase)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_active_info(series, 1, 2, i, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(ActiveInfoNegativeState)
{
    int const series[] = {-1,1,0,0,1,0,0,1};
    inform_error err;
    ASSERT_NAN(inform_active_info(series, 1, 8, 3, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(ActiveInfoBadState)
{
    int const series[] = {1,2,0,0,1,0,0,1};
    inform_error err;
    ASSERT_NAN(inform_active_info(series, 1, 8, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(ActiveInfoSingleSeries_Base2)
{
    ASSERT_DBL_NEAR_TOL(0.918296,
            inform_active_info((int[]){1,1,0,0,1,0,0,1}, 1, 8, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
            inform_active_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.305958,
            inform_active_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.347458,
            inform_active_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.347458,
            inform_active_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.399533,
            inform_active_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.399533,
            inform_active_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.305958,
            inform_active_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.305958,
            inform_active_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.347458,
            inform_active_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, NULL),
            1e-6);
}

UNIT(ActiveInfoSingleSeries_Base4)
{
    ASSERT_DBL_NEAR_TOL(1.270942,
            inform_active_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(1.270942,
            inform_active_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, NULL),
            1e-6);

    ASSERT_DBL_NEAR_TOL(0.469566,
            inform_active_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, NULL),
            1e-6);
}

UNIT(ActiveInfoEnsemble)
{
    {
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_DBL_NEAR_TOL(0.459148,
                inform_active_info(series, 2, 8, 2, 2, NULL),
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
        ASSERT_DBL_NEAR_TOL(0.3080467,
                inform_active_info(series, 9, 9, 2, 2, NULL),
                1e-6);
    }
}

UNIT(ActiveInfoEnsemble_Base4)
{
    {
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_DBL_NEAR_TOL(1.324292,
                inform_active_info(series, 4, 9, 4, 2, NULL),
                1e-6);
    }
}

UNIT(LocalActiveInfoSeriesNULLSeries)
{
    double ai[8];
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_active_info(NULL, 1, 3, 2, 2, ai, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(LocalActiveInfoSeriesNoInits)
{
    double ai[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_active_info(series, 0, 3, 2, 2, ai, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(LocalActiveInfoSeriesTooShort)
{
    double ai[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_active_info(series, 1, i, 2, 2, ai, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(LocalActiveInfoHistoryTooLong)
{
    double ai[6];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    for (size_t i = 2; i < 4; ++i)
    {
        ASSERT_NULL(inform_local_active_info(series, 1, 2, 2, 2, ai, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EKLONG, err);
    }
}

UNIT(LocalActiveInfoZeroHistory)
{
    double ai[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_active_info(series, 1, 2, 2, 0, ai, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(LocalActiveInfoInvalidBase)
{
    double ai[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_active_info(series, 1, 2, i, 2, ai, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(LocalActiveInfoNegativeState)
{
    double ai[8];
    int const series[] = {-1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NULL(inform_local_active_info(series, 1, 8, 2, 2, ai, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(LocalActiveInfoBadState)
{
    double ai[8];
    int const series[] = {2,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NULL(inform_local_active_info(series, 1, 8, 2, 2, ai, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(LocalActiveInfoAllocatesOutput)
{
    inform_error err = INFORM_SUCCESS;
    double *ai = inform_local_active_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, NULL, &err);
    ASSERT_NOT_NULL(ai);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    free(ai);
}

UNIT(LocalActiveInfoSingleSeries_Base2)
{
    double ai[7] = {0, 0, 0, 0, 0, 0, 0};

    ASSERT_NOT_NULL(inform_local_active_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(ai), 1e-6);

    ASSERT_NOT_NULL(inform_local_active_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(0.305958, AVERAGE(ai), 1e-6);

    ASSERT_NOT_NULL(inform_local_active_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(0.347458, AVERAGE(ai), 1e-6);

    ASSERT_NOT_NULL(inform_local_active_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(0.347458, AVERAGE(ai), 1e-6);

    ASSERT_NOT_NULL(inform_local_active_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(0.399533, AVERAGE(ai), 1e-6);

    ASSERT_NOT_NULL(inform_local_active_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(0.399533, AVERAGE(ai), 1e-6);

    ASSERT_NOT_NULL(inform_local_active_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(0.305958, AVERAGE(ai), 1e-6);

    ASSERT_NOT_NULL(inform_local_active_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(0.305958, AVERAGE(ai), 1e-6);

    ASSERT_NOT_NULL(inform_local_active_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(0.347458, AVERAGE(ai), 1e-6);
}

UNIT(LocalActiveInfoSingleSeries_Base4)
{
    double ai[7];
    ASSERT_NOT_NULL(inform_local_active_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(1.270942, AVERAGE(ai), 1e-6);

    ASSERT_NOT_NULL(inform_local_active_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(1.270942, AVERAGE(ai), 1e-6);

    ASSERT_NOT_NULL(inform_local_active_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, ai, NULL));
    ASSERT_DBL_NEAR_TOL(0.469566, AVERAGE(ai), 1e-6);
}

UNIT(LocalActiveInfoEnsemble)
{
    {
        double ai[12];
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_NOT_NULL(inform_local_active_info(series, 2, 8, 2, 2, ai, NULL));
        ASSERT_DBL_NEAR_TOL(0.459148, AVERAGE(ai), 1e-6);
    }

    {
        double ai[63];
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
        ASSERT_NOT_NULL(inform_local_active_info(series, 9, 9, 2, 2, ai, NULL));
        ASSERT_DBL_NEAR_TOL(0.3080467, AVERAGE(ai), 1e-6);
    }
}

UNIT(LocalActiveInfoEnsemble_Base4)
{
    {
        double ai[28];
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_NOT_NULL(inform_local_active_info(series, 4, 9, 4, 2, ai, NULL));
        ASSERT_DBL_NEAR_TOL(1.324292, AVERAGE(ai), 1e-6);
    }
}

BEGIN_SUITE(ActiveInformation)
    ADD_UNIT(ActiveInfoSeriesNULLSeries)
    ADD_UNIT(ActiveInfoSeriesNoInits)
    ADD_UNIT(ActiveInfoSeriesTooShort)
    ADD_UNIT(ActiveInfoHistoryTooLong)
    ADD_UNIT(ActiveInfoZeroHistory)
    ADD_UNIT(ActiveInfoInvalidBase)
    ADD_UNIT(ActiveInfoNegativeState)
    ADD_UNIT(ActiveInfoBadState)
    ADD_UNIT(ActiveInfoSingleSeries_Base2)
    ADD_UNIT(ActiveInfoSingleSeries_Base4)
    ADD_UNIT(ActiveInfoEnsemble)
    ADD_UNIT(ActiveInfoEnsemble_Base4)

    ADD_UNIT(LocalActiveInfoSeriesNULLSeries)
    ADD_UNIT(LocalActiveInfoSeriesNoInits)
    ADD_UNIT(LocalActiveInfoSeriesTooShort)
    ADD_UNIT(LocalActiveInfoHistoryTooLong)
    ADD_UNIT(LocalActiveInfoZeroHistory)
    ADD_UNIT(LocalActiveInfoInvalidBase)
    ADD_UNIT(LocalActiveInfoNegativeState)
    ADD_UNIT(LocalActiveInfoBadState)
    ADD_UNIT(LocalActiveInfoAllocatesOutput)
    ADD_UNIT(LocalActiveInfoSingleSeries_Base2)
    ADD_UNIT(LocalActiveInfoSingleSeries_Base4)
    ADD_UNIT(LocalActiveInfoEnsemble)
    ADD_UNIT(LocalActiveInfoEnsemble_Base4)
END_SUITE
