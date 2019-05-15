#include "../parseRegEx2/regexToAutomata.cc"

#ifndef random_H
#define random_H
#include "../random/random.cc"
#endif

#ifndef Graph_H
#define Graph_H
#include "../Graph/Graph.cc"
#endif

#include "../Methods/rr2.cc"


void runQueries(Graph* newG, Random* rand, char* queryFile) {
    string line;
    ifstream myfile3(queryFile); 
	while (getline(myfile3, line)) {

		if (line[0] == '#') continue; 
		char *cstr = &line[0u]; 

		char *t = strtok(cstr, " "); 
		int u = atoi(t); 

		t = strtok(NULL, " "); 
		int v = atoi(t); 

        t = strtok(NULL, " ");
        string nodeA = string(t);
        
        t = strtok(NULL, " ");
        string edgeA = string(t);

        automata* node = conversionNode(nodeA);
        automata* edge = conversionNode(edgeA);

        cout << RandomWalk(u, v, newG, node, edge, rand);
    }
    return;
}

int main(int argc, char *argv[]) {
    char *edgeFile = argv[1];
    char *labelFile = argv[2];
	char *queryFile = argv[3];

    // automata* edge = conversionNode("(1.2.3)+");
    // automata* node = conversionNode("(1U2U3)+");

    Graph* newG = new Graph(edgeFile, labelFile, 1);
    Random* rand = new Random(newG->numEdges, 1);

    runQueries(newG, rand, queryFile);
    return 0;
}