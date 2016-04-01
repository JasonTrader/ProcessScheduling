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
	unsigned int quantum;
	std::vector<Process> unarrived_procs;
	std::vector<Process> arrived_procs;
	std::vector<Process> finished_procs;
	std::vector<Core*> cores;
	SCHED_TYPE sched_string;
	std::vector<Process> waitq;

public:
	PCB(std::vector<Process> _procs, unsigned int _sim_time, SCHED_TYPE _sched_string, unsigned int _core_num, unsigned int _quantum, bool _uniproc) {
		unarrived_procs = _procs;
		std::sort(unarrived_procs.begin(), unarrived_procs.end());
		sim_time = _sim_time;
		sched_string = _sched_string;
		while (_core_num-- > 0) {
			cores.push_back(new Core());
		}
		uniproc = _uniproc;
		quantum = _quantum;
	}

	//runs one clock tick
	void Update(unsigned int clock_int) {
		//allow new processes to arrive
		while (clock_int == unarrived_procs.front().getArrivalTime()) {
			arrived_procs.push_back(unarrived_procs.front());
			unarrived_procs.erase(unarrived_procs.begin());
		}

		Process *next = getNext(arrived_procs, sched_string, cores[0], quantum);
		if (uniproc) {
			Process *proc_ret = new Process();
			proc_ret = cores[0]->Update(*next);
			if (proc_ret != NULL) {
				if (proc_ret->hasBurstTimeLeft()) {
					arrived_procs.push_back(*proc_ret);
				}
			}
		}


		//decrement burst for all processes waiting on IO burst AND check for finished_procs
		for (unsigned int i = 0; i < arrived_procs.size(); i++) {
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
