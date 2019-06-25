// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"
#include <inform/effective_info.h>
#include <math.h>
#include <ginger/unit.h>

UNIT(EffectiveInfoNullTPM)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_effective_info(NULL, NULL, 0, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETPM, err);
}

UNIT(EffectiveInfoZeroSize)
{
    double tpm[4] = {0.0, 1.0, 0.0, 0.0};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_effective_info(tpm, NULL, 0, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ESIZE, err);
}

UNIT(EffectiveInfoZeroRowTPM)
{
    double tpm[4] = {0.0, 1.0, 0.0, 0.0};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_effective_info(tpm, NULL, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETPM, err);
}

UNIT(EffectiveInfoNegativeProbabilitiesTPM)
{
    double tpm[4] = {-0.5, 1.0, 0.5, 0.5};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_effective_info(tpm, NULL, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_ETPM, err);
}

UNIT(EffectiveInfoUnNormalizedRowTPM)
{
    inform_error err = INFORM_SUCCESS;
    {
        double tpm[4] = {0.5, 0.5, 0.5, 0.25};
        ASSERT_NAN(inform_effective_info(tpm, NULL, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ETPM, err);
    }
    {
        double tpm[4] = {0.5, 0.5, 0.5, 0.75};
        ASSERT_NAN(inform_effective_info(tpm, NULL, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_ETPM, err);
    }
}

UNIT(EffectiveInfoZeroIntervention)
{
    double tpm[4] = {0.25, 0.75, 0.3, 0.7};
    double inter[2] = {0.0, 0.0};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_effective_info(tpm, inter, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EDIST, err);
}

UNIT(EffectiveInfoNegativeProbabilitiesIntervention)
{
    double tpm[4] = {0.25, 0.75, 0.3, 0.7};
    double inter[2] = {0.0, -0.2};
    inform_error err = INFORM_SUCCESS;
    ASSERT_NAN(inform_effective_info(tpm, inter, 2, &err));
    ASSERT_TRUE(inform_failed(&err));
    ASSERT_EQUAL(INFORM_EDIST, err);
}

UNIT(EffectiveInfoUnNormalizedIntervention)
{
    inform_error err = INFORM_SUCCESS;
    double tpm[4] = {0.25, 0.75, 0.3, 0.7};
    {
        double inter[2] = {0.5, 0.25};
        ASSERT_NAN(inform_effective_info(tpm, inter, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EDIST, err);
    }
    {
        double inter[2] = {0.5, 0.75};
        ASSERT_NAN(inform_effective_info(tpm, inter, 2, &err));
        ASSERT_TRUE(inform_failed(&err));
        ASSERT_EQUAL(INFORM_EDIST, err);
    }
}

UNIT(EffectiveInfoNonUniformIntervention)
{
    inform_error err = INFORM_SUCCESS;
    {
        double const tpm[4] = {0.2, 0.8, 0.75, 0.25};
        double const inter[2] = {0.25, 0.75};
        ASSERT_DBL_NEAR_TOL(0.174227,
            inform_effective_info(tpm, inter, 2, &err), 1e-6);
        ASSERT_TRUE(inform_succeeded(&err));
    }
    {
        double const tpm[9] = {1.0/3, 1.0/3, 1.0/3,
                               0.250, 0.750, 0.000,
                               0.125, 0.500, 0.375};
        double const inter[3] = {0.300, 0.250, 0.450};
        ASSERT_DBL_NEAR_TOL(0.1724976,
            inform_effective_info(tpm, inter, 3, &err), 1e-6);
        ASSERT_TRUE(inform_succeeded(&err));
    }
}

UNIT(EffectiveInfoUniformIntervention)
{
    inform_error err = INFORM_SUCCESS;
    {
        double const tpm[4] = {0.2, 0.8, 0.75, 0.25};
        ASSERT_DBL_NEAR_TOL(0.231593,
            inform_effective_info(tpm, NULL, 2, &err), 1e-6);
        ASSERT_TRUE(inform_succeeded(&err));
    }
    {
        double const tpm[9] = {1.0/3, 1.0/3, 1.0/3,
                               0.250, 0.750, 0.000,
                               0.125, 0.500, 0.375};
        ASSERT_DBL_NEAR_TOL(0.202701,
            inform_effective_info(tpm, NULL, 3, &err), 1e-6);
        ASSERT_TRUE(inform_succeeded(&err));
    }
}

UNIT(EffectiveInfoExamplesFromHoel)
{
    // E. Hoel, "When the map is better than the territory", arXiv:1612.09592
    inform_error err = INFORM_SUCCESS;
    {
        double const tpm[16] = {
            0, 0, 1, 0,
            1, 0, 0, 0,
            0, 0, 0, 1,
            0, 1, 0, 0,
        };
        err = INFORM_SUCCESS;
        ASSERT_DBL_NEAR(2.0, inform_effective_info(tpm, NULL, 4, &err));
        ASSERT_TRUE(inform_succeeded(&err));
    }
    {
        double const tpm[16] = {
            1.0/3, 1.0/3, 1.0/3, 0.000,
            1.0/3, 1.0/3, 1.0/3, 0.000,
            0.000, 0.000, 0.000, 1.000,
            0.000, 0.000, 0.000, 1.000,
        };
        err = INFORM_SUCCESS;
        ASSERT_DBL_NEAR(1.0, inform_effective_info(tpm, NULL, 4, &err));
        ASSERT_TRUE(inform_succeeded(&err));
    }
    {
        double const tpm[16] = {
            1.0/4, 1.0/4, 1.0/4, 1.0/4,
            1.0/4, 1.0/4, 1.0/4, 1.0/4,
            1.0/4, 1.0/4, 1.0/4, 1.0/4,
            1.0/4, 1.0/4, 1.0/4, 1.0/4,
        };
        err = INFORM_SUCCESS;
        ASSERT_DBL_NEAR(0.0, inform_effective_info(tpm, NULL, 4, &err));
        ASSERT_TRUE(inform_succeeded(&err));
    }
    {
        double const tpm[64] = {
            1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 0.000,
            1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 0.000,
            1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 0.000,
            1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 0.000,
            1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 0.000,
            1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 0.000,
            1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 0.000,
            0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000,
        };
        err = INFORM_SUCCESS;
        ASSERT_DBL_NEAR_TOL(0.543565, inform_effective_info(tpm, NULL, 8, &err), 1e-6);
        ASSERT_TRUE(inform_succeeded(&err));
    }
    {
        double const tpm[64] = {
            1.0/5, 1.0/5, 1.0/5, 1.0/5, 1.0/5, 0.000, 0.000, 0.000,
            1.0/7, 3.0/7, 1.0/7, 0.000, 1.0/7, 0.000, 1.0/7, 0.000,
            0.000, 1.0/6, 1.0/6, 1.0/6, 1.0/6, 1.0/6, 1.0/6, 0.000,
            1.0/7, 0.000, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 2.0/7, 0.000,
            1.0/9, 2.0/9, 2.0/9, 1.0/9, 0.000, 2.0/9, 1.0/9, 0.000,
            1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 1.0/7, 0.000,
            1.0/6, 1.0/6, 0.000, 1.0/6, 1.0/6, 1.0/6, 1.0/6, 0.000,
            0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000,
        };
        err = INFORM_SUCCESS;
        ASSERT_DBL_NEAR_TOL(0.805890, inform_effective_info(tpm, NULL, 8, &err), 1e-6);
        ASSERT_TRUE(inform_succeeded(&err));
    }
    {
        double const tpm[64] = {
            1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8,
            1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8,
            1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8,
            1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8,
            1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8,
            1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8, 1.0/8,
            0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000, 0.000,
            0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 1.000,
        };
        err = INFORM_SUCCESS;
        ASSERT_DBL_NEAR_TOL(0.630240, inform_effective_info(tpm, NULL, 8, &err), 1e-6);
        ASSERT_TRUE(inform_succeeded(&err));
    }
}

BEGIN_SUITE(EffectiveInformation)
    ADD_UNIT(EffectiveInfoNullTPM)
    ADD_UNIT(EffectiveInfoZeroSize)
    ADD_UNIT(EffectiveInfoZeroRowTPM)
    ADD_UNIT(EffectiveInfoNegativeProbabilitiesTPM)
    ADD_UNIT(EffectiveInfoUnNormalizedRowTPM)
    ADD_UNIT(EffectiveInfoZeroIntervention)
    ADD_UNIT(EffectiveInfoNegativeProbabilitiesIntervention)
    ADD_UNIT(EffectiveInfoUnNormalizedIntervention)

    ADD_UNIT(EffectiveInfoNonUniformIntervention)
    ADD_UNIT(EffectiveInfoUniformIntervention)
    ADD_UNIT(EffectiveInfoExamplesFromHoel)
END_SUITE
