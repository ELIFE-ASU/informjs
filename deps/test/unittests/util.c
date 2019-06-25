// Copyright 2016-2018 ELIFE. All rights reserved.
// Use of this source code is governed by a MIT
// license that can be found in the LICENSE file.
#include "util.h"

double average(double const *xs, size_t n)
{
    double x = 0;
    for (size_t i = 0; i < n; ++i)
    {
        x += xs[i];
    }
    return x / n;
}
