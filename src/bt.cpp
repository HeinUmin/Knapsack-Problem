#include "utils.h"

namespace {
Knapsack<TypeWeight, TypeValue> *knap;
TypeWeight current_weight;
TypeValue current_value;
TypeValue max_value;
bool *selection;
}  // namespace

TypeValue bound(int i) {
    TypeWeight left = knap->getCapacity() - current_weight;
    TypeValue bound = current_value;
    while (i <= knap->getCount() && knap->getWeight(i) <= left) {
        left -= knap->getWeight(i);
        bound += knap->getValue(i);
        i++;
    }
    if (i <= knap->getCount()) {
        bound += left * knap->getValue(i) / knap->getWeight(i);
    }
    return bound;
}

void backTrack(int i) {
    if (i > knap->getCount()) {
        if (current_value > max_value) {
            max_value = current_value;
            for (int j = 1; j <= knap->getCount(); j++) {
                knap->setSelection(j, selection[j]);
            }
        }
        return;
    }
    TypeWeight w = knap->getWeight(i);
    TypeValue v = knap->getValue(i);
    if (current_weight + w <= knap->getCapacity()) {
        selection[i] = true;
        current_weight += w;
        current_value += v;
        backTrack(i + 1);
        current_weight -= w;
        current_value -= v;
    }
    if (bound(i + 1) > max_value) {
        selection[i] = false;
        backTrack(i + 1);
    }
}

bool solve(Knapsack<TypeWeight, TypeValue> *knapsack) {
    cout << "Backtrack:" << endl;
    knap = knapsack;
    current_weight = 0;
    current_value = 0;
    max_value = 0;
    selection = new bool[knapsack->getCount() + 1]{};
    backTrack(1);
    knap->setOptimum(max_value);
    delete[] selection;
    return knap->getOptimum() != 0;
}
