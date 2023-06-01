#include "utils.h"
#include <queue>

struct Pnode {
    bool *selection;
    int level;
    TypeWeight weight;
    TypeValue value;
    TypeValue cx;
    bool operator>(const Pnode &p) const { return cx > p.cx; }
};

namespace {
Knapsack<TypeWeight, TypeValue> *knap;
TypeValue min_cost;
priority_queue<Pnode, vector<Pnode>, greater<>> pq;
}  // namespace

void branchBound(Pnode node) {
    int n = knap->getCount();
    pq.pop();
    if (min_cost != 0 && min_cost < node.cx) {
        delete[] node.selection;
        return;
    }
    if (node.level > n) {
        min_cost = node.cx;
        knap->setOptimum(node.value);
        for (int i = 1; i <= n; i++) {
            knap->setSelection(i, node.selection[i]);
        }
        delete[] node.selection;
        return;
    }
    TypeWeight w = knap->getWeight(node.level);
    TypeValue v = knap->getValue(node.level);
    if (node.weight + w <= knap->getCapacity()) {
        Pnode left = Pnode();
        left.weight = node.weight + w;
        left.value = node.value + v;
        left.level = node.level + 1;
        left.cx = node.cx;
        left.selection = new bool[left.level]{};
        for (int i = 1; i < node.level; i++) {
            left.selection[i] = node.selection[i];
        }
        left.selection[node.level] = true;
        pq.push(left);
    }
    Pnode right = Pnode();
    right.weight = node.weight;
    right.value = node.value;
    right.level = node.level + 1;
    right.cx = node.cx + v;
    right.selection = new bool[right.level]{};
    for (int i = 1; i < node.level; i++) {
        right.selection[i] = node.selection[i];
    }
    right.selection[node.level] = false;
    pq.push(right);
    delete[] node.selection;
}

bool solve(Knapsack<TypeWeight, TypeValue> *knapsack) {
    cout << "Branch and Bound:" << endl;
    knap = knapsack;
    min_cost = 0;
    Pnode first = Pnode();
    first.level = 1;
    pq.push(first);
    while (!pq.empty()) { branchBound(pq.top()); }
    return knap->getOptimum() != 0;
}
