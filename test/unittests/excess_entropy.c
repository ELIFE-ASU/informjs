// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/excess_entropy.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(ExcessEntropySeriesNULLSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_excess_entropy(NULL, 1, 3, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(ExcessEntropySeriesNoInits)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_excess_entropy(series, 0, 3, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(ExcessEntropySeriesTooShort)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_excess_entropy(series, 1, i, 2, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(ExcessEntropyZeroHistory)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_excess_entropy(series, 1, 2, 2, 0, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(ExcessEntropyKTooLong)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 1; i < 3; ++i)
    {
        if (2 * i >= 3)
        {
            err = INFORM_SUCCESS;
            ASSERT_NAN(inform_excess_entropy(series, 1, 3, 2, i, &err));
            ASSERT_TRUE(inform_failed(&err));
            ASSERT_EQUAL(INFORM_EKLONG, err);
        }
        else
        {
            err = INFORM_SUCCESS;
            ASSERT_NOT_NAN(inform_excess_entropy(series, 1, 3, 2, i, &err));
            ASSERT_TRUE(inform_succeeded(&err)); 
        }
    }
}

UNIT(ExcessEntropyInvalidBase)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_excess_entropy(series, 1, 2, i, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(ExcessEntropyNegativeState)
{
    int const series[] = {-1,1,0,0,1,0,0,1};
    inform_error err;
    ASSERT_NAN(inform_excess_entropy(series, 1, 8, 3, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(ExcessEntropyBadState)
{
    int const series[] = {1,2,0,0,1,0,0,1};
    inform_error err;
    ASSERT_NAN(inform_excess_entropy(series, 1, 8, 2, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(ExcessEntropyK2)
{
    ASSERT_DBL_NEAR_TOL(1.521928,
        inform_excess_entropy((int[]){1,1,0,0,1,0,0,1}, 1, 8, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_excess_entropy((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.666667,
        inform_excess_entropy((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.109170,
        inform_excess_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.109170,
        inform_excess_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.792481,
        inform_excess_entropy((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.000000,
        inform_excess_entropy((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.666667,
        inform_excess_entropy((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.666667,
        inform_excess_entropy((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.650022,
        inform_excess_entropy((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, NULL),
        1e-6);
}

UNIT(ExcessEntropyK3)
{
    ASSERT_DBL_NEAR_TOL(1.584963,
        inform_excess_entropy((int[]){1,1,0,0,1,0,0,1}, 1, 8, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_excess_entropy((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.500000,
        inform_excess_entropy((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.311278,
        inform_excess_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.311278,
        inform_excess_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.811278,
        inform_excess_entropy((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.500000,
        inform_excess_entropy((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.500000,
        inform_excess_entropy((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.500000,
        inform_excess_entropy((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_excess_entropy((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 3, NULL),
        1e-6);
}

UNIT(ExcessEntropyK2_Base4)
{
    ASSERT_DBL_NEAR_TOL(1.918296,
        inform_excess_entropy((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.000000,
        inform_excess_entropy((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.316689,
        inform_excess_entropy((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, NULL),
        1e-6);
}

UNIT(ExcessEntropyK3_Base4)
{
    ASSERT_DBL_NEAR_TOL(2.000000,
        inform_excess_entropy((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(1.500000,
        inform_excess_entropy((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 3, NULL),
        1e-6);

    ASSERT_DBL_NEAR_TOL(0.000000,
        inform_excess_entropy((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 3, NULL),
        1e-6);
}

UNIT(ExcessEntropyEnsembleK2)
{
    {
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_DBL_NEAR_TOL(0.846439,
            inform_excess_entropy(series, 2, 8, 2, 2, NULL),
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
        ASSERT_DBL_NEAR_TOL(0.448839,
                inform_excess_entropy(series, 9, 9, 2, 2, NULL),
                1e-6);
    }
}

UNIT(ExcessEntropyEnsembleK3)
{
    {
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_DBL_NEAR_TOL(1.584963,
            inform_excess_entropy(series, 2, 8, 2, 3, NULL),
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
        ASSERT_DBL_NEAR_TOL(0.829542,
                inform_excess_entropy(series, 9, 9, 2, 3, NULL),
                1e-6);
    }
}

UNIT(ExcessEntropyEnsembleK2_Base4)
{
    {
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_DBL_NEAR_TOL(2.041814,
                inform_excess_entropy(series, 4, 9, 4, 2, NULL),
                1e-6);
    }
}

UNIT(ExcessEntropyEnsembleK3_Base4)
{
    {
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_DBL_NEAR_TOL(2.780639,
                inform_excess_entropy(series, 4, 9, 4, 3, NULL),
                1e-6);
    }
}

UNIT(LocalExcessEntropySeriesNULLSeries)
{
    double ee[8];
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_excess_entropy(NULL, 1, 3, 2, 2, ee, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(LocalExcessEntropySeriesNoInits)
{
    double ee[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_excess_entropy(series, 0, 3, 2, 2, ee, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(LocalExcessEntropySeriesTooShort)
{
    double ee[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_excess_entropy(series, 1, i, 2, 2, ee, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(LocalExcessEntropyZeroHistory)
{
    double ee[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_excess_entropy(series, 1, 2, 2, 0, ee, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(LocalExcessEntropyKTooLong)
{
    double ee[20];
    int const series[] = {1,1,0,0,1,0,0,1};
    for (size_t i = 1; i < 3; ++i)
    {
        if (2 * i >= 3)
        {
            inform_error err = INFORM_SUCCESS;
            ASSERT_NULL(inform_local_excess_entropy(series, 1, 3, 2, i, ee, &err));
            ASSERT_TRUE(inform_failed(&err));
            ASSERT_EQUAL(INFORM_EKLONG, err);
        }
        else
        {
            inform_error err = INFORM_SUCCESS;
            ASSERT_NOT_NULL(inform_local_excess_entropy(series, 1, 3, 2, i, ee, &err));
            ASSERT_TRUE(inform_succeeded(&err));
        }
    }
}

UNIT(LocalExcessEntropyInvalidBase)
{
    double ee[8];
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_excess_entropy(series, 1, 2, i, 2, ee, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(LocalExcessEntropyNegativeState)
{
    double ee[8];
    int const series[] = {-1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NULL(inform_local_excess_entropy(series, 1, 8, 2, 2, ee, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(LocalExcessEntropyBadState)
{
    double ee[8];
    int const series[] = {2,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NULL(inform_local_excess_entropy(series, 1, 8, 2, 2, ee, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(LocalExcessEntropyK2)
{
    double ee[6] = {0, 0, 0, 0, 0, 0};

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.666667, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.109170, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.109170, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.792481, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(1.000000, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.666667, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.666667, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.650022, AVERAGE(ee), 1e-6);
}

UNIT(LocalExcessEntropyK3)
{
    double ee[4] = {0, 0, 0, 0};

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){1,0,0,0,0,0,0,0,0}, 1, 9, 2, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){0,0,1,1,1,1,0,0,0}, 1, 9, 2, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(1.500000, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.311278, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){1,0,0,0,0,0,0,1,1}, 1, 9, 2, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.311278, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){0,0,0,0,0,1,1,0,0}, 1, 9, 2, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.811278, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){0,0,0,0,1,1,0,0,0}, 1, 9, 2, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(1.500000, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){1,1,1,0,0,0,0,1,1}, 1, 9, 2, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(1.500000, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){0,0,0,1,1,1,1,0,0}, 1, 9, 2, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(1.500000, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){0,0,0,0,0,0,1,1,0}, 1, 9, 2, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(ee), 1e-6);
}

UNIT(LocalExcessEntropyK2_Base4)
{
    double ee[6];
    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(1.918296, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(1.000000, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 2, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.316689, AVERAGE(ee), 1e-6);
}

UNIT(LocalExcessEntropyK3_Base4)
{
    double ee[4];
    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){3,3,3,2,1,0,0,0,1}, 1, 9, 4, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(2.000000, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){2,2,3,3,3,3,2,1,0}, 1, 9, 4, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(1.500000, AVERAGE(ee), 1e-6);

    ASSERT_NOT_NULL(inform_local_excess_entropy((int[]){2,2,2,2,2,2,1,1,1}, 1, 9, 4, 3, ee, NULL));
    ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(ee), 1e-6);
}

UNIT(LocalExcessEntropyEnsembleK2)
{
    {
        double ee[10];
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_NOT_NULL(inform_local_excess_entropy(series, 2, 8, 2, 2, ee, NULL));
        ASSERT_DBL_NEAR_TOL(0.846439, AVERAGE(ee), 1e-6);
    }

    {
        double ee[54];
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
        ASSERT_NOT_NULL(inform_local_excess_entropy(series, 9, 9, 2, 2, ee, NULL));
        ASSERT_DBL_NEAR_TOL(0.448839, AVERAGE(ee), 1e-6);
    }
}

UNIT(LocalExcessEntropyEnsembleK3)
{
    {
        double ee[6];
        int series[16] = {
            1,1,0,0,1,0,0,1,
            0,0,0,1,0,0,0,1,
        };
        ASSERT_NOT_NULL(inform_local_excess_entropy(series, 2, 8, 2, 3, ee, NULL));
        ASSERT_DBL_NEAR_TOL(1.584963, AVERAGE(ee), 1e-6);
    }

    {
        double ee[36];
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
        ASSERT_NOT_NULL(inform_local_excess_entropy(series, 9, 9, 2, 3, ee, NULL));
        ASSERT_DBL_NEAR_TOL(0.829542, AVERAGE(ee), 1e-6);
    }
}

UNIT(LocalExcessEntropyEnsembleK2_Base4)
{
    {
        double ee[24];
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_NOT_NULL(inform_local_excess_entropy(series, 4, 9, 4, 2, ee, NULL));
        ASSERT_DBL_NEAR_TOL(2.041814, AVERAGE(ee), 1e-6);
    }
}

UNIT(LocalExcessEntropyEnsembleK3_Base4)
{
    {
        double ee[16];
        int series[36] = {
            3, 3, 3, 2, 1, 0, 0, 0, 1,
            2, 2, 3, 3, 3, 3, 2, 1, 0,
            0, 0, 0, 0, 1, 1, 0, 0, 0,
            1, 1, 0, 0, 0, 1, 1, 2, 2,
        };
        ASSERT_NOT_NULL(inform_local_excess_entropy(series, 4, 9, 4, 3, ee, NULL));
        ASSERT_DBL_NEAR_TOL(2.780639, AVERAGE(ee), 1e-6);
    }
}

BEGIN_SUITE(ExcessEntropy)
    ADD_UNIT(ExcessEntropySeriesNULLSeries)
    ADD_UNIT(ExcessEntropySeriesNoInits)
    ADD_UNIT(ExcessEntropySeriesTooShort)
    ADD_UNIT(ExcessEntropyZeroHistory)
    ADD_UNIT(ExcessEntropyKTooLong)
    ADD_UNIT(ExcessEntropyInvalidBase)
    ADD_UNIT(ExcessEntropyNegativeState)
    ADD_UNIT(ExcessEntropyBadState)
    ADD_UNIT(ExcessEntropyK2)
    ADD_UNIT(ExcessEntropyK3)
    ADD_UNIT(ExcessEntropyK2_Base4)
    ADD_UNIT(ExcessEntropyK3_Base4)
    ADD_UNIT(ExcessEntropyEnsembleK2)
    ADD_UNIT(ExcessEntropyEnsembleK3)
    ADD_UNIT(ExcessEntropyEnsembleK2_Base4)
    ADD_UNIT(ExcessEntropyEnsembleK3_Base4)

    ADD_UNIT(LocalExcessEntropySeriesNULLSeries)
    ADD_UNIT(LocalExcessEntropySeriesNoInits)
    ADD_UNIT(LocalExcessEntropySeriesTooShort)
    ADD_UNIT(LocalExcessEntropyZeroHistory)
    ADD_UNIT(LocalExcessEntropyKTooLong)
    ADD_UNIT(LocalExcessEntropyInvalidBase)
    ADD_UNIT(LocalExcessEntropyNegativeState)
    ADD_UNIT(LocalExcessEntropyBadState)
    ADD_UNIT(LocalExcessEntropyK2)
    ADD_UNIT(LocalExcessEntropyK3)
    ADD_UNIT(LocalExcessEntropyK2_Base4)
    ADD_UNIT(LocalExcessEntropyK3_Base4)
    ADD_UNIT(LocalExcessEntropyEnsembleK2)
    ADD_UNIT(LocalExcessEntropyEnsembleK3)
    ADD_UNIT(LocalExcessEntropyEnsembleK2_Base4)
    ADD_UNIT(LocalExcessEntropyEnsembleK3_Base4)
END_SUITE
