#ifndef INSTANCESTABLE_H
#define INSTANCESTABLE_H

#include "graphNO.hpp"


class InstanceStable {


 private:

  GraphNO * g;

  std::vector<int> bestFoundStable;
  int currentOpt;

  bool isNotNeighborFromCurrentStable(int id);




 public:

void stableMax();
void stableMaxMPIvertex();
void stableMaxMPIedge();
void stableMaxMPIgrasp();

};

#endif
