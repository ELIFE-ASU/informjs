// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/mutual_info.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(MutualInfoNULLSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_mutual_info(NULL, 1, 3, (int[]){2,2}, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(MutualInfoTooFewSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_mutual_info((int[]){1,0,1}, 1, 3, (int[]){2,2}, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOSOURCES, err);
}

UNIT(MutualInfoSeriesTooShort)
{
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_mutual_info(xs, 2, 0, (int[]){2,2}, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(MutualInfoInvalidBase)
{
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_mutual_info(xs, 2, 4, (int[]){i,2}, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);

        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_mutual_info(xs, 2, 4, (int[]){2,i}, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(MutualInfoNegativeState)
{
    {
        int const xs[] = {1,1,0,0,-1,0,0,1,1,1,0,0,1,0,0,1};
        inform_error err = INFORM_SUCCESS;
        ASSERT_NAN(inform_mutual_info(xs, 2, 8, (int[]){2,2}, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ENEGSTATE, err);
    }
    {
        int const xs[] = {1,1,0,0,1,0,0,1,1,1,0,0,-1,0,0,1};
        inform_error err = INFORM_SUCCESS;
        ASSERT_NAN(inform_mutual_info(xs, 2, 8, (int[]){2,2}, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ENEGSTATE, err);
    }
}

UNIT(MutualInfoBadState)
{
    {
        int const xs[] = {1,2,0,0,1,0,0,1,1,1,0,0,1,0,0,1};
        inform_error err = INFORM_SUCCESS;
        ASSERT_NAN(inform_mutual_info(xs, 2, 8, (int[]){2,2}, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBADSTATE, err);
    }
    {
        int const xs[] = {1,1,0,0,1,0,0,1,1,1,0,2,1,0,0,1};
        inform_error err = INFORM_SUCCESS;
        ASSERT_NAN(inform_mutual_info(xs, 2, 8, (int[]){2,2}, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBADSTATE, err);
    }
}

UNIT(MutualInfoUnivariate)
{
    inform_error err = INFORM_SUCCESS;
    {
        int series[] = {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0};
        ASSERT_DBL_NEAR_TOL(1.000000,
            inform_mutual_info(series, 2, 8, (int[]){2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int series[] = {0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1};
        ASSERT_DBL_NEAR_TOL(0.991076,
            inform_mutual_info(series, 2, 9, (int[]){2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int series[] = {1,1,0,1,0,1,1,1,0,1,1,0,0,0,1,0,1,1};
        ASSERT_DBL_NEAR_TOL(0.072780,
            inform_mutual_info(series, 2, 9, (int[]){2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int series[] = {0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1};
        ASSERT_DBL_NEAR_TOL(0.000000,
            inform_mutual_info(series, 2, 9, (int[]){2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int series[] = {1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1};
        ASSERT_DBL_NEAR_TOL(0.072780,
            inform_mutual_info(series, 2, 9, (int[]){2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int series[] = {1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,1,1,1};
        ASSERT_DBL_NEAR_TOL(0.018311,
            inform_mutual_info(series, 2, 9, (int[]){2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int series[] = {0,1,0,1,0,1,0,1,0,2,0,2,0,2,0,2};
        ASSERT_DBL_NEAR_TOL(1.000000,
            inform_mutual_info(series, 2, 8, (int[]){2,3}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int series[] = {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,2,2,2,2};
        ASSERT_DBL_NEAR_TOL(0.666667,
            inform_mutual_info(series, 2, 12, (int[]){2,3}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int series[] = {0,0,1,1,2,1,1,0,0,0,0,0,1,1,1,0,0,0};
        ASSERT_DBL_NEAR_TOL(0.473851,
            inform_mutual_info(series, 2, 9, (int[]){3,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int series[] = {0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,0};
        ASSERT_DBL_NEAR_TOL(0.251629,
            inform_mutual_info(series, 2, 9, (int[]){2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int series[] = {1,0,0,1,0,0,1,0,2,0,1,2,0,1,2,0};
        ASSERT_DBL_NEAR_TOL(0.954434,
            inform_mutual_info(series, 2, 8, (int[]){2,3}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
}

UNIT(MutualInfoMultivariate)
{
    inform_error err = INFORM_SUCCESS;
    {
        int x[24] = {0,0,0,0,1,1,1,1,
                     1,1,1,1,0,0,0,0,
                     0,0,1,1,1,1,0,0};
        ASSERT_DBL_NEAR_TOL(1.000000,
            inform_mutual_info(x, 3, 8, (int[]){2,2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int x[27] = {0,0,1,1,1,1,0,0,0,
                     1,1,0,0,0,0,1,1,1,
                     0,0,1,1,0,0,1,1,0};
        ASSERT_DBL_NEAR_TOL(0.998291,
            inform_mutual_info(x, 3, 9, (int[]){2,2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int x[27] = {1,1,0,1,0,1,1,1,0,
                     1,1,0,0,0,1,0,1,1,
                     0,0,1,1,0,0,1,1,0};
        ASSERT_DBL_NEAR_TOL(0.481066,
            inform_mutual_info(x, 3, 9, (int[]){2,2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int x[27] = {0,0,0,0,0,0,0,0,0,
                     1,1,1,0,0,0,1,1,1,
                     0,0,1,1,0,0,1,1,0};
        ASSERT_DBL_NEAR_TOL(0.018311,
            inform_mutual_info(x, 3, 9, (int[]){2,2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int x[27] = {1,1,1,1,0,0,0,0,1,
                     1,1,1,0,0,0,1,1,1,
                     0,0,1,1,0,0,1,1,0};
        ASSERT_DBL_NEAR_TOL(0.703288,
            inform_mutual_info(x, 3, 9, (int[]){2,2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int x[27] = {1,1,0,0,1,1,0,0,1,
                     1,1,1,0,0,0,1,1,1,
                     0,0,1,0,0,0,1,0,1};
        ASSERT_DBL_NEAR_TOL(0.324409,
            inform_mutual_info(x, 3, 9, (int[]){2,2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int x[24] = {0,1,0,1,0,1,0,1,
                     0,2,0,2,0,2,0,2,
                     0,0,1,0,0,0,1,0};
        ASSERT_DBL_NEAR_TOL(1.311278,
            inform_mutual_info(x, 3, 8, (int[]){2,3,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int x[36] = {0,0,0,0,0,0,1,1,1,1,1,1,
                     0,0,0,0,1,1,1,1,2,2,2,2,
                     0,0,1,0,0,0,1,0,1,1,0,0};
        ASSERT_DBL_NEAR_TOL(0.814536,
            inform_mutual_info(x, 3, 12, (int[]){2,3,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int x[27] = {0,0,1,1,2,1,1,0,0,
                     0,0,0,1,1,1,0,0,0,
                     0,0,1,0,0,0,1,0,1};
        ASSERT_DBL_NEAR_TOL(1.031579,
            inform_mutual_info(x, 3, 9, (int[]){3,2,2}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int x[27] = {0,1,0,0,1,0,0,1,0,
                     1,0,0,1,0,0,1,0,0,
                     0,0,1,0,0,0,1,0,1};
        ASSERT_DBL_NEAR_TOL(0.557728,
            inform_mutual_info(x, 3, 9, (int[]){3,3,3}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int x[24] = {2,0,1,1,0,2,1,0,
                     2,0,1,2,0,1,2,0,
                     2,0,1,0,1,0,2,0};
        ASSERT_DBL_NEAR_TOL(1.872556,
            inform_mutual_info(x, 3, 8, (int[]){3,3,3}, &err), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
}

UNIT(LocalMutualInfoNULLSeries)
{
    double mi[8];
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_mutual_info(NULL, 1, 3, (int[]){2,2}, mi, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(LocalMutualInfoTooFewSeries)
{
    double mi[8];
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_mutual_info(xs, 1, 8, (int[]){2,2}, mi, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOSOURCES, err);
}

UNIT(LocalMutualInfoSeriesTooShort)
{
    double mi[8];
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_local_mutual_info(xs, 2, 0, (int[]){2,2}, mi, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(LocalMutualInfoInvalidBase)
{
    double mi[8];
    int const xs[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_mutual_info(xs, 2, 4, (int[]){i,2}, mi, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);

        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_mutual_info(xs, 2, 4, (int[]){2,i}, mi, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(LocalMutualInfoNegativeState)
{
    double mi[8];
    inform_error err;
    {
        int const xs[] = {1,1,0,0,-1,0,0,1,1,1,0,0,1,0,0,1};
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_mutual_info(xs, 2, 8, (int[]){2,2}, mi, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ENEGSTATE, err);
    }
    {
        int const xs[] = {1,1,0,0,1,0,0,1,1,1,0,0,-1,0,0,1};
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_local_mutual_info(xs, 2, 8, (int[]){2,2}, mi, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ENEGSTATE, err);
    }
}

UNIT(LocalMutualInfoBadState)
{
    double mi[8];
    inform_error err;
    {
        err = INFORM_SUCCESS;
        int const xs[] = {1,2,0,0,1,0,0,1,1,1,0,0,1,0,0,1};
        ASSERT_NULL(inform_local_mutual_info(xs, 2, 8, (int[]){2,2}, mi, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBADSTATE, err);
    }
    {
        err = INFORM_SUCCESS;
        int const xs[] = {1,2,0,0,1,0,0,1,1,1,0,0,1,0,0,1};
        ASSERT_NULL(inform_local_mutual_info(xs, 2, 8, (int[]){2,2}, mi, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBADSTATE, err);
    }
}

UNIT(LocalMutualInfoAllocatesOutput)
{
    int const xs[] = {0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1};
    inform_error err = INFORM_SUCCESS;
    double *mi = inform_local_mutual_info(xs, 2, 9, (int[]){2,2}, NULL, &err);
    ASSERT_NOT_NULL(mi);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    free(mi);
}

UNIT(LocalMutualInfoUnivariate)
{
    inform_error err = INFORM_SUCCESS;
    double mi_8[8];
    double mi_9[9];
    double mi_12[12];

    {
        int xs[16] = {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 2, 8, (int[]){2,2}, mi_8, &err));
        ASSERT_DBL_NEAR_TOL(1.000000, AVERAGE(mi_8), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[18] = {0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,1,1,1};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 2, 9, (int[]){2,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.991076, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[18] = {1,1,0,1,0,1,1,1,0,1,1,0,0,0,1,0,1,1};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 2, 9, (int[]){2,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.072780, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[18] = {0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 2, 9, (int[]){2,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[18] = {1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 2, 9, (int[]){2,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.072780, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[18] = {1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,1,1,1};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 2, 9, (int[]){2,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.018311, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[16] = {0,1,0,1,0,1,0,1,0,2,0,2,0,2,0,2};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 2, 8, (int[]){2,3}, mi_8, &err));
        ASSERT_DBL_NEAR_TOL(1.000000, AVERAGE(mi_8), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[24] = {0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,2,2,2,2};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 2, 12, (int[]){2,3}, mi_12, &err));
        ASSERT_DBL_NEAR_TOL(0.666667, AVERAGE(mi_12), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[18] = {0,0,1,1,2,1,1,0,0,0,0,0,1,1,1,0,0,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 2, 9, (int[]){3,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.473851, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[18] = {0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 2, 9, (int[]){3,3}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.251629, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[16] = {1,0,0,1,0,0,1,0,2,0,1,2,0,1,2,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 2, 8, (int[]){2,3}, mi_8, &err));
        ASSERT_DBL_NEAR_TOL(0.954434, AVERAGE(mi_8), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
}

UNIT(LocalMutualInfoMultivariate)
{
    inform_error err = INFORM_SUCCESS;
    double mi_8[8];
    double mi_9[9];
    double mi_12[12];

    {
        int xs[24] = {0,0,0,0,1,1,1,1,
                     1,1,1,1,0,0,0,0,
                     0,0,1,1,1,1,0,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 3, 8, (int[]){2,2,2}, mi_8, &err));
        ASSERT_DBL_NEAR_TOL(1.000000, AVERAGE(mi_8), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[27] = {0,0,1,1,1,1,0,0,0,
                     1,1,0,0,0,0,1,1,1,
                     0,0,1,1,0,0,1,1,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 3, 9, (int[]){2,2,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.998291, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[27] = {1,1,0,1,0,1,1,1,0,
                     1,1,0,0,0,1,0,1,1,
                     0,0,1,1,0,0,1,1,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 3, 9, (int[]){2,2,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.481066, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[27] = {0,0,0,0,0,0,0,0,0,
                     1,1,1,0,0,0,1,1,1,
                     0,0,1,1,0,0,1,1,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 3, 9, (int[]){2,2,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.018311, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[27] = {1,1,1,1,0,0,0,0,1,
                     1,1,1,0,0,0,1,1,1,
                     0,0,1,1,0,0,1,1,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 3, 9, (int[]){2,2,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.703288, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[27] = {1,1,0,0,1,1,0,0,1,
                     1,1,1,0,0,0,1,1,1,
                     0,0,1,0,0,0,1,0,1};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 3, 9, (int[]){2,2,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.324409, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[24] = {0,1,0,1,0,1,0,1,
                     0,2,0,2,0,2,0,2,
                     0,0,1,0,0,0,1,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 3, 8, (int[]){2,3,2}, mi_8, &err));
        ASSERT_DBL_NEAR_TOL(1.311278, AVERAGE(mi_8), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[36] = {0,0,0,0,0,0,1,1,1,1,1,1,
                     0,0,0,0,1,1,1,1,2,2,2,2,
                     0,0,1,0,0,0,1,0,1,1,0,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 3, 12, (int[]){2,3,2}, mi_12, &err));
        ASSERT_DBL_NEAR_TOL(0.814536, AVERAGE(mi_12), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[27] = {0,0,1,1,2,1,1,0,0,
                     0,0,0,1,1,1,0,0,0,
                     0,0,1,0,0,0,1,0,1};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 3, 9, (int[]){3,2,2}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(1.031579, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[27] = {0,1,0,0,1,0,0,1,0,
                     1,0,0,1,0,0,1,0,0,
                     0,0,1,0,0,0,1,0,1};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 3, 9, (int[]){3,3,3}, mi_9, &err));
        ASSERT_DBL_NEAR_TOL(0.557728, AVERAGE(mi_9), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
    {
        int xs[24] = {2,0,1,1,0,2,1,0,
                     2,0,1,2,0,1,2,0,
                     2,0,1,0,1,0,2,0};
        ASSERT_NOT_NULL(inform_local_mutual_info(xs, 3, 8, (int[]){3,3,3}, mi_8, &err));
        ASSERT_DBL_NEAR_TOL(1.872556, AVERAGE(mi_8), 1e-6);
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
}

BEGIN_SUITE(MutualInfo)
    ADD_UNIT(MutualInfoNULLSeries)
    ADD_UNIT(MutualInfoTooFewSeries)
    ADD_UNIT(MutualInfoSeriesTooShort)
    ADD_UNIT(MutualInfoInvalidBase)
    ADD_UNIT(MutualInfoNegativeState)
    ADD_UNIT(MutualInfoBadState)
    ADD_UNIT(MutualInfoUnivariate)
    ADD_UNIT(MutualInfoMultivariate)
    ADD_UNIT(LocalMutualInfoNULLSeries)
    ADD_UNIT(MutualInfoTooFewSeries)
    ADD_UNIT(LocalMutualInfoSeriesTooShort)
    ADD_UNIT(LocalMutualInfoTooFewSeries)
    ADD_UNIT(LocalMutualInfoInvalidBase)
    ADD_UNIT(LocalMutualInfoNegativeState)
    ADD_UNIT(LocalMutualInfoBadState)
    ADD_UNIT(LocalMutualInfoAllocatesOutput)
    ADD_UNIT(LocalMutualInfoUnivariate)
    ADD_UNIT(LocalMutualInfoMultivariate)
END_SUITE
