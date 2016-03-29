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

  Process(int PID, unsigned int arriv_time, std::vector<std::pair<string, unsigned int>> bursts){
    tot_burst_time = 0;
    for(int i = 0; i<bursts.size(); i++){
      tot_burst_time += bursts[i].second;
    }
  }

  bool operator<(const Process &other) {//compares on arrival time
    return arriv_time < other.arriv_time;
  }

  unsigned int getArrivalTime() {
    return arriv_time;
  }
  unsigned int getTurnaroundTime(unsigned int clockTime){
    return clockTime - arriv_time;
  }

  unsigned int getTotBurst(){
    return tot_burst_time;
  }

#pragma region core functions
  unsigned int getBurstTimeLeft(){
    if(!bursts.empty()){
      return bursts[0].second;
    }
  }

  void decBurstTimeLeft(){
    if(!bursts.empty()){
      bursts[0].second -= 1;
    }
  }

  void removeFrontBurst(){
    if(!bursts.empty()){
      if(bursts[0].first == "CPU"){
        bursts.erase(bursts.begin());
      }
    }
  }

  bool isDone(){
    return bursts.empty();
  }

  bool isWaitingIO() {
    if (burst[0].first == "IO" && burst[0].second <= 0) {
      bursts.erase(bursts.begin());
      return false;
    }
    else if (bursts[0].first == "IO")
      return true;
    return false;
  }

#pragma endregion


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
