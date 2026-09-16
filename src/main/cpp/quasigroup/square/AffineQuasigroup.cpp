#include "AffineQuasigroup.h"

namespace Quasigroup {
AffineQuasigroup::AffineQuasigroup(const int order,
                                   const unsigned long long int seed)
    : LatinSquareQuasigroup(order), GeneratedObject(seed) {
  generate();
}

AffineQuasigroup::AffineQuasigroup(AbelianGroup *abelian_group,
                                   AbelianGroupAutomorphism *alpha,
                                   AbelianGroupAutomorphism *beta, const int c)
    : LatinSquareQuasigroup(abelian_group->getOrder()) {
  this->abelianGroup = abelian_group;
  this->alpha = alpha;
  this->beta = beta;
  this->c = c;

  initializeLatinSquare();
}

void AffineQuasigroup::initializeLatinSquare() const {
  for (int x = 0; x < order; x++) {
    for (int y = 0; y < order; y++) {
      latinSquare[x][y] = abelianGroup->getProduct(
          abelianGroup->getProduct(alpha->getImage(x), beta->getImage(y)), c);
    }
  }
}

void AffineQuasigroup::generate() {
  this->abelianGroup = new AbelianGroup(order);
  this->alpha = new AbelianGroupAutomorphism(abelianGroup, getSeed() + 2);
  this->beta = new AbelianGroupAutomorphism(abelianGroup, getSeed() + 3);
  this->c = mersenne() % order;

  initializeLatinSquare();
}

AffineQuasigroup::~AffineQuasigroup() {
  delete alpha;
  delete beta;
  delete abelianGroup;
}

AbelianGroup *AffineQuasigroup::getAbelianGroup() const { return abelianGroup; }

AbelianGroupAutomorphism *AffineQuasigroup::getAlpha() const { return alpha; }

AbelianGroupAutomorphism *AffineQuasigroup::getBeta() const { return beta; }

int AffineQuasigroup::getC() const { return c; }
}  // namespace Quasigroup
