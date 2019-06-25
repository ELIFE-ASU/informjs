// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/separable_info.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(SeparableInformationNULLSeries)
{
    int const series[] = {1,1,0,0,1,0,0,1};

    inform_error err = INFORM_SUCCESS;
    double si = inform_separable_info(NULL, series, 1, 1, 8, 2, 2, &err);
    ASSERT_NAN(si);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    si = inform_separable_info(series, NULL, 1, 1, 8, 2, 2, &err);
    ASSERT_NAN(si);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(SeparableInformationNoSources)
{
    int const series[] = {1,1,0,0,1,0,0,1};

    inform_error err = INFORM_SUCCESS;
    double si = inform_separable_info(series, series, 0, 1, 8, 2, 2, &err);
    ASSERT_NAN(si);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOSOURCES, err);
}

UNIT(SeparableInformationNoInits)
{
    int const series[] = {1,1,0,0,1,0,0,1};

    inform_error err = INFORM_SUCCESS;
    double si = inform_separable_info(series, series, 1, 0, 8, 2, 2, &err);
    ASSERT_NAN(si);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(SeparableInformationSeriesTooShort)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        double si = inform_separable_info(series, series, 1, 1, i, 2, 2, &err);
        ASSERT_NAN(si);
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(SeparableInformationHistoryTooLong)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 2; i < 4; ++i)
    {
        err = INFORM_SUCCESS;
        double si = inform_separable_info(series, series, 1, 1, 2, 2, i, &err);
        ASSERT_NAN(si);
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EKLONG, err);
    }
}

