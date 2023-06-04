#include "utils.h"
#include <forward_list>

namespace {
Knapsack<TypeWeight, TypeValue> *knap;
forward_list<pair<TypeWeight, TypeValue>> *list;  // 用链表存储每一层的元组
}  // namespace

void dynamicProgram(int i) {
    auto comp_it = list[i - 1].begin();       // 比较的迭代器
    auto insert_it = list[i].before_begin();  // 插入的迭代器
    TypeValue pre_v = 0;                      // 前一次插入的价值
    for (auto &it : list[i - 1]) {            // 遍历上一层的元组
        TypeWeight w = it.first + knap->getWeight(i);  // 当前重量
        TypeValue v = it.second + knap->getValue(i);   // 当前价值
        while (comp_it != list[i - 1].end() && comp_it->first < w) {
            pre_v = comp_it->second;  // 插入价值小于w的元组
            insert_it = list[i].emplace_after(insert_it, comp_it->first, pre_v);
            comp_it++;
        }
        if (w > knap->getCapacity()) { break; }  // 超过背包容量
        if (pre_v >= v) { continue; }  // 前一次插入价值大于等于v
        if ((comp_it != list[i - 1].end()) && (comp_it->first == w) &&
            (comp_it->second >= v)) {
            pre_v = comp_it->second;  // 插入价值等于w的且价值大于等于v的元组
            insert_it = list[i].emplace_after(insert_it, comp_it->first, pre_v);
            continue;
        }
        pre_v = v;  // 插入当前元组
        insert_it = list[i].emplace_after(insert_it, w, pre_v);
        while (comp_it != list[i - 1].end() && comp_it->second <= pre_v) {
            comp_it++;  // 跳过价值小于等于前一次插入价值的元组
        }
    }
}

void traceback() {
    int n = knap->getCount();
    TypeWeight w = 0;
    TypeValue v = 0;
    for (auto &it : list[n]) {  // 找到最优解
        w = it.first;
        v = it.second;
    }
    knap->setOptimum(v);
    for (int i = n; i > 0; i--) {
        auto it = list[i - 1].begin();
        TypeWeight cur_weight = w - knap->getWeight(i);
        TypeValue cur_value = v - knap->getValue(i);
#ifdef USE_DOUBLE  // 浮点数比较
        while (cur_weight - it->first >= EPS) { it++; }
        if (abs(cur_weight - it->first) < EPS &&
            abs(cur_value - it->second) < EPS)
#else
        while (it->first < cur_weight) { it++; }
        if ((it->first == cur_weight) && (it->second == cur_value))
#endif
        {  // 找到当前元组
            knap->setSelection(i, true);
            w = cur_weight;
            v = cur_value;
        } else {
            knap->setSelection(i, false);
        }
    }
}

bool solve(Knapsack<TypeWeight, TypeValue> *knapsack) {
    cout << "Dynamic Programming with tuple:" << endl;
    int n = knapsack->getCount();
    knap = knapsack;
    list = new forward_list<pair<TypeWeight, TypeValue>>[n + 1];
    list[0].emplace_front(0, 0);
    for (int i = 1; i <= n; i++) { dynamicProgram(i); }  // 动态规划求解最优解
    traceback();  // 回溯求解物品选择状态
    delete[] list;
    return knap->getOptimum() != 0;
}
