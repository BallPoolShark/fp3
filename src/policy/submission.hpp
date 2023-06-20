#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for random policy, 
 * your policy class should have get_move method
 */
class ABP{
public:
  static Move get_move(State *state, int depth);
};

int getMax(State *state, int depth, int curlv, int beta);
int getMin(State *state, int depth, int curlv, int alpha);