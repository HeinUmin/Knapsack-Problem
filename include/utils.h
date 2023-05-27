#ifndef UTILITIES_H
#define UTILITIES_H
#include "knapsack.h"

#ifdef USE_DOUBLE
typedef double TypeWeight;
typedef double TypeValue;
#else
typedef int TypeWeight;
typedef int TypeValue;
#endif  // USE_DOUBLE

struct element
{
    int id;
    double value;
    bool operator<(const element &e) const { return value < e.value; }
};

bool solve(Knapsack<TypeWeight, TypeValue> *knapsack);

void sortPack(Knapsack<TypeWeight, TypeValue> *knapsack,
              TypeWeight *weight,
              TypeValue *value,
              element *q);

#endif