#ifndef QUASIGROUP_LATINSQUAREQUASIGROUP_H
#define QUASIGROUP_LATINSQUAREQUASIGROUP_H

#include <functional>

#include "Quasigroup.h"

namespace Quasigroup {
/*
 * The class of quasigroups defined by the Latin square
 */

class LatinSquareQuasigroup : public Quasigroup {
 public:
  [[nodiscard]] int getProduct(int x, int y) const override;

  explicit LatinSquareQuasigroup(int order);

  explicit LatinSquareQuasigroup(const Quasigroup &q);

  LatinSquareQuasigroup(int order, std::ifstream &input);

  LatinSquareQuasigroup(int order, int **latinSquare);

  LatinSquareQuasigroup(
      std::initializer_list<std::initializer_list<int> > latinSquare);

  LatinSquareQuasigroup(int order, const std::function<int(int, int)> &product);

  ~LatinSquareQuasigroup() override;

  friend bool operator==(const LatinSquareQuasigroup &q1,
                         const LatinSquareQuasigroup &q2);

  void swapRows(int firstLineNumber, int secondLineNumber) const;

  void swapColumns(int firstColumnNumber, int secondColumnNumber) const;

  void setRow(int rowNumber, const std::vector<int> &values) const;

  void setColumn(int columnNumber, const std::vector<int> &values) const;

 protected:
  int **latinSquare;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_LATINSQUAREQUASIGROUP_H