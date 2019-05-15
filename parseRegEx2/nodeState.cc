#include "nodeState.h"

state::state(int _label) {
    label = _label;
}

void state::setTransition(state* _next, bool _dir) {
    if (_dir) {
        fwdTransitions.push_back(_next);
    }
    else {
        bwdTransitions.push_back(_next);
    }
}

vector < state* > state::posTransition(int label, bool _dir) {
    vector <state*> out;
    if (_dir) {
        for (int i = 0; i < fwdTransitions.size(); ++i) {
            if (fwdTransitions[i]->label == label) {
                out.push_back(fwdTransitions[i]);
            } 
        }
    }
    else {
        for (int i = 0; i < bwdTransitions.size(); ++i) {
            if (bwdTransitions[i]->label == label) {
                out.push_back(bwdTransitions[i]);
            } 
        }
    }
    return out;
}

vector < int > state::labelTransitions(bool _dir) {
    if (_dir) {
        if (labelTransitionsF.empty()) 
            for (int i = 0; i < fwdTransitions.size(); ++i) {
                labelTransitionsF.push_back(fwdTransitions[i]->label);
                labelToStateF[fwdTransitions[i]->label].push_back(fwdTransitions[i]);
            }
        return labelTransitionsF;
    }
    else {
        if (labelTransitionsB.empty()) 
            for (int i = 0; i < bwdTransitions.size(); ++i) {
                labelTransitionsB.push_back(bwdTransitions[i]->label);
                labelToStateB[bwdTransitions[i]->label].push_back(bwdTransitions[i]);
            }
        return labelTransitionsB;
    }
}

vector < state* > state::goTransition(int label, bool _dir) {
    if (_dir) return labelToStateF[label];
    else return labelToStateB[label];
}