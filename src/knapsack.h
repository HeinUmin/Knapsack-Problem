#include <fstream>
#include <iostream>
#include <string>

#ifdef USE_DOUBLE
typedef double DataType;
#else
typedef int DataType;
#endif

using namespace std;

class Knapsack
{
  private:
    int count;
    DataType capacity;
    DataType optimum;
    bool *selection;
    DataType *weight;
    DataType *value;
    Knapsack(const Knapsack &);
    Knapsack &operator=(const Knapsack &);
    Knapsack(Knapsack &&) noexcept;
    Knapsack &operator=(Knapsack &&) noexcept;

  public:
    explicit Knapsack(char *file_input);
    Knapsack(int count, char *file_c, char *file_w, char *file_v);
    ~Knapsack();
    [[nodiscard]] int getCount() const;
    [[nodiscard]] DataType getCapacity() const;
    [[nodiscard]] DataType getOptimum() const;
    [[nodiscard]] DataType getWeight(int index) const;
    [[nodiscard]] DataType getValue(int index) const;
    [[nodiscard]] bool getSelection(int index) const;
    void setOptimum(DataType opti);
    bool setSelection(int index, bool select);
    bool checkOptimum(char *file_o) const;
    bool checkSelection(char *file_s) const;
};

void solve(Knapsack &bag);
