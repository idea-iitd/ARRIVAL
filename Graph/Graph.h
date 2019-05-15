#include "../Node/Node.cc"

class Graph {

public:

	Graph(char *graphfilename, char *featfilename, int dir_control);

	void addEdge(int src, int dst, int label, int dir_control); 
	int diameter(); 
	void initializeRRParams(int diameter); 

	vector<Node*> nodes; 
	int numNodes; 
	int numEdges; 

	int numWalks, numStops, walkLength; 

};

