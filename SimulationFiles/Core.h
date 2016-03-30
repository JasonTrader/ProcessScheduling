#ifndef __CORE_H__
#define __CORE_H__
#include "Process.h"

class Core {
private:
	Process m_curr_process;
	bool m_needs_process;
	unsigned int unused_count = 0;
	unsigned int curr_run_time = 0;
	//bool m_process_preempted;
public:
	Core Core() {
		m_curr_process = NULL;
		m_needs_process = true;
		//m_process_preempted = false;
	}

	//runs one clock tick for a process argument should be passed as NULL if replacement is not desired
	Process Update(Process &p) {
		//new process in, used for pre-emption/replacement
		if(p != NULL) {
			curr_run_time = 0;
			m_curr_process = p;
			m_needs_process = false;
			return m_curr_process;
		}
		if(m_curr_process == NULL){
			unused_count++;
			return NULL;
		}
		//decrement burst time
		if( m_curr_process.getBurstTimeLeft() > 0) {
				m_curr_process.decBurstTimeLeft();
				curr_run_time++;
			}
		//remove from core if process finishes cpu burst
		if (m_curr_process.getBurstTimeLeft() == 0) {
			m_curr_process.removeFrontBurst();
			m_needs_process = true;
			Process temp = m_curr_process;
			m_curr_process = NULL;
			return temp;
		}
		return NULL;
	}

	bool needsProcess() {
		return m_needs_process;
	}

	unsigned int getCurrRunTime(){
		return curr_run_time;
	}

	unsigned int getProcBurstTimeLeft(){
		if(!needsProcess){
			return m_curr_process.getBurstTimeLeft();
		}
	}


};
#endif
