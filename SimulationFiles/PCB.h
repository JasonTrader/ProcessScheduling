#ifndef __PCB_H__
#define __PCB_H__

#include <queue>
#include <vector>
#include "Scheduling.h"

enum SCHED_TYPE { FCFS, RR, SPN, SRT, HRRN, Feedback};

class PCB {
private:
	unsigned int sim_time;
	vector<Process> procs;
	SCHED_TYPE sched_string;

public:
	PCB(std::vector<Process> procs, unsigned int sim_time, SCHED_TYPE sched_string){
		this.procs = procs;
		this.sim_time = sim_time;
		this.sched_string = sched_string;
	}


};

#endif
