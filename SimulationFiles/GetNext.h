#ifndef __GETNEXT_H__
#define __GETNEXT_H__
#include "Core.h"

enum SCHED_TYPE { FCFS, RR, SPN, SRT, Feedback};

Process getNext(std::vector<Process> &procs_in_use, SCHED_TYPE sched, Core *core, unsigned int quantum){
  if(procs_in_use.empty()){
    return NULL;
  }
  switch(sched){
    case FCFS:
      if(core->needsProcess()){
        return procs_in_use[0];
      }
      return NULL;

    case RR:
      unsigned int curr_used = core->getCurrRunTime();
      if(curr_used < quantum && !(core->needsProcess())) {
        return NULL;
      }
      return procs_in_use[0];

    case SPN:
      if (core->needsProcess()){
        Process next_to_run = new Process();
        for (int i = 0; i < procs_in_use->size(); i++) {
          if (i == 0)
            next_to_run = procs_in_use[i];
          if (next_to_run.getBurstTimeLeft() > procs_in_use[i]->getBurstTimeLeft()) {
            next_to_run = procs_in_use[i];
          }
        }
        return next_to_run;
      }
      return NULL;

    case SRT: 
      Process next_to_run = new Process();
      for (int i = 0; i < procs_in_use->size(); i++) {
        if (i == 0)
          next_to_run = procs_in_use[i];
        if (next_to_run.getBurstTimeLeft() > procs_in_use[i]->getBurstTimeLeft()) {
           next_to_run = procs_in_use[i];
        }
      }
      return next_to_run;
      
      return NULL;
    case default:
      cout << "We Messed up somewhere" << endl;
      return NULL;
  }
}

#endif
