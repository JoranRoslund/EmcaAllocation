#include "bbrs.h"
#include <iostream>

#define DEFAULT_MIN 9999
#define DEFAULT_INDEX 99

#define UL_CAPABLE_COST 1
#define DL_ONLY_COST 1

using namespace std;

int BBRS::allocateBasebandResource(const TxDirection txDirection)
{
  int minLoad = DEFAULT_MIN;
  int allocatedEmca = DEFAULT_INDEX;
  const int cost[2] = {UL_CAPABLE_COST, DL_ONLY_COST};

  if (txDirection == DL_ONLY)
  {
    // Scan over EMCAs
    for (int i=0; i<MAX_NUMBER_OF_EMCAS; ++i)
    {
      // Compare the load of EMCA plus possible penalty.
      //If it is lower than the best alternative found so far, choose this EMCA.
      if (emcaLoadDl[i]< minLoad)
      {
	minLoad = emcaLoadDl[i];
	allocatedEmca = i;
      }
    }
    // Add load to allocated EMCA
    emcaLoadDl[allocatedEmca] += cost[txDirection];
    allocations[allocatedEmca].append("D");
  }
  else
  {
    // Scan over EMCAs
    for (int i=MAX_NUMBER_OF_EMCAS-1; i>=0;--i)
    {
      // Compare the load of EMCA plus possible penalty.
      //If it is lower than the best alternative found so far, choose this EMCA.
      if (emcaLoadUl[i]< minLoad)
      {
	minLoad = emcaLoadUl[i];
	allocatedEmca = i;
      }
    }
    // Add load to allocated EMCA
    emcaLoadUl[allocatedEmca] += cost[txDirection];
    allocations[allocatedEmca].append("U");
  }

  return allocatedEmca;
}

void BBRS::reset()
{
  for (int i=0; i<MAX_NUMBER_OF_EMCAS; ++i)
  {
    emcaLoadUl[i] = 0;
    emcaLoadDl[i] = 0;
    allocations[i] = "";
  }
  remainingUplinks = MAX_NUMBER_OF_UPLINKS;
}

int BBRS::getMaxAllocation()
{
  int maxSoFar = 0;

  for (int i=0; i<MAX_NUMBER_OF_EMCAS; ++i)
  {
    if (emcaLoadUl[i] + emcaLoadDl[i]> maxSoFar)
    {
      maxSoFar = emcaLoadUl[i]+emcaLoadDl[i];
    }
  }

  return maxSoFar;
}

void BBRS::reportStatus()
{
  for (int i=0; i<MAX_NUMBER_OF_EMCAS; ++i)
  {
    cout << i << " " << allocations[i] << endl;
  }
}
