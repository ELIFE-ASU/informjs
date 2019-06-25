// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/predictive_info.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(PredictiveInfoSeriesNULLSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_predictive_info(NULL, 1, 3, 2, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(PredictiveInfoSeriesNoInits)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_predictive_info(series, 0, 3, 2, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(PredictiveInfoSeriesTooShort)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_predictive_info(series, 1, i, 2, 2, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(PredictiveInfoZeroHistory)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_predictive_info(series, 1, 2, 2, 0, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(PredictiveInfoZeroFuture)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_predictive_info(series, 1, 2, 2, 2, 0, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(PredictiveInfoKTooLong)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 1; i < 4; ++i)
    {
        for (size_t j = 1; j < 4; ++j)
        {
            if (i + j >= 3)
            {
                err = INFORM_SUCCESS;
                ASSERT_NAN(inform_predictive_info(series, 1, 3, 2, i, j, &err));
                ASSERT_TRUE(inform_failed(&err));
                ASSERT_EQUAL(INFORM_EKLONG, err);
            }
            else
            {
                err = INFORM_SUCCESS;
                ASSERT_NOT_NAN(inform_predictive_info(series, 1, 3, 2, i, j, &err));
                ASSERT_TRUE(inform_succeeded(&err)); 
            }
        }
    }
}

