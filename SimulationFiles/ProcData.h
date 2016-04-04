#ifndef __PROCDATA_H__
#define __PROCDATA_H__
#include <iostream>
#include <fstream>
#include "Process.h"

struct ProcData{
	unsigned int PID;
	unsigned int arriv_time;
	unsigned int tot_burst_time;
	unsigned int turnaround_time;
	unsigned int wait_time;
	unsigned int response_time;
	unsigned int clock_int;
	std::string filename;

	ProcData(Process &p, unsigned int _clock_int, std::string _filename) {
		clock_int = _clock_int;
		PID = p.getPID();
		arriv_time = p.getArrivalTime();
		tot_burst_time = p.getTotBurst();
		turnaround_time = p.getTurnaroundTime(clock_int);
		wait_time = p.getWaitTime(clock_int);
		response_time = p.getResponseTime();
		filename = _filename;

	}
#pragma region gettors and setters

	std::string getFileName() { return filename; }

#pragma endregion

#pragma region core functions

	void writeDataToFile() {
		std::ofstream proc_data;
		proc_data.open(filename, std::ios::app);
		proc_data << clock_int << " " << PID << " " << arriv_time << " " << tot_burst_time << " " << turnaround_time << " "
			<< wait_time << " " << response_time << "\n";
		proc_data.close();
	}

#pragma endregion
	
};

#endif
