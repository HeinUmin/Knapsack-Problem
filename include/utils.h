#ifndef UTILS_H
#define UTILS_H

#include "knapsack.h"
using namespace std;

#ifdef USE_DOUBLE
typedef double TypeWeight;
typedef double TypeValue;
#else
typedef long long TypeWeight;
typedef long long TypeValue;
#endif  // USE_DOUBLE

bool solve(Knapsack<TypeWeight, TypeValue> *knapsack);

#endif