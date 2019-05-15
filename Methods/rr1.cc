#ifndef Graph_H
#define Graph_H
#include "../Graph/Graph.cc"
#endif

#ifndef automata_H
#include "../parseRegEx2/automata.cc"
#define automata_H
#endif

#ifndef random_H
#define random_H
#include "../random/random.cc"
#endif

int RandomWalk(int src, int dst, Graph* g, automata* nodeAutomata, automata* edgeAutomata, Random* rand ) {
    // walk number -> nodes visited in order
	vector < vector < int > > fwd_walk, bwd_walk; 

	// current walk content
	unordered_set < int > fwd_set, bwd_set;

	// node -> nodestate -> edgeState -> penalty
	unordered_map < int, unordered_map < state*, unordered_map < state*, int > > > fwdCntr, bwdCntr;
	
	// ordered vector of current walk
	vector < int > fwd, bwd;

	// node -> nodestate -> edgestate -> walk numbers by which it has been reached
	unordered_map < int, unordered_map < state*, unordered_map < state*, vector < int > > > > walkNumber_F, walkNumber_B; 

	// walk counter
	int walkCounterF = 0, walkCounterB = 0;

	// walklength counter
	int lengthCounterF = 0, lengthCounterB = 0; 

	// Parameter initialization
	int nodeF = src; 
    state* nodeStateF = nodeAutomata->startState;
    state* edgeStateF = edgeAutomata->startState;

	int nodeB = dst; 
    state* nodeStateB = nodeAutomata->finalStates[rand->next() % nodeAutomata->finalStates.size()];
    state* edgeStateB = edgeAutomata->finalStates[rand->next() % edgeAutomata->finalStates.size()];

	Node* prevNode;
	Node* currNode;
    state* prevNodeState;
    state* prevEdgeState;
	vector < int > allEdgeLabels; 
	vector < int > allNodeLabels;
	vector < state* > posEdges;
	int prev;
	int ind; 
	int numChild;
	int edgeLabel;
	int nodeLabel;
	int incr;
	cout<<"Walk Starts"<<endl;
	while((walkCounterF < g->numWalks) && (walkCounterB < g->numWalks)) { 
		cout<<nodeF<<endl;
		cout<<nodeStateF<<endl;
		cout<<edgeStateF<<endl<<endl;

        prevNode = g->nodes[nodeF];
		currNode = g->nodes[nodeF];

		prev = nodeF; 
		prevNodeState = nodeStateF; 
		prevEdgeState = edgeStateF;

		fwd.push_back(nodeF); 
		fwd_set.insert(nodeF);

		allEdgeLabels = edgeStateF->labelTransitions(true);
		allNodeLabels = nodeStateF->labelTransitions(true);

		ind = rand->next() % allEdgeLabels.size();
		edgeLabel = allEdgeLabels[ind];
		incr = 0;
		while (currNode->fwd_labelled_edges.find(edgeLabel) == currNode->fwd_labelled_edges.end()) {
			incr++;
			if (incr == allEdgeLabels.size()) {
				break;
			}
			ind = rand->next() % allEdgeLabels.size();
			edgeLabel = allEdgeLabels[ind];
		}

		if (incr == allEdgeLabels.size()) {
			numChild = 0;
		}
		else numChild = (currNode->fwd_labelled_edges[edgeLabel]).size(); 
		posEdges = prevEdgeState->posTransition(edgeLabel, true);
		edgeStateF = posEdges[rand->next() % posEdges.size()];
		for (incr = 0; incr < numChild; incr++) {
			ind = (rand->next()) % numChild;
			nodeF = prevNode->fwd_labelled_edges[edgeLabel][ind];
			if (fwd_set.find(nodeF) != fwd_set.end() || fwdCntr[nodeF][nodeStateF][edgeStateF] > g->numWalks) continue;
			currNode = g->nodes[nodeF];

			// Check for matching
			// (Since the automata is edge based, for matching nodes, we have to match first and then update the automata state)
			if (walkNumber_B.find(nodeF) != walkNumber_B.end()) {
				if (walkNumber_B[nodeF].find(nodeStateF)!=walkNumber_B[nodeF].end()){
					if (walkNumber_B[nodeF][nodeStateF].find(edgeStateF)!=walkNumber_B[nodeF][nodeStateF].end()){
						vector<int> matches = walkNumber_B[nodeF][nodeStateF][edgeStateF];
						for (int i = 0; i < matches.size();++i) {
							if (matches[i] == walkCounterB) {
								for (int bwd_matches = 0; bwd_matches < bwd.size(); ++bwd_matches) {
									if (fwd_set.find(bwd[bwd_matches]) != fwd_set.end()) {
										break;
									}
									if (bwd[bwd_matches] == nodeF) {
										return 1;
									}
								}
							}
							else {
								for (int bwd_matches = 0; bwd_matches < bwd_walk[matches[i]].size(); ++bwd_matches) {
									if (fwd_set.find(bwd_walk[matches[i]][bwd_matches]) != fwd_set.end()) {
										break;
									}
									if (bwd_walk[matches[i]][bwd_matches] == nodeF) {
										return 1;
									}
								}

							}
						}
					}
				}
			}
			int ind2 = rand->next() % allNodeLabels.size();
			int incr2 = 0;
			nodeLabel = allNodeLabels[ind2];

			//To get the correct node label
			while (currNode->labels.find(nodeLabel) == currNode->labels.end()) {
				incr2++;
				if (incr2 == allNodeLabels.size()) {
					break;
				}
				ind2 = rand->next() % allNodeLabels.size();
				nodeLabel = allNodeLabels[ind2];
			}

			if (incr2 == allNodeLabels.size()) {
				continue;
			}
			else {
				vector<state*> possTrans = prevNodeState->posTransition(nodeLabel, true);
				nodeStateF = possTrans[rand->next()%possTrans.size()];
				walkNumber_F[nodeF][nodeStateF][edgeStateF].push_back(walkCounterF);
				if (++lengthCounterF == g->walkLength) {
					nodeF = -1;
				}
				break;
			}
		}
		if (incr == numChild) {
			fwdCntr[prev][prevNodeState][prevEdgeState] += g->numWalks/4;
			nodeF = -1;
		}
		if (nodeF == -1) {
			nodeF = src;
			lengthCounterF = 0;
			walkCounterF++;
			nodeStateF = nodeAutomata->startState;
			edgeStateF = edgeAutomata->startState;
			fwd_walk.push_back(fwd);
			fwd.clear();
			fwd_set.clear();
		}
		cout<<nodeF<<endl;
		cout<<nodeStateF<<endl;
		cout<<edgeStateF<<endl<<endl;;

		prevNode = g->nodes[nodeB];
		currNode = g->nodes[nodeB];
		prev = nodeB; 
		prevNodeState = nodeStateB; 
		prevEdgeState = edgeStateB;

		bwd.push_back(nodeB); 
		bwd_set.insert(nodeB);

		cout<<nodeB<<endl;
		cout<<edgeStateB<<endl;
		cout<<nodeStateB<<endl<<endl;

		allEdgeLabels = edgeStateB->labelTransitions(false); 
		allNodeLabels = nodeStateB->labelTransitions(false);

		ind = rand->next() % allEdgeLabels.size();
		edgeLabel = allEdgeLabels[ind];
		incr = 0;
		while (currNode->bwd_labelled_edges.find(edgeLabel) == currNode->bwd_labelled_edges.end()) {
			incr++;
			if (incr == allEdgeLabels.size()) {
				break;
			}
			ind = rand->next() % allEdgeLabels.size();
			edgeLabel = allEdgeLabels[ind];
		}
		if (incr == allEdgeLabels.size()) {
			numChild = 0;
		}
		else numChild = (currNode->bwd_labelled_edges[edgeLabel]).size(); 
		posEdges = prevEdgeState->posTransition(edgeLabel, false);
		edgeStateB = posEdges[rand->next() % posEdges.size()];
		for (incr = 0; incr < numChild; incr++) {
			ind = (rand->next()) % numChild;
			nodeB = prevNode->bwd_labelled_edges[edgeLabel][ind];
			if (bwd_set.find(nodeB) != bwd_set.end() || bwdCntr[nodeB][nodeStateB][edgeStateB] > g->numWalks) continue;
			currNode = g->nodes[nodeB];

			// Check for matching
			// (Since the automata is edge based, for matching nodes, we have to match first and then update the automata state)
			if (walkNumber_F.find(nodeB) != walkNumber_F.end()) {
				if (walkNumber_F[nodeB].find(nodeStateB)!=walkNumber_F[nodeB].end()){
					if (walkNumber_F[nodeB][nodeStateB].find(edgeStateB)!=walkNumber_F[nodeB][nodeStateB].end()){
						vector<int> matches = walkNumber_F[nodeB][nodeStateB][edgeStateB];
						for (int i = 0; i < matches.size();++i) {
							if (matches[i] == walkCounterF) {
								for (int fwd_matches = 0; fwd_matches < fwd.size(); ++fwd_matches) {
									if (bwd_set.find(fwd[fwd_matches]) != bwd_set.end()) {
										break;
									}
									if (fwd[fwd_matches] == nodeB) {
										return 1;
									}
								}
							}
							else {
								for (int fwd_matches = 0; fwd_matches < fwd_walk[matches[i]].size(); ++fwd_matches) {
									if (bwd_set.find(fwd_walk[matches[i]][fwd_matches]) != bwd_set.end()) {
										break;
									}
									if (fwd_walk[matches[i]][fwd_matches] == nodeB) {
										return 1;
									}
								}

							}
						}
					}
				}
			}
			int ind2 = rand->next() % allNodeLabels.size();
			int incr2 = 0;
			nodeLabel = allNodeLabels[ind2];

			//To get the correct node label
			while (currNode->labels.find(nodeLabel) == currNode->labels.end()) {
				incr2++;
				if (incr2 == allNodeLabels.size()) {
					break;
				}
				ind2 = rand->next() % allNodeLabels.size();
				nodeLabel = allNodeLabels[ind2];
			}

			if (incr2 == allNodeLabels.size()) {
				continue;
			}
			else {
				vector<state*> possTrans = prevNodeState->posTransition(nodeLabel, false);
				nodeStateB = possTrans[rand->next()%possTrans.size()];
				walkNumber_B[nodeB][nodeStateB][edgeStateB].push_back(walkCounterB);
				if (++lengthCounterB == g->walkLength) {
					nodeB = -1;
				}
				break;
			}
		}
		if (incr == numChild) {
			bwdCntr[prev][prevNodeState][prevEdgeState] += g->numWalks/4;
			nodeB = -1;
		}
		if (nodeB == -1) {
			nodeB = dst;
			lengthCounterB = 0;
			walkCounterB++;
			nodeStateB = nodeAutomata->finalStates[rand->next() % nodeAutomata->finalStates.size()];
			edgeStateB = edgeAutomata->finalStates[rand->next() % edgeAutomata->finalStates.size()];
			bwd_walk.push_back(bwd);
			bwd.clear();
			bwd_set.clear();
		}
		cout<<nodeB<<endl;
		cout<<edgeStateB<<endl;
		cout<<nodeStateB<<endl<<endl;
    }
	return 0;
}