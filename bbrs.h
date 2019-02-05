#ifndef __BBRS_H
#define __BBRS_H

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
      emcaLoad{0,0,0,0}, remainingUplinks(MAX_NUMBER_OF_UPLINKS) {};
    int allocateBasebandResource(TxDirection);
    void reset();
    int getMaxAllocation();
  
  private:
    int emcaLoad[MAX_NUMBER_OF_EMCAS];
    int remainingUplinks;

};

#endif
