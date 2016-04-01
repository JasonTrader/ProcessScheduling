#ifndef __GETNEXT_H__
#define __GETNEXT_H__
#include <iostream>
#include "Core.h"

enum SCHED_TYPE { FCFS, RR, SPN, SRT, Feedback };

Process* getNext(std::vector<Process> &procs_in_use, SCHED_TYPE sched, Core *core, unsigned int quantum) {
	if (procs_in_use.empty()) {
		return NULL;
	}
	switch (sched) {
	case FCFS:
		if (core->needsProcess()) {
			Process *p = new Process();
			*p = procs_in_use[0];
			return p;
		}
		return NULL;
		break;

	case RR:
		if (core->getCurrRunTime() < quantum && !(core->needsProcess())) {
			return NULL;
		}
		return &procs_in_use[0];
		break;

	case SPN:
		if (core->needsProcess()) {
			Process *next_to_run = new Process();
			for (unsigned int i = 0; i < procs_in_use.size(); i++) {
				if (i == 0)
					next_to_run = &procs_in_use[i];
				if (next_to_run->getBurstTimeLeft() > procs_in_use[i].getBurstTimeLeft()) {
					next_to_run = &procs_in_use[i];
				}
			}
			return next_to_run;
		}
		return NULL;
		break;

	case SRT: // DOES NOT WORK RIGHT
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
	}
	default:
		std::cout << "We Messed up somewhere" << std::endl;
		return NULL;
		break;
	}
}

#endif
