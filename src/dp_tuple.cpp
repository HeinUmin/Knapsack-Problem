#include "utils.h"
#include <forward_list>

namespace {
Knapsack<TypeWeight, TypeValue> *knap;
forward_list<pair<TypeWeight, TypeValue>> *list;
}  // namespace

void dynamicProgram(int i) {
    auto comp_it = list[i - 1].begin();
    auto insert_it = list[i].before_begin();
    TypeValue pre_v = 0;
    for (auto &it : list[i - 1]) {
        TypeWeight w = it.first + knap->getWeight(i);
        TypeValue v = it.second + knap->getValue(i);
        while (comp_it != list[i - 1].end() && comp_it->first < w) {
            if (pre_v >= comp_it->second) {
                comp_it++;
                continue;
            }
            pre_v = comp_it->second;
            insert_it = list[i].emplace_after(insert_it, comp_it->first, pre_v);
            comp_it++;
        }
        if (w > knap->getCapacity()) { break; }
        if (pre_v >= v) { continue; }
        if ((comp_it != list[i - 1].end()) && (comp_it->first == w) &&
            (comp_it->second >= v)) {
            pre_v = comp_it->second;
            insert_it = list[i].emplace_after(insert_it, comp_it->first, pre_v);
            continue;
        }
        pre_v = v;
        insert_it = list[i].emplace_after(insert_it, w, pre_v);
    }
}

void traceback() {
    int n = knap->getCount();
    TypeWeight w = 0;
    TypeValue v = 0;
    for (auto &it : list[n]) {
        w = it.first;
        v = it.second;
    }
    knap->setOptimum(v);
    for (int i = n; i > 0; i--) {
        auto it = list[i - 1].begin();
        TypeWeight cur_weight = w - knap->getWeight(i);
        TypeValue cur_value = v - knap->getValue(i);
        while ((long long)it->first < (long long)cur_weight) { it++; }
        if (((long long)it->first == (long long)cur_weight) &&
            ((long long)it->second == (long long)cur_value)) {
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
    for (int i = 1; i <= n; i++) { dynamicProgram(i); }
    traceback();
    delete[] list;
    return knap->getOptimum() != 0;
}