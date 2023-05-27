#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <fstream>
#include <iostream>

template <typename TypeW, typename TypeV>
class Knapsack
{
  private:
    int count;
    TypeW capacity;
    TypeV optimum;
    bool *selection;
    TypeW *weight;
    TypeV *value;

  public:
    explicit Knapsack(int count);
    explicit Knapsack(char *file_input);
    Knapsack(int count, char *file_c, char *file_w, char *file_v);
    ~Knapsack();
    Knapsack(const Knapsack &) = delete;
    Knapsack &operator=(const Knapsack &) = delete;
    Knapsack(Knapsack &&) = delete;
    Knapsack &operator=(Knapsack &&) = delete;
    [[nodiscard]] int getCount() const;
    [[nodiscard]] TypeW getCapacity() const;
    [[nodiscard]] TypeV getOptimum() const;
    [[nodiscard]] TypeW getWeight(int index) const;
    [[nodiscard]] TypeV getValue(int index) const;
    [[nodiscard]] int getSelection(int index) const;
    void setOptimum(TypeV opti);
    bool setSelection(int index, bool select = true);
    bool checkOptimum(char *file_o) const;
    bool checkSelection(char *file_s) const;
    void printResult() const;
};

template <typename TypeW, typename TypeV>
Knapsack<TypeW, TypeV>::Knapsack(int count)
    : count(count), capacity(0), optimum(0), selection(new bool[count + 1]{}),
      weight(new TypeW[count + 1]{}), value(new TypeV[count + 1]{}) {}

template <typename TypeW, typename TypeV>
Knapsack<TypeW, TypeV>::Knapsack(char *file_input)
    : count(0), capacity(0), optimum(0) {
    std::ifstream fs;
    fs.open(file_input);
    fs >> count;
    fs >> capacity;
    value = new TypeV[count + 1]{};
    weight = new TypeW[count + 1]{};
    selection = new bool[count + 1]{};
    for (int i = 1; i <= count; i++) {
        fs >> value[i];
        fs >> weight[i];
    }
    fs.close();
}

template <typename TypeW, typename TypeV>
Knapsack<TypeW, TypeV>::Knapsack(int count,
                                 char *file_c,
                                 char *file_w,
                                 char *file_v)
    : count(count), capacity(0), optimum(0), selection(new bool[count + 1]{}),
      weight(new TypeW[count + 1]{}), value(new TypeV[count + 1]{}) {
    std::ifstream file;
    file.open(file_c);
    file >> capacity;
    file.close();
    file.open(file_w);
    for (int i = 1; i <= count; i++) { file >> weight[i]; }
    file.close();
    file.open(file_v);
    for (int i = 1; i <= count; i++) { file >> value[i]; }
    file.close();
}

template <typename TypeW, typename TypeV>
Knapsack<TypeW, TypeV>::~Knapsack() {
    delete[] selection;
    delete[] weight;
    delete[] value;
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
    return weight[index];
}

template <typename TypeW, typename TypeV>
inline TypeV Knapsack<TypeW, TypeV>::getValue(int index) const {
    if (index < 0 || index > count) { return -1; }
    return value[index];
}

template <typename TypeW, typename TypeV>
inline int Knapsack<TypeW, TypeV>::getSelection(int index) const {
    if (index < 0 || index > count) { return false; }
    return selection[index];
}

template <typename TypeW, typename TypeV>
inline void Knapsack<TypeW, TypeV>::setOptimum(TypeV opti) {
    optimum = opti;
}

template <typename TypeW, typename TypeV>
inline bool Knapsack<TypeW, TypeV>::setSelection(int index, bool select) {
    if (index < 0 || index > count) { return false; }
    selection[index] = select;
    return true;
}

template <typename TypeW, typename TypeV>
bool Knapsack<TypeW, TypeV>::checkOptimum(char *file_o) const {
    std::ifstream file;
    TypeV opti_ans = 0;
    file.open(file_o);
    file >> opti_ans;
    file.close();
    if (optimum == opti_ans) {
        std::cout << "Check passed!" << std::endl;
        return true;
    } else {
        std::cout << "Check failed!" << std::endl;
        return false;
    }
}

template <typename TypeW, typename TypeV>
bool Knapsack<TypeW, TypeV>::checkSelection(char *file_s) const {
    std::ifstream file;
    int select_ans = false;
    file.open(file_s);
    for (int i = 1; i <= count; i++) {
        file >> select_ans;
        if (selection[i] != select_ans) {
            std::cout << "Check failed!" << std::endl;
            return false;
        }
    }
    file.close();
    std::cout << "Check passed!" << std::endl;
    return true;
}

template <typename TypeW, typename TypeV>
void Knapsack<TypeW, TypeV>::printResult() const {
    std::cout << "optimum: " << optimum << std::endl << "selection: ";
    for (int i = 1; i <= count; i++) { std::cout << selection[i] << " "; }
    std::cout << std::endl;
}

#endif  // KNAPSACK_H