// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include <ginger/unit.h>
#include <ginger/vector.h>
#include <inform/pid.h>
#include <inform/utilities/random.h>

#define COMPARE_SOURCES(EXP, SRCS) \
do { \
    for (size_t i = 0; i < gvector_len((SRCS)); ++i) \
    { \
        size_t const n = (EXP)[i][0]; \
        size_t const m = n * gvector_size((SRCS)[i]->name); \
        ASSERT_EQUAL_U(n, gvector_len((SRCS)[i]->name)); \
        ASSERT_EQUAL_U(0, memcmp(&((EXP)[i][1]), (SRCS)[i]->name, m)); \
    } \
} while(0);

#define TestPIDHasse(EXP, N, M, Q) \
do { \
    int data[10*(N+1)], base[(N)]; \
    for (size_t i = 0; i < 10*(N+1); ++i) data[i] = 1; \
    for (size_t i = 0; i < (N); ++i) base[i] = 2;\
\
    inform_error err = INFORM_SUCCESS; \
    inform_pid_lattice *l = inform_pid(data, data+10, (N), 10, 2, base, &err); \
    ASSERT_TRUE(inform_succeeded(&err)); \
    ASSERT_NOT_NULL(l); \
    ASSERT_NOT_NULL(l->sources); \
    ASSERT_EQUAL_U((M), gvector_len(l->sources)); \
    if (EXP != NULL) { \
        COMPARE_SOURCES((EXP), l->sources); \
    } \
    size_t n = 0; \
    for (size_t i = 0; i < (M); ++i) { \
        n += gvector_len(l->sources[i]->above); \
    } \
    ASSERT_EQUAL((Q), n); \
    inform_pid_lattice_free(l); \
} while (0);

UNIT(PIDNULLStimulus)
{
    int const responses[10] = {0,0,1,0,0, 0,1,1,0,0};

    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(NULL, responses, 2, 5, 2, (int[2]){2,2}, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}

UNIT(PIDNULLResponses)
{
    int const stimulus[5] = {0,1,1,0,0};

    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, NULL, 2, 5, 2, (int[2]){2,2}, &err));
    ASSERT_EQUAL(INFORM_ETIMESERIES, err);
}


UNIT(PIDNoResponses)
{
    int const stimulus[5] = {0,1,1,0,0};
    int const responses[10] = {0,0,1,0,0, 0,1,1,0,0};

    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 0, 5, 2, (int[2]){2,2}, &err));
    ASSERT_EQUAL(INFORM_ENOSOURCES, err);
}


UNIT(PIDShortSeries)
{
    int const stimulus[5] = {0,1,1,0,0};
    int const responses[10] = {0,0,1,0,0, 0,1,1,0,0};

    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 2, 0, 2, (int[2]){2,2}, &err));
    ASSERT_EQUAL(INFORM_ESHORTSERIES, err);
}


UNIT(PIDInvalidBase)
{
    int const stimulus[5] = {0,1,1,0,0};
    int const responses[10] = {0,0,1,0,0, 0,1,1,0,0};

    inform_error err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, -1, (int[2]){2,2}, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 0, (int[2]){2,2}, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 1, (int[2]){2,2}, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, NULL, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){-1,2}, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){0,2}, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){1,2}, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){2,-1}, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){2,0}, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);

    err = INFORM_SUCCESS;
    ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){2,-1}, &err));
    ASSERT_EQUAL(INFORM_EBASE, err);
}


UNIT(PIDNegativeState)
{
    inform_error err;
    {
        int const stimulus[5] = {0,-1,1,0,0};
        int const responses[10] = {0,0,1,0,0, 0,1,1,0,0};

        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){2,2}, &err));
        ASSERT_EQUAL(INFORM_ENEGSTATE, err);
    }
    {
        int const stimulus[5] = {0,1,1,0,0};
        int const responses[10] = {0,-1,1,0,0, 0,1,1,0,0};

        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){2,2}, &err));
        ASSERT_EQUAL(INFORM_ENEGSTATE, err);
    }
    {
        int const stimulus[5] = {0,1,1,0,0};
        int const responses[10] = {0,1,1,0,0, 0,1,1,-1,0};

        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){2,2}, &err));
        ASSERT_EQUAL(INFORM_ENEGSTATE, err);
    }
}


