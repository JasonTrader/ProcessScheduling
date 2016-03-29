#ifndef __PCB_H__
#define __PCB_H__

#include "Core.h"
#include <queue>
#include <vector>
#include "Scheduling.h"

enum SCHED_TYPE { FCFS, RR, SPN, SRT, HRRN, Feedback};

class PCB {
private:
	unsigned int sim_time;
	vector<Process> unarrived_procs;
	vector<Process> arrived_procs;
	vector<Process> finished_procs;
	vector<Core> cores;
	SCHED_TYPE sched_string;

	void sortUnarrivedProcesses()) {
		std::sort(unarrived_procs->begin(), unarrived_procs->end());
	}

public:
	PCB(std::vector<Process> procs, unsigned int sim_time, SCHED_TYPE sched_string, vector<Core> cores){
		this.procs = unarrived_procs;
		this.sim_time = sim_time;
		this.sched_string = sched_string;
		this.cores = cores;

		sortUnarrivedProcesses();
	}

	//runs one clock tick
	void Update(unsigned int clock_int) {
		//allow new processes to arrive
		while (clock_int == unarrived_procs.front()->getArrivalTime()) {
				arrived_procs.push_back(unarrived_procs.front());
				unarrived_procs.erase(procs.begin());
		}

		//call scheduling function for one clock tick
		switch(sched_string)
		{
			case FCFS : runFCFS(arrived_procs, cores[0]); break;
		}

		//decrement burst for all processes waiting on IO burst AND check for finished_procs
		for (int i = 0; i < arrived_procs.size(); i++) {
			if (arrived_procs[i].isWaitingIO())
				arrived_procs[i].decBurstTimeLeft();

			//Question: will this cause a process to be skipped when a process is removed from arrived_procs?
			//I'm assuming so... which is a problem in this code.
			if (arrived_procs[i].isDone()) {
				finished_procs.push_back(arrived_procs[i]);
				arrived_procs.erase(arrived_procs.begin() + i);
			}
		}
}

	unsigned int getSimTime() {
		return sim_time;
	}

};

#endif
