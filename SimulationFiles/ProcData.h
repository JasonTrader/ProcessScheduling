#ifndef __PROCDATA_H__
#define __PROCDATA_H__
#include <iostream>
#include <fstream>
#include <string>
#include "Process.h"

struct ProcData{
	unsigned int PID;
	unsigned int arriv_time;
	unsigned int tot_burst_time;
	unsigned int turnaround_time;
	unsigned int wait_time;
	unsigned int response_time;
	unsigned int clock_int;

	ProcData(Process &p, unsigned int _clock_int) {
		clock_int = _clock_int;
		PID = p.getPID();
		arriv_time = p.getArrivalTime(); 
		tot_burst_time = p.getTotBurst(); 
		turnaround_time = p.getTurnaroundTime(clock_int); 
		wait_time = p.getWaitTime(clock_int); 
		response_time = p.getResponseTime();


	}

	void writeDataToFile() {
		std::ofstream proc_data;
		proc_data.open("ProcessData.txt");
		proc_data << clock_int << " " << PID << " " << arriv_time << " " << tot_burst_time << " " << turnaround_time << " "
			<< wait_time << " " << response_time << "\n";
	}
};

#endif
