#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <vector>
#include <utility>
#include <string>

class Process {
private:
	unsigned int PID;
	unsigned int arriv_time;
	unsigned int tot_burst_time;
	unsigned int response_time;
	unsigned int queue_level = 1;
	bool responded_to = false;
	bool empty_proc;
	std::vector<std::pair<std::string, unsigned int> > bursts;

public:

	Process(unsigned int _PID, unsigned int _arriv_time, std::vector<std::pair<std::string, unsigned int> > _bursts) {
		PID = _PID;
		arriv_time = _arriv_time;
		bursts = _bursts;
		tot_burst_time = 0;
		for (unsigned int i = 0; i < bursts.size(); i++) {
			tot_burst_time += bursts[i].second;
		}
		empty_proc = false;
	}

	Process() {
		empty_proc = true;
	}

	//compares on arrival time
	bool operator<(const Process &other) {
		return arriv_time < other.arriv_time;
	}

#pragma region gettors and setters

	unsigned int getPID() { return PID; }

	unsigned int getArrivalTime() { return arriv_time; }

	unsigned int getTurnaroundTime(unsigned int clockTime) { return clockTime - arriv_time; }

	unsigned int getTotBurst() { return tot_burst_time; }

	unsigned int getBurstTimeLeft() {
		int ret;
		(!bursts.empty()) ? ret = bursts[0].second : ret = 0;
		return ret;
	}

	unsigned int getWaitTime(unsigned int clockTime) { return (clockTime - arriv_time) - tot_burst_time; }

	unsigned int getResponseTime() { return response_time; }

	unsigned int getQueueLevel() { return queue_level; }

	void setResponseTime(unsigned int clockTime) {
		if (!responded_to) {
			responded_to = true;
			response_time = (clockTime - arriv_time);
		}
	}
#pragma endregion

#pragma region core functions

	bool isEmpty() { return empty_proc; }

	bool isDone() { return bursts.empty(); }

	void decBurstTimeLeft() {
		if (!bursts.empty()) {
			bursts[0].second -= 1;
		}
	}

	void removeFrontBurst() {
		if (!bursts.empty()) {
			bursts.erase(bursts.begin());
		}
	}

	bool isWaitingIO() {
		if (bursts[0].first == "IO" && bursts[0].second <= 0) {
			bursts.erase(bursts.begin());
			return false;
		}
		else if (bursts[0].first == "IO")
			return true;
		return false;
	}

	bool hasBurstTimeLeft() {
		if (bursts.empty()) {
			return false;
		}
		if (bursts[0].second > 0) {
			return true;
		}
		return false;
	}

	void addQueueLevel() {
		if (queue_level < 6) {
			queue_level++;
		}
	}
#pragma endregion

	

	
};

#endif