UNIT(PredictiveInfoInvalidBase)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_predictive_info(series, 1, 2, i, 2, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(PredictiveInfoNegativeState)
{
    int const series[] = {-1,1,0,0,1,0,0,1};
    inform_error err;
    ASSERT_NAN(inform_predictive_info(series, 1, 8, 3, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(PredictiveInfoBadState)
{
    int const series[] = {1,2,0,0,1,0,0,1};
    inform_error err;
    ASSERT_NAN(inform_predictive_info(series, 1, 8, 2, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(PredictiveInfo21)
{
    ASSERT_DBL_NEAR_TOL(0.918296,
        inform_predictive_info((int[]){1,1,0,0,1,0,0,1}, 1, 8, 2, 2, 1, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, 1, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.305958,
        inform_predictive_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, 1, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.347458,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 1, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.347458,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 1, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.399533,
        inform_predictive_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, 1, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.399533,
        inform_predictive_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, 1, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.305958,
        inform_predictive_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, 1, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.305958,
        inform_predictive_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, 1, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.347458,
        inform_predictive_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, 1, NULL),
        1e-6);
}

UNIT(PredictiveInfo22)
{
    ASSERT_DBL_NEAR_TOL(1.521928,
        inform_predictive_info((int[]){1,1,0,0,1,0,0,1}, 1, 8, 2, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.666667,
        inform_predictive_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.109170,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.109170,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.792481,
        inform_predictive_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.000000,
        inform_predictive_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.666667,
        inform_predictive_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.666667,
        inform_predictive_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.650022,
        inform_predictive_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, 2, NULL),
        1e-6);
}

UNIT(PredictiveInfo23)
{
    ASSERT_DBL_NEAR_TOL(1.500000,
        inform_predictive_info((int[]){1,1,0,0,1,0,0,1}, 1, 8, 2, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.970951,
        inform_predictive_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.170951,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.170951,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.721928,
        inform_predictive_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.370951,
        inform_predictive_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.121928,
        inform_predictive_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.121928,
        inform_predictive_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_predictive_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, 3, NULL),
        1e-6);
}

UNIT(PredictiveInfo12)
{
    ASSERT_DBL_NEAR_TOL(0.666667,
        inform_predictive_info((int[]){1,1,0,0,1,0,0,1}, 1, 8, 2, 1, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 1, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.305958,
        inform_predictive_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 1, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.076010,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 1, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.076010,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 1, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.399533,
        inform_predictive_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 1, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.399533,
        inform_predictive_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 1, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.305958,
        inform_predictive_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 1, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.305958,
        inform_predictive_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 1, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.591673,
        inform_predictive_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 1, 2, NULL),
        1e-6);
}

UNIT(PredictiveInfo33)
{
    ASSERT_DBL_NEAR_TOL(1.584963,
        inform_predictive_info((int[]){1,1,0,0,1,0,0,1}, 1, 8, 2, 3, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 3, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.500000,
        inform_predictive_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 3, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.311278,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 3, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.311278,
        inform_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 3, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.811278,
        inform_predictive_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 3, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.500000,
        inform_predictive_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 3, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.500000,
        inform_predictive_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 3, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.500000,
        inform_predictive_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 3, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_predictive_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 3, 3, NULL),
        1e-6);
}

UNIT(PredictiveInfo21_Base4)
{
    ASSERT_DBL_NEAR_TOL(1.270942,
        inform_predictive_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, 1, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.270942,
        inform_predictive_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, 1, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.469566,
        inform_predictive_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, 1, NULL),
        1e-6);
}

UNIT(PredictiveInfo22_Base4)
{
    ASSERT_DBL_NEAR_TOL(1.918296,
        inform_predictive_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.000000,
        inform_predictive_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.316689,
        inform_predictive_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, 2, NULL),
        1e-6);
}

UNIT(PredictiveInfo23_Base4)
{
    ASSERT_DBL_NEAR_TOL(1.921928,
        inform_predictive_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.970951,
        inform_predictive_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_predictive_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, 3, NULL),
        1e-6);
}

UNIT(PredictiveInfo12_Base4)
{
    ASSERT_DBL_NEAR_TOL(1.556657,
        inform_predictive_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 1, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.591673,
        inform_predictive_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 1, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.305958,
        inform_predictive_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 1, 2, NULL),
        1e-6);
}

UNIT(PredictiveInfo33_Base4)
{
    ASSERT_DBL_NEAR_TOL(2.000000,
        inform_predictive_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 3, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.500000,
        inform_predictive_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 3, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_predictive_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 3, 3, NULL),
        1e-6);
}

UNIT(PredictiveInfoEnsemble21)
{
    {
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_DBL_NEAR_TOL(0.459148,
            inform_predictive_info(series, 2, 8, 2, 2, 1, NULL),
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
                inform_predictive_info(series, 9, 9, 2, 2, 1, NULL),
                1e-6);
    }
}

UNIT(PredictiveInfoEnsemble23)
{
    {
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_DBL_NEAR_TOL(1.061278,
            inform_predictive_info(series, 2, 8, 2, 2, 3, NULL),
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
        ASSERT_DBL_NEAR_TOL(0.628720,
                inform_predictive_info(series, 9, 9, 2, 2, 3, NULL),
                1e-6);
    }
}

UNIT(PredictiveInfoEnsemble21_Base4)
{
    {
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_DBL_NEAR_TOL(1.324292,
                inform_predictive_info(series, 4, 9, 4, 2, 1, NULL),
                1e-6);
    }
}

UNIT(PredictiveInfoEnsemble23_Base4)
{
    {
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_DBL_NEAR_TOL(2.385475,
                inform_predictive_info(series, 4, 9, 4, 2, 3, NULL),
                1e-6);
    }
}

UNIT(LocalPredictiveInfoSeriesNULLSeries)
{
    double pi[8];
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_predictive_info(NULL, 1, 3, 2, 2, 1, pi, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(LocalPredictiveInfoSeriesNoInits)
{
    double pi[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_predictive_info(series, 0, 3, 2, 2, 1, pi, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(LocalPredictiveInfoSeriesTooShort)
{
    double pi[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_predictive_info(series, 1, i, 2, 2, 1, pi, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(LocalPredictiveInfoZeroHistory)
{
    double pi[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_predictive_info(series, 1, 2, 2, 0, 1, pi, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(LocalPredictiveInfoZeroFuture)
{
    double pi[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_predictive_info(series, 1, 2, 2, 1, 0, pi, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(LocalPredictiveInfoKTooLong)
{
    double pi[20];
    int const series[] = {1,1,0,0,1,0,0,1};
    for (size_t i = 1; i < 4; ++i)
    {
        for (size_t j = 1; j < 5; ++j)
        {
            if (i + j >= 3)
            {
                inform_error err = INFORM_SUCCESS;
                ASSERT_NULL(inform_local_predictive_info(series, 1, 3, 2, i, j, pi, &err));
                ASSERT_TRUE(inform_failed(&err));
                ASSERT_EQUAL(INFORM_EKLONG, err);
            }
            else
            {
                inform_error err = INFORM_SUCCESS;
                ASSERT_NOT_NULL(inform_local_predictive_info(series, 1, 3, 2, i, j, pi, &err));
                ASSERT_TRUE(inform_succeeded(&err));
            }
        }
    }
}

UNIT(LocalPredictiveInfoInvalidBase)
{
    double pi[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_predictive_info(series, 1, 2, i, 2, 1, pi, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(LocalPredictiveInfoNegativeState)
{
    double pi[8];
    int const series[] = {-1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NULL(inform_local_predictive_info(series, 1, 8, 2, 2, 1, pi, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(LocalPredictiveInfoBadState)
{
    double pi[8];
    int const series[] = {2,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NULL(inform_local_predictive_info(series, 1, 8, 2, 2, 1, pi, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(LocalPredictiveInfo21)
{
    double pi[7] = {0, 0, 0, 0, 0, 0, 0};

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.305958, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.347458, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.347458, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.399533, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.399533, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.305958, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.305958, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.347458, AVERAGE(pi), 1e-6);
}

UNIT(LocalPredictiveInfo22)
{
    double pi[6] = {0, 0, 0, 0, 0, 0};

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.666667, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.109170, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.109170, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.792481, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.000000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.666667, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.666667, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.650022, AVERAGE(pi), 1e-6);
}

UNIT(LocalPredictiveInfo23)
{
    double pi[5] = {0, 0, 0, 0, 0};

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.970951, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.170951, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.170951, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.721928, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.370951, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.121928, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.121928, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(pi), 1e-6);
}

UNIT(LocalPredictiveInfo12)
{
    double pi[7] = {0, 0, 0, 0, 0, 0, 0};

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.305958, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.076010, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.076010, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.399533, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.399533, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.305958, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.305958, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.591673, AVERAGE(pi), 1e-6);
}

UNIT(LocalPredictiveInfo33)
{
    double pi[4] = {0, 0, 0, 0};

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.500000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.311278, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.311278, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.811278, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.500000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.500000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.500000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(pi), 1e-6);
}

UNIT(LocalPredictiveInfo21_Base4)
{
    double pi[7];
    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.270942, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.270942, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, 1, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.469566, AVERAGE(pi), 1e-6);
}

UNIT(LocalPredictiveInfo22_Base4)
{
    double pi[6];
    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.918296, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.000000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.316689, AVERAGE(pi), 1e-6);
}

UNIT(LocalPredictiveInfo23_Base4)
{
    double pi[5];
    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.921928, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.970951, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(pi), 1e-6);
}

UNIT(LocalPredictiveInfo12_Base4)
{
    double pi[7];
    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.556657, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.591673, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 1, 2, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.305958, AVERAGE(pi), 1e-6);
}

UNIT(LocalPredictiveInfo33_Base4)
{
    double pi[4];
    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(2.000000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(1.500000, AVERAGE(pi), 1e-6);

    ASSERT_NOT_NULL(inform_local_predictive_info((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 3, 3, pi, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(pi), 1e-6);
}

UNIT(LocalPredictiveInfoEnsemble21)
{
    {
        double pi[12];
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_NOT_NULL(inform_local_predictive_info(series, 2, 8, 2, 2, 1, pi, NULL));
        ASSERT_DBL_NEAR_TOL(0.459148, AVERAGE(pi), 1e-6);
    }

    {
        double pi[63];
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
        ASSERT_NOT_NULL(inform_local_predictive_info(series, 9, 9, 2, 2, 1, pi, NULL));
        ASSERT_DBL_NEAR_TOL(0.3080467, AVERAGE(pi), 1e-6);
    }
}

UNIT(LocalPredictiveInfoEnsemble23)
{
    {
        double pi[8];
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_NOT_NULL(inform_local_predictive_info(series, 2, 8, 2, 2, 3, pi, NULL));
        ASSERT_DBL_NEAR_TOL(1.061278, AVERAGE(pi), 1e-6);
    }

    {
        double pi[45];
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
        ASSERT_NOT_NULL(inform_local_predictive_info(series, 9, 9, 2, 2, 3, pi, NULL));
        ASSERT_DBL_NEAR_TOL(0.628720, AVERAGE(pi), 1e-6);
    }
}

UNIT(LocalPredictiveInfoEnsemble21_Base4)
{
    {
        double pi[28];
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_NOT_NULL(inform_local_predictive_info(series, 4, 9, 4, 2, 1, pi, NULL));
        ASSERT_DBL_NEAR_TOL(1.324292, AVERAGE(pi), 1e-6);
    }
}

UNIT(LocalPredictiveInfoEnsemble23_Base4)
{
    {
        double pi[20];
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_NOT_NULL(inform_local_predictive_info(series, 4, 9, 4, 2, 3, pi, NULL));
        ASSERT_DBL_NEAR_TOL(2.385475, AVERAGE(pi), 1e-6);
    }
}

BEGIN_SUITE(PredictiveInformation)
    ADD_UNIT(PredictiveInfoSeriesNULLSeries)
    ADD_UNIT(PredictiveInfoSeriesNoInits)
    ADD_UNIT(PredictiveInfoSeriesTooShort)
    ADD_UNIT(PredictiveInfoZeroHistory)
    ADD_UNIT(PredictiveInfoZeroFuture)
    ADD_UNIT(PredictiveInfoKTooLong)
    ADD_UNIT(PredictiveInfoInvalidBase)
    ADD_UNIT(PredictiveInfoNegativeState)
    ADD_UNIT(PredictiveInfoBadState)
    ADD_UNIT(PredictiveInfo21)
    ADD_UNIT(PredictiveInfo22)
    ADD_UNIT(PredictiveInfo23)
    ADD_UNIT(PredictiveInfo12)
    ADD_UNIT(PredictiveInfo33)
    ADD_UNIT(PredictiveInfo21_Base4)
    ADD_UNIT(PredictiveInfo22_Base4)
    ADD_UNIT(PredictiveInfo23_Base4)
    ADD_UNIT(PredictiveInfo12_Base4)
    ADD_UNIT(PredictiveInfo33_Base4)
    ADD_UNIT(PredictiveInfoEnsemble21)
    ADD_UNIT(PredictiveInfoEnsemble23)
    ADD_UNIT(PredictiveInfoEnsemble21_Base4)
    ADD_UNIT(PredictiveInfoEnsemble23_Base4)

    ADD_UNIT(LocalPredictiveInfoSeriesNULLSeries)
    ADD_UNIT(LocalPredictiveInfoSeriesNoInits)
    ADD_UNIT(LocalPredictiveInfoSeriesTooShort)
    ADD_UNIT(LocalPredictiveInfoZeroHistory)
    ADD_UNIT(LocalPredictiveInfoZeroFuture)
    ADD_UNIT(LocalPredictiveInfoKTooLong)
    ADD_UNIT(LocalPredictiveInfoInvalidBase)
    ADD_UNIT(LocalPredictiveInfoNegativeState)
    ADD_UNIT(LocalPredictiveInfoBadState)
    ADD_UNIT(LocalPredictiveInfo21)
    ADD_UNIT(LocalPredictiveInfo22)
    ADD_UNIT(LocalPredictiveInfo23)
    ADD_UNIT(LocalPredictiveInfo12)
    ADD_UNIT(LocalPredictiveInfo33)
    ADD_UNIT(LocalPredictiveInfo21_Base4)
    ADD_UNIT(LocalPredictiveInfo22_Base4)
    ADD_UNIT(LocalPredictiveInfo23_Base4)
    ADD_UNIT(LocalPredictiveInfo12_Base4)
    ADD_UNIT(LocalPredictiveInfo33_Base4)
    ADD_UNIT(LocalPredictiveInfoEnsemble21)
    ADD_UNIT(LocalPredictiveInfoEnsemble23)
    ADD_UNIT(LocalPredictiveInfoEnsemble21_Base4)
    ADD_UNIT(LocalPredictiveInfoEnsemble23_Base4)
END_SUITE
