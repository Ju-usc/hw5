#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    int mxS = static_cast<int>(maxShifts);
    int arrSize = static_cast<int>(avail[0].size());
    int arrShifts[arrSize];
    for(int i = 0; i < arrSize; ++i) {
        arrShifts[i] = mxS;
    }

    vector<Worker_T> temp;

    for (size_t i = 0 ;  i < avail.size() ; ++i) {
        sched.push_back(temp);
    }
    // cout << "starting " << endl;
    return helper(avail, dailyNeed, maxShifts, sched, 0, 0, arrShifts);
   
    // Add your code below
}


// if it reaches the day after the max day, we assume we have scheduled all days 
// iterate through all workers,
// if current worker is valid to be added, 
// add it to the schedule and decrease 1 in the arrShifts data.
// if the vector is fulled, we add day.
// backtrack if it's not valid, at the end of the loop
// if we pop back the worker from schedule, 
// after we pop, check if the day is empty, update the day--
// then we recurse it again.
// 










bool helper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, int lastWorker,
    size_t day, int arrShifts[]){

    if(day == avail.size()){
        return true;
    }
    if(lastWorker == (int)avail[0].size()){
        return false;
    }

    for(Worker_T id = 0; id < avail[0].size(); ++id){
        
        // cout << "dealing with day: " << day << " id: " << id << endl;
        // int d = 0;
        // for(auto s : sched)
        // {
        //     cout << "Day " << d << ": ";
        //     for(auto nurse : s)
        //     {
        //         cout << nurse << " ";
        //     }
        //     cout << endl;
        //     d++;
        // }
        // cout << endl;
        
        if(isValid(avail, arrShifts, day, id, sched)){
            sched[day].push_back(id); //add worker's id to the schedule
            arrShifts[id]--; //update the maxshift array

            // cout << "Valid: " << "day: " << day << " id: " << id <<endl;
            // cout << "adding day: " << day << " id: " << id <<endl;

            

            if(sched[day].size() == dailyNeed){
                day++; //update the day if the vector is filled.
            }

            if(helper(avail, dailyNeed, maxShifts, sched, id, day, arrShifts)){
                return true;
            }
            // if(lastWorker >= (int)avail[0].size()){
            //     day--;
            //     cout << "day is updated to " << day << endl;
            // }
            // cout << "backtracked " << endl;
            // cout << "removing day: " << day << " id: " << id <<endl;
            if(sched[day].empty()){
                day--;
            }
            arrShifts[sched[day].back()]++;
            sched[day].pop_back();
        }
    }
    // cout << "removing day: " << day << " lastworker: " << lastWorker <<endl;
    // if(sched[day].empty()){
    //     day--;
    // }
    // arrShifts[sched[day].back()]++;
    // sched[day].pop_back();
    return false;

}

bool isValid(const AvailabilityMatrix& avail,
    int arrShifts[],
    size_t day, 
    Worker_T workerid,DailySchedule& sched){


    if(find(sched[day].begin(), sched[day].end(), workerid) != sched[day].end()){
       return false;
    }


    // cout << "arrShifts: ";
    // for(size_t i=0; i < avail[0].size(); ++i){
    //     cout << arrShifts[i] << " ";
    // }
    // cout << endl;

    // int d = 0;
    // for(auto s : avail)
    // {
    //     cout << "Day " << d << ": ";
    //     for(auto nurse : s)
    //     {
    //         cout <<" id: " <<nurse << " ";
    //     }
    //     cout << endl;
    //     d++;
    // }

    // cout << endl;
    if(avail[day][workerid] == 0){
        // cout << "day: " << day <<  " id: " << workerid << " worker is invalid" <<endl;
        return false;
    }

    if(arrShifts[workerid] <= 0){
        return false;
    }
    


    return true;
}

