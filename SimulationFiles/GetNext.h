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
      if(core[0]->needsProcess()){
        return procs_in_use[0];
      }
      return NULL;
    case RR:
      unsigned int quant_used = core[0]->getCurrRunTime();
      if(quant_used < quantum){
        return NULL;
      }
      return procs_in_use[0];
    case default:
      //Might need to throw error later
      return NULL;
  }
}

#endif
