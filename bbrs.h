#ifndef __BBRS_H
#define __BBRS_H

#include <string>

#define MAX_NUMBER_OF_EMCAS 4
#define MAX_NUMBER_OF_UPLINKS 6

typedef enum TxDirection
{
  UL_CAPABLE = 0,
  DL_ONLY
} TxDirection;


class BBRS
{
  public:
    BBRS() :
      emcaLoadUl{0,0,0,0}, 
      emcaLoadDl{0,0,0,0},
      remainingUplinks(MAX_NUMBER_OF_UPLINKS) {};
    int allocateBasebandResource(TxDirection);
    void reset();
    int getMaxAllocation();
    void reportStatus();
  
  private:
    int emcaLoadUl[MAX_NUMBER_OF_EMCAS];
    int emcaLoadDl[MAX_NUMBER_OF_EMCAS];
    int remainingUplinks;
    std::string allocations[MAX_NUMBER_OF_EMCAS];

};

#endif
