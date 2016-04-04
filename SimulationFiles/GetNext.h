#ifndef __GETNEXT_H__
#define __GETNEXT_H__
#include <iostream>
#include "Core.h"

enum SCHED_TYPE { FCFS, RR, SPN, SRT, Feedback };

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

	/*case SRT: // DOES NOT WORK RIGHT
	{
		Process *next_to_run = new Process();
		for (unsigned int i = 0; i < procs_in_use.size(); i++) {
			if (i == 0)
				next_to_run = &procs_in_use[i];
			if (next_to_run->getBurstTimeLeft() > procs_in_use[i].getBurstTimeLeft()) {
				next_to_run = &procs_in_use[i];
			}
		}
		return next_to_run;
	}*/
	default:
		std::cout << "We Messed up somewhere" << std::endl;
		return -1;
		break;
	}
}

#endif
