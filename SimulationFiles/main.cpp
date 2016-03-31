#include <iostream>
#include "PCB.h"
using namespace std;

int main() {
	vector<Process> procs;
	//hard coded for now
	unsigned int sim_time = 100000;
	SCHED_TYPE sched_string = FCFS;
	unsigned int core_num = 1;
	unsigned int quantum = 20;
	bool uniproc = true;

	string line;
	ifstream myfile("data.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			stringstream ss(line);
			istream_iterator<string> begin(ss);
			istream_iterator<string> end;
			vector<string> vstrings(begin, end);
			
			vector<pair<string, unsigned int>> bursts;
			for (int i = 5; i < vstrings.size(); i += 2) {
				if (vstrings[i - 1].compare("CPU")) {
					bursts.push_back(<"CPU", atoi(vstrings[i].c_str()>));
				}
				else {
					bursts.push_back(<"IO", atoi(vstrings[i].c_str()>));
				}
			}

			procs.push_back(new Process(vstrings[0], vstrings[2], burts));
		}
		myfile.close();
	}
	else cout << "Unable to open data file :(" << endl;
	
	PCB pcb = PCB(procs, sim_time, sched_string, core_num, quantum, uniproc);

	//start running simulation
	for (int clock_int = 0; clock_int < pcb.getSimTime(); clock_int++) {
		pcb.Update(clock_int);
	}

	return 0;
}
