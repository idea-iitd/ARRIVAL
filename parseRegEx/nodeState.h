#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class state
{

public:
    
    vector < state* > fwdTransitions;
    vector < state* > bwdTransitions;

    unordered_map < int, vector < state* > > labelToStateF;
    unordered_map < int, vector < state* > > labelToStateB;
    vector < int > labelTransitionsF;
    vector < int > labelTransitionsB;

    int label;
    
    state(int _label);
    
    void setTransition(state* _next, bool _dir); 
    vector < state* > posTransition(int label, bool _dir);
    vector < int > labelTransitions(bool _dir);
    vector < state* > goTransition(int label, bool _dir);

};
