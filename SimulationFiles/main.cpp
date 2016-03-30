#include <iostream>
#include "PCB.h"
using namespace std;

int main() {
  //put set up here
  PCB pcb = PCB(procs, sim_time, sched_string, cores);

  sort(unarrived_procs->begin(), unarrived_procs->end());

  for (int clock_int = 0; clock_int < pcb.getSimTime(); clock_int++) {
    pcb.Update(clock_int);
  }

  return 0;
}
