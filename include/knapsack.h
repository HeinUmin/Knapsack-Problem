#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <algorithm>
#include <fstream>
#include <iostream>

template <typename TypeW, typename TypeV>
class Knapsack {
  private:
    int count;
    TypeW capacity;
    TypeV optimum;
    struct Item {
        int id;
        TypeW weight;
        TypeV value;
        bool selection;
        bool operator<(const Item &item) const {  // 按价值率排序
            return (double)value / weight > (double)item.value / item.weight;
        }
    } *item;

  public:
    explicit Knapsack(char *file_input);
    Knapsack(int n, char *f_c, char *f_w, char *f_v);
    ~Knapsack();
    Knapsack(const Knapsack &) = delete;
    Knapsack &operator=(const Knapsack &) = delete;
    Knapsack(Knapsack &&) = delete;
    Knapsack &operator=(Knapsack &&) = delete;
    [[nodiscard]] bool isReady() const;  // 检查是否初始化成功
    [[nodiscard]] int getCount() const;
    [[nodiscard]] TypeW getCapacity() const;
    [[nodiscard]] TypeV getOptimum() const;
    [[nodiscard]] TypeW getWeight(int index) const;
    [[nodiscard]] TypeV getValue(int index) const;
    [[nodiscard]] bool getSelection(int index) const;
    void setOptimum(TypeV opti);
    bool setSelection(int index, bool select = true);
    bool checkOptimum(char *file_o) const;    // 检查最优解是否正确
    bool checkSelection(char *file_s) const;  // 检查物品选择是否正确
    void printResult() const;
};

template <typename TypeW, typename TypeV>
Knapsack<TypeW, TypeV>::Knapsack(char *file_input)
    : count(0), capacity(0), optimum(0) {
    std::ifstream fs;
    fs.open(file_input);
    fs >> count;
    fs >> capacity;
    item = new Item[count + 1]{};
    for (int i = 1; i <= count; i++) {
        item[i].id = i;
        fs >> item[i].value;
        fs >> item[i].weight;
    }
    fs.close();
    std::sort(item + 1, item + count + 1);
}

template <typename TypeW, typename TypeV>
Knapsack<TypeW, TypeV>::Knapsack(int n, char *f_c, char *f_w, char *f_v)
    : count(n), capacity(0), optimum(0), item(new Item[n + 1]{}) {
    std::ifstream fs_c, fs_w, fs_v;
    fs_c.open(f_c);
    fs_c >> capacity;
    fs_c.close();
    fs_w.open(f_w);
    fs_v.open(f_v);
    for (int i = 1; i <= n; i++) {
        item[i].id = i;
        fs_w >> item[i].weight;
        fs_v >> item[i].value;
    }
    fs_v.close();
    fs_c.close();
    std::sort(item + 1, item + n + 1);
}

template <typename TypeW, typename TypeV>
Knapsack<TypeW, TypeV>::~Knapsack() {
    delete[] item;
}

template <typename TypeW, typename TypeV>
inline bool Knapsack<TypeW, TypeV>::isReady() const {
    return count > 0 && capacity > 0 && item[count].weight > 0 &&
           item[count].value > 0;
}

template <typename TypeW, typename TypeV>
inline int Knapsack<TypeW, TypeV>::getCount() const {
    return count;
}

template <typename TypeW, typename TypeV>
inline TypeW Knapsack<TypeW, TypeV>::getCapacity() const {
    return capacity;
}

template <typename TypeW, typename TypeV>
inline TypeV Knapsack<TypeW, TypeV>::getOptimum() const {
    return optimum;
}

template <typename TypeW, typename TypeV>
inline TypeW Knapsack<TypeW, TypeV>::getWeight(int index) const {
    if (index < 0 || index > count) { return -1; }
    return item[index].weight;
}

template <typename TypeW, typename TypeV>
inline TypeV Knapsack<TypeW, TypeV>::getValue(int index) const {
    if (index < 0 || index > count) { return -1; }
    return item[index].value;
}

template <typename TypeW, typename TypeV>
inline bool Knapsack<TypeW, TypeV>::getSelection(int index) const {
    if (index < 0 || index > count) { return false; }
    return item[index].selection;
}

template <typename TypeW, typename TypeV>
inline void Knapsack<TypeW, TypeV>::setOptimum(TypeV opti) {
    optimum = opti;
}

template <typename TypeW, typename TypeV>
inline bool Knapsack<TypeW, TypeV>::setSelection(int index, bool select) {
    if (index < 0 || index > count) { return false; }
    item[index].selection = select;
    return true;
}

template <typename TypeW, typename TypeV>
bool Knapsack<TypeW, TypeV>::checkOptimum(char *file_o) const {
    std::ifstream file;
    TypeV opti_ans = 0;
    file.open(file_o);
    file >> opti_ans;
    file.close();
    if ((long long)optimum == (long long)opti_ans) {
        std::cout << "Check the optimum passed!" << std::endl;
        return true;
    } else {
        std::cout << "Check the optimum failed!" << std::endl;
        return false;
    }
}

template <typename TypeW, typename TypeV>
bool Knapsack<TypeW, TypeV>::checkSelection(char *file_s) const {
    std::ifstream file;
    int select_ans = false;
    bool *selection = new bool[count + 1];
    for (int i = 1; i <= count; i++) {
        selection[item[i].id] = item[i].selection;  // selection按照id排序
    }
    file.open(file_s);
    for (int i = 1; i <= count; i++) {
        file >> select_ans;
        if (selection[i] != select_ans) {
            std::cout << "Check selections failed!" << std::endl;
            return false;
        }
    }
    file.close();
    std::cout << "Check selections passed!" << std::endl;
    delete[] selection;
    return true;
}

template <typename TypeW, typename TypeV>
void Knapsack<TypeW, TypeV>::printResult() const {
    bool *selection = new bool[count + 1];
    for (int i = 1; i <= count; i++) {
        selection[item[i].id] = item[i].selection;  // selection按照id排序
    }
    std::cout << "optimum: " << optimum << std::endl << "selection: ";
    for (int i = 1; i <= count; i++) { std::cout << selection[i]; }
    std::cout << std::endl;
    delete[] selection;
}

#endif  // KNAPSACK_H