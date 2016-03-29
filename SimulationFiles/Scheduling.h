#ifndef __SCHEDULING_H__
#define __SCHEDULING_H__
#include "Core.h"
#include "ProcData.h"
#include <queue>
#include <vector>
#include <algorithm>

void runFCFS(std::vector<Process> &procs, Core* core){
	//Riley - I took some of our code from here and moved it into the PCB creating an Update function
	//I'm assuming we want this function to be called every clock tick, instead of managing the clock ticks insides the function

	//my assumption is that the vector procs is already sorted by arrival time (the first time this function is called)
	//and that after a process is done in the core it is put to the end of the line in procs
	if (core->needsProcess()) {
		//send the core the process that arrived first & is not waiting on IO
		for (int i = 0; i < procs.size(); i++) {
			if (!procs[i].isWaitingIO()) {
				Process temp = core->Update(procs[i]);
				procs.erase(procs.begin() + i);

				if (temp != NULL)
					procs.push_back(temp);

				break;
			}
		}
	}
	else {
		//the core does not need a process so we pass it null
		Process temp = core->Update(NULL);

		if (temp != NULL)
			procs.push_back(temp);
	}
}

#endif