UNIT(PIDBadState)
{
    inform_error err;
    {
        int const stimulus[5] = {0,2,1,0,0};
        int const responses[10] = {0,0,1,0,0, 0,1,1,0,0};

        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){2,2}, &err));
        ASSERT_EQUAL(INFORM_EBADSTATE, err);
    }
    {
        int const stimulus[5] = {0,1,1,0,0};
        int const responses[10] = {0,2,1,0,0, 0,1,1,0,0};

        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){2,2}, &err));
        ASSERT_EQUAL(INFORM_EBADSTATE, err);
    }
    {
        int const stimulus[5] = {0,1,1,0,0};
        int const responses[10] = {0,1,1,0,0, 0,1,1,2,0};

        err = INFORM_SUCCESS;
        ASSERT_NULL(inform_pid(stimulus, responses, 2, 5, 2, (int[2]){2,2}, &err));
        ASSERT_EQUAL(INFORM_EBADSTATE, err);
    }
}

UNIT(PIDHasseOrder)
{
    {
        size_t expected[1][2] = { {1,1} };
        TestPIDHasse(expected, 1, 1, 0);
    }

    {
        size_t expected[4][3] = { {2,1,2}, {1,1,0}, {1,2,0}, {1,3,0} };
        TestPIDHasse(expected, 2, 4, 4);
    }

    {
        size_t expected[18][4] = {
            {3,1,2,4}, {2,1,4,0}, {2,1,2,0}, {2,2,4,0}, {2,2,5,0}, {2,1,6,0},
            {2,3,4,0}, {1,2,0,0}, {3,3,5,6}, {1,1,0,0}, {1,4,0,0}, {2,3,6,0},
            {2,3,5,0}, {2,5,6,0}, {1,5,0,0}, {1,3,0,0}, {1,6,0,0}, {1,7,0,0},
        };
        TestPIDHasse(expected, 3, 18, 30);
    }

    {
        size_t expected[166][7] = {
            {4,1,2,4,8,0,0},    {3,1,4,8,0,0,0},    {3,1,2,8,0,0,0},   {3,1,2,4,0,0,0},
            {3,2,4,8,0,0,0},    {3,1,6,8,0,0,0},    {3,1,4,10,0,0,0},  {3,1,2,12,0,0,0},
            {3,2,5,8,0,0,0},    {3,2,4,9,0,0,0},    {3,3,4,8,0,0,0},   {2,1,4,0,0,0,0},
            {2,1,2,0,0,0,0},    {2,2,8,0,0,0,0},    {4,2,5,9,12,0,0},  {2,2,4,0,0,0,0},
            {4,1,6,10,12,0,0},  {4,3,5,6,8,0,0},    {4,3,4,9,10,0,0},  {2,1,8,0,0,0,0},
            {2,4,8,0,0,0,0},    {3,2,9,12,0,0,0},   {3,2,5,12,0,0,0},  {3,2,5,9,0,0,0},
            {3,1,6,10,0,0,0},   {3,1,6,12,0,0,0},   {3,1,10,12,0,0,0}, {3,3,6,8,0,0,0},
            {3,3,5,8,0,0,0},    {6,3,5,6,9,10,12},  {3,3,4,10,0,0,0},  {3,3,4,9,0,0,0},
            {3,4,9,10,0,0,0},   {3,5,6,8,0,0,0},    {2,3,8,0,0,0,0},   {5,3,6,9,10,12,0},
            {2,2,12,0,0,0,0},   {5,3,5,9,10,12,0},  {2,1,6,0,0,0,0},   {5,3,5,6,10,12,0},
            {5,3,5,6,9,12,0},   {5,3,5,6,9,10,0},   {2,1,10,0,0,0,0},  {2,3,4,0,0,0,0},
            {2,2,5,0,0,0,0},    {2,1,12,0,0,0,0},   {2,4,10,0,0,0,0},  {2,4,9,0,0,0,0},
            {2,2,9,0,0,0,0},    {2,5,8,0,0,0,0},    {5,5,6,9,10,12,0}, {2,6,8,0,0,0,0},
            {4,3,6,10,12,0,0},  {4,3,6,9,12,0,0},   {4,3,6,9,10,0,0},  {4,3,5,10,12,0,0},
            {4,3,5,9,12,0,0},   {4,3,5,9,10,0,0},   {4,3,5,6,12,0,0},  {4,3,5,6,10,0,0},
            {4,3,5,6,9,0,0},    {2,1,14,0,0,0,0},   {4,3,9,10,12,0,0}, {2,4,11,0,0,0,0},
            {2,2,13,0,0,0,0},   {4,5,9,10,12,0,0},  {4,5,6,10,12,0,0}, {4,5,6,9,12,0,0},
            {4,5,6,9,10,0,0},   {4,6,9,10,12,0,0},  {2,7,8,0,0,0,0},   {3,3,5,12,0,0,0},
            {3,3,10,12,0,0,0},  {3,3,5,10,0,0,0},   {3,3,9,12,0,0,0},  {3,3,9,10,0,0,0},
            {3,3,6,9,0,0,0},    {1,1,0,0,0,0,0},    {1,2,0,0,0,0,0},   {1,4,0,0,0,0,0},
            {4,3,5,9,14,0,0},   {3,5,10,12,0,0,0},  {3,5,9,12,0,0,0},  {3,5,9,10,0,0,0},
            {3,3,6,12,0,0,0},   {4,5,6,11,12,0,0},  {3,5,6,10,0,0,0},  {3,5,6,9,0,0,0},
            {3,6,10,12,0,0,0},  {3,6,9,12,0,0,0},   {3,6,9,10,0,0,0},  {3,3,5,6,0,0,0},
            {4,3,6,10,13,0,0},  {4,7,9,10,12,0,0},  {1,8,0,0,0,0,0},   {2,5,10,0,0,0,0},
            {3,3,9,14,0,0,0},   {3,5,9,14,0,0,0},   {3,3,10,13,0,0,0}, {3,3,5,9,0,0,0},
            {3,5,6,12,0,0,0},   {3,5,6,11,0,0,0},   {3,3,6,13,0,0,0},  {2,3,12,0,0,0,0},
            {3,3,6,10,0,0,0},   {3,6,11,12,0,0,0},  {3,6,10,13,0,0,0}, {3,3,5,14,0,0,0},
            {2,6,9,0,0,0,0},    {3,7,10,12,0,0,0},  {3,7,9,12,0,0,0},  {3,7,9,10,0,0,0},
            {3,5,11,12,0,0,0},  {3,9,10,12,0,0,0},  {2,6,12,0,0,0,0},  {3,6,11,13,0,0,0},
            {2,6,10,0,0,0,0},   {2,3,6,0,0,0,0},    {3,3,13,14,0,0,0}, {2,5,12,0,0,0,0},
            {3,7,11,12,0,0,0},  {3,7,10,13,0,0,0},  {2,5,9,0,0,0,0},   {3,7,9,14,0,0,0},
            {2,5,6,0,0,0,0},    {2,3,10,0,0,0,0},   {3,5,11,14,0,0,0}, {2,3,5,0,0,0,0},
            {2,3,9,0,0,0,0},    {2,9,12,0,0,0,0},   {2,9,10,0,0,0,0},  {2,10,12,0,0,0,0},
            {2,7,12,0,0,0,0},   {4,7,11,13,14,0,0}, {2,7,10,0,0,0,0},  {2,3,14,0,0,0,0},
            {2,6,11,0,0,0,0},   {2,7,9,0,0,0,0},    {2,6,13,0,0,0,0},  {2,5,14,0,0,0,0},
            {2,3,13,0,0,0,0},   {2,5,11,0,0,0,0},   {2,9,14,0,0,0,0},  {2,10,13,0,0,0,0},
            {2,11,12,0,0,0,0},  {1,6,0,0,0,0,0},    {1,9,0,0,0,0,0},   {3,7,11,14,0,0,0},
            {1,3,0,0,0,0,0},    {1,10,0,0,0,0,0},   {1,5,0,0,0,0,0},   {3,7,13,14,0,0,0},
            {3,11,13,14,0,0,0}, {3,7,11,13,0,0,0},  {1,12,0,0,0,0,0},  {2,7,13,0,0,0,0},
            {2,11,14,0,0,0,0},  {2,11,13,0,0,0,0},  {2,7,11,0,0,0,0},  {2,7,14,0,0,0,0},
            {2,13,14,0,0,0,0},  {1,11,0,0,0,0,0},   {1,13,0,0,0,0,0},  {1,7,0,0,0,0,0},
            {1,14,0,0,0,0,0},   {1,15,0,0,0,0,0}
        };

        TestPIDHasse(expected, 4, 166, 452);
    }
}

