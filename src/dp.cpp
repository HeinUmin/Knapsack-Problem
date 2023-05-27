#include "utils.h"

namespace {
Knapsack<TypeWeight, TypeValue> *knap;
TypeWeight *weight;
TypeValue *value;
element *q;
int **matrix;
}  // namespace

void dynamicProgram(int i) {
    for (int y = 0; y <= knap->getCapacity(); y++) {
        if (y < weight[i]) {
            matrix[i][y] = matrix[i - 1][y];
            continue;
        }
        if (matrix[i - 1][y] >= (matrix[i - 1][y - weight[i]] + value[i])) {
            matrix[i][y] = matrix[i - 1][y];
            continue;
        }
        matrix[i][y] = matrix[i - 1][y - weight[i]] + value[i];
    }
}

void traceback() {
    int capacity = knap->getCapacity();
    knap->setOptimum(matrix[knap->getCount()][capacity]);
    for (int i = knap->getCount(); i > 0; i--) {
        if (matrix[i][capacity] == matrix[i - 1][capacity]) {
            knap->setSelection(q[knap->getCount() - i].id, false);
        } else {
            knap->setSelection(q[knap->getCount() - i].id, true);
            capacity = capacity - weight[i];
        }
    }
}

bool solve(Knapsack<TypeWeight, TypeValue> *knapsack) {
#ifdef USE_DOUBLE
    return false;
#endif
    int n = knapsack->getCount();
    knap = knapsack;
    weight = new TypeWeight[n + 1]{};
    value = new TypeValue[n + 1]{};
    q = new element[n]{};
    sortPack(knapsack, weight, value, q);
    matrix = new TypeValue *[n + 1];
    for (int i = 0; i <= n; i++) {
        matrix[i] = new TypeValue[knapsack->getCapacity() + 1]{};
    }
    for (int i = 1; i <= n; i++) { dynamicProgram(i); }
    traceback();
    for (int i = 0; i <= n; i++) { delete[] matrix[i]; }
    delete[] matrix;
    delete[] q;
    delete[] value;
    delete[] weight;
    return knapsack->getOptimum() != 0;
}
