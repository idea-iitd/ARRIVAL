#include "Node.h"

Node::Node(int _NodeId){
	nodeId = _NodeId;
}

void Node::addEdge(int _destId, bool _direction, int _label = 0){
	if ( _direction) {
		fwd_labelled_edges[_label].push_back(_destId);
		numFwdEdges[_label] += 1;
        allFwdEdges.push_back(_destId);
	}
	else {
		bwd_labelled_edges[_label].push_back(_destId);
		numBwdEdges[_label] += 1;
        allBwdEdges.push_back(_destId);
	}
}

void Node::add_label(int l){
	labels.insert(l);
}