UNIT(PIDXOR)
{
    double const imin[4] = { 0., 0., 0., 1. };
    double const pi[4]   = { 0., 0., 0., 1. };

    int const data[12] = {0,1,1,0, 0,1,0,1, 0,0,1,1};

    inform_error err = INFORM_SUCCESS;
    inform_pid_lattice *l = inform_pid(data, data+4, 2, 4, 2, (int[]){2,2}, &err);

    ASSERT_EQUAL(INFORM_SUCCESS, err);
    ASSERT_NOT_NULL(l);
    for (size_t i = 0; i < l->size; ++i)
    {
        ASSERT_DBL_NEAR(imin[i], l->sources[i]->imin);
        ASSERT_DBL_NEAR(pi[i], l->sources[i]->pi);
    }

    inform_pid_lattice_free(l);
}

UNIT(PIDAND)
{
    double const x = 1.5 - 0.75 * log2(3);
    double const imin[4] = { x, x, x, x + 0.5 };
    double const pi[4]   = { x, 0., 0., 0.5 };

    int const data[12] = {0,0,0,1, 0,1,0,1, 0,0,1,1};

    inform_error err = INFORM_SUCCESS;
    inform_pid_lattice *l = inform_pid(data, data+4, 2, 4, 2, (int[]){2,2}, &err);

    ASSERT_EQUAL(INFORM_SUCCESS, err);
    ASSERT_NOT_NULL(l);
    for (size_t i = 0; i < l->size; ++i)
    {
        ASSERT_DBL_NEAR(imin[i], l->sources[i]->imin);
        ASSERT_DBL_NEAR(pi[i], l->sources[i]->pi);
    }

    inform_pid_lattice_free(l);
}

UNIT(PIDOR)
{
    double const x = 1.5 - 0.75 * log2(3);
    double const imin[4] = { x, x, x, x + 0.5 };
    double const pi[4]   = { x, 0., 0., 0.5 };

    int const data[12] = {0,1,1,1, 0,1,0,1, 0,0,1,1};

    inform_error err = INFORM_SUCCESS;
    inform_pid_lattice *l = inform_pid(data, data+4, 2, 4, 2, (int[]){2,2}, &err);

    ASSERT_EQUAL(INFORM_SUCCESS, err);
    ASSERT_NOT_NULL(l);
    for (size_t i = 0; i < l->size; ++i)
    {
        ASSERT_DBL_NEAR(imin[i], l->sources[i]->imin);
        ASSERT_DBL_NEAR(pi[i], l->sources[i]->pi);
    }

    inform_pid_lattice_free(l);
}

UNIT(PIDStochastic)
{
    double const imin[4] = { 0.001317, 0.011000, 0.001317, 0.012888 };
    double const pi[4]   = { 0.001317, 0.009683, 0.000000, 0.001887 };

    int const data[60] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,
                          0,0,0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,
                          0,1,1,0,0,1,1,1,0,0,1,1,1,1,0,0,1,1,1,1};

    inform_error err = INFORM_SUCCESS;
    inform_pid_lattice *l = inform_pid(data, data+20, 2, 20, 2, (int[]){2,2}, &err);

    ASSERT_EQUAL(INFORM_SUCCESS, err);
    ASSERT_NOT_NULL(l);
    for (size_t i = 0; i < l->size; ++i)
    {
        ASSERT_DBL_NEAR_TOL(imin[i], l->sources[i]->imin, 1e-6);
        ASSERT_DBL_NEAR_TOL(pi[i], l->sources[i]->pi, 1e-6);
    }

    inform_pid_lattice_free(l);
}

UNIT(PIDWilliamsBeer4a)
{
    double const x = log2(3.0) - 1, y = 1/3.;
    double const imin[4] = { x, x + y, x + y, x + 1 };
    double const pi[4]   = { x, y, y, y };

    int const data[9] = {0,1,2, 0,0,1, 0,1,0};

    inform_error err = INFORM_SUCCESS;
    inform_pid_lattice *l = inform_pid(data, data+3, 2, 3, 3, (int[]){2,2}, &err);

    ASSERT_EQUAL(INFORM_SUCCESS, err);
    ASSERT_NOT_NULL(l);
    for (size_t i = 0; i < l->size; ++i)
    {
        ASSERT_DBL_NEAR(imin[i], l->sources[i]->imin);
        ASSERT_DBL_NEAR(pi[i], l->sources[i]->pi);
    }

    inform_pid_lattice_free(l);
}

UNIT(PIDWilliamsBeer4b)
{
    double const imin[4] = { 0.5, 0.5, 1.0, 1.5 };
    double const pi[4]   = { 0.5, 0.0, 0.5, 0.5};

    int const data[12] = {0,1,1,2, 0,0,1,1, 0,1,1,0};

    inform_error err = INFORM_SUCCESS;
    inform_pid_lattice *l = inform_pid(data, data+4, 2, 4, 3, (int[]){2,2}, &err);

    ASSERT_EQUAL(INFORM_SUCCESS, err);
    ASSERT_NOT_NULL(l);
    for (size_t i = 0; i < l->size; ++i)
    {
        ASSERT_DBL_NEAR(imin[i], l->sources[i]->imin);
        ASSERT_DBL_NEAR(pi[i], l->sources[i]->pi);
    }

    inform_pid_lattice_free(l);
}

UNIT(PID4Variables)
{
    int const data[100] = {0,1,1,2,2,1,2,3,3,2,1,2,3,1,1,2,2,1,2,1,
                           1,1,0,1,1,0,1,0,1,1,1,0,0,1,0,1,0,1,1,0,
                           1,0,0,0,1,1,1,0,0,1,0,1,1,0,1,1,0,0,0,1,
                           0,0,1,1,1,1,0,0,1,0,1,1,0,1,1,1,0,0,0,0,
                           0,0,0,1,1,1,1,0,1,1,1,0,1,1,1,0,0,1,1,0};

    inform_error err = INFORM_SUCCESS;
    inform_pid_lattice *l = inform_pid(data, data+20, 4, 20, 4, (int[]){2,2,2,2}, &err);

    ASSERT_EQUAL(INFORM_SUCCESS, err);
    ASSERT_NOT_NULL(l);
    double total = 0.0;
    for (size_t i = 0; i < l->size; ++i)
    {
        total += l->sources[i]->pi;
        ASSERT_TRUE(l->sources[i]->pi <= l->sources[i]->imin);
    }
    ASSERT_DBL_NEAR(total, l->top->imin);

    inform_pid_lattice_free(l);
}

UNIT(PIDRandom)
{
    int *data = inform_random_series(5000, 2);
    ASSERT_NOT_NULL(data);

    inform_error err = INFORM_SUCCESS;
    inform_pid_lattice *l = inform_pid(data, data+1000, 4, 1000, 2, (int[]){2,2,2,2}, &err);

    ASSERT_EQUAL(INFORM_SUCCESS, err);
    ASSERT_NOT_NULL(l);
    double total = 0.0;
    for (size_t i = 0; i < l->size; ++i)
    {
        total += l->sources[i]->pi;
        ASSERT_TRUE(l->sources[i]->pi <= l->sources[i]->imin);
    }
    ASSERT_DBL_NEAR(total, l->top->imin);

    inform_pid_lattice_free(l);
    free(data);
}

// UNIT(PIDMemory)
// {
//     size_t const m = 7, n = 10000;
//     int const b = 2;
//     int const bases[7] = {b,b,b,b,b,b,b};
//
//     int *data = inform_random_series((m+1)*n, b);
//     ASSERT_NOT_NULL(data);
//
//     inform_error err = INFORM_SUCCESS;
//     inform_pid_lattice *l = inform_pid(data, data+n, m, n, b, bases, &err);
//     ASSERT_NULL(l);
//     ASSERT_EQUAL(INFORM_ENOMEM, err);
//
//     free(data);
// }

BEGIN_SUITE(PID)
    ADD_UNIT(PIDNULLStimulus)
    ADD_UNIT(PIDNULLResponses)
    ADD_UNIT(PIDNoResponses)
    ADD_UNIT(PIDShortSeries)
    ADD_UNIT(PIDInvalidBase)
    ADD_UNIT(PIDNegativeState)
    ADD_UNIT(PIDBadState)

    ADD_UNIT(PIDHasseOrder)
    ADD_UNIT(PIDXOR)
    ADD_UNIT(PIDAND)
    ADD_UNIT(PIDOR)
    ADD_UNIT(PIDStochastic)
    ADD_UNIT(PIDWilliamsBeer4a)
    ADD_UNIT(PIDWilliamsBeer4b)
    ADD_UNIT(PID4Variables)
    ADD_UNIT(PIDRandom)
    // ADD_UNIT(PIDMemory)
END_SUITE
