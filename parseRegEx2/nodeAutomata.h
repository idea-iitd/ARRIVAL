#include "nodeState.cc"

class automata 
{
    public:
        vector < state* > finalStates;
        state* startState;
        state* finalState;
        bool universal;
        automata(int _label);
        automata();
        void concat(automata* _automaton);
        void closure();
        void plus();
        void unionor(automata* _automaton); 
};
