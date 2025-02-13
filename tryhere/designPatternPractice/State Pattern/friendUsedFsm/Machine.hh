#pragma once
#include<iostream>
#include "MachineStates.hh"
#include <stdexcept>

class AbstractState;

class Machine
{
  public:
    Machine(int stockQuantity);
    void sell(int quantity);
    void refill(int refill);
    int getCurrentStock();
    ~Machine();

  private:
    int mStockQuantity;
    AbstractState* mState;
};
