// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <ginger/unit.h>
#include <inform/dist.h>

UNIT(AllocZero)
{
    inform_dist *dist = inform_dist_alloc(0);
    ASSERT_NULL(dist);
}

UNIT(AllocOne)
{
    inform_dist *dist = inform_dist_alloc(1);
    ASSERT_NOT_NULL(dist);
    ASSERT_EQUAL(1, inform_dist_size(dist));
    ASSERT_EQUAL(0, inform_dist_counts(dist));
    ASSERT_FALSE(inform_dist_is_valid(dist));
    inform_dist_free(dist);
}

UNIT(AllocTwo)
{
    inform_dist *dist = inform_dist_alloc(2);
    ASSERT_NOT_NULL(dist);
    ASSERT_EQUAL(2, inform_dist_size(dist));
    ASSERT_EQUAL(0, inform_dist_counts(dist));
    ASSERT_FALSE(inform_dist_is_valid(dist));
    inform_dist_free(dist);
}

UNIT(GetNull)
{
    inform_dist *dist = NULL;
    ASSERT_EQUAL(0, inform_dist_get(dist, 0));
    ASSERT_EQUAL(0, inform_dist_get(dist, 1));
    ASSERT_EQUAL(0, inform_dist_get(dist, 2));
}

UNIT(SetNull)
{
    inform_dist *dist = NULL;
    ASSERT_EQUAL(0, inform_dist_set(dist, 0, 1));
    ASSERT_EQUAL(0, inform_dist_set(dist, 1, 1));
    ASSERT_EQUAL(0, inform_dist_set(dist, 2, 1));
}

UNIT(Set)
{
    inform_dist *dist = inform_dist_alloc(3);
    ASSERT_NOT_NULL(dist);
    ASSERT_FALSE(inform_dist_is_valid(dist));

    ASSERT_EQUAL(1, inform_dist_set(dist, 0, 1));
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL(2, inform_dist_set(dist, 1, 2));
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL(3, inform_dist_set(dist, 2, 3));
    ASSERT_TRUE(inform_dist_is_valid(dist));

    ASSERT_EQUAL(3, inform_dist_size(dist));
    ASSERT_EQUAL(6, inform_dist_counts(dist));

    for (size_t i = 0; i < inform_dist_size(dist); ++i)
    {
        inform_dist_set(dist, i, 0);
    }
    ASSERT_FALSE(inform_dist_is_valid(dist));
    ASSERT_EQUAL(3, inform_dist_size(dist));
    ASSERT_EQUAL(0, inform_dist_counts(dist));
    inform_dist_free(dist);
}

UNIT(Get)
{
    inform_dist *dist = inform_dist_alloc(3);
    ASSERT_NOT_NULL(dist);
    ASSERT_FALSE(inform_dist_is_valid(dist));

    ASSERT_EQUAL(1, inform_dist_set(dist, 0, 1));
    ASSERT_EQUAL(2, inform_dist_set(dist, 1, 2));
    ASSERT_EQUAL(3, inform_dist_set(dist, 2, 3));

    for (size_t i = 0; i < inform_dist_size(dist); ++i)
    {
        ASSERT_EQUAL(i+1, inform_dist_get(dist, i));
    }
    inform_dist_free(dist);
}

UNIT(ReallocNull)
{
    inform_dist *dist = NULL;
    inform_dist *resize = inform_dist_realloc(dist, 5);
    ASSERT_FALSE(resize == dist);
    ASSERT_NOT_NULL(resize);
    ASSERT_EQUAL(5, inform_dist_size(resize));
    ASSERT_EQUAL(0, inform_dist_counts(resize));
    for (size_t i = 0; i < inform_dist_size(resize); ++i)
    {
        ASSERT_EQUAL(0, inform_dist_get(resize,i));
    }
    inform_dist_free(resize);
}

