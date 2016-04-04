#include "PCB.h"
#include <iterator>
#include <sstream>
#include <stdio.h>
using namespace std;

int main() {
	vector<Process> procs;
	//hard coded for now
	unsigned int sim_time = 100000;
	SCHED_TYPE sched_string = Feedback;
	unsigned int core_num = 1;
	unsigned int quantum = 50;
	bool uniproc = true;
	string filename = "Feedback.txt";
	string file = "AddFeedback.txt";

	remove(file.c_str());
	remove(filename.c_str());
	string line;
	ifstream myfile("data.txt");
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

	PCB pcb = PCB(procs, sim_time, sched_string, core_num, quantum, uniproc, filename);

	//start running simulation
	for (unsigned int clock_int = 0; clock_int < pcb.getSimTime(); clock_int++) {
		pcb.Update(clock_int);
		if (clock_int % 1000 == 0)
			cout << "At clock int: " << clock_int << endl;
	}
	pcb.writeAdditionalData(file);

	return 0;
}
