#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>


#ifndef parseFunc_H
#define parseFunc_H
#include "../parseFunctions/parseFunctions.cc"
#endif

using namespace std;

class Node {

public:

	Node(int _NodeId);

	void addEdge(int _destId, bool _direction, int _label);
    void add_label(int l, int sort);
	void sort_labels();
	void add_attr(string s, int i);

    int nodeId;

	unordered_map < string, int > attributes;
    vector < int > labels;

    vector < int > allFwdEdges;
	vector < int > allBwdEdges;
	unordered_map < int, int > numFwdEdges;
	unordered_map < int, int > numBwdEdges;

	unordered_map < int, vector < int > > fwd_labelled_edges;
	unordered_map < int, vector < int > > bwd_labelled_edges;

	
};