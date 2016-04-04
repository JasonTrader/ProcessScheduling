#ifndef __PCB_H__
#define __PCB_H__

#include "Core.h"
#include <queue>
#include <algorithm>
#include "GetNext.h"
#include "ProcData.h"

class PCB {
private:
	unsigned int sim_time;
	unsigned int quantum;
	std::vector<Process> unarrived_procs;
	std::vector<Process> arrived_procs;
	std::vector<Process> finished_procs;
	std::vector<Process> waiting_procs;
	std::vector<Core*> cores;
	SCHED_TYPE sched_string;
	std::vector<Process> waitq;
	std::string filename;

public:

	PCB(std::vector<Process> _procs, unsigned int _sim_time, SCHED_TYPE _sched_string, unsigned int _core_num, unsigned int _quantum, std::string _filename) {
		unarrived_procs = _procs;
		std::sort(unarrived_procs.begin(), unarrived_procs.end());
		sim_time = _sim_time;
		sched_string = _sched_string;
		while (_core_num-- > 0) {
			cores.push_back(new Core());
		}
		quantum = _quantum;
		filename = _filename;
	}

#pragma region gettors and setters

	unsigned int getSimTime() { return sim_time; }

#pragma endregion

#pragma region core functions
	//runs one clock tick
	void Update(unsigned int clock_int) {
		//allow new processes to arrive
		while (!unarrived_procs.empty() && clock_int == unarrived_procs.front().getArrivalTime()) {
			arrived_procs.push_back(unarrived_procs.front());
			unarrived_procs.erase(unarrived_procs.begin());
			if(unarrived_procs.empty()){
				break;
			}
		}
		for(int ci = 0; ci< cores.size(); ci++){
			int nextPlace = getNext(arrived_procs, sched_string, cores[ci], quantum);
			Process proc_ret;
			if(nextPlace == -1){
				Process myEmpty;
				proc_ret = cores[ci]->Update(myEmpty);
			}
			else{
				arrived_procs[nextPlace].setResponseTime(clock_int);
				proc_ret = cores[ci]->Update(arrived_procs[nextPlace]);
				arrived_procs.erase(arrived_procs.begin() + nextPlace);
			}
			if (!proc_ret.isEmpty()) {
				if(sched_string == Feedback){
					proc_ret.addQueueLevel();
				}
				if (proc_ret.hasBurstTimeLeft()) {
					arrived_procs.push_back(proc_ret);
				}
				else {
					proc_ret.removeFrontBurst();
					if (proc_ret.isDone()) {
						finished_procs.push_back(proc_ret);
						ProcData temp(proc_ret, clock_int, filename);
						temp.writeDataToFile();
					}
					else {
						waiting_procs.push_back(proc_ret);
					}
				}
			}
		}
		//decrement burst for all processes waiting on IO burst AND check for finished_procs
		for (unsigned int i = 0; i < waiting_procs.size(); i++) {
			if (waiting_procs[i].isWaitingIO())
				waiting_procs[i].decBurstTimeLeft();
			else {
				arrived_procs.push_back(waiting_procs[i]);
				waiting_procs.erase(waiting_procs.begin() + i);
				i--;
				if(i == waiting_procs.size()){
					break;
				}
			}
		}
	}

	void writeAdditionalData(std::string file) {
		int empty_cycles = 0;
		for (int i = 0; i < cores.size(); i++) {
			empty_cycles += cores[i]->getUnusedCount();
		}
		int num_completed_procs = finished_procs.size();
		std::fstream f;
		f.open(file, std::ios::app);
		f.seekg(std::ios_base::beg);
		f << empty_cycles << " " << num_completed_procs << "\n";
		f.close();
	}
#pragma endregion
};

#endif
