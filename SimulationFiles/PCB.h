#ifndef __PCB_H__
#define __PCB_H__

#include <queue>
#include <vector>
#include "Core.h"

class PCB {
private:
	unsigned int m_completed_processes = 0;
	unsigned int m_num_context_switch = 0;
	enum schedule_type { FCFS, RR, SPN, SRT, HRRN, Feedback};

public:
};

#endif
