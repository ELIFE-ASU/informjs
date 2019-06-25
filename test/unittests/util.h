// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#pragma once

#include <stdlib.h>
#include <inttypes.h>
#include <inform/utilities.h>

#define AVERAGE(XS) average(XS, sizeof(XS) / sizeof(double))
double average(double const *xs, size_t n);

#define inform_dist_fill_array(dist, array) \
    ASSERT_NOT_NULL(dist); \
    ASSERT_EQUAL(sizeof(array)/sizeof(int), inform_dist_size(dist)); \
    for (size_t i = 0; i < inform_dist_size(dist); ++i) \
    { \
        inform_dist_set(dist, i, array[i]); \
    }

#define inform_dist_fill(dist, ...) inform_dist_fill_array(dist, ((int[]){__VA_ARGS__}))