#include "knapsack.h"

int main(int argc, char *argv[]) {
    if (argc == 3) {
        Knapsack knapsack = Knapsack(argv[1]);
        solve(knapsack);
        cout << knapsack.checkOptimum(argv[2]) << endl;
    } else if (argc == 6) {
        char *p_end = nullptr;
        int count = strtol(argv[1], &p_end, 10);
        Knapsack knapsack = Knapsack(count, argv[2], argv[3], argv[4]);
        solve(knapsack);
        cout << knapsack.checkSelection(argv[5]) << endl;
    } else {
        cout << "usage: " << argv[0]
             << " {<file_question> <file_optimum> | <count> "
                "<file_capacity> <file_weight> <file_value> <file_selection>}"
             << endl;
        return -1;
    }
    return 0;
}

Knapsack::Knapsack(char *file_input) : count(0), capacity(0), optimum(0) {
    ifstream fs;
    fs.open(file_input);
    fs >> count;
    fs >> capacity;
    value = new DataType[count];
    weight = new DataType[count];
    selection = new bool[count];
    for (int i = 0; i < count; i++) {
        fs >> value[i];
        fs >> weight[i];
    }
    fs.close();
}

Knapsack::Knapsack(int count, char *file_c, char *file_w, char *file_v)
    : count(count), capacity(0), optimum(0), selection(new bool[count]),
      weight(new DataType[count]), value(new DataType[count]) {
    ifstream file;
    file.open(file_c);
    file >> capacity;
    file.close();
    file.open(file_w);
    for (int i = 0; i < count; i++) { file >> weight[i]; }
    file.close();
    file.open(file_v);
    for (int i = 0; i < count; i++) { file >> value[i]; }
    file.close();
}

Knapsack::~Knapsack() {
    delete[] selection;
    delete[] weight;
    delete[] value;
}

int Knapsack::getCount() const {
    return count;
}

DataType Knapsack::getCapacity() const {
    return capacity;
}

DataType Knapsack::getOptimum() const {
    return optimum;
}

DataType Knapsack::getWeight(int index) const {
    if (index < 0 || index >= count) { return -1; }
    return weight[index];
}

DataType Knapsack::getValue(int index) const {
    if (index < 0 || index >= count) { return -1; }
    return value[index];
}

bool Knapsack::getSelection(int index) const {
    if (index < 0 || index >= count) { return false; }
    return selection[index];
}

void Knapsack::setOptimum(DataType opti) {
    optimum = opti;
}

bool Knapsack::setSelection(int index, bool select) {
    if (index < 0 || index >= count) { return false; }
    selection[index] = select;
    return true;
}

bool Knapsack::checkOptimum(char *file_o) const {
    ifstream file;
    DataType opti_ans = 0;
    file.open(file_o);
    file >> opti_ans;
    file.close();
    return optimum == opti_ans;
}

bool Knapsack::checkSelection(char *file_s) const {
    ifstream file;
    bool select_ans = false;
    file.open(file_s);
    for (int i = 0; i < count; i++) {
        file >> select_ans;
        if (selection[i] != select_ans) { return false; }
    }
    file.close();
    return true;
}
