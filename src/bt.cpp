#include "utils.h"

namespace {
Knapsack<TypeWeight, TypeValue> *knap;
TypeWeight *weight;
TypeValue *value;
element *q;
TypeWeight current_weight;
TypeValue current_value;
TypeValue max_value;
bool *selection;
}  // namespace

TypeValue bound(int i) {
    TypeWeight left = knap->getCapacity() - current_weight;
    TypeValue bound = current_value;
    while (i <= knap->getCount() && weight[i] <= left) {
        left -= weight[i];
        bound += value[i];
        i++;
    }
    if (i <= knap->getCount()) { bound += left * value[i] / weight[i]; }
    return bound;
}

void backTrack(int i) {
    if (i > knap->getCount()) {
        if (current_value > max_value) {
            max_value = current_value;
            for (int j = 1; j <= knap->getCount(); j++) {
                knap->setSelection(q[knap->getCount() - j].id, selection[j]);
            }
        }
        return;
    }
    if (current_weight + weight[i] <= knap->getCapacity()) {
        selection[i] = true;
        current_weight += weight[i];
        current_value += value[i];
        backTrack(i + 1);
        current_weight -= weight[i];
        current_value -= value[i];
    }
    if (bound(i + 1) > max_value) {
        selection[i] = false;
        backTrack(i + 1);
    }
}

bool solve(Knapsack<TypeWeight, TypeValue> *knapsack) {
    int n = knapsack->getCount();
    knap = knapsack;
    weight = new TypeWeight[n + 1]{};
    value = new TypeValue[n + 1]{};
    q = new element[n]{};
    sortPack(knapsack, weight, value, q);
    current_weight = 0;
    current_value = 0;
    max_value = 0;
    selection = new bool[n + 1]{};
    backTrack(1);
    knap->setOptimum(max_value);
    delete[] q;
    delete[] value;
    delete[] weight;
    return true;
}
