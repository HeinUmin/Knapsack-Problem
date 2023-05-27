#include "utils.h"
#include <queue>

using namespace std;

struct Pnode
{
    bool *selection;
    int level;
    TypeWeight weight;
    TypeValue value;
    TypeValue cx;
    bool operator>(const Pnode &p) const { return cx > p.cx; }
};

namespace {
Knapsack<TypeWeight, TypeValue> *knap;
TypeWeight *weight;
TypeValue *value;
element *q;
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
            knap->setSelection(q[n - i].id, node.selection[i]);
        }
        delete[] node.selection;
        return;
    }
    if (node.weight + weight[node.level] <= knap->getCapacity()) {
        Pnode left = Pnode();
        left.weight = node.weight + weight[node.level];
        left.value = node.value + value[node.level];
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
    right.cx = node.cx + value[node.level];
    right.selection = new bool[right.level]{};
    for (int i = 1; i < node.level; i++) {
        right.selection[i] = node.selection[i];
    }
    right.selection[node.level] = false;
    pq.push(right);
    delete[] node.selection;
}

bool solve(Knapsack<TypeWeight, TypeValue> *knapsack) {
    int n = knapsack->getCount();
    knap = knapsack;
    weight = new TypeWeight[n + 1]{};
    value = new TypeValue[n + 1]{};
    q = new element[n]{};
    sortPack(knapsack, weight, value, q);
    min_cost = 0;
    Pnode first = Pnode();
    first.level = 1;
    pq.push(first);
    while (!pq.empty()) { branchBound(pq.top()); }
    delete[] q;
    delete[] weight;
    delete[] value;
    return true;
}
