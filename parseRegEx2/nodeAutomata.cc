#include "nodeAutomata.h"
#include <iostream>
#include <algorithm> 

automata::automata(int _label) {
    startState = new state(-1);
    state* noOutFinal = new state(_label);
    startState->setTransition(noOutFinal, true); 
    finalStates.push_back(noOutFinal);
    universal = false;
}

void automata::closure() {
    vector<state*>::iterator it;
    for (it = startState->fwdTransitions.begin(); it != startState->fwdTransitions.end(); ++it) {
        vector < state* >::iterator it2;
        for (it2 = finalStates.begin(); it2!= finalStates.end(); ++it2) {
            (*it)->setTransition(*it2, false);
            (*it2)->setTransition((*it), true);
        }
    }
    finalStates.push_back(startState);
}

void automata::plus() { 
    vector<state*>::iterator it;
    for (it = startState->fwdTransitions.begin(); it != startState->fwdTransitions.end(); ++it) {
        vector < state* >::iterator it2;
        for (it2 = finalStates.begin(); it2!= finalStates.end(); ++it2) {
            (*it)->setTransition(*it2, false);
            (*it2)->setTransition((*it), true);
        }
    }
}

void automata::unionor(automata* _automaton) {
    vector<state*>::iterator it;
    for (it = _automaton->startState->fwdTransitions.begin(); it != _automaton->startState->fwdTransitions.end(); ++it) {
        startState->setTransition((*it), true);
    }
    for ( int i = 0; i < _automaton->finalStates.size(); ++i ) {
        finalStates.push_back(_automaton->finalStates[i]);
    }
}

void automata::concat(automata* _automaton) {
    vector<state*>::iterator it;
    for (it = _automaton->startState->fwdTransitions.begin(); it != _automaton->startState->fwdTransitions.end(); ++it) {
            vector < state* >::iterator it2;
            for (it2 = finalStates.begin(); it2!= finalStates.end(); ++it2) {
                (*it)->setTransition(*it2, false);
                (*it2)->setTransition((*it), true);
            }
    }
    finalStates = _automaton->finalStates;
}