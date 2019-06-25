// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/information_flow.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(InformationFlowNULLSeries)
{
    int const series[] = {1,1,0,0,1,0,0,1};

    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(NULL, NULL, NULL, 0, 0, 0, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(series, NULL, NULL, 1, 0, 0, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(NULL, series, NULL, 0, 1, 0, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(NULL, NULL, series, 0, 0, 1, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(series, NULL, series, 1, 0, 1, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(NULL, series, series, 0, 1, 1, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(InformationFlowNoInits)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(series, series, NULL, 0, 0, 0, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(series, series, NULL, 1, 0, 0, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(series, series, NULL, 0, 1, 0, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(series, series, NULL, 0, 0, 1, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(series, series, NULL, 1, 0, 1, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(series, series, NULL, 0, 1, 1, 2, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(InformationFlowSeriesTooShort)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NAN(inform_information_flow(series, series, NULL, 1, 1, 0, 0, 4, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(series, series, NULL, 1, 1, 0, 2, 0, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(InformationFlowInvalidBase)
{
    int const series[] = {1,1,0,0,1,0,0,1};
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 2; ++i)
    {
        err = INFORM_SUCCESS;
        ASSERT_NAN(inform_information_flow(series, series, NULL, 1, 1, 0, 2, 3, i, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EBASE, err);
    }
}

UNIT(InformationFlowNegativeState)
{
    int const seriesA[] = { 1,1,0,0,1,0,0,1};
    int const seriesB[] = {-1,1,0,0,1,0,0,1};
    int const seriesC[] = { 0,0,1,0,1,0,1,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NAN(inform_information_flow(seriesA, seriesB, seriesC, 1, 1, 1, 1, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(seriesB, seriesA, seriesC, 1, 1, 1, 1, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(seriesA, seriesC, seriesB, 1, 1, 1, 1, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ENEGSTATE, err);
}

UNIT(InformationFlowBadState)
{
    int const seriesA[] = {1,1,0,0,1,0,0,1};
    int const seriesB[] = {2,1,0,0,1,0,0,1};
    int const seriesC[] = {0,0,1,0,1,0,1,1};
    inform_error err = INFORM_SUCCESS;

    ASSERT_NAN(inform_information_flow(seriesA, seriesB, seriesC, 1, 1, 1, 1, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(seriesB, seriesA, seriesC, 1, 1, 1, 1, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);

    err = INFORM_SUCCESS;
    ASSERT_NAN(inform_information_flow(seriesA, seriesC, seriesB, 1, 1, 1, 1, 8, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EBADSTATE, err);
}

UNIT(InformationFlowNoBackground)
{
    {
        int const seriesA[6] = {1,1,1,0,0,0};
        int const seriesB[6] = {0,0,0,1,1,1};
        int const seriesS[6] = {1,1,1,1,1,1};

        ASSERT_DBL_NEAR(1.0,
            inform_information_flow(seriesA, seriesB, NULL, 1, 1, 0, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(1.0,
            inform_information_flow(seriesB, seriesA, NULL, 1, 1, 0, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(1.0,
            inform_information_flow(seriesA, seriesB, seriesS, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(1.0,
            inform_information_flow(seriesB, seriesA, seriesS, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(1.0,
            inform_information_flow(seriesA, seriesA, NULL, 1, 1, 0, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(1.0,
            inform_information_flow(seriesB, seriesB, NULL, 1, 1, 0, 2, 3, 2, NULL));
    }

    {
        int const seriesA[6] = {1,1,1,1,0,0};
        int const seriesB[6] = {0,0,1,1,1,1};
        int const seriesS[6] = {1,1,1,1,1,1};

        double const expect = log2(3.0) - 4.0/3.0;

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesA, seriesB, NULL, 1, 1, 0, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesB, seriesA, NULL, 1, 1, 0, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesA, seriesB, seriesS, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesB, seriesA, seriesS, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(expect + 2.0 / 3.0,
            inform_information_flow(seriesA, seriesA, NULL, 1, 1, 0, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(expect + 2.0 / 3.0,
            inform_information_flow(seriesB, seriesB, NULL, 1, 1, 0, 2, 3, 2, NULL));
    }

    {
        int const seriesA[12] = {1,1,1,1,0,0,
                                 0,1,1,0,0,0};
        int const seriesB[6]  = {0,0,1,1,1,1};
        int const seriesS[6]  = {1,1,1,1,1,1};

        double const expect = log2(3.0) - 4.0/3.0;

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesA, seriesB, NULL, 2, 1, 0, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesB, seriesA, NULL, 1, 2, 0, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesA, seriesB, seriesS, 2, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesB, seriesA, seriesS, 1, 2, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(log2(3.0),
            inform_information_flow(seriesA, seriesA, NULL, 2, 2, 0, 2, 3, 2, NULL));
    }
}

UNIT(InformationFlow)
{
    {
        int const seriesA[6] = {1,1,1,0,0,0};
        int const seriesB[6] = {0,0,0,1,1,1};
        int const seriesS[6] = {0,0,1,1,0,0};

        ASSERT_DBL_NEAR(1.0,
            inform_information_flow(seriesA, seriesB, seriesS, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(1.0,
            inform_information_flow(seriesB, seriesA, seriesS, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(0.0,
            inform_information_flow(seriesS, seriesA, seriesB, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(0.0,
            inform_information_flow(seriesS, seriesB, seriesA, 1, 1, 1, 2, 3, 2, NULL));
    }

    {
        int const seriesA[6] = {1,1,0,0,0,0};
        int const seriesB[6] = {0,0,0,0,1,1};
        int const seriesS[6] = {0,0,1,1,0,0};

        double const expect = 2.0 / 3.0;

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesA, seriesB, seriesS, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesB, seriesA, seriesS, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesS, seriesA, seriesB, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(expect,
            inform_information_flow(seriesS, seriesB, seriesA, 1, 1, 1, 2, 3, 2, NULL));
    }

    {
        int const seriesA[6] = {1,1,0,0,0,0};
        int const seriesB[6] = {0,0,1,0,1,1};
        int const seriesS[6] = {0,0,1,1,0,0};

        ASSERT_DBL_NEAR(2.0/3.0,
            inform_information_flow(seriesA, seriesB, seriesS, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(2.0/3.0,
            inform_information_flow(seriesB, seriesA, seriesS, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(log2(3.0)/2.0 - 1.0/3.0,
            inform_information_flow(seriesS, seriesA, seriesB, 1, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(1.0 - 0.5 * log2(3.0),
            inform_information_flow(seriesS, seriesB, seriesA, 1, 1, 1, 2, 3, 2, NULL));
    }

    {
        int const seriesA[12] = {1,1,0,0,0,0,
                                 0,1,1,0,1,0};
        int const seriesB[6]  = {0,0,1,0,1,1};
        int const seriesS[6]  = {0,0,1,1,0,0};

        ASSERT_DBL_NEAR(1.0,
            inform_information_flow(seriesA, seriesB, seriesS, 2, 1, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(1.0,
            inform_information_flow(seriesB, seriesA, seriesS, 1, 2, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(log2(3.0) - 1.0,
            inform_information_flow(seriesS, seriesA, seriesB, 1, 2, 1, 2, 3, 2, NULL));

        ASSERT_DBL_NEAR(1.0/3.0,
            inform_information_flow(seriesS, seriesB, seriesA, 1, 1, 2, 2, 3, 2, NULL));
    }
}

BEGIN_SUITE(InformationFlow)
    ADD_UNIT(InformationFlowNULLSeries)
    ADD_UNIT(InformationFlowNoInits)
    ADD_UNIT(InformationFlowSeriesTooShort)
    ADD_UNIT(InformationFlowInvalidBase)
    ADD_UNIT(InformationFlowNegativeState)
    ADD_UNIT(InformationFlowBadState)
    ADD_UNIT(InformationFlowNoBackground)
    ADD_UNIT(InformationFlow)
END_SUITE
