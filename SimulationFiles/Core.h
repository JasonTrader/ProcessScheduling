#ifndef __CORE_H__
#define __CORE_H__
#include "Process.h"

class Core {
private:
	Process m_curr_process;
	bool m_needs_process;
	unsigned int unused_count = 0;
	unsigned int curr_run_time = 0;

public:

	Core() {
		m_curr_process = Process();
		m_needs_process = true;
	}

#pragma region gettors and setters 

	unsigned int getCurrRunTime() { return curr_run_time; }

	unsigned int getProcBurstTimeLeft() {
		if (!needsProcess()) {
			return m_curr_process.getBurstTimeLeft();
		}
	}

	unsigned int getUnusedCount() { return unused_count; }

	Process getProcess() { return m_curr_process; }

#pragma endregion

#pragma region core functions

	//runs one clock tick for a process argument will return empty process if not pre-empted or finished
	Process Update(Process &p) {
		//new process in, used for pre-emption/replacement
		if (!p.isEmpty()) {
			curr_run_time = 0;
			Process temp = m_curr_process;
			m_curr_process = p;
			m_needs_process = false;
			unused_count++;
			return temp;
		}
		if (m_curr_process.isEmpty()) {
			unused_count++;
			return Process();
		}
		//decrement burst time
		if (m_curr_process.getBurstTimeLeft() > 0) {
			m_curr_process.decBurstTimeLeft();
			curr_run_time++;
		}
		//remove from core if process finishes cpu burst
		if (m_curr_process.getBurstTimeLeft() == 0) {
			m_needs_process = true;
			Process temp = m_curr_process;
			m_curr_process = Process();
			return temp;
		}
		return Process();
	}

	bool needsProcess() { return m_needs_process; }

#pragma endregion

};
#endif
