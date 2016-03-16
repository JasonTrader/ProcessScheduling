#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <vector>
#include <utility>


class Process{
private:
  int PID;
  unsigned int arriv_time;
  unsigned int tot_burst_time;
  unsigned int response_time;
  bool responded_to;
  std::vector<std::pair<string, unsigned int>> bursts;

public:
  unsigned int getTurnaroundTime(unsigned int clockTime){
    return clockTime - arriv_time;
  }

  unsigned int getWaitTime(unsigned int clockTime){
    return (clockTime - arriv_time) - tot_burst_time
  }

  unsigned int getResponseTime(){
    return response_time;
  }

  void setResponseTime(unsigned int clockTime){
    if(!responded_to){
      responded_to = true;
      response_time = (clockTime - arriv_time);
    }
  }


};

#endif
