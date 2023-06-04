#include "utils.h"
#include <queue>

struct Pnode {  // 优先队列中的结点
    int level;
    TypeWeight weight;
    TypeValue value;
    TypeValue cx;  // 当前成本
    bool *selection;
    bool operator>(const Pnode &p) const { return cx > p.cx; }
};

namespace {
Knapsack<TypeWeight, TypeValue> *knap;
TypeValue min_cost;                                  // 当前最优解的成本
priority_queue<Pnode, vector<Pnode>, greater<>> pq;  // 优先队列（成本低优先）
}  // namespace

void branchBound(Pnode node) {
    int n = knap->getCount();
    pq.pop();
    if (min_cost != 0 && min_cost < node.cx) {
        delete[] node.selection;  // 当前最优解的成本小于当前结点的成本，剪枝
        return;
    }
    if (node.level > n) {  // 到达叶子结点
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
    if (node.weight + w <= knap->getCapacity()) {  // 左子树可展开
        Pnode left = {node.level + 1, node.weight + w, node.value + v, node.cx,
                      new bool[node.level + 1]{}};
        for (int i = 1; i < node.level; i++) {
            left.selection[i] = node.selection[i];
        }
        left.selection[node.level] = true;  // 左子树选择当前物品
        pq.push(left);
    }
    Pnode right = {node.level + 1, node.weight, node.value, node.cx + v,
                   new bool[node.level + 1]{}};
    for (int i = 1; i < node.level; i++) {
        right.selection[i] = node.selection[i];
    }
    right.selection[node.level] = false;  // 右子树不选择当前物品
    pq.push(right);
    delete[] node.selection;
}

bool solve(Knapsack<TypeWeight, TypeValue> *knapsack) {
    cout << "Branch and Bound:" << endl;
    knap = knapsack;
    min_cost = 0;
    Pnode first = {1, 0, 0, 0, new bool[1]{}};  // 根结点
    pq.push(first);                             // 优先队列插入根结点
    while (!pq.empty()) { branchBound(pq.top()); }  // 优先队列不为空，继续分支
    return knap->getOptimum() != 0;
}
