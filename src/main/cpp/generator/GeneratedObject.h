#ifndef QUASIGROUP_GENERATEDOBJECT_H
#define QUASIGROUP_GENERATEDOBJECT_H

#include <random>

namespace Quasigroup {
/*
 * Abstract class for randomly generated objects
 */

class GeneratedObject {
  unsigned long long int seed;
  std::random_device rd;

 public:
  virtual ~GeneratedObject() = default;
  unsigned long long int getSeed() const;

 protected:
  std::mt19937 mersenne;

  virtual void generate() = 0;

  explicit GeneratedObject(unsigned long long int seed = 0);
};
}  // namespace Quasigroup

#endif  // QUASIGROUP_GENERATEDOBJECT_H