UNIT(ReallocGrow)
{
    inform_dist *dist = inform_dist_alloc(3);
    ASSERT_NOT_NULL(dist);
    for (size_t i = 0; i < inform_dist_size(dist); ++i)
    {
        inform_dist_set(dist, i, (uint32_t) i+1);
    }
    ASSERT_EQUAL(3, inform_dist_size(dist));
    ASSERT_EQUAL(6, inform_dist_counts(dist));

    inform_dist *resized = inform_dist_realloc(dist, 5);
    ASSERT_NOT_NULL(resized);
    ASSERT_TRUE(resized == dist);
    ASSERT_EQUAL(5, inform_dist_size(resized));
    ASSERT_EQUAL(6, inform_dist_counts(resized));
    for (size_t i = 0; i < 3; ++i)
    {
        ASSERT_EQUAL(i+1, inform_dist_get(resized, i));
    }
    for (size_t i = 3; i < inform_dist_size(resized); ++i)
    {
        ASSERT_EQUAL(0, inform_dist_get(resized, i));
    }
    inform_dist_free(resized);
}

UNIT(ReallocShrink)
{
    inform_dist *dist = inform_dist_alloc(5);
    ASSERT_NOT_NULL(dist);
    for (size_t i = 0; i < inform_dist_size(dist); ++i)
    {
        inform_dist_set(dist, i, (uint32_t) i+1);
    }
    ASSERT_EQUAL(5, inform_dist_size(dist));
    ASSERT_EQUAL(15, inform_dist_counts(dist));

    inform_dist *resized = inform_dist_realloc(dist, 3);
    ASSERT_NOT_NULL(resized);
    ASSERT_TRUE(resized == dist);
    ASSERT_EQUAL(3, inform_dist_size(resized));
    ASSERT_EQUAL(6, inform_dist_counts(resized));
    for (size_t i = 0; i < inform_dist_size(resized); ++i)
    {
        ASSERT_EQUAL(i+1, inform_dist_get(resized, i));
    }
    inform_dist_free(resized);
}

UNIT(CopyNull)
{
    inform_dist *dest = inform_dist_alloc(5);
    ASSERT_NOT_NULL(dest);
    ASSERT_NULL(inform_dist_copy(NULL, dest));
    inform_dist_free(dest);
}

UNIT(CopyToNULL)
{
    inform_dist *source = inform_dist_alloc(5);
    ASSERT_NOT_NULL(source);
    for (size_t i = 0; i < inform_dist_size(source); ++i)
    {
        inform_dist_set(source, i, (uint32_t) i+1);
    }
    inform_dist *dest = NULL;
    ASSERT_NULL(dest);
    dest = inform_dist_copy(source, dest);
    ASSERT_NOT_NULL(dest);
    ASSERT_EQUAL(inform_dist_size(source), inform_dist_size(dest));
    ASSERT_EQUAL(inform_dist_counts(source), inform_dist_counts(dest));
    for (size_t i = 0; i < inform_dist_size(source); ++i)
    {
        ASSERT_EQUAL(inform_dist_get(source,i), inform_dist_get(dest,i));
        ASSERT_EQUAL(i+1, inform_dist_get(dest,i));
    }
    inform_dist_free(dest);
    inform_dist_free(source);
}

UNIT(CopySamePlace)
{
    inform_dist *source = inform_dist_alloc(5);
    inform_dist *dest = source;
    ASSERT_TRUE(source == inform_dist_copy(source, dest));
    inform_dist_free(source);
}

UNIT(CopySameSize)
{
    inform_dist *source = inform_dist_alloc(3);
    for (size_t i = 0; i < inform_dist_size(source); ++i)
    {
        inform_dist_set(source, i, (uint32_t) i+1);
    }
    inform_dist *dest = inform_dist_alloc(3);

    inform_dist *redest;
    redest = inform_dist_copy(source, dest);
    ASSERT_NOT_NULL(redest);
    ASSERT_TRUE(redest == dest);
    ASSERT_EQUAL(inform_dist_size(source), inform_dist_size(dest));
    ASSERT_EQUAL(inform_dist_counts(source), inform_dist_counts(dest));
    for (size_t i = 0; i < inform_dist_size(source); ++i)
    {
        ASSERT_EQUAL(inform_dist_get(source,i), inform_dist_get(dest,i));
        ASSERT_EQUAL(i+1, inform_dist_get(dest,i));
    }
    inform_dist_free(dest);
    inform_dist_free(source);
}

UNIT(CopyResize)
{
    inform_dist *source = inform_dist_alloc(3);
    for (size_t i = 0; i < inform_dist_size(source); ++i)
    {
        inform_dist_set(source, i, (uint32_t) i+1);
    }
    inform_dist *dest = inform_dist_alloc(5);

    inform_dist *redest;
    redest = inform_dist_copy(source, dest);
    ASSERT_NOT_NULL(redest);
    ASSERT_TRUE(redest == dest);
    ASSERT_EQUAL(inform_dist_size(source), inform_dist_size(dest));
    ASSERT_EQUAL(inform_dist_counts(source), inform_dist_counts(dest));
    for (size_t i = 0; i < inform_dist_size(source); ++i)
    {
        ASSERT_EQUAL(inform_dist_get(source,i), inform_dist_get(dest,i));
        ASSERT_EQUAL(i+1, inform_dist_get(dest,i));
    }
    inform_dist_free(dest);
    inform_dist_free(source);
}

UNIT(DupNull)
{
    inform_dist *dist = NULL;
    inform_dist *dist2 = inform_dist_dup(dist);
    ASSERT_NULL(dist2);
}

UNIT(Dup)
{
    inform_dist *dist = inform_dist_alloc(5);
    ASSERT_NOT_NULL(dist);
    for (size_t i = 0; i < inform_dist_size(dist); ++i)
    {
        inform_dist_set(dist, i, (uint32_t) (i*i));
    }
    inform_dist *dup = inform_dist_dup(dist);
    ASSERT_NOT_NULL(dup);
    ASSERT_EQUAL(inform_dist_size(dist), inform_dist_size(dup));
    ASSERT_EQUAL(inform_dist_counts(dist), inform_dist_counts(dup));
    for (size_t i = 0; i < inform_dist_size(dist); ++i)
    {
        ASSERT_EQUAL(inform_dist_get(dist,i), inform_dist_get(dup,i));
    }
    inform_dist_free(dup);
    inform_dist_free(dist);
}

UNIT(Create)
{
    ASSERT_NULL(inform_dist_create(NULL, 0));
    ASSERT_NULL(inform_dist_create(NULL, 1));
    ASSERT_NULL(inform_dist_create((uint32_t[3]){3,4,5}, 0));

    inform_dist *dist = inform_dist_create((uint32_t[3]){3,4,5}, 1);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(1, inform_dist_size(dist));
    ASSERT_EQUAL(3, inform_dist_counts(dist));
    ASSERT_EQUAL(3, inform_dist_get(dist, 0));
    inform_dist_free(dist);

    dist = inform_dist_create((uint32_t[3]){3,4,5}, 2);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(2, inform_dist_size(dist));
    ASSERT_EQUAL(7, inform_dist_counts(dist));
    ASSERT_EQUAL(3, inform_dist_get(dist, 0));
    ASSERT_EQUAL(4, inform_dist_get(dist, 1));
    inform_dist_free(dist);

    dist = inform_dist_create((uint32_t[3]){3,4,5}, 3);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(3, inform_dist_size(dist));
    ASSERT_EQUAL(12, inform_dist_counts(dist));
    ASSERT_EQUAL(3, inform_dist_get(dist, 0));
    ASSERT_EQUAL(4, inform_dist_get(dist, 1));
    ASSERT_EQUAL(5, inform_dist_get(dist, 2));
    inform_dist_free(dist);
}

UNIT(Infer)
{
    ASSERT_NULL(inform_dist_infer(NULL, 0));
    ASSERT_NULL(inform_dist_infer(NULL, 1));
    ASSERT_NULL(inform_dist_infer((int[3]){0,0,1}, 0));
    ASSERT_NULL(inform_dist_infer((int[3]){0,-1,2}, 3));

    inform_dist *dist = inform_dist_infer((int[4]){0,1,1,1}, 4);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(2, inform_dist_size(dist));
    ASSERT_EQUAL(4, inform_dist_counts(dist));
    ASSERT_EQUAL(1, inform_dist_get(dist, 0));
    ASSERT_EQUAL(3, inform_dist_get(dist, 1));
    inform_dist_free(dist);

    dist = inform_dist_infer((int[8]){1,1,0,2,2,1,2,0}, 8);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(3, inform_dist_size(dist));
    ASSERT_EQUAL(8, inform_dist_counts(dist));
    ASSERT_EQUAL(2, inform_dist_get(dist, 0));
    ASSERT_EQUAL(3, inform_dist_get(dist, 1));
    ASSERT_EQUAL(3, inform_dist_get(dist, 2));
    inform_dist_free(dist);

    dist = inform_dist_infer((int[5]){0,0,0,0,0}, 5);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(1, inform_dist_size(dist));
    ASSERT_EQUAL(5, inform_dist_counts(dist));
    ASSERT_EQUAL(5, inform_dist_get(dist, 0));
    inform_dist_free(dist);
}

UNIT(Approximate)
{
    ASSERT_NULL(inform_dist_approximate(NULL, 0, 1e-6));
    ASSERT_NULL(inform_dist_approximate(NULL, 1, 1e-6));
    ASSERT_NULL(inform_dist_approximate((double[3]){0.5,0.2,0.3}, 0, 1e-6));
    ASSERT_NULL(inform_dist_approximate((double[3]){0.5,0.2,0.3}, 1, 1e-6));
    ASSERT_NULL(inform_dist_approximate((double[3]){0.5,0.2,0.3}, 2, 1e-6));

    ASSERT_NULL(inform_dist_approximate((double[1]){0.5}, 1, 1e-6));
    ASSERT_NULL(inform_dist_approximate((double[2]){0.5, 0.6}, 2, 1e-6));
    ASSERT_NULL(inform_dist_approximate((double[2]){0.5, 0.5+3e-6}, 2, 1e-6));

    inform_dist *dist = NULL;

    dist = inform_dist_approximate((double[3]){0.5,0.2,0.3}, 3, 1e-3);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(3, inform_dist_size(dist));
    ASSERT_EQUAL(10, inform_dist_counts(dist));
    ASSERT_EQUAL(5, inform_dist_get(dist, 0));
    ASSERT_EQUAL(2, inform_dist_get(dist, 1));
    ASSERT_EQUAL(3, inform_dist_get(dist, 2));
    inform_dist_free(dist);

    dist = inform_dist_approximate((double[3]){0.25,0.25,0.5}, 3, 1e-3);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(3, inform_dist_size(dist));
    ASSERT_EQUAL(4, inform_dist_counts(dist));
    ASSERT_EQUAL(1, inform_dist_get(dist, 0));
    ASSERT_EQUAL(1, inform_dist_get(dist, 1));
    ASSERT_EQUAL(2, inform_dist_get(dist, 2));
    inform_dist_free(dist);

    dist = inform_dist_approximate((double[2]){1./3, 2./3}, 2, 1e-3);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(2, inform_dist_size(dist));
    ASSERT_EQUAL(3, inform_dist_counts(dist));
    ASSERT_EQUAL(1, inform_dist_get(dist, 0));
    ASSERT_EQUAL(2, inform_dist_get(dist, 1));
    inform_dist_free(dist);

    {
        double expected[4] = {1./3, 1./3, 1./6, 1./6};
        double got[4];
        dist = inform_dist_approximate(expected, 4, 1e-3);
        ASSERT_TRUE(inform_dist_is_valid(dist));
        ASSERT_EQUAL_U(4, inform_dist_size(dist));
        ASSERT_EQUAL(998, inform_dist_counts(dist));
        ASSERT_EQUAL(333, inform_dist_get(dist, 0));
        ASSERT_EQUAL(333, inform_dist_get(dist, 1));
        ASSERT_EQUAL(166, inform_dist_get(dist, 2));
        ASSERT_EQUAL(166, inform_dist_get(dist, 3));
        inform_dist_dump(dist, got, 4);
        for (size_t i = 0; i < 4; ++i)
            ASSERT_DBL_NEAR_TOL(expected[i], got[i], 1e-3);
        inform_dist_free(dist);
    }

    {
        double expected[4] = {1./7, 2./7, 1./3, 10./42};
        double got[4];
        dist = inform_dist_approximate(expected, 4, 1e-3);
        ASSERT_TRUE(inform_dist_is_valid(dist));
        ASSERT_EQUAL_U(4, inform_dist_size(dist));
        ASSERT_EQUAL(998, inform_dist_counts(dist));
        ASSERT_EQUAL(142, inform_dist_get(dist, 0));
        ASSERT_EQUAL(285, inform_dist_get(dist, 1));
        ASSERT_EQUAL(333, inform_dist_get(dist, 2));
        ASSERT_EQUAL(238, inform_dist_get(dist, 3));
        inform_dist_dump(dist, got, 4);
        for (size_t i = 0; i < 4; ++i)
            ASSERT_DBL_NEAR_TOL(expected[i], got[i], 1e-3);
        inform_dist_free(dist);
    }
}

UNIT(Uniform)
{
    inform_dist *dist;
    ASSERT_NULL(inform_dist_uniform(0));

    dist = inform_dist_uniform(1);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(1, inform_dist_size(dist));
    ASSERT_EQUAL(1, inform_dist_counts(dist));
    ASSERT_EQUAL(1, inform_dist_get(dist, 0));
    inform_dist_free(dist);

    dist = inform_dist_uniform(2);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(2, inform_dist_size(dist));
    ASSERT_EQUAL(2, inform_dist_counts(dist));
    ASSERT_EQUAL(1, inform_dist_get(dist, 0));
    ASSERT_EQUAL(1, inform_dist_get(dist, 1));
    inform_dist_free(dist);

    dist = inform_dist_uniform(3);
    ASSERT_TRUE(inform_dist_is_valid(dist));
    ASSERT_EQUAL_U(3, inform_dist_size(dist));
    ASSERT_EQUAL(3, inform_dist_counts(dist));
    ASSERT_EQUAL(1, inform_dist_get(dist, 0));
    ASSERT_EQUAL(1, inform_dist_get(dist, 1));
    ASSERT_EQUAL(1, inform_dist_get(dist, 2));
    inform_dist_free(dist);
}

UNIT(Tick)
{
    inform_dist *dist = inform_dist_alloc(3);
    ASSERT_NOT_NULL(dist);
    ASSERT_FALSE(inform_dist_is_valid(dist));

    ASSERT_EQUAL(0, inform_dist_get(dist,0));

    ASSERT_EQUAL(1, inform_dist_tick(dist,0));
    ASSERT_EQUAL(1, inform_dist_get(dist,0));
    ASSERT_TRUE(inform_dist_is_valid(dist));

    ASSERT_EQUAL(1, inform_dist_tick(dist,1));
    ASSERT_EQUAL(1, inform_dist_get(dist,1));

    ASSERT_EQUAL(2, inform_dist_tick(dist,0));
    ASSERT_EQUAL(2, inform_dist_get(dist,0));

    ASSERT_EQUAL(1, inform_dist_tick(dist,2));
    ASSERT_EQUAL(1, inform_dist_get(dist,2));

    ASSERT_EQUAL(3, inform_dist_size(dist));
    ASSERT_EQUAL(4, inform_dist_counts(dist));

    inform_dist_free(dist);
}

UNIT(Prob)
{
    inform_dist* dist = inform_dist_alloc(5);
    ASSERT_NOT_NULL(dist);

    for (size_t i = 0; i < inform_dist_size(dist); ++i)
    {
        inform_dist_set(dist, i, (uint32_t) i+1);
    }
    ASSERT_EQUAL(15, inform_dist_counts(dist));
    for (size_t i = 0; i < inform_dist_size(dist); ++i)
    {
        ASSERT_DBL_NEAR((double)(i+1)/15, inform_dist_prob(dist,i));
    }

    inform_dist_free(dist);
}

UNIT(Dump)
{
    inform_dist *dist = NULL;
    ASSERT_EQUAL(0, inform_dist_dump(dist, NULL, 0));

    dist = inform_dist_alloc(5);
    ASSERT_NOT_NULL(dist);

    ASSERT_EQUAL(0, inform_dist_dump(dist, NULL, 0));

    for (size_t i = 1; i < inform_dist_size(dist); ++i)
    {
        inform_dist_set(dist, i, (uint32_t) i+1);
    }
    ASSERT_EQUAL(14, inform_dist_counts(dist));
    double expect[5] = {0., 2./14, 3./14, 4./14, 5./14};
    double got[7] = {0., 0., 0., 0., 0., 0.};
    ASSERT_EQUAL(0, inform_dist_dump(dist, got, 4));
    ASSERT_EQUAL(0, inform_dist_dump(dist, got, 6));
    ASSERT_EQUAL(5, inform_dist_dump(dist, got, 5));
    for (size_t i = 0; i < inform_dist_size(dist); ++i)
    {
        ASSERT_DBL_NEAR(expect[i], got[i]);
    }
    inform_dist_free(dist);
}

UNIT(Accumulate)
{
    inform_dist *dist = NULL;
    ASSERT_EQUAL(0, inform_dist_accumulate(dist, (int[4]){0, 0, 1, 0}, 4));

    dist = inform_dist_alloc(2);
    ASSERT_NOT_NULL(dist);

    ASSERT_EQUAL_U(0, inform_dist_accumulate(dist, NULL, 0));
    ASSERT_EQUAL_U(0, inform_dist_accumulate(dist, NULL, 1));

    ASSERT_EQUAL_U(0, inform_dist_accumulate(dist, (int[5]){0,0,1,1,0}, 0));

    ASSERT_EQUAL_U(5, inform_dist_accumulate(dist, (int[5]){0,0,1,1,0}, 5));
    ASSERT_EQUAL(5, inform_dist_counts(dist));
    
    ASSERT_EQUAL_U(3, inform_dist_accumulate(dist, (int[3]){0,1,0}, 3));
    ASSERT_EQUAL(8, inform_dist_counts(dist));
    
    ASSERT_EQUAL(5, inform_dist_get(dist, 0));
    ASSERT_EQUAL(3, inform_dist_get(dist, 1));

    ASSERT_EQUAL(0, inform_dist_accumulate(dist, (int[2]){-1, 2}, 2));
    ASSERT_EQUAL(1, inform_dist_accumulate(dist, (int[2]){1, 2}, 2));
    ASSERT_EQUAL(5, inform_dist_get(dist, 0));
    ASSERT_EQUAL(4, inform_dist_get(dist, 1));
    ASSERT_EQUAL(9, inform_dist_counts(dist));

    inform_dist_free(dist);
}

BEGIN_SUITE(Distribution)
    ADD_UNIT(AllocZero)
    ADD_UNIT(AllocOne)
    ADD_UNIT(AllocTwo)
    ADD_UNIT(GetNull)
    ADD_UNIT(SetNull)
    ADD_UNIT(Set)
    ADD_UNIT(Get)
    ADD_UNIT(ReallocNull)
    ADD_UNIT(ReallocGrow)
    ADD_UNIT(ReallocShrink)
    ADD_UNIT(CopyNull)
    ADD_UNIT(CopyToNULL)
    ADD_UNIT(CopySamePlace)
    ADD_UNIT(CopySameSize)
    ADD_UNIT(CopyResize)
    ADD_UNIT(DupNull)
    ADD_UNIT(Dup)
    ADD_UNIT(Create)
    ADD_UNIT(Infer)
    ADD_UNIT(Approximate)
    ADD_UNIT(Uniform)
    ADD_UNIT(Tick)
    ADD_UNIT(Prob)
    ADD_UNIT(Dump)
    ADD_UNIT(Accumulate)
END_SUITE
