#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Node {

public:

	Node(int _NodeId);

	void addEdge(int _destId, bool _direction, int _label);
    void add_label(int l, int sort);
	void sort_labels();
    int nodeId;
    vector < int > labels;

    vector < int > allFwdEdges;
	vector < int > allBwdEdges;
	unordered_map < int, int > numFwdEdges;
	unordered_map < int, int > numBwdEdges;

	unordered_map < int, vector < int > > fwd_labelled_edges;
	unordered_map < int, vector < int > > bwd_labelled_edges;
	
};