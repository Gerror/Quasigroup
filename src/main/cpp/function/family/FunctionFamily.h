#ifndef QUASIGROUP_FUNCTIONFAMILY_H
#define QUASIGROUP_FUNCTIONFAMILY_H

#include <fstream>

namespace Quasigroup {
class FunctionFamily {
  int numberOfFunctions;
  int functionSize;

 public:
  FunctionFamily(int k, int n, int numberOfFunctions, int functionSize);

  FunctionFamily(int k, int n, int numberOfFunctions, int functionSize,
                 std::ifstream &input);

  FunctionFamily(const FunctionFamily &ff);

  FunctionFamily(int k, int n, int numberOfFunctions, int functionSize,
                 int **functionFamily);

  FunctionFamily() = default;

  virtual ~FunctionFamily();

  int getK() const;

  int getN() const;

  int getNumberOfFunctions() const;

  int getFunctionSize() const;

  int getFunctionValue(int varValue, int functionNumber = 0) const;

  friend std::ostream &operator<<(std::ostream &out, const FunctionFamily &ff);

  friend bool operator==(const FunctionFamily &ff1, const FunctionFamily &ff2);

  FunctionFamily &operator=(const FunctionFamily &ff);

 protected:
  int k;
  int n;
  int **functionFamily;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_FUNCTIONFAMILY_H