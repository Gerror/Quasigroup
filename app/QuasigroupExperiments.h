#ifndef QUASIGROUP_EXPERIMENTS_H
#define QUASIGROUP_EXPERIMENTS_H

#endif  // QUASIGROUP_EXPERIMENTS_H

namespace QuasigroupExperiments {

void runAllAlgorithmsExperimentOnJMQuasigroups(int qSizeStart, int qSizeEnd,
                                               int countPerIterations);

void runAssociativityExperimentOnAbelianGroups(int qSizeStart, int qSizeEnd,
                                               int countPerIterations);

void runAffinityExperimentOnAbelianGroups(int qSizeStart, int qSizeEnd,
                                          int countPerIterations);

}  // namespace QuasigroupExperiments
