#include "PCB.h"
#include <iterator>
#include <sstream>
#include <map>
#include <stdio.h>
using namespace std;

//arg1 scheduling algorithm
//arg2 quantum, NOTE not all algorithms use quantum
//arg3 primary output file name
//arg4 secondary output file name
//arg5 input data file, NOTE must be well formed
//arg6 number of cores, NOTE must be 1 for uniprocessor
int main(int argc, char *argv) {
	vector<Process> procs;
	//hard coded for now
	unsigned int sim_time = 100000;
	map<string, SCHED_TYPE> my_map;
	my_map["FCFS"] = FCFS; my_map["RR"] = RR; my_map["SPN"] = SPN; my_map["SRT"] = SRT; my_map["Feedback"] = Feedback;
	SCHED_TYPE sched_string = my_map[to_string(argv[1])];
	unsigned int core_num = argv[6];
	unsigned int quantum = argv[2];
	string filename = to_string(argv[3]);
	string file = to_string(argv[4]);

	remove(file.c_str());
	remove(filename.c_str());
	string line;
	ifstream myfile(to_string(argv[5]));
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			istringstream ss(line);
			istream_iterator<string> begin(ss);
			istream_iterator<string> end;
			vector<string> vstrings(begin, end);

			vector<pair<string, unsigned int> > bursts;
			unsigned int PID = atoi(vstrings[0].c_str());
			unsigned int arrival_time = atoi(vstrings[2].c_str());

			for (unsigned int i = 4; i < vstrings.size(); i += 2) {
				if (vstrings[i - 1].compare("CPU") == 0) {
					bursts.push_back(make_pair("CPU", atoi(vstrings[i].c_str())));
				}
				else {
					bursts.push_back(make_pair("IO", atoi(vstrings[i].c_str())));
				}
			}

			Process *p = new Process(PID, arrival_time, bursts);
			procs.push_back(*p);
		}
		myfile.close();
	}
	else cout << "Unable to open data file :(" << endl;

	PCB pcb = PCB(procs, sim_time, sched_string, core_num, quantum, filename);

	//start running simulation
	for (unsigned int clock_int = 0; clock_int < pcb.getSimTime(); clock_int++) {
		pcb.Update(clock_int);
		if (clock_int % 1000 == 0)
			cout << "At clock int: " << clock_int << endl;
	}
	pcb.writeAdditionalData(file);

	return 0;
}
