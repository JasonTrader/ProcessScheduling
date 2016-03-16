#ifndef __CORE_H__
#define __CORE_H__
#include "Process.h"

class Core {
private:
	Process *m_curr_process;
	bool m_needs_process;
	//bool m_process_preempted;
public:
	Core Core() {
		*m_curr_process = NULL;
		m_needs_process = true;
		//m_process_preempted = false;
	}

	Core ~Core() {
		delete m_curr_process;
	}

	//runs one clock tick for a process argument should be passed as NULL if replacement is not desired
	Process Update(Process &p) {
		//new process in, used for pre-emption/replacement
		if(*p != NULL) {
			m_curr_process = p;
			m_needs_process = false;
			return m_curr_process;
		}
		//decrement burst time
		if(m_curr_process.getBurstTimeLeft() > 0) {
				m_curr_process.decBurstTimeLeft();
			}
		//remove from core if process finishes cpu burst
		if (m_curr_process.getBurstTimeLeft() == 0) {
			m_curr_process.removeFrontBurst();
			m_needs_process = true;
			return m_curr_process;
		}
		return NULL;
	}

/*#pragma region pre-empted functions
	void SetPreemptionStatus(bool b) {
		m_process_preempted = b;
	}

	bool IsProcessPreempted() {
		return m_process_preempted;
	}
#pragma endregion*/
};
#endif
