#include <iostream>
#include <vector>
#include "bbrs.h"
#include <assert.h>
#include <random>
#include <algorithm>
#include <time.h>

#define MAX_NUMBER_OF_SECTORS 6
#define MAX_ALLOC 20
#define MAX_NUMBER_OF_CELLS 16

using namespace std;

void unlock (vector<int> scList, BBRS &bbrs)
{
  // Flag to check if it's the first time we unlock an SC in the sector
  bool firstSc[MAX_NUMBER_OF_SECTORS] = {true, true, true, true, true, true};
  TxDirection txDirection;

  for (vector<int>::iterator it = scList.begin(); it != scList.end(); ++it)
  {
    cout << *it << "(" ;
    if (firstSc[ *it ])
    {
      // Next time won't be first
      firstSc[ *it ] = false;
      // First sector carrier in the sector is UL capable
      txDirection = UL_CAPABLE;
    }
    else
    {
      // Subsequent ones DL only
      txDirection = DL_ONLY;
    }
    int emca = bbrs.allocateBasebandResource(txDirection) ;
    cout << emca << "),";
  }
  cout << endl;
}

int RandomSector () { return (rand()%MAX_NUMBER_OF_SECTORS);}

int main()
{
  srand(time(NULL));
  BBRS bbrs;

  for (int i=0; i < 10000; ++i)
  {
    cout << i <<endl;
    const int numberOfSectors = rand()%MAX_NUMBER_OF_CELLS+1;
    vector<int> sc(numberOfSectors);
    generate(sc.begin(), sc.end(), RandomSector);
    unlock(sc, bbrs);
    assert( bbrs.getMaxAllocation() <= MAX_ALLOC);
    cout << "----------------------------------------------" <<endl;
    bbrs.reset();
  }
}
