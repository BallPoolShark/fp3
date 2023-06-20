#include <cstdlib>

#include "../state/state.hpp"
#include "./ABP.hpp"

int getMax(State *state, int depth, int curlv, int beta);
int getMin(State *state, int depth, int curlv, int alpha);
/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */


Move ABP::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  auto actions = state->legal_actions;
  int alpha=-500000000;
  Move Maxmove;
  for(auto nm : actions){
        State* nst=state->next_state(nm);
        int nv=0;
        // if(alpha==-500000000) nv=getMin(nst, depth, 1, 500000000);
        // else 
        nv=getMin(nst, depth, 1, alpha);
        if(nv>alpha){
            alpha=nv;
            Maxmove=nm;
        }
    }
  return Maxmove;
}

int getMax(State *state, int depth, int curlv, int beta){
    int maxv=-500000000;
    if(curlv>=depth){
        if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto actions : state->legal_actions){
            State* nst=state->next_state(actions);
            int v=nst->evaluate();
            if(v>beta) return v;
            if(v>maxv){
                maxv=v;
            }
        }
    }else{
        if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto actions : state->legal_actions){
            State* nst=state->next_state(actions);
            int v=0;
            // if(maxv==-500000000) v=getMin(nst, depth, curlv+1, 500000000);
            // else 
            v=getMin(nst, depth, curlv+1, maxv);
            if(v>beta) return v;
            if(v>maxv){
                maxv=v;
            }
        }
    }
    return maxv;
}



int getMin(State *state, int depth, int curlv, int alpha){
    int minv=500000000;
    if(curlv>=depth){
        if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto actions : state->legal_actions){
            State* nst=state->next_state(actions);
            int v=nst->evaluate();
            if(v<alpha) return v;
            if(v<minv){
                minv=v;
            }
        }
    }else{
        if(!state->legal_actions.size())
            state->get_legal_actions();
        for(auto actions : state->legal_actions){
            State* nst=state->next_state(actions);
            int v=0;
            // if(minv==500000000) v=getMin(nst, depth, curlv+1, -500000000);
            // else 
            v=getMin(nst, depth, curlv+1, minv);
            if(v<alpha) return v;
            if(v<minv){
                minv=v;
            }
        }
    }
    return minv;
}