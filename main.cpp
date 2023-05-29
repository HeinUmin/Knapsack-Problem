#include "utils.h"
#include <unistd.h>
using namespace std;

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
            if (access(optarg, R_OK) < 0) {
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
        char *capacity = nullptr, *weight = nullptr, *value = nullptr;
        while ((opt = getopt(argc, argv, "n:c:w:v:o:s:")) != -1) {
            switch (opt) {
            case 'n':
                n = strtol(optarg, nullptr, 10);
                continue;
            case 'c':
                capacity = optarg;
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
        if (!n || !capacity || !weight || !value) {
            usage(argv[0]);
            return -1;
        }
        knapsack =
            new Knapsack<TypeWeight, TypeValue>(n, capacity, weight, value);
    }
    if (solve(knapsack)) {
        knapsack->printResult();
        if (optimum) { knapsack->checkOptimum(optimum); }
        if (selection) { knapsack->checkSelection(selection); }
    } else {
        cout << "Cannot solve this problem." << endl;
    }
    delete knapsack;
    return 0;
}

void sortPack(Knapsack<TypeWeight, TypeValue> *knap,
              TypeWeight *weight,
              TypeValue *value,
              element *q) {
    int number = knap->getCount();
    for (int i = 1; i <= number; i++) {
        q[i - 1].id = i;
        q[i - 1].value = (double)knap->getValue(i) / knap->getWeight(i);
    }
    sort(q, q + number);
    for (int i = 1; i <= number; i++) {
        int id = q[number - i].id;
        weight[i] = knap->getWeight(id);
        value[i] = knap->getValue(id);
    }
}
