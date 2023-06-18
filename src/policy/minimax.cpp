#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"

int getMax(State *state, int depth, int curlv);
int getMin(State *state, int depth, int curlv);
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */


Move MM::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  int maxv=-5000000;
  Move Maxmove;
  for(auto nm : actions){
            State* nst=state->next_state(nm);
            if(getMin(nst, depth, 1)>maxv){
                maxv=getMin(nst, depth, 1);
                Maxmove=nm;
            }
        }
  return Maxmove;
}

int getMax(State *state, int depth, int curlv){
    int maxv=-5000000;
    if(curlv==depth){
        if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto actions : state->legal_actions){
            State* nst=state->next_state(actions);
            int v=nst->evaluate();
            if(v>maxv){
                maxv=v;
            }
        }
    }else{
        if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto actions : state->legal_actions){
            State* nst=state->next_state(actions);
            int v=getMin(nst, depth, curlv+1);
            if(v>maxv){
                maxv=v;
            }
        }
    }
    return maxv;
}



int getMin(State *state, int depth, int curlv){
    int minv=5000000;
    if(curlv==depth){
        if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto actions : state->legal_actions){
            State* nst=state->next_state(actions);
            int v=nst->evaluate();
            if(v<minv){
                minv=v;
            }
        }
    }else{
        if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto actions : state->legal_actions){
            State* nst=state->next_state(actions);
            int v=getMax(nst, depth, curlv+1);
            if(v<minv){
                minv=v;
            }
        }
    }
    return minv;
}