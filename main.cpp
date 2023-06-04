#include "utils.h"
#include <chrono>
#include <unistd.h>

void usage(char *program) {
    cout << "usage: " << program << " {-q <file_question> | -n <count>"
         << " -c <file_capacity> -w <file_weight> -v <file_value>}"
         << " [-o <file_optimum>] [-s <file_selection>]" << endl;
}

int main(int argc, char *argv[]) {
    int opt = 0;
    char *optimum = nullptr, *selection = nullptr;
    Knapsack<TypeWeight, TypeValue> *knapsack = nullptr;
    if (argc < 8) {
        char *question = nullptr;
        while ((opt = getopt(argc, argv, "q:o:s:")) != -1) {
            switch (opt) {
            case 'q':
                question = optarg;
                break;
            case 'o':
                optimum = optarg;
                break;
            case 's':
                selection = optarg;
                break;
            default:
                usage(argv[0]);
                return -1;
            }
            if (access(optarg, R_OK) < 0) {  // 判断文件是否可读
                cout << "Cannot read file: " << optarg << endl;
                return -1;
            }
        }
        if (!question) {
            usage(argv[0]);
            return -1;
        }
        knapsack = new Knapsack<TypeWeight, TypeValue>(question);
    } else {
        int n = 0;
        char *capa = nullptr, *weight = nullptr, *value = nullptr;
        while ((opt = getopt(argc, argv, "n:c:w:v:o:s:")) != -1) {
            switch (opt) {
            case 'n':
                n = strtol(optarg, nullptr, 10);
                continue;
            case 'c':
                capa = optarg;
                break;
            case 'w':
                weight = optarg;
                break;
            case 'v':
                value = optarg;
                break;
            case 'o':
                optimum = optarg;
                break;
            case 's':
                selection = optarg;
                break;
            default:
                usage(argv[0]);
                return -1;
            }
            if (access(optarg, R_OK) < 0) {
                cout << "Cannot read file: " << optarg << endl;
                return -1;
            }
        }
        if (!n || !capa || !weight || !value) {
            usage(argv[0]);
            return -1;
        }
        knapsack = new Knapsack<TypeWeight, TypeValue>(n, capa, weight, value);
    }
    if (!knapsack->isReady()) {  // 判断是否初始化成功
        cout << "Initialization failed. Please check your input file." << endl;
        return -1;
    }
    auto start = chrono::steady_clock::now();    // 计时开始
    if (solve(knapsack)) {                       // 求解0/1背包问题
        auto end = chrono::steady_clock::now();  // 计时结束
        cout << "Time: " << (end - start) / 1us << "us" << endl;
        knapsack->printResult();
        if (optimum) { knapsack->checkOptimum(optimum); }
        if (selection) { knapsack->checkSelection(selection); }
    } else {
        cout << "Cannot solve this problem." << endl;
    }
    cout << endl;
    delete knapsack;
    return 0;
}
