#ifndef __PCB_H__
#define __PCB_H__

#include "Core.h"
#include <queue>
#include <vector>
#include <algorithm>
#include "GetNext.h"

class PCB {
private:
	bool uniproc;
	unsigned int sim_time;
	vector<Process> unarrived_procs;
	vector<Process> arrived_procs;
	vector<Process> finished_procs;
	vector<Core*> cores;
	SCHED_TYPE sched_string;
	vector<Process> waitq;

public:
	PCB(std::vector<Process> procs, unsigned int sim_time, SCHED_TYPE sched_string, unsigned int core_num, unsigned int quantum, bool uniproc){
		this.procs = unarrived_procs;
		std::sort(unarrived_procs.begin(), unarrived_procs.end()));
		this.sim_time = sim_time;
		this.sched_string = sched_string;
		while(core_num--> 0){
			cores.push_back(new Core());
		}
		this.uniproc = uniproc;
	}

	//runs one clock tick
	void Update(unsigned int clock_int) {
		//allow new processes to arrive
		while (clock_int == unarrived_procs.front().getArrivalTime()) {
			arrived_procs.push_back(unarrived_procs.front());
			unarrived_procs.erase(procs.begin());
		}

		Process next = getNext(arrived_procs, sched_string, cores, quantum);
		if(uniproc){
			Process proc_ret = cores[0].Update(next);
			if(proc_ret != NULL){
				if(proc_ret.hasBurstTimeLeft()){
					arrived_procs.push_back(proc_ret);
				}
			}
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
				i--;
			}
		}
}

	unsigned int getSimTime() {
		return sim_time;
	}

};

#endif