UNIT(SeparableInformationZeroHistory)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    double si = inform_separable_info(series, series, 1, 1, 2, 2, 0, &err);
    ASSERT_NAN(si);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(SeparableInformationInvalidBase)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        double si = inform_separable_info(series, series, 1, 1, 2, i, 2, &err);
        ASSERT_NAN(si);
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(SeparableInformationNegativeState)
{
    int const seriesA[] = { 1,1,0,0,1,0,0,1};
    int const seriesB[] = {-1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    double si = inform_separable_info(seriesA, seriesB, 1, 1, 8, 2, 2, &err);
    ASSERT_NAN(si);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);

    err = INFORM_SUCCESS;
    si = inform_separable_info(seriesB, seriesA, 1, 1, 8, 2, 2, &err);
    ASSERT_NAN(si);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(SeparableInformationBadState)
{
    int const seriesA[] = {1,1,0,0,1,0,0,1};
    int const seriesB[] = {2,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    double si = inform_separable_info(seriesA, seriesB, 1, 1, 8, 2, 2, &err);
    ASSERT_NAN(si);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);

    err = INFORM_SUCCESS;
    si = inform_separable_info(seriesB, seriesA, 1, 1, 8, 2, 2, &err);
    ASSERT_NAN(si);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(SeparableInformationSingleSource)
{
    {
        int series[10] = {
                1,1,1,0,0,
                1,1,0,0,1
        };
        ASSERT_DBL_NEAR_TOL(0.251629,
                inform_separable_info(series, series, 1, 1, 5, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.918296,
                inform_separable_info(series+5, series, 1, 1, 5, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.918296,
                inform_separable_info(series, series+5, 1, 1, 5, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.918296,
                inform_separable_info(series+5, series+5, 1, 1, 5, 2, 2, NULL), 1e-6);
    }

    {
        int series[20] = {
                0,0,1,1,1,0,0,0,0,1,
                1,1,0,0,0,0,0,0,1,1
        };
        ASSERT_DBL_NEAR_TOL(0.250000,
                inform_separable_info(series, series, 1, 1, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.750000,
                inform_separable_info(series+10, series, 1, 1, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.466917,
                inform_separable_info(series, series+10, 1, 1, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.360073,
                inform_separable_info(series+10, series+10, 1, 1, 10, 2, 2, NULL), 1e-6);
    }

    {
        int series[20] = {
                0,1,0,1,0,0,1,1,0,0,
                0,0,1,0,1,1,1,0,1,1
        };
        ASSERT_DBL_NEAR_TOL(0.265712,
                inform_separable_info(series, series, 1, 1, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.610073,
                inform_separable_info(series+10, series, 1, 1, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.466917,
                inform_separable_info(series, series+10, 1, 1, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.216917,
                inform_separable_info(series+10, series+10, 1, 1, 10, 2, 2, NULL), 1e-6);
    }
}

UNIT(SeparableInformationMultipleSources)
{
    {
        int series[15] = {
                1,1,1,0,0,
                1,1,0,0,1,
                0,0,1,1,1,
        };
        ASSERT_DBL_NEAR_TOL(0.000000,
                inform_separable_info(series, series+10, 2, 1, 5, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(1.584962,
                inform_separable_info(series+5, series, 2, 1, 5, 2, 2, NULL), 1e-6);
    }

    {
        int series[30] = {
                0,0,1,1,1,0,0,0,0,1,
                1,1,0,0,0,0,0,0,1,1,
                0,0,1,0,1,1,1,0,1,1,
        };
        ASSERT_DBL_NEAR_TOL(0.405639,
                inform_separable_info(series, series+20, 2, 1, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(1.000000,
                inform_separable_info(series+10, series, 2, 1, 10, 2, 2, NULL), 1e-6);
    }

    {
        int series[30] = {
                0,1,0,1,0,0,1,1,0,0,
                0,0,1,0,1,1,1,0,1,1,
                1,1,0,0,0,0,0,0,1,1,
        };
        ASSERT_DBL_NEAR_TOL(0.668122,
                inform_separable_info(series, series+20, 2, 1, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.798795,
                inform_separable_info(series+10, series, 2, 1, 10, 2, 2, NULL), 1e-6);
    }
}

UNIT(SeparableInformationSingleEnsemble)
{
    {
        int xseries[50] = {
            1, 1, 1, 0, 0, 1, 1, 0, 1, 0,
            0, 1, 0, 1, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
            0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
        };
        int yseries[50] = {
            0, 1, 0, 0, 0, 1, 0, 1, 1, 0,
            0, 0, 0, 1, 1, 1, 0, 1, 0, 0,
            1, 0, 1, 0, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
        };

        ASSERT_DBL_NEAR_TOL(0.058542,
                inform_separable_info(xseries, xseries, 1, 5, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.149684,
                inform_separable_info(yseries, xseries, 1, 5, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.114929,
                inform_separable_info(xseries, yseries, 1, 5, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.007299,
                inform_separable_info(yseries, yseries, 1, 5, 10, 2, 2, NULL), 1e-6);

        ASSERT_DBL_NEAR_TOL(0.055386,
                inform_separable_info(xseries, xseries, 1, 4, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.189922,
                inform_separable_info(yseries, xseries, 1, 4, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.118559,
                inform_separable_info(xseries, yseries, 1, 4, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.029041,
                inform_separable_info(yseries, yseries, 1, 4, 10, 2, 2, NULL), 1e-6);
    }
    {
        int xseries[50] = {
            0, 1, 0, 1, 0, 0, 1, 1, 1, 1,
            0, 1, 0, 1, 1, 1, 0, 0, 1, 0,
            1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
            0, 1, 1, 1, 1, 1, 0, 1, 1, 1,
        };
        int yseries[50] = {
            1, 1, 1, 1, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
            0, 1, 1, 1, 0, 1, 0, 0, 0, 0,
            0, 1, 0, 0, 1, 1, 0, 1, 0, 0,
            0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
        };

        ASSERT_DBL_NEAR_TOL(0.075943,
                inform_separable_info(xseries, xseries, 1, 5, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.107415,
                inform_separable_info(yseries, xseries, 1, 5, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.185962,
                inform_separable_info(xseries, yseries, 1, 5, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.033401,
                inform_separable_info(yseries, yseries, 1, 5, 10, 2, 2, NULL), 1e-6);

        ASSERT_DBL_NEAR_TOL(0.095538,
                inform_separable_info(xseries, xseries, 1, 4, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.268156,
                inform_separable_info(yseries, xseries, 1, 4, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.233567,
                inform_separable_info(xseries, yseries, 1, 4, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.027411,
                inform_separable_info(yseries, yseries, 1, 4, 10, 2, 2, NULL), 1e-6);
    }
}

UNIT(SeparableInformationMultipleEnsembles)
{
    {
        int series[150] = {
            1, 1, 1, 0, 0, 1, 1, 0, 1, 0,
            0, 1, 0, 1, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
            0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
            1, 1, 1, 1, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
            0, 1, 1, 1, 0, 1, 0, 0, 0, 0,
            0, 1, 0, 0, 1, 1, 0, 1, 0, 0,
            0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
            0, 1, 0, 0, 0, 1, 0, 1, 1, 0,
            0, 0, 0, 1, 1, 1, 0, 1, 0, 0,
            1, 0, 1, 0, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
        };

        ASSERT_DBL_NEAR_TOL(0.158276,
                inform_separable_info(series, series+100, 2, 5, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.159120,
                inform_separable_info(series+50, series, 2, 5, 10, 2, 2, NULL), 1e-6);
    }
    {
        int series[150] = {
            0, 1, 0, 1, 0, 0, 1, 1, 1, 1,
            0, 1, 0, 1, 1, 1, 0, 0, 1, 0,
            1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
            0, 1, 1, 1, 1, 1, 0, 1, 1, 1,
            0, 1, 0, 0, 0, 1, 0, 1, 1, 0,
            0, 0, 0, 1, 1, 1, 0, 1, 0, 0,
            1, 0, 1, 0, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
            1, 1, 1, 1, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
            0, 1, 1, 1, 0, 1, 0, 0, 0, 0,
            0, 1, 0, 0, 1, 1, 0, 1, 0, 0,
            0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
        };

        ASSERT_DBL_NEAR_TOL(0.276672,
                inform_separable_info(series, series+100, 2, 5, 10, 2, 2, NULL), 1e-6);
        ASSERT_DBL_NEAR_TOL(0.183652,
                inform_separable_info(series+50, series, 2, 5, 10, 2, 2, NULL), 1e-6);
    }
}

UNIT(LocalSeparableInformationNULLSeries)
{
    double si[8], *got;
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    got = inform_local_separable_info(NULL, series, 1, 1, 8, 2, 2, si, &err);
    ASSERT_NULL(got);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    got = inform_local_separable_info(NULL, series, 1, 1, 8, 2, 2, si, &err);
    ASSERT_NULL(got);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(LocalSeparableInformationNoSources)
{
    double si[8], *got;
    int const series[] = {1,1,0,0,1,0,0,1};

    inform_error err = INFORM_SUCCESS;
    got = inform_local_separable_info(series, series, 0, 1, 8, 2, 2, si, &err);
    ASSERT_NULL(got);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOSOURCES, err);
}

UNIT(LocalSeparableInformationNoInits)
{
    double si[8], *got;
    int const series[] = {1,1,0,0,1,0,0,1};

    inform_error err = INFORM_SUCCESS;
    got = inform_local_separable_info(series, series, 1, 0, 8, 2, 2, si, &err);
    ASSERT_NULL(got);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(LocalSeparableInformationSeriesTooShort)
{
    double si[8], *got;
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    for (size_t i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        got = inform_local_separable_info(series, series, 1, 1, i, 2, 2, si, &err);
        ASSERT_NULL(got);
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
    }
}

UNIT(LocalSeparableInformationHistoryTooLong)
{
    double si[8], *got;
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (size_t i = 2; i < 4; ++i)
    {
        err = INFORM_SUCCESS;
        got = inform_local_separable_info(series, series, 1, 1, 2, 2, i, si, &err);
        ASSERT_NULL(got);
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EKLONG, err);
    }
}

UNIT(LocalSeparableInformationZeroHistory)
{
    double si[8], *got;
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    got = inform_local_separable_info(series, series, 1, 1, 2, 2, 0, si, &err);
    ASSERT_NULL(got);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(LocalSeparableInformationInvalidBase)
{
    double si[8], *got;
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        got = inform_local_separable_info(series, series, 1, 1, 8, i, 2, si, &err);
        ASSERT_NULL(got);
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(LocalSeparableInformationNegativeState)
{
    double si[8], *got;
    int const seriesA[] = { 1,1,0,0,1,0,0,1};
    int const seriesB[] = {-1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    got = inform_local_separable_info(seriesA, seriesB, 1, 1, 8, 2, 2, si, &err);
    ASSERT_NULL(got);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);

    err = INFORM_SUCCESS;
    got = inform_local_separable_info(seriesB, seriesA, 1, 1, 8, 2, 2, si, &err);
    ASSERT_NULL(got);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(LocalSeparableInformationBadState)
{
    double si[8], *got;
    int const seriesA[] = {1,1,0,0,1,0,0,1};
    int const seriesB[] = {2,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    got = inform_local_separable_info(seriesA, seriesB, 1, 1, 8, 2, 2, si, &err);
    ASSERT_NULL(got);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);

    err = INFORM_SUCCESS;
    got = inform_local_separable_info(seriesB, seriesA, 1, 1, 8, 2, 2, si, &err);
    ASSERT_NULL(got);
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(LocalSeparableInformationAllocatesOutput)
{
    inform_error err = INFORM_SUCCESS;
    int source[] = {0,0,1,0,0,1,0,1,0};
    int target[] = {0,1,0,0,1,0,0,1,0};
    double *si = inform_local_separable_info(source, target, 1, 1, 9, 2, 2, NULL, &err);
    ASSERT_NOT_NULL(si);
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    free(si);
}

UNIT(LocalSeparableInformationSingleSource)
{
    {
        double si[3];
        int series[10] = {
                1,1,1,0,0,
                1,1,0,0,1
        };
        ASSERT_NOT_NULL(inform_local_separable_info(series, series, 1, 1, 5, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.251629, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series+5, series, 1, 1, 5, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.918296, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series, series+5, 1, 1, 5, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.918296, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series+5, series+5, 1, 1, 5, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.918296, AVERAGE(si), 1e-6);
    }

    {
        double si[8];
        int series[20] = {
                0,0,1,1,1,0,0,0,0,1,
                1,1,0,0,0,0,0,0,1,1
        };
        ASSERT_NOT_NULL(inform_local_separable_info(series, series, 1, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.250000, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series+10, series, 1, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.750000, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series, series+10, 1, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.466917, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series+10, series+10, 1, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.360073, AVERAGE(si), 1e-6);
    }

    {
        double si[8];
        int series[20] = {
                0,1,0,1,0,0,1,1,0,0,
                0,0,1,0,1,1,1,0,1,1
        };
        ASSERT_NOT_NULL(inform_local_separable_info(series, series, 1, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.265712, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series+10, series, 1, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.610073, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series, series+10, 1, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.466917, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series+10, series+10, 1, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.216917, AVERAGE(si), 1e-6);
    }
}

UNIT(LocalSeparableInformationMultipleSources)
{
    {
        double si[3];
        int series[15] = {
                1,1,1,0,0,
                1,1,0,0,1,
                0,0,1,1,1,
        };
        ASSERT_NOT_NULL(inform_local_separable_info(series, series+10, 2, 1, 5, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.000000, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series+5, series, 2, 1, 5, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(1.584962, AVERAGE(si), 1e-6);
    }

    {
        double si[8];
        int series[30] = {
                0,0,1,1,1,0,0,0,0,1,
                1,1,0,0,0,0,0,0,1,1,
                0,0,1,0,1,1,1,0,1,1,
        };
        ASSERT_NOT_NULL(inform_local_separable_info(series, series+20, 2, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.405639, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series+10, series, 2, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(1.000000, AVERAGE(si), 1e-6);
    }

    {
        double si[8];
        int series[30] = {
                0,1,0,1,0,0,1,1,0,0,
                0,0,1,0,1,1,1,0,1,1,
                1,1,0,0,0,0,0,0,1,1,
        };
        ASSERT_NOT_NULL(inform_local_separable_info(series, series+20, 2, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.668122, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series+10, series, 2, 1, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.798795, AVERAGE(si), 1e-6);
    }
}

UNIT(LocalSeparableInformationSingleEnsemble)
{
    {
        int xseries[50] = {
            1, 1, 1, 0, 0, 1, 1, 0, 1, 0,
            0, 1, 0, 1, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
            0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
        };
        int yseries[50] = {
            0, 1, 0, 0, 0, 1, 0, 1, 1, 0,
            0, 0, 0, 1, 1, 1, 0, 1, 0, 0,
            1, 0, 1, 0, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
        };

        {
            double si[40];
            ASSERT_NOT_NULL(inform_local_separable_info(xseries, xseries, 1, 5, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.058542, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(yseries, xseries, 1, 5, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.149684, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(xseries, yseries, 1, 5, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.114929, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(yseries, yseries, 1, 5, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.007299, AVERAGE(si), 1e-6);
        }
        {
            double si[32];
            ASSERT_NOT_NULL(inform_local_separable_info(xseries, xseries, 1, 4, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.055386, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(yseries, xseries, 1, 4, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.189922, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(xseries, yseries, 1, 4, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.118559, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(yseries, yseries, 1, 4, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.029041, AVERAGE(si), 1e-6);
        }
    }
    {
        int xseries[50] = {
            0, 1, 0, 1, 0, 0, 1, 1, 1, 1,
            0, 1, 0, 1, 1, 1, 0, 0, 1, 0,
            1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
            0, 1, 1, 1, 1, 1, 0, 1, 1, 1,
        };
        int yseries[50] = {
            1, 1, 1, 1, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
            0, 1, 1, 1, 0, 1, 0, 0, 0, 0,
            0, 1, 0, 0, 1, 1, 0, 1, 0, 0,
            0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
        };        

        {
            double si[40];
            ASSERT_NOT_NULL(inform_local_separable_info(xseries, xseries, 1, 5, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.075943, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(yseries, xseries, 1, 5, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.107415, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(xseries, yseries, 1, 5, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.185962, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(yseries, yseries, 1, 5, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.033401, AVERAGE(si), 1e-6);
        }
        {
            double si[32];
            ASSERT_NOT_NULL(inform_local_separable_info(xseries, xseries, 1, 4, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.095538, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(yseries, xseries, 1, 4, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.268156, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(xseries, yseries, 1, 4, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.233567, AVERAGE(si), 1e-6);
            ASSERT_NOT_NULL(inform_local_separable_info(yseries, yseries, 1, 4, 10, 2, 2, si, NULL));
            ASSERT_DBL_NEAR_TOL(0.027411, AVERAGE(si), 1e-6);
        }
    }
}

UNIT(LocalSeparableInformationMultipleEnsembles)
{
    double si[40];
    {
        int series[150] = {
            1, 1, 1, 0, 0, 1, 1, 0, 1, 0,
            0, 1, 0, 1, 1, 1, 0, 0, 0, 0,
            0, 0, 0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0, 0, 1,
            0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
            1, 1, 1, 1, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
            0, 1, 1, 1, 0, 1, 0, 0, 0, 0,
            0, 1, 0, 0, 1, 1, 0, 1, 0, 0,
            0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
            0, 1, 0, 0, 0, 1, 0, 1, 1, 0,
            0, 0, 0, 1, 1, 1, 0, 1, 0, 0,
            1, 0, 1, 0, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
        };
        
        ASSERT_NOT_NULL(inform_local_separable_info(series, series+100, 2, 5, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.158276, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series+50, series, 2, 5, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.159120, AVERAGE(si), 1e-6);
    }
    {
        int series[150] = {
            0, 1, 0, 1, 0, 0, 1, 1, 1, 1,
            0, 1, 0, 1, 1, 1, 0, 0, 1, 0,
            1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
            1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
            0, 1, 1, 1, 1, 1, 0, 1, 1, 1,
            0, 1, 0, 0, 0, 1, 0, 1, 1, 0,
            0, 0, 0, 1, 1, 1, 0, 1, 0, 0,
            1, 0, 1, 0, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 1, 1, 1, 1, 1, 1,
            0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
            1, 1, 1, 1, 1, 0, 0, 0, 1, 0,
            0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
            0, 1, 1, 1, 0, 1, 0, 0, 0, 0,
            0, 1, 0, 0, 1, 1, 0, 1, 0, 0,
            0, 1, 1, 1, 1, 0, 1, 1, 1, 1,
        };
        
        ASSERT_NOT_NULL(inform_local_separable_info(series, series+100, 2, 5, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.276672, AVERAGE(si), 1e-6);
        ASSERT_NOT_NULL(inform_local_separable_info(series+50, series, 2, 5, 10, 2, 2, si, NULL));
        ASSERT_DBL_NEAR_TOL(0.183652, AVERAGE(si), 1e-6);
    }
}

BEGIN_SUITE(SeparableInformation)
    ADD_UNIT(SeparableInformationNULLSeries)
    ADD_UNIT(SeparableInformationNoSources)
    ADD_UNIT(SeparableInformationNoInits)
    ADD_UNIT(SeparableInformationSeriesTooShort)
    ADD_UNIT(SeparableInformationHistoryTooLong)
    ADD_UNIT(SeparableInformationZeroHistory)
    ADD_UNIT(SeparableInformationInvalidBase)
    ADD_UNIT(SeparableInformationNegativeState)
    ADD_UNIT(SeparableInformationBadState)
    ADD_UNIT(SeparableInformationSingleSource)
    ADD_UNIT(SeparableInformationMultipleSources)
    ADD_UNIT(SeparableInformationSingleEnsemble)
    ADD_UNIT(SeparableInformationMultipleEnsembles)

    ADD_UNIT(LocalSeparableInformationNULLSeries)
    ADD_UNIT(LocalSeparableInformationNoSources)
    ADD_UNIT(LocalSeparableInformationNoInits)
    ADD_UNIT(LocalSeparableInformationSeriesTooShort)
    ADD_UNIT(LocalSeparableInformationHistoryTooLong)
    ADD_UNIT(LocalSeparableInformationZeroHistory)
    ADD_UNIT(LocalSeparableInformationInvalidBase)
    ADD_UNIT(LocalSeparableInformationNegativeState)
    ADD_UNIT(LocalSeparableInformationBadState)
    ADD_UNIT(LocalSeparableInformationAllocatesOutput)
    ADD_UNIT(LocalSeparableInformationSingleSource)
    ADD_UNIT(LocalSeparableInformationMultipleSources)
    ADD_UNIT(LocalSeparableInformationSingleEnsemble)
    ADD_UNIT(LocalSeparableInformationMultipleEnsembles)
END_SUITE
