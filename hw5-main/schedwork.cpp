

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper (const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, std::vector<unsigned int>& filled_days, unsigned int row, unsigned int col);

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
    // Add your code below
    unsigned int row = 0, col = 0; // can't compare int w unsigned, this helps?
    std::vector<unsigned int> filled_days;
    for(unsigned int i=0; i<avail.size(); i++)
    {
        std::vector<unsigned int> matrix_row;
        sched.push_back(matrix_row);
        for(unsigned int j=0; j<dailyNeed; j++)
        {
            sched[i].push_back(INVALID_ID); // initialize all schedule slots
        }
    }
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, filled_days, row, col);

}


bool scheduleHelper(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched, std::vector<unsigned int>& filled_days, unsigned int row, unsigned int col)
{
    if(row >= sched.size())
    {
        return true; 
    }
    if (col == dailyNeed)
    {
        if (scheduleHelper(avail, dailyNeed, maxShifts, sched, filled_days, row + 1, col))
        {
            return true;
        }
    }
    else
    {
      unsigned int i=0;
      while (i!=avail[row].size())
      {
          filled_days.push_back(0); // initialize filled days vector at 0
          i++;
      }
      for(unsigned int i = 0; i < avail[0].size(); i++)
      {
        sched[row][col] = i;
        unsigned int index = filled_days.at(i); // index is shared within this block, should work?
        index++;
        if(index <= maxShifts && avail[row][i])
        {
          if((col != dailyNeed - 1) && (scheduleHelper(avail, dailyNeed, maxShifts, sched, filled_days, row, col + 1))) //subtract 1 because col starts at 0
          {
            return true;
          }
        }
        index--;
      }
      return false;
    }
}
