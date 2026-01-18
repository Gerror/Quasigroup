#ifndef QUASIGROUP_WELLKNOWNPROPERFAMILYCATALOG_H
#define QUASIGROUP_WELLKNOWNPROPERFAMILYCATALOG_H
#include "ProperFamily.h"

/*
 * A class of predefined regular families from which cryptographically valuable
 * quasigroups can be guaranteed to be obtained
 *
 * Example of adding new static family:
 *
 * static ProperFamily createFamily() {
 *   static int row1[2] = {0, 0};
 *   static int row2[2] = {1, 1};
 *   static int* rows[2] = {row1, row2};
 *   return ProperFamily(2, 2, rows);
 * }
 *
 * public:
 *   static const ProperFamily& family() {
 *     static const ProperFamily instance = createFamily();
 *     return instance;
 *   }
 */
namespace Quasigroup {
class WellKnownProperFamilyCatalog {
 public:
  WellKnownProperFamilyCatalog() = delete;
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_WELLKNOWNPROPERFAMILYCATALOG_H
