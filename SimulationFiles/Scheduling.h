#ifndef __SCHEDULING_H__
#define __SCHEDULING_H__
#include "Core.h"
#include "ProcData.h"
#include <queue>
#include <vector>
#include <algorithm>

//IMPORTANT: Check all dot and arrow operators because I'm probably using the wrong ones

void runFCFS(std::vector<Process> &procs, Core* core){
	std::sort(procs->begin(), procs->end());
    std::queue<Process> arriv_q; //no priority queue because there's no priority to sort on
    int clock_tick_counter = 0;
    for(clock_tick_counter; clock_tick_counter<procs.size(); clock_tick_counter++){
    	while(clock_tick_counter == procs.front().getArrivalTime()) {
    		arriv_q.push(procs.front());
    		procs.erase(procs.begin());
    	}
    if (!arriv_q.empty()) {
    	//push a process into the core for x amount of time
    	//record whatever data we're recording
    	//do the update function
    }
  }
}



#endif
