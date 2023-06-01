#include "utils.h"

#ifdef USE_DOUBLE

bool solve(Knapsack<TypeWeight, TypeValue> *knapsack) {
    std::cout << "Dynamic Programming:\n";
    return false;
}

#else

namespace {
Knapsack<TypeWeight, TypeValue> *knap;
TypeValue **matrix;
}  // namespace

void dynamicProgram(int i) {
    TypeWeight w = knap->getWeight(i);
    TypeValue v = knap->getValue(i);
    for (int y = 0; y <= knap->getCapacity(); y++) {
        if (y < w) {
            matrix[i][y] = matrix[i - 1][y];
            continue;
        }
        if (matrix[i - 1][y] >= (matrix[i - 1][y - w] + v)) {
            matrix[i][y] = matrix[i - 1][y];
            continue;
        }
        matrix[i][y] = matrix[i - 1][y - w] + v;
    }
}

void traceback() {
    int n = knap->getCount();
    TypeWeight capacity = knap->getCapacity();
    knap->setOptimum(matrix[n][capacity]);
    for (int i = n; i > 0; i--) {
        if (matrix[i][capacity] == matrix[i - 1][capacity]) {
            knap->setSelection(i, false);
        } else {
            knap->setSelection(i, true);
            capacity = capacity - knap->getWeight(i);
        }
    }
}

bool solve(Knapsack<TypeWeight, TypeValue> *knapsack) {
    cout << "Dynamic Programming:" << endl;
    int n = knapsack->getCount();
    knap = knapsack;
    matrix = new TypeValue *[n + 1];
    for (int i = 0; i <= n; i++) {
        matrix[i] = new TypeValue[knapsack->getCapacity() + 1]{};
    }
    for (int i = 1; i <= n; i++) { dynamicProgram(i); }
    traceback();
    for (int i = 0; i <= n; i++) { delete[] matrix[i]; }
    delete[] matrix;
    return knap->getOptimum() != 0;
}

#endif  // USE_DOUBLE