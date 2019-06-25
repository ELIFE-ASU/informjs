// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <float.h>
#include <inform/dist.h>
#include <inform/utilities.h>
#include <ginger/unit.h>

UNIT(RangeNullSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_range(NULL, 0, NULL, NULL, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(RangeEmpty)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_range((double[]){1,2,3}, 0, NULL, NULL, &err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(RangeNullMinMax)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(2.0, inform_range((double[]){1,2,3}, 3, NULL, NULL, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
}

UNIT(RangeMinMax)
{
    inform_error err = INFORM_SUCCESS;
    double min, max;
    ASSERT_DBL_NEAR(2.0, inform_range((double[]){1,2,3}, 3, &min, &max, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    ASSERT_DBL_NEAR(1.0, min);
    ASSERT_DBL_NEAR(3.0, max);
}

UNIT(BinNullSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin(NULL, 0, 2, NULL, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(BinEmpty)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin((double[]){1,2,3,4,5,6}, 0, 2, NULL, &err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(BinInvalidBinning)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin((double[]){1,2,3,4,5,6}, 6, -1, NULL, &err));
    ASSERT_EQUAL(INFORM_EBIN, err);

    err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin((double[]){1,2,3,4,5,6}, 6, 0, NULL, &err));
    ASSERT_EQUAL(INFORM_EBIN, err);
    
    err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin((double[]){1,2,3,4,5,6}, 6, 1, NULL, &err));
    ASSERT_EQUAL(INFORM_EBIN, err);
}

UNIT(BinNullBinned)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin((double[]){1,2,3,4,5,6}, 6, 2, NULL, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(BinNoRange)
{
    int binned[4] = {-1,-1,-1,-1};
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin((double[]){1,1,1,1}, 4, 2, binned, &err));
    ASSERT_EQUAL(INFORM_EBIN, err);
    for (size_t i = 0; i < 4; ++i)
    {
        ASSERT_EQUAL(0, binned[i]);
    }
}

UNIT(BinTwo)
{
    inform_error err = INFORM_SUCCESS;
    int binned[6];
    int expect[6] = {0,0,0,1,1,1};
    ASSERT_DBL_NEAR(2.5, inform_bin((double[]){1,2,3,4,5,6}, 6, 2, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(BinThree)
{
    inform_error err = INFORM_SUCCESS;
    int binned[6];
    int expect[6] = {0,0,1,1,2,2};
    ASSERT_DBL_NEAR(5.0/3, inform_bin((double[]){1,2,3,4,5,6}, 6, 3, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(BinSix)
{
    inform_error err = INFORM_SUCCESS;
    int binned[6];
    int expect[6] = {0,1,2,3,4,5};
    ASSERT_DBL_NEAR(5.0/6, inform_bin((double[]){1,2,3,4,5,6}, 6, 6, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(BinStepNullSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin_step(NULL, 0, 2, NULL, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(BinStepEmpty)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin_step((double[]){1,2,3,4,5,6}, 0, 2, NULL, &err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(BinStepInvalidBinning)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin_step((double[]){1,2,3,4,5,6}, 6, -1., NULL, &err));
    ASSERT_EQUAL(INFORM_EBIN, err);

    err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin_step((double[]){1,2,3,4,5,6}, 6, 0., NULL, &err));
    ASSERT_EQUAL(INFORM_EBIN, err);

    err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin_step((double[]){1,2,3,4,5,6}, 6, DBL_EPSILON, NULL, &err));
    ASSERT_EQUAL(INFORM_EBIN, err);
}

UNIT(BinStepNullBinned)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_DBL_NEAR(0.0, inform_bin_step((double[]){1,2,3,4,5,6}, 6, 2., NULL, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(BinStepTwo)
{
    inform_error err = INFORM_SUCCESS;
    int binned[6];
    int expect[6] = {0,0,1,1,2,2};
    ASSERT_DBL_NEAR(3, inform_bin_step((double[]){1,2,3,4,5,6}, 6, 2., binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(BinStepFiveHalves)
{
    inform_error err = INFORM_SUCCESS;
    int binned[6];
    int expect[6] = {0,0,0,1,1,2};
    ASSERT_DBL_NEAR(3, inform_bin_step((double[]){1,2,3,4,5,6}, 6, 5./2, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(BinStepOne)
{
    inform_error err = INFORM_SUCCESS;
    int binned[6];
    int expect[6] = {0,1,2,3,4,5};
    ASSERT_DBL_NEAR(6, inform_bin_step((double[]){1,2,3,4,5,6}, 6, 1.0, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(BinStepHalf)
{
    inform_error err = INFORM_SUCCESS;
    int binned[6];
    int expect[6] = {0,2,4,6,8,10};
    ASSERT_DBL_NEAR(11, inform_bin_step((double[]){1,2,3,4,5,6}, 6, 0.5, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(BinBoundsNullSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(0, inform_bin_bounds(NULL, 0, NULL, 0, NULL, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(BinBoundsEmpty)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(0, inform_bin_bounds((double[]){1,2,3,4,5,6}, 0,
                NULL, 0, NULL, &err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(BinBoundsInvalidBinning)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(0, inform_bin_bounds((double[]){1,2,3,4,5,6}, 6,
                NULL, 0, NULL, &err));
    ASSERT_EQUAL(INFORM_EBIN, err);

    err = INFORM_SUCCESS;
    ASSERT_EQUAL(0, inform_bin_bounds((double[]){1,2,3,4,5,6}, 6,
                (double[]){3.0}, 0, NULL, &err));
    ASSERT_EQUAL(INFORM_EBIN, err);
}

UNIT(BinBoundsNullBinned)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(0, inform_bin_bounds((double[]){1,2,3,4,5,6}, 6,
                (double[]){3}, 1, NULL, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(BinBoundsOne)
{
    inform_error err = INFORM_SUCCESS;
    int binned[6];
    int expect[6] = {0,0,1,1,1,1};
    ASSERT_EQUAL(2, inform_bin_bounds((double[]){1,2,3,4,5,6}, 6,
                (double[]){3}, 1, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(BinBoundsTwo)
{
    inform_error err = INFORM_SUCCESS;
    int binned[6];
    int expect[6] = {0,0,1,1,1,2};
    ASSERT_EQUAL(3, inform_bin_bounds((double[]){1,2,3,4,5,6}, 6,
                (double[]){2.5, 5.5}, 2, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(BinBoundsNone)
{
    inform_error err = INFORM_SUCCESS;
    int binned[6];
    int expect[6] = {0,0,0,0,0,0};
    ASSERT_EQUAL(1, inform_bin_bounds((double[]){1,2,3,4,5,6}, 6,
                (double[]){6.1}, 1, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(BinBoundsAll)
{
    inform_error err = INFORM_SUCCESS;
    int binned[6];
    int expect[6] = {1,1,1,1,1,1};
    ASSERT_EQUAL(2, inform_bin_bounds((double[]){1,2,3,4,5,6}, 6,
                (double[]){0.}, 1, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(CoalesceNullSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(0, inform_coalesce(NULL, 0, NULL, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(CoalesceEmpty)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(0, inform_coalesce((int[]){1,2,3,4}, 0, NULL, &err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(CoalesceNullCoalesce)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(0, inform_coalesce((int[]){1,2,3,4}, 4, NULL, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(CoalesceUnchanged)
{
    inform_error err = INFORM_SUCCESS;
    int series[6] = {0,2,2,1,2,3};
    int binned[6];
    int *expect = series;
    ASSERT_EQUAL(4, inform_coalesce(series, 6, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(CoalesceShifted)
{
    inform_error err = INFORM_SUCCESS;
    int series[6] = {1,3,3,2,3,4};
    int binned[6];
    int expect[6] = {0,2,2,1,2,3};
    ASSERT_EQUAL(4, inform_coalesce(series, 6, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(CoalesceNoGaps)
{
    inform_error err = INFORM_SUCCESS;
    int series[6] = {2,8,7,2,0,0};
    int binned[6];
    int expect[6] = {1,3,2,1,0,0};
    ASSERT_EQUAL(4, inform_coalesce(series, 6, binned, &err));
    ASSERT_EQUAL(INFORM_SUCCESS, err);
    for (size_t i = 0; i < 6; ++i)
    {
        ASSERT_EQUAL(expect[i], binned[i]);
    }
}

UNIT(EncodeNullState)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode(NULL, 0, 0, &err));
    ASSERT_EQUAL(INFORM_EARG, err);
}

UNIT(EncodeEmpty)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode((int[]){0,0,1}, 0, 0, &err));
    ASSERT_EQUAL(INFORM_EARG, err);
}

UNIT(EncodeBadBase)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode((int[]){0,0,1}, 3, 0, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode((int[]){0,0,1}, 3, 1, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);
}

UNIT(EncodeToLarge)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode((int[]){0,0,1}, 32, 2, &err));
    ASSERT_EQUAL(INFORM_EENCODE, err);

    err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode((int[]){0,0,1}, 16, 4, &err));
    ASSERT_EQUAL(INFORM_EENCODE, err);
}

UNIT(EncodeOneBaseTwo)
{
    ASSERT_EQUAL(0, inform_encode((int[]){0}, 1, 2, NULL));
    ASSERT_EQUAL(1, inform_encode((int[]){1}, 1, 2, NULL));

    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode((int[]){2}, 1, 2, &err));
    ASSERT_EQUAL(INFORM_EENCODE, err);
}

UNIT(EncodeOneBaseThree)
{
    ASSERT_EQUAL(0, inform_encode((int[]){0}, 1, 3, NULL));
    ASSERT_EQUAL(1, inform_encode((int[]){1}, 1, 3, NULL));
    ASSERT_EQUAL(2, inform_encode((int[]){2}, 1, 3, NULL));

    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode((int[]){3}, 1, 3, &err));
    ASSERT_EQUAL(INFORM_EENCODE, err);
}

UNIT(EncodeTwoBaseTwo)
{
    ASSERT_EQUAL(0, inform_encode((int[]){0,0}, 2, 2, NULL));
    ASSERT_EQUAL(1, inform_encode((int[]){0,1}, 2, 2, NULL));
    ASSERT_EQUAL(2, inform_encode((int[]){1,0}, 2, 2, NULL));
    ASSERT_EQUAL(3, inform_encode((int[]){1,1}, 2, 2, NULL));

    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode((int[]){0,2}, 2, 2, &err));
    ASSERT_EQUAL(INFORM_EENCODE, err);

    err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode((int[]){2,0}, 2, 2, &err));
    ASSERT_EQUAL(INFORM_EENCODE, err);
}

UNIT(EncodeTwoBaseThree)
{
    ASSERT_EQUAL(0, inform_encode((int[]){0,0}, 2, 3, NULL));
    ASSERT_EQUAL(1, inform_encode((int[]){0,1}, 2, 3, NULL));
    ASSERT_EQUAL(2, inform_encode((int[]){0,2}, 2, 3, NULL));
    ASSERT_EQUAL(3, inform_encode((int[]){1,0}, 2, 3, NULL));
    ASSERT_EQUAL(4, inform_encode((int[]){1,1}, 2, 3, NULL));
    ASSERT_EQUAL(5, inform_encode((int[]){1,2}, 2, 3, NULL));
    ASSERT_EQUAL(6, inform_encode((int[]){2,0}, 2, 3, NULL));
    ASSERT_EQUAL(7, inform_encode((int[]){2,1}, 2, 3, NULL));
    ASSERT_EQUAL(8, inform_encode((int[]){2,2}, 2, 3, NULL));

    inform_error err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode((int[]){0,3}, 2, 3, &err));
    ASSERT_EQUAL(INFORM_EENCODE, err);

    err = INFORM_SUCCESS;
    ASSERT_EQUAL(-1, inform_encode((int[]){3,0}, 2, 3, &err));
    ASSERT_EQUAL(INFORM_EENCODE, err);
}

UNIT(DecodeNegativeEncoding)
{
    inform_error err = INFORM_SUCCESS;
    inform_decode(-1, 0, NULL, 0, &err);
    ASSERT_EQUAL(INFORM_EARG, err);
}

UNIT(DecodeBadBase)
{
    inform_error err = INFORM_SUCCESS;
    inform_decode(3, 0, NULL, 0, &err);
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    inform_decode(3, 1, NULL, 0, &err);
    ASSERT_EQUAL(INFORM_EBASE, err);
}

UNIT(DecodeToNullState)
{
    inform_error err = INFORM_SUCCESS;
    inform_decode(3, 2, NULL, 0, &err);
    ASSERT_EQUAL(INFORM_EARG, err);
}

UNIT(DecodeToEmptyState)
{
    inform_error err = INFORM_SUCCESS;
    int state[2];
    inform_decode(3, 2, state, 0, &err);
    ASSERT_EQUAL(INFORM_EARG, err);
}

UNIT(DecodeBaseTwo)
{
    int state[3];
    {
        int expect[3] = {0,1,0};
        inform_decode(2, 2, state, 3, NULL);
        for (size_t i = 0; i < 3; ++i) ASSERT_EQUAL(expect[i], state[i]);
    }

    {
        int expect[3] = {1,0,1};
        inform_decode(5, 2, state, 3, NULL);
        for (size_t i = 0; i < 3; ++i) ASSERT_EQUAL(expect[i], state[i]);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int expect[3] = {0,0,0};
        inform_decode(8, 2, state, 3, &err);
        for (size_t i = 0; i < 3; ++i) ASSERT_EQUAL(expect[i], state[i]);
        ASSERT_EQUAL(INFORM_EENCODE, err);
    }
}

UNIT(DecodeBaseThree)
{
    int state[3];
    {
        int expect[3] = {0,2,2};
        inform_decode(8, 3, state, 3, NULL);
        for (size_t i = 0; i < 3; ++i) ASSERT_EQUAL(expect[i], state[i]);
    }

    {
        int expect[3] = {1,1,0};
        inform_decode(12, 3, state, 3, NULL);
        for (size_t i = 0; i < 3; ++i) ASSERT_EQUAL(expect[i], state[i]);
    }

    {
        inform_error err = INFORM_SUCCESS;
        int expect[3] = {0,1,0};
        inform_decode(30, 3, state, 3, &err);
        for (size_t i = 0; i < 3; ++i) ASSERT_EQUAL(expect[i], state[i]);
        ASSERT_EQUAL(INFORM_EENCODE, err);
    }
}

UNIT(DecodeEncode)
{
    int state[4];
    inform_error err = INFORM_SUCCESS;
    for (int i = 0; i < 81; ++i)
    {
        inform_decode(i, 3, state, 4, &err); 
        ASSERT_EQUAL(INFORM_SUCCESS, err);

        ASSERT_EQUAL(i, inform_encode(state, 4, 3, &err));
        ASSERT_EQUAL(INFORM_SUCCESS, err);
    }
}

UNIT(RandomInt)
{
    for (int b = 2; b < 5; ++b)
    {
        inform_dist *dist = inform_dist_alloc(b);
        for (size_t i = 0; i < 100000; ++i)
        {
            int x = inform_random_int(0,b);
            ASSERT_TRUE(0 <= x && x < b);
            inform_dist_tick(dist, x);
        }
        for (size_t i = 0; i < inform_dist_size(dist); ++i)
        {
            ASSERT_TRUE(inform_dist_get(dist, i) > 0);
        }
        inform_dist_free(dist);
    }
}

UNIT(RandomIntMinMax)
{
    for (int b = 2; b < 5; ++b)
    {
        inform_dist *dist = inform_dist_alloc(b + 1);
        for (size_t i = 0; i < 100000; ++i)
        {
            int x = inform_random_int(1,b + 1);
            ASSERT_TRUE(1 <= x && x < b + 1);
            inform_dist_tick(dist, x);
        }
        ASSERT_EQUAL(0, inform_dist_get(dist, 0));
        for (size_t i = 1; i < inform_dist_size(dist); ++i)
        {
            ASSERT_TRUE(inform_dist_get(dist, i) > 0);
        }
        inform_dist_free(dist);
    }
}

UNIT(TPMNullSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_tpm(NULL, 1, 10, 2, NULL, &err));
    ASSERT_TRUE(inform_failed(&err));
}

UNIT(TPMNoInits)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_tpm((int[6]){0,1,0,1,1,0}, 0, 6, 2, NULL, &err));
    ASSERT_TRUE(inform_failed(&err));
}

UNIT(TPMShortSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_tpm((int[6]){0,1,0,1,1,0}, 6, 1, 2, NULL, &err));
    ASSERT_TRUE(inform_failed(&err));
}

UNIT(TPMInvalidBase)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_tpm((int[6]){0,1,0,1,1,0}, 2, 3, 1, NULL, &err));
    ASSERT_TRUE(inform_failed(&err));
}

UNIT(TPMInvalidState)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_tpm((int[6]){0,-1,0,1,1,0}, 2, 3, 2, NULL, &err));
    ASSERT_TRUE(inform_failed(&err));

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_tpm((int[6]){0,1,0,1,2,0}, 2, 3, 2, NULL, &err));
    ASSERT_TRUE(inform_failed(&err));
}

UNIT(TPMAllocates)
{
    inform_error err = INFORM_SUCCESS;
    double expected[4] = {0.000000, 1.000000, 0.666667, 0.333333};
    double *tpm = inform_tpm((int[6]){0,1,0,1,1,0}, 2, 3, 2, NULL, &err);
    ASSERT_TRUE(inform_succeeded(&err));
    ASSERT_NOT_NULL(tpm);
    for (size_t i = 0; i < 4; ++i)
    {
        ASSERT_DBL_NEAR_TOL(expected[i], tpm[i], 1e-6);
    }
    free(tpm);
}

UNIT(TPMNoAllocation)
{
    inform_error err = INFORM_SUCCESS;
    double expected[4] = {0.000000, 1.000000, 0.666667, 0.333333};
    double got[4];
    uint64_t before = (uint64_t)got;
    double *tpm = inform_tpm((int[6]){0,1,0,1,1,0}, 2, 3, 2, got, &err);
    uint64_t after = (uint64_t)tpm;
    ASSERT_TRUE(inform_succeeded(&err));
    ASSERT_EQUAL_U(after, before);
    for (size_t i = 0; i < 4; ++i)
    {
        ASSERT_DBL_NEAR_TOL(expected[i], got[i], 1e-6);
    }
}

UNIT(TPMZeroRow)
{
    inform_error err = INFORM_SUCCESS;
    double expected[4] = {0.000000, 0.000000, 0.250000, 0.750000};
    double got[4];
    inform_tpm((int[6]){1,1,1,1,1,0}, 2, 3, 2, got, &err);
    ASSERT_EQUAL(INFORM_ETPMROW, err);
    for (size_t i = 0; i < 4; ++i)
    {
        ASSERT_DBL_NEAR_TOL(expected[i], got[i], 1e-6);
    }
}

UNIT(TPMBase2)
{
    inform_error err;
    double got[4];
    {
        err = INFORM_SUCCESS;
        double expected[4] = {0.250000, 0.750000, 0.400000, 0.600000};
        inform_tpm((int[10]){0,0,1,1,0,1,0,1,1,1}, 1, 10, 2, got, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        for (size_t i = 0; i < 4; ++i)
            ASSERT_DBL_NEAR_TOL(expected[i], got[i], 1e-6);
    }
    {
        err = INFORM_SUCCESS;
        double expected[4] = {0.333333, 0.666667, 0.400000, 0.600000};
        inform_tpm((int[10]){0,0,1,1,0,1,0,1,1,1}, 2, 5, 2, got, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        for (size_t i = 0; i < 4; ++i)
            ASSERT_DBL_NEAR_TOL(expected[i], got[i], 1e-6);
    }
}

UNIT(TPMBase3)
{
    inform_error err;
    double got[9];
    {
        err = INFORM_SUCCESS;
        double expected[9] = {
            0.333333, 0.666667, 0.000000,
            0.250000, 0.250000, 0.500000,
            0.000000, 0.500000, 0.500000,
        };
        inform_tpm((int[10]){0,1,2,2,1,1,0,0,1,2}, 1, 10, 3, got, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        for (size_t i = 0; i < 9; ++i)
            ASSERT_DBL_NEAR_TOL(expected[i], got[i], 1e-6);
    }
    {
        err = INFORM_SUCCESS;
        double expected[9] = {
            0.333333, 0.666667, 0.000000,
            0.333333, 0.000000, 0.666667,
            0.000000, 0.500000, 0.500000,
        };
        inform_tpm((int[10]){0,1,2,2,1,1,0,0,1,2}, 2, 5, 3, got, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        for (size_t i = 0; i < 9; ++i)
            ASSERT_DBL_NEAR_TOL(expected[i], got[i], 1e-6);
    }
}

UNIT(BlackBoxNullSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box(NULL, 0, 0, 0, NULL, NULL, NULL, NULL, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(BlackBoxEmptySeries)
{
    inform_error err = INFORM_SUCCESS;
    int series[] = {0,1,1,1,0};
    ASSERT_NULL(inform_black_box(series, 0, 0, 0, NULL, NULL, NULL, NULL, &err));
    ASSERT_EQUAL(INFORM_ENOSOURCES, err);
}

UNIT(BlackBoxNoInits)
{
    inform_error err = INFORM_SUCCESS;
    int series[] = {0,1,1,1,0};
    ASSERT_NULL(inform_black_box(series, 1, 0, 0, NULL, NULL, NULL, NULL, &err));
    ASSERT_EQUAL(INFORM_ENOINITS, err);
}

UNIT(BlackBoxShortSeries)
{
    inform_error err = INFORM_SUCCESS;
    int series[] = {0,1,1,1,0,1};
    ASSERT_NULL(inform_black_box(series, 2, 1, 0, NULL, NULL, NULL, NULL, &err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}

UNIT(BlackBoxBadBase)
{
    inform_error err = INFORM_SUCCESS;
    int series[] = {0,1,1,1,0,1};
    ASSERT_NULL(inform_black_box(series, 2, 1, 3, NULL, NULL, NULL, NULL, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){0,0}, NULL, NULL,
        NULL, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){1,1}, NULL, NULL,
        NULL, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){-1,1}, NULL, NULL,
        NULL, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);
}

UNIT(BlackBoxNegativeState)
{
    inform_error err;
    {
        err = INFORM_SUCCESS;
        int series[] = {0,-1,1,1,0,1};
        ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){2,2}, NULL, NULL,
            NULL, &err));
        ASSERT_EQUAL(INFORM_ENEGSTATE, err);
    }
    {
        err = INFORM_SUCCESS;
        int series[] = {0,1,1,1,0,-1};
        ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){2,2}, NULL, NULL,
            NULL, &err));
        ASSERT_EQUAL(INFORM_ENEGSTATE, err);
    }
}

UNIT(BlackBoxInvalidState)
{
    inform_error err = INFORM_SUCCESS;
    {
        int series[] = {0,2,1,1,0,1};
        ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){2,2}, NULL, NULL,
            NULL, &err));
        ASSERT_EQUAL(INFORM_EBADSTATE, err);
    }
    {
        int series[] = {0,1,1,1,0,2};
        ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){2,2}, NULL, NULL,
            NULL, &err));
        ASSERT_EQUAL(INFORM_EBADSTATE, err);
    }
}

UNIT(BlackBoxInvalidHistory)
{
    inform_error err = INFORM_SUCCESS;
    int series[] = {0,1,1,1,0,1};
    ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){2,2},
        (size_t[]){0,0}, NULL, NULL, &err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
    
    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){2,2},
        (size_t[]){0,1}, (size_t[]){0,0}, NULL, &err));
    ASSERT_EQUAL(INFORM_EKZERO, err);
}

UNIT(BlackBoxHistoryFutureTooLong)
{
    inform_error err = INFORM_SUCCESS;
    int series[] = {0,1,1,1,0,1};
    ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){2,2},
        (size_t[]){4,0}, NULL, NULL, &err));
    ASSERT_EQUAL(INFORM_EKLONG, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){2,2},
        (size_t[]){2,4}, NULL, NULL, &err));
    ASSERT_EQUAL(INFORM_EKLONG, err);
    
    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){2,2},
        (size_t[]){0,1}, (size_t[]){4,0}, NULL, &err));
    ASSERT_EQUAL(INFORM_EKLONG, err);
    
    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box(series, 2, 1, 3, (int[]){2,2},
        (size_t[]){0,1}, (size_t[]){1,3}, NULL, &err));
    ASSERT_EQUAL(INFORM_EKLONG, err);
}

UNIT(BlackBoxEncodingError)
{
    inform_error err = INFORM_SUCCESS;
    {
        int series[32] = {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,
                          0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_black_box(series, 1, 1, 32, (int[]){2},
            (size_t[]){31}, NULL, NULL, &err));
        ASSERT_EQUAL(INFORM_EENCODE, err);
    }
    {
        int series[32] = {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,
                          0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_black_box(series, 1, 1, 32, (int[]){4},
            (size_t[]){16}, NULL, NULL, &err));
        ASSERT_EQUAL(INFORM_EENCODE, err);
    }
    {
        int series[32] = {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,
                          0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_black_box(series, 1, 1, 32, (int[]){4},
            (size_t[]){29}, (size_t[]){2}, NULL, &err));
        ASSERT_EQUAL(INFORM_EENCODE, err);
    }
    {
        int series[38] = {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,
                          0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0};
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_black_box(series, 2, 1, 16, (int[]){2,2},
            (size_t[]){15, 16}, NULL, NULL, &err));
        ASSERT_EQUAL(INFORM_EENCODE, err);
    }
    {
        int series[38] = {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,
                          0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0};
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_black_box(series, 2, 1, 16, (int[]){2,4},
            (size_t[]){15, 8}, NULL, NULL, &err));
        ASSERT_EQUAL(INFORM_EENCODE, err);
    }
    {
        int series[38] = {0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,
                          0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0};
        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_black_box(series, 2, 1, 16, (int[]){2,3},
            (size_t[]){10, 5}, (size_t[]){4,6}, NULL, &err));
        ASSERT_EQUAL(INFORM_EENCODE, err);
    }
}

UNIT(BlackBoxAllocates)
{
    inform_error err = INFORM_SUCCESS;
    int *box = inform_black_box((int[]){0,1,1,0,1,0}, 1, 1, 6, (int[]){2},
        NULL, NULL, NULL, &err);
    ASSERT_NOT_NULL(box);
    ASSERT_TRUE(inform_succeeded(&err));
    free(box);
}

UNIT(BlackBoxSingleSeries)
{
    inform_error err = INFORM_SUCCESS;
    {
        int box[8];
        int series[8] = {0,1,1,0,1,1,0,0};
        inform_black_box(series, 1, 1, 8, (int[]){2}, NULL, NULL, box, &err);
        for (size_t i = 0; i < 8; ++i)
            ASSERT_EQUAL(series[i], box[i]);
    }
    {
        int box[8];
        int series[8] = {0,1,1,0,1,1,0,0};
        inform_black_box(series, 1, 1, 8, (int[]){2}, (size_t[]){1}, NULL, box, &err);
        for (size_t i = 0; i < 8; ++i)
            ASSERT_EQUAL(series[i], box[i]);
    }
    {
        int box[7];
        int series[8] = {0,1,1,0,1,1,0,0};
        int expect[7] = {1,3,2,1,3,2,0};
        inform_black_box(series, 1, 1, 8, (int[]){2}, (size_t[]){2}, NULL, box, &err);
        for (size_t i = 0; i < 7; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[6];
        int series[8] = {0,1,1,0,1,1,0,0};
        int expect[6] = {3,6,5,3,6,4};
        inform_black_box(series, 1, 1, 8, (int[]){2}, (size_t[]){3}, NULL, box, &err);
        for (size_t i = 0; i < 6; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[7];
        int series[8] = {0,1,1,0,1,1,0,0};
        int expect[7] = {1,3,2,1,3,2,0};
        inform_black_box(series, 1, 1, 8, (int[]){2}, NULL, (size_t[]){1}, box, &err);
        for (size_t i = 0; i < 7; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[7];
        int series[8] = {0,1,1,0,1,1,0,0};
        int expect[7] = {1,3,2,1,3,2,0};
        inform_black_box(series, 1, 1, 8, (int[]){2}, (size_t[]){1}, (size_t[]){1}, box, &err);
        for (size_t i = 0; i < 7; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[6];
        int series[8] = {0,1,1,0,1,1,0,0};
        int expect[6] = {3,6,5,3,6,4};
        inform_black_box(series, 1, 1, 8, (int[]){2}, NULL, (size_t[]){2}, box, &err);
        for (size_t i = 0; i < 6; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[6];
        int series[8] = {0,1,1,0,1,1,0,0};
        int expect[6] = {3,6,5,3,6,4};
        inform_black_box(series, 1, 1, 8, (int[]){2}, (size_t[]){1}, (size_t[]){2}, box, &err);
        for (size_t i = 0; i < 6; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[6];
        int series[8] = {0,1,2,0,1,1,0,2};
        int expect[6] = {5,15,19,4,12,11};
        inform_black_box(series, 1, 1, 8, (int[]){3}, (size_t[]){1}, (size_t[]){2}, box, &err);
        for (size_t i = 0; i < 6; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
}

UNIT(BlackBoxSingleSeriesEnsemble)
{
    inform_error err = INFORM_SUCCESS;
    {
        int box[16];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        inform_black_box(series, 1, 2, 8, (int[]){2}, NULL, NULL, box, &err);
        for (size_t i = 0; i < 16; ++i)
            ASSERT_EQUAL(series[i], box[i]);
    }
    {
        int box[16];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        inform_black_box(series, 1, 2, 8, (int[]){2}, (size_t[]){1}, NULL, box, &err);
        for (size_t i = 0; i < 16; ++i)
            ASSERT_EQUAL(series[i], box[i]);
    }
    {
        int box[14];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[14] = {1,3,2,1,3,2,0,
                          0,1,3,2,1,2,1};
        inform_black_box(series, 1, 2, 8, (int[]){2}, (size_t[]){2}, NULL, box, &err);
        for (size_t i = 0; i < 14; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[12];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[12] = {3,6,5,3,6,4,
                          1,3,6,5,2,5};
        inform_black_box(series, 1, 2, 8, (int[]){2}, (size_t[]){3}, NULL, box, &err);
        for (size_t i = 0; i < 12; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[14];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[14] = {1,3,2,1,3,2,0,
                          0,1,3,2,1,2,1};
        inform_black_box(series, 1, 2, 8, (int[]){2}, NULL, (size_t[]){1}, box, &err);
        for (size_t i = 0; i < 14; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[14];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[14] = {1,3,2,1,3,2,0,
                          0,1,3,2,1,2,1};
        inform_black_box(series, 1, 2, 8, (int[]){2}, (size_t[]){1}, (size_t[]){1}, box, &err);
        for (size_t i = 0; i < 14; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[12];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[12] = {3,6,5,3,6,4,
                          1,3,6,5,2,5};
        inform_black_box(series, 1, 2, 8, (int[]){2}, NULL, (size_t[]){2}, box, &err);
        for (size_t i = 0; i < 12; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[12];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[12] = {3,6,5,3,6,4,
                          1,3,6,5,2,5};
        inform_black_box(series, 1, 2, 8, (int[]){2}, (size_t[]){1}, (size_t[]){2}, box, &err);
        for (size_t i = 0; i < 12; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[12];
        int series[16] = {0,1,2,0,1,1,0,2,
                          2,1,1,2,0,0,1,2};
        int expect[12] = {5,15,19,4,12,11,
                          22,14,15,18,1,5};
        inform_black_box(series, 1, 2, 8, (int[]){3}, (size_t[]){1}, (size_t[]){2}, box, &err);
        for (size_t i = 0; i < 12; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
}

UNIT(BlackBoxMultipleSeries)
{
    inform_error err = INFORM_SUCCESS;
    {
        int box[8];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[8] = {0,2,3,1,2,3,0,1};
        inform_black_box(series, 2, 1, 8, (int[]){2,2}, NULL, NULL, box, &err);
        for (size_t i = 0; i < 8; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[8];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[8] = {0,2,3,1,2,3,0,1};
        inform_black_box(series, 2, 1, 8, (int[]){2,2}, (size_t[]){1,1}, NULL, box, &err);
        for (size_t i = 0; i < 8; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[7];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[7] = {2,7,5,2,7,4,1};
        inform_black_box(series, 2, 1, 8, (int[]){2,2}, (size_t[]){2,1}, NULL, box, &err);
        for (size_t i = 0; i < 7; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[7];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[7] = {4,5,3,6,5,2,1};
        inform_black_box(series, 2, 1, 8, (int[]){2,2}, (size_t[]){1,2}, NULL, box, &err);
        for (size_t i = 0; i < 7; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[7];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[7] = {4,13,11,6,13,10,1};
        inform_black_box(series, 2, 1, 8, (int[]){2,2}, (size_t[]){2,2}, NULL, box, &err);
        for (size_t i = 0; i < 7; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[7];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[7] = {2,6,5,3,6,5,0};
        inform_black_box(series, 2, 1, 8, (int[]){2,2}, NULL, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 7; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[7];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[7] = {4,13,11,6,13,10,1};
        inform_black_box(series, 2, 1, 8, (int[]){2,2}, NULL, (size_t[]){1,1}, box, &err);
        for (size_t i = 0; i < 7; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[7];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[7] = {0,5,7,2,5,6,1};
        inform_black_box(series, 2, 1, 8, (int[]){2,2}, NULL, (size_t[]){0,1}, box, &err);
        for (size_t i = 0; i < 7; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[6];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,0,1,1,0,1,0,1};
        int expect[6] = {6,13,11,6,13,8};
        inform_black_box(series, 2, 1, 8, (int[]){2,2}, (size_t[]){2,1}, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 6; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[6];
        int series[16] = {0,1,2,0,1,1,0,2,
                          0,0,1,1,0,1,0,1};
        int expect[6] = {10,31,39,8,25,22};
        inform_black_box(series, 2, 1, 8, (int[]){3,2}, (size_t[]){2,1}, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 6; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[6];
        int series[16] = {0,1,1,0,1,1,0,0,
                          0,2,1,1,0,2,0,1};
        int expect[6] = {11,19,16,9,20,12};
        inform_black_box(series, 2, 1, 8, (int[]){2,3}, (size_t[]){2,1}, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 6; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[6];
        int series[16] = {0,3,1,0,1,1,2,0,
                          0,1,1,1,0,1,0,1};
        int expect[6] = {27,105,35,10,45,48};
        inform_black_box(series, 2, 1, 8, (int[]){4,2}, (size_t[]){2,1}, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 6; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[6];
        int series[16] = {0,1,1,1,0,1,0,1,
                          0,3,1,0,1,1,2,0};
        int expect[6] = {15,29,24,21,9,22};
        inform_black_box(series, 2, 1, 8, (int[]){2,4}, (size_t[]){2,1}, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 6; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
}

UNIT(BlackBoxMultipleSeriesEnsemble)
{
    inform_error err = INFORM_SUCCESS;
    {
        int box[16];
        int series[32] = {0,1,1,0,1,1,0,0, 0,0,1,1,0,1,0,1,
                          1,1,0,1,0,0,1,0, 0,0,0,1,0,0,1,0};
        int expect[16] = {1,3,2,1,2,2,1,0, 0,0,2,3,0,2,1,2};
        inform_black_box(series, 2, 2, 8, (int[]){2,2}, NULL, NULL, box, &err);
        for (size_t i = 0; i < 16; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[16];
        int series[32] = {0,1,1,0,1,1,0,0, 0,0,1,1,0,1,0,1,
                          1,1,0,1,0,0,1,0, 0,0,0,1,0,0,1,0};
        int expect[16] = {1,3,2,1,2,2,1,0, 0,0,2,3,0,2,1,2};
        inform_black_box(series, 2, 2, 8, (int[]){2,2}, (size_t[]){1,1}, NULL, box, &err);
        for (size_t i = 0; i < 16; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[14];
        int series[32] = {0,1,1,0,1,1,0,0, 0,0,1,1,0,1,0,1,
                          1,1,0,1,0,0,1,0, 0,0,0,1,0,0,1,0};
        int expect[14] = {3,6,5,2,6,5,0, 0,2,7,4,2,5,2};
        inform_black_box(series, 2, 2, 8, (int[]){2,2}, (size_t[]){2,1}, NULL, box, &err);
        for (size_t i = 0; i < 14; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[14];
        int series[32] = {0,1,1,0,1,1,0,0, 0,0,1,1,0,1,0,1,
                          1,1,0,1,0,0,1,0, 0,0,0,1,0,0,1,0};
        int expect[14] = {7,6,1,6,4,1,2, 0,4,5,2,4,1,6};
        inform_black_box(series, 2, 2, 8, (int[]){2,2}, (size_t[]){1,2}, NULL, box, &err);
        for (size_t i = 0; i < 14; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[14];
        int series[32] = {0,1,1,0,1,1,0,0, 0,0,1,1,0,1,0,1,
                          1,1,0,1,0,0,1,0, 0,0,0,1,0,0,1,0};
        int expect[14] = {7,14,9,6,12,9,2, 0,4,13,10,4,9,6};
        inform_black_box(series, 2, 2, 8, (int[]){2,2}, (size_t[]){2,2}, NULL, box, &err);
        for (size_t i = 0; i < 14; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[14];
        int series[32] = {0,1,1,0,1,1,0,0, 0,0,1,1,0,1,0,1,
                          1,1,0,1,0,0,1,0, 0,0,0,1,0,0,1,0};
        int expect[14] = {3,7,4,3,6,4,1, 0,2,6,5,2,4,3};
        inform_black_box(series, 2, 2, 8, (int[]){2,2}, NULL, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 14; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[14];
        int series[32] = {0,1,1,0,1,1,0,0, 0,0,1,1,0,1,0,1,
                          1,1,0,1,0,0,1,0, 0,0,0,1,0,0,1,0};
        int expect[14] = {7,14,9,6,12,9,2, 0,4,13,10,4,9,6};
        inform_black_box(series, 2, 2, 8, (int[]){2,2}, NULL, (size_t[]){1,1}, box, &err);
        for (size_t i = 0; i < 14; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[14];
        int series[32] = {0,1,1,0,1,1,0,0, 0,0,1,1,0,1,0,1,
                          1,1,0,1,0,0,1,0, 0,0,0,1,0,0,1,0};
        int expect[14] = {3,6,5,2,4,5,2, 0,0,5,6,0,5,2};
        inform_black_box(series, 2, 2, 8, (int[]){2,2}, NULL, (size_t[]){0,1}, box, &err);
        for (size_t i = 0; i < 14; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[12];
        int series[32] = {0,1,1,0,1,1,0,0, 0,0,1,1,0,1,0,1,
                          1,1,0,1,0,0,1,0, 0,0,0,1,0,0,1,0};
        int expect[12] = {7,12,11,6,12,9, 2,6,13,10,4,11};
        inform_black_box(series, 2, 2, 8, (int[]){2,2}, (size_t[]){2,1}, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 12; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[12];
        int series[32] = {0,1,2,0,1,1,0,2, 0,0,1,1,0,1,0,1,
                          1,0,1,1,0,1,0,0, 1,1,0,1,0,0,1,0};
        int expect[12] = {10,31,39,8,25,22, 3,8,25,20,6,21};
        inform_black_box(series, 2, 2, 8, (int[]){3,2}, (size_t[]){2,1}, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 12; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[12];
        int series[32] = {1,0,1,1,0,1,0,0, 1,1,0,1,0,0,1,0,
                          0,1,2,0,1,1,0,2, 0,0,1,1,0,1,0,1};
        int expect[12] = {16,11,18,16,7,12, 18,16,7,12,4,6};
        inform_black_box(series, 2, 2, 8, (int[]){2,3}, (size_t[]){2,1}, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 12; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[12];
        int series[32] = {0,3,1,0,1,1,2,0, 0,1,2,1,0,1,3,1,
                          0,1,1,0,1,0,1,1, 0,0,1,1,0,1,0,0};
        int expect[12] = {27,105,34,11,44,49, 12,51,73,34,15,58};
        inform_black_box(series, 2, 2, 8, (int[]){4,2}, (size_t[]){2,1}, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 12; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
    {
        int box[12];
        int series[32] = {0,1,1,0,1,0,1,1, 0,0,1,1,0,1,0,0,
                          0,3,1,0,1,1,2,0, 0,1,2,1,0,1,3,1};
        int expect[12] = {15,25,20,9,21,14, 5,14,25,20,9,19};
        inform_black_box(series, 2, 2, 8, (int[]){2,4}, (size_t[]){2,1}, (size_t[]){1,0}, box, &err);
        for (size_t i = 0; i < 12; ++i)
            ASSERT_EQUAL(expect[i], box[i]);
    }
}

UNIT(BlackBoxPartsNullSeries)
{
    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box_parts(NULL, 0, 0, NULL, NULL, 0, NULL, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(BlackBoxPartsEmptySeries)
{
    inform_error err = INFORM_SUCCESS;
    int series[] = {0,1,1,1,0};
    ASSERT_NULL(inform_black_box_parts(series, 0, 0, NULL, NULL, 0, NULL, &err));
    ASSERT_EQUAL(INFORM_ENOSOURCES, err);
}

UNIT(BlackBoxPartsBadBase)
{
    inform_error err = INFORM_SUCCESS;
    int series[] = {0,1,1,1,0,1};
    ASSERT_NULL(inform_black_box_parts(series, 2, 3, NULL, NULL, 0, NULL,
        &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box_parts(series, 2, 3, (int[]){0,0}, NULL, 0,
        NULL, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box_parts(series, 2, 3, (int[]){1,1}, NULL, 0,
        NULL, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box_parts(series, 2, 3, (int[]){-1,1}, NULL, 0,
        NULL, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);
}

UNIT(BlackBoxPartsNegativeState)
{
    inform_error err;
    {
        err = INFORM_SUCCESS;
        int series[] = {0,-1,1,1,0,1};
        ASSERT_NULL(inform_black_box_parts(series, 2, 3, (int[]){2,2}, NULL, 0,
            NULL, &err));
        ASSERT_EQUAL(INFORM_ENEGSTATE, err);
    }
    {
        err = INFORM_SUCCESS;
        int series[] = {0,1,1,1,0,-1};
        ASSERT_NULL(inform_black_box_parts(series, 2, 3, (int[]){2,2}, NULL, 0,
            NULL, &err));
        ASSERT_EQUAL(INFORM_ENEGSTATE, err);
    }
}

UNIT(BlackBoxPartsShortParts)
{
    inform_error err = INFORM_SUCCESS;
    int series[] = {0,1,1,1,0,1};
    size_t parts[] = {0,1};
 
    ASSERT_NULL(inform_black_box_parts(series, 2, 3, (int[]){2,2}, NULL, 0,
        NULL, &err));
    ASSERT_EQUAL(INFORM_EPARTS, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_black_box_parts(series, 2, 3, (int[]){2,2}, parts, 0,
        NULL, &err));
    ASSERT_EQUAL(INFORM_EPARTS, err);
}

UNIT(BlackBoxPartsInvalid)
{
    inform_error err = INFORM_SUCCESS;
    int series[] = {0,1,1,1,0,1};
    {
        size_t parts[] = {1,1};
        ASSERT_NULL(inform_black_box_parts(series, 2, 3, (int[]){2,2}, parts, 1,
            NULL, &err));
        ASSERT_EQUAL(INFORM_EPARTS, err);
    }
    {
        size_t parts[] = {2,0};
        ASSERT_NULL(inform_black_box_parts(series, 2, 3, (int[]){2,2}, parts, 2,
            NULL, &err));
        ASSERT_EQUAL(INFORM_EPARTS, err);
    }
    {
        size_t parts[] = {0,1};
        ASSERT_NULL(inform_black_box_parts(series, 2, 3, (int[]){2,2}, parts, 3,
            NULL, &err));
        ASSERT_EQUAL(INFORM_EPARTS, err);
    }
    {
        size_t parts[] = {0,1};
        ASSERT_NULL(inform_black_box_parts(series, 2, 3, (int[]){2,2}, parts, 1,
            NULL, &err));
        ASSERT_EQUAL(INFORM_EPARTS, err);
    }
}

UNIT(BlackBoxPartsOnePartition)
{
    {
        inform_error err = INFORM_SUCCESS;
        int series[] = {0,1,1,1,0,1};
        int expected[3], got[4];
        inform_black_box(series, 2, 1, 3, (int[]){2,2}, NULL, NULL, expected, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        inform_black_box_parts(series, 2, 3, (int[]){2,2}, (size_t[]){0,0}, 1,
            got, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        for (size_t i = 0; i < 3; ++i)
        {
            ASSERT_EQUAL(expected[i], got[i]);
        }
        ASSERT_EQUAL(4, got[3]);
    }
    {
        inform_error err = INFORM_SUCCESS;
        int series[] = {0,1,1,1,0,1,0,0,1};
        int expected[3], got[4];
        inform_black_box(series, 3, 1, 3, (int[]){2,2,2}, NULL, NULL, expected, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        inform_black_box_parts(series, 3, 3, (int[]){2,2,2}, (size_t[]){0,0,0},
            1, got, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        for (size_t i = 0; i < 3; ++i)
        {
            ASSERT_EQUAL(expected[i], got[i]);
        }
        ASSERT_EQUAL(8, got[3]);
    }
}

UNIT(BlackBoxPartsTwoPartitions)
{
    {
        inform_error err = INFORM_SUCCESS;
        int series[] = {0,1,1,1,0,1};
        int got[8];
        inform_black_box_parts(series, 2, 3, (int[]){2,2}, (size_t[]){0,1}, 2,
            got, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        for (size_t i = 0; i < 6; ++i)
        {
            ASSERT_EQUAL(series[i], got[i]);
        }
        ASSERT_EQUAL(2, got[6]);
        ASSERT_EQUAL(2, got[7]);
    }
    {
        inform_error err = INFORM_SUCCESS;
        int series[] = {0,1,1,1,0,1,0,0,1};
        int expected[3], got[8];
        inform_black_box(series, 2, 1, 3, (int[]){2,2}, NULL, NULL, expected, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        inform_black_box_parts(series, 3, 3, (int[]){2,2,2}, (size_t[]){0,0,1},
            2, got, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        for (size_t i = 0; i < 3; ++i)
        {
            ASSERT_EQUAL(expected[i], got[i]);
        }
        for (size_t i = 0; i < 3; ++i)
        {
            ASSERT_EQUAL(series[i+6], got[i+3]);
        }
        ASSERT_EQUAL(4, got[6]);
        ASSERT_EQUAL(2, got[7]);
    }
    {
        inform_error err = INFORM_SUCCESS;
        int series[] = {0,1,1,1,0,1,0,0,1};
        int subseries[] = {0,1,1,0,0,1};
        int expected[3], got[8];
        inform_black_box(subseries, 2, 1, 3, (int[]){2,2}, NULL, NULL, expected, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        inform_black_box_parts(series, 3, 3, (int[]){2,2,2}, (size_t[]){0,1,0},
            2, got, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        for (size_t i = 0; i < 3; ++i)
        {
            ASSERT_EQUAL(expected[i], got[i]);
        }
        for (size_t i = 0; i < 3; ++i)
        {
            ASSERT_EQUAL(series[i+3], got[i+3]);
        }
        ASSERT_EQUAL(4, got[6]);
        ASSERT_EQUAL(2, got[7]);
    }
    {
        inform_error err = INFORM_SUCCESS;
        int series[] = {0,1,1,1,0,1,0,0,1};
        int expected[3], got[8];
        inform_black_box(series + 3, 2, 1, 3, (int[]){2,2}, NULL, NULL, expected, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        inform_black_box_parts(series, 3, 3, (int[]){2,2,2}, (size_t[]){0,1,1},
            2, got, &err);
        ASSERT_TRUE(inform_succeeded(&err));
        for (size_t i = 0; i < 3; ++i)
        {
            ASSERT_EQUAL(series[i], got[i]);
        }
        for (size_t i = 0; i < 3; ++i)
        {
            ASSERT_EQUAL(expected[i], got[i+3]);
        }
        ASSERT_EQUAL(2, got[6]);
        ASSERT_EQUAL(4, got[7]);
    }
}

UNIT(BlackBoxPartsThreePartitions)
{
    inform_error err = INFORM_SUCCESS;
    int series[] = {0,1,1,1,0,1,0,0,1};
    int got[12];
    inform_black_box_parts(series, 3, 3, (int[]){2,2,2}, (size_t[]){0,1,2}, 3,
        got, &err);
    ASSERT_TRUE(inform_succeeded(&err));
    for (size_t i = 0; i < 9; ++i)
    {
        ASSERT_EQUAL(series[i], got[i]);
    }
    ASSERT_EQUAL(2, got[9]);
    ASSERT_EQUAL(2, got[10]);
    ASSERT_EQUAL(2, got[11]);
}

UNIT(PartitionsFirst)
{
    size_t *parts = NULL;
    ASSERT_NULL((parts = inform_first_partitioning(0)));

    for (size_t n = 1; n < 5; ++n)
    {
        ASSERT_NOT_NULL((parts = inform_first_partitioning(n)));
        for (size_t i = 0; i < n; ++i)
        {
            ASSERT_EQUAL_U(0, parts[i]);
        }
        free(parts);
    }
}

UNIT(PartitionsNext1)
{
    size_t const size = 1;
    size_t *parts = inform_first_partitioning(size);
    ASSERT_NOT_NULL(parts);
    ASSERT_EQUAL_U(0, parts[0]);

    ASSERT_EQUAL_U(0, inform_next_partitioning(parts, size));

    free(parts);
}

UNIT(PartitionsNext2)
{
    size_t const size = 2;
    size_t *parts = inform_first_partitioning(size);
    ASSERT_NOT_NULL(parts);

    ASSERT_EQUAL_U(2, inform_next_partitioning(parts, size));
    size_t const expected[] = {0,1};
    for (size_t i = 0; i < size; ++i)
        ASSERT_EQUAL_U(expected[i], parts[i]);

    free(parts);
}

UNIT(PartitionsNext3)
{
    size_t const size = 3;
    size_t *parts = inform_first_partitioning(size);
    ASSERT_NOT_NULL(parts);

    size_t const expected_size[4] = {2,2,2,3};
    size_t const *expected[] = {
        (size_t[]){0,0,1},
        (size_t[]){0,1,0},
        (size_t[]){0,1,1},
        (size_t[]){0,1,2},
    };

    size_t i = 0, n = 0;
    while ((n = inform_next_partitioning(parts, size)) && i < 4)
    {
        ASSERT_EQUAL_U(expected_size[i], n);
        for (size_t j = 0; j < size; ++j)
            ASSERT_EQUAL_U(expected[i][j], parts[j]);
        ++i;
    }
    ASSERT_EQUAL_U(0, inform_next_partitioning(parts, size));

    free(parts);
}

UNIT(PartitionsNext4)
{
    size_t const size = 4;
    size_t *parts = inform_first_partitioning(size);
    ASSERT_NOT_NULL(parts);

    size_t const expected_size[14] = {2,2,2,3,2,2,3,2,2,3,3,3,3,4};
    size_t const *expected[] = {
        (size_t[]){0,0,0,1},
        (size_t[]){0,0,1,0},
        (size_t[]){0,0,1,1},
        (size_t[]){0,0,1,2},
        (size_t[]){0,1,0,0},
        (size_t[]){0,1,0,1},
        (size_t[]){0,1,0,2},
        (size_t[]){0,1,1,0},
        (size_t[]){0,1,1,1},
        (size_t[]){0,1,1,2},
        (size_t[]){0,1,2,0},
        (size_t[]){0,1,2,1},
        (size_t[]){0,1,2,2},
        (size_t[]){0,1,2,3},
    };

    size_t i = 0, n = 0;
    while ((n = inform_next_partitioning(parts, size)) && i < 14)
    {
        ASSERT_EQUAL_U(expected_size[i], n);
        for (size_t j = 0; j < size; ++j)
            ASSERT_EQUAL_U(expected[i][j], parts[j]);
        ++i;
    }
    ASSERT_EQUAL_U(0, inform_next_partitioning(parts, size));

    free(parts);
}

static size_t bell_number(size_t n)
{
    size_t bell_number = 0;
    size_t *partitioning = inform_first_partitioning(n);
    do
    {
        ++bell_number;
    } while (inform_next_partitioning(partitioning, n));
    free(partitioning);
    return bell_number;
}

UNIT(PartitionsBellNumbers)
{
    size_t const bell_numbers[11] = {
        1, 2, 5, 15, 52, 203, 877, 4140, 21147, 115975, 678570,
    };
    for (size_t i = 1; i <= 11; ++i)
        ASSERT_EQUAL_U(bell_numbers[i-1], bell_number(i));
}

BEGIN_SUITE(Utilities)
    ADD_UNIT(RangeNullSeries)
    ADD_UNIT(RangeEmpty)
    ADD_UNIT(RangeNullMinMax)
    ADD_UNIT(RangeMinMax)

    ADD_UNIT(BinNullSeries)
    ADD_UNIT(BinEmpty)
    ADD_UNIT(BinInvalidBinning)
    ADD_UNIT(BinNullBinned)
    ADD_UNIT(BinNoRange)
    ADD_UNIT(BinTwo)
    ADD_UNIT(BinThree)
    ADD_UNIT(BinSix)

    ADD_UNIT(BinStepNullSeries)
    ADD_UNIT(BinStepEmpty)
    ADD_UNIT(BinStepInvalidBinning)
    ADD_UNIT(BinStepNullBinned)
    ADD_UNIT(BinStepTwo)
    ADD_UNIT(BinStepFiveHalves)
    ADD_UNIT(BinStepOne)
    ADD_UNIT(BinStepHalf)

    ADD_UNIT(BinBoundsNullSeries)
    ADD_UNIT(BinBoundsEmpty)
    ADD_UNIT(BinBoundsInvalidBinning)
    ADD_UNIT(BinBoundsNullBinned)
    ADD_UNIT(BinBoundsOne)
    ADD_UNIT(BinBoundsTwo)
    ADD_UNIT(BinBoundsNone)
    ADD_UNIT(BinBoundsAll)

    ADD_UNIT(CoalesceNullSeries)
    ADD_UNIT(CoalesceEmpty)
    ADD_UNIT(CoalesceNullCoalesce)
    ADD_UNIT(CoalesceUnchanged)
    ADD_UNIT(CoalesceShifted)
    ADD_UNIT(CoalesceNoGaps)

    ADD_UNIT(EncodeNullState)
    ADD_UNIT(EncodeEmpty)
    ADD_UNIT(EncodeBadBase)
    ADD_UNIT(EncodeToLarge)
    ADD_UNIT(EncodeOneBaseTwo)
    ADD_UNIT(EncodeOneBaseThree)
    ADD_UNIT(EncodeTwoBaseTwo)
    ADD_UNIT(EncodeTwoBaseThree)

    ADD_UNIT(DecodeNegativeEncoding)
    ADD_UNIT(DecodeBadBase)
    ADD_UNIT(DecodeToNullState)
    ADD_UNIT(DecodeToEmptyState)
    ADD_UNIT(DecodeBaseTwo)
    ADD_UNIT(DecodeBaseThree)

    ADD_UNIT(DecodeEncode)

    ADD_UNIT(RandomInt)
    ADD_UNIT(RandomIntMinMax)

    ADD_UNIT(TPMNullSeries)
    ADD_UNIT(TPMNoInits)
    ADD_UNIT(TPMShortSeries)
    ADD_UNIT(TPMInvalidBase)
    ADD_UNIT(TPMInvalidState)
    ADD_UNIT(TPMAllocates)
    ADD_UNIT(TPMNoAllocation)
    ADD_UNIT(TPMZeroRow)
    ADD_UNIT(TPMBase2)
    ADD_UNIT(TPMBase3)

    ADD_UNIT(BlackBoxNullSeries)
    ADD_UNIT(BlackBoxEmptySeries)
    ADD_UNIT(BlackBoxNoInits)
    ADD_UNIT(BlackBoxShortSeries)
    ADD_UNIT(BlackBoxBadBase)
    ADD_UNIT(BlackBoxNegativeState)
    ADD_UNIT(BlackBoxInvalidState)
    ADD_UNIT(BlackBoxInvalidHistory)
    ADD_UNIT(BlackBoxHistoryFutureTooLong)
    ADD_UNIT(BlackBoxEncodingError)
    ADD_UNIT(BlackBoxAllocates)
    ADD_UNIT(BlackBoxSingleSeries)
    ADD_UNIT(BlackBoxSingleSeriesEnsemble)
    ADD_UNIT(BlackBoxMultipleSeries)
    ADD_UNIT(BlackBoxMultipleSeriesEnsemble)

    ADD_UNIT(BlackBoxPartsNullSeries)
    ADD_UNIT(BlackBoxPartsEmptySeries)
    ADD_UNIT(BlackBoxPartsBadBase)
    ADD_UNIT(BlackBoxPartsNegativeState)
    ADD_UNIT(BlackBoxPartsShortParts)
    ADD_UNIT(BlackBoxPartsInvalid)
    ADD_UNIT(BlackBoxPartsOnePartition)
    ADD_UNIT(BlackBoxPartsTwoPartitions)
    ADD_UNIT(BlackBoxPartsThreePartitions)

    ADD_UNIT(PartitionsFirst)
    ADD_UNIT(PartitionsNext1)
    ADD_UNIT(PartitionsNext2)
    ADD_UNIT(PartitionsNext3)
    ADD_UNIT(PartitionsNext4)
    ADD_UNIT(PartitionsBellNumbers)
END_SUITE
