#include "../Node/Node.cc"

class Graph {

public:

	Graph(char *graphfilename, char *featfilename, char* attrfilename, int dir_control);

	void addEdge(int src, int dst, int label, int dir_control);
	void addNode();
	void addLabel(int node, int label);
	void addAttr(int node, string s, int value);

	int diameter(); 
	void updateParams();

	vector<Node*> nodes; 
	int numNodes; 
	int numEdges; 
	int dia;
	int toUpdate;

	int numWalks, numStops, walkLength; 

};

