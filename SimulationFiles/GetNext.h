#ifndef __GETNEXT_H__
#define __GETNEXT_H__
#include <iostream>
#include <climits>
#include <cmath>
#include "Core.h"

enum SCHED_TYPE { FCFS, RR, SPN, SRT, Feedback };

//if nothing needs to be changed, return -1, if a new process needs into the core return 0
int getNext(std::vector<Process> &procs_in_use, SCHED_TYPE sched, Core *core, unsigned int quantum) {
	if (procs_in_use.empty()) {
		return -1;
	}
	int next_to_run;
	switch (sched) {
	case FCFS:
		if (core->needsProcess()) {
			return 0;
		}
		return -1;
		break;

	case RR:
		if (core->getCurrRunTime() < quantum && !(core->needsProcess())) {
			return -1;
		}
		return 0;
		break;

	case SPN:
		if (core->needsProcess()) {
			next_to_run = 0;
			for (unsigned int i = 0; i < procs_in_use.size(); i++) {
				if (procs_in_use[next_to_run].getBurstTimeLeft() > procs_in_use[i].getBurstTimeLeft()) {
					next_to_run = i;
				}
			}
			return next_to_run;
		}
		return -1;
		break;

	case SRT:
	{
		int temp;
		if (core->needsProcess()) {
			temp = INT_MAX;
		}
		else {
			temp = core->getProcess().getBurstTimeLeft();
		}
		next_to_run = -1;
		for (int i = 0; i < procs_in_use.size(); i++) {
			if (temp > procs_in_use[i].getBurstTimeLeft()) {
				temp = procs_in_use[i].getBurstTimeLeft();
				next_to_run = i;
			}
		}
		return next_to_run;
	}

	case Feedback:
	{
		if(!core->needsProcess() && pow(2, core->getProcess().getQueueLevel()) > core->getCurrRunTime()){
			return -1;
		}
		else{
			int minLevel = INT_MAX;
			int minPos = 0;
			for(int i = 0; i<procs_in_use.size(); i++){
				if(procs_in_use[i].getQueueLevel() < minLevel){
					minPos = i;
					minLevel = procs_in_use[i].getQueueLevel();
				}
			}
			return minPos;
		}
	}

	default:
		std::cout << "We Messed up somewhere" << std::endl;
		return -1;
		break;
	}
}


#endif
