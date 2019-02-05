#include "bbrs.h"
#include <iostream>

#define DEFAULT_MIN 9999
#define DEFAULT_INDEX 99

#define UL_CAPABLE_COST 30
#define DL_ONLY_COST 20
#define PENALTY_COST 15

using namespace std;

int BBRS::allocateBasebandResource(const TxDirection txDirection)
{
  int minLoad = DEFAULT_MIN;
  int allocatedEmca = DEFAULT_INDEX;
  const int cost[2] = {UL_CAPABLE_COST, DL_ONLY_COST};

  // If we are allocating an uplink, reduce number of remaining uplinks
  if (txDirection == UL_CAPABLE)
  {
    --remainingUplinks;
  }

  // Scan over EMCAs
  for (int i=0; i<MAX_NUMBER_OF_EMCAS; ++i)
  {
    int uplinkOpportunities = 0;
    int penalty = 0;
    // Check how many alternatives there are for the uplink on the other EMCAs
    for (int j=0; j<MAX_NUMBER_OF_EMCAS; ++j)
    {
      if ((i != j) && (emcaLoad[j] < UL_CAPABLE_COST))
      {
	++uplinkOpportunities;
      }
    }

    // Add penalty if we are about to starve out uplink resources, i.e. if 
    // the are more remaining uplinks than there are other opportunities.
    if (remainingUplinks > uplinkOpportunities)
    {
      penalty = PENALTY_COST;
    }

    // Compare the load of EMCA plus possible penalty.
    // If it is lower than the best alternative found so far, choose this EMCA.
    if (emcaLoad[i]+penalty < minLoad)
    {
      minLoad = emcaLoad[i]+penalty;
      allocatedEmca = i;
    }
  }
  // Add load to allocated EMCA
  emcaLoad[allocatedEmca] += cost[txDirection];

  if (txDirection == DL_ONLY)
  {
    allocations[allocatedEmca].append("D");
  }
  else
  {
    allocations[allocatedEmca].append("U");
  }

  return allocatedEmca;
}

void BBRS::reset()
{
  for (int i=0; i<MAX_NUMBER_OF_EMCAS; ++i)
  {
    emcaLoad[i] = 0;
    allocations[i] = "";
  }
  remainingUplinks = MAX_NUMBER_OF_UPLINKS;
}

int BBRS::getMaxAllocation()
{
  int maxSoFar = 0;

  for (int i=0; i<MAX_NUMBER_OF_EMCAS; ++i)
  {
    if (emcaLoad[i] > maxSoFar)
    {
      maxSoFar = emcaLoad[i];
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
