#include "Graph.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

Graph::Graph(char *graphfilename, char *featfilename, int dir_control) {

	string line; 
	double elapsed;
	struct timespec start, finish;

	clock_gettime( CLOCK_MONOTONIC, &start); 

    numNodes = 0; 

    // Read and add labels and nodes from featfile
	ifstream myfile3(featfilename); 
	while (getline(myfile3, line)) {

		if (line[0] == '#') continue; 
		char *cstr = &line[0u]; 

		char *t = strtok(cstr, " "); 
		int u = atoi(t); 

        for (int j = numNodes; j <= u; j ++ ) {
            nodes.push_back(new Node(j)); 
			numNodes ++ ; 
        }

		t = strtok(NULL, " "); 
		int l = atoi(t); 

		nodes[u]->add_label(l); 
	}
	myfile3.close(); 
	
	// Add edges between Nodes, directed or undirected controlled 
	ifstream myfile2(graphfilename); 
	while (getline(myfile2, line)) {

		if (line[0] == '#') continue; 
		char *cstr = &line[0u]; 

		char *t = strtok(cstr, " "); 
		int u = atoi(t);

		for (int j = numNodes; j <= u; j++) {
            nodes.push_back(new Node(j));
			numNodes++;
        }

		t = strtok(NULL, " ");
		int v = atoi(t);

		for (int j = numNodes; j <= v; j++) {
            nodes.push_back(new Node(j));
			numNodes++;
        }

		int l; 
		t = strtok(NULL, " "); 
		if (t == NULL) {
			l = 1; 
		}
		else 
			l = atoi(t); 

		addEdge(u, v, l, dir_control); 
	}
	myfile2.close();

	// Estimate diameter of graph by sampling 10 random nodes
	int dia = diameter();
	for (int i = 0; i < 9; i ++ ) {
		int d = diameter(); 
		if (d > dia) dia = d; 
	}
	// Use diameter to initialize the parameters
	initializeRRParams(dia); 

	clock_gettime(CLOCK_MONOTONIC, &finish); 
	cout << "Initialization Time: " << (finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec)/pow(10, 9) << endl; 

}

// Adding edges constrained on whether directional edge or not
void Graph::addEdge(int src, int dst, int l, int dir_control = 1) {

	nodes[src]->addEdge(dst, true, l); 
	nodes[dst]->addEdge(src, false, l);
	 
	if (dir_control == 0) {
		nodes[src]->addEdge(dst, false, l); 
		nodes[dst]->addEdge(src, true, l); 
	}
	numEdges ++ ; 
}

void Graph::initializeRRParams(int diameter) {
	numStops = (float)(floor(pow((numNodes), 2.0/3) * pow(log(numNodes), 1.0/3))); 
	walkLength = diameter;
	numWalks = (float)numStops / (2 * walkLength); 

	if (numWalks == 0) numWalks = 1;

}

// Simple bfs to estimate the depth
int Graph::diameter() {
	vector<int> color;
	vector<int> queue;
	color.reserve(numNodes);
	for (int i = 0; i < numNodes; i++) color.push_back(0);
	int src = rand()%numNodes;
	int dia = 1;
	int u = src;
	
	color[src] = 1;
	while (u >= 0){
		Node *n = nodes[u];
        vector<int> fwdedges = n -> allFwdEdges;
		
		for (int i = 0; i < fwdedges.size(); i++) {
			int v = fwdedges[i];
			if (color[v] >= 1) continue;
			color[v] = color[u] + 1;
			queue.push_back(v);
		}
		if (queue.size() == 0) break;
		u = queue[0];
		queue.erase(queue.begin());
	}
	for (int i = 0; i < numNodes; i++)
		if (dia < (color[i]))
			dia = color[i];
	return dia;
}


