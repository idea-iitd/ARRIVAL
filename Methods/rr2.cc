#ifndef Graph_H
#define Graph_H
#include "../Graph/Graph.cc"
#endif

#ifndef automata_H
#include "../parseRegEx2/nodeAutomata.cc"
#define automata_H
#endif

#ifndef random_H
#define random_H
#include "../random/random.cc"
#endif

void step (){
	return;
}

void Walk (int src, int dst, Graph* g, automata* nodeAutomata, automata* edgeAutomata, Random* rand) {
	return;
}

int RandomWalk(int src, int dst, Graph* g, automata* nodeAutomata, automata* edgeAutomata, Random* rand ) {
    // walk number -> nodes visited in order
	vector < vector < int > > fwd_walk, bwd_walk; 

	// current walk content
	unordered_set < int > fwd_set, bwd_set;

	// node -> nodestate -> edgeState -> penalty
	unordered_map < int, unordered_map < int, unordered_map < int, int > > > fwdCntr, bwdCntr;
	
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
    state* nodeStateB = nodeAutomata->finalState;
    state* edgeStateB = edgeAutomata->finalState;

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
	int incr2;
	
	while((walkCounterF < g->numWalks) && (walkCounterB < g->numWalks)) { 
		//cout<<walkCounterF<<","<<walkCounterB<<endl;
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
		bool penaltyflag = false;
		while (true) { // loop till we find both edge and node satisfying

			// Finding edge label that satisfies.
			while (currNode->fwd_labelled_edges.find(edgeLabel) == currNode->fwd_labelled_edges.end()) {
				incr++;
				if (incr == allEdgeLabels.size()) {
					break;
				}
				ind = rand->next() % allEdgeLabels.size();
				edgeLabel = allEdgeLabels[ind];
			}
			
			// If we have checked for the edgelabel n times then break out, and PENALIZE the node on previous labels.
			if (incr == allEdgeLabels.size()) {
				penaltyflag = true;
				break;
			}


			// Find an edge and appropiate node label
			incr2 = 0;
			numChild = (currNode->fwd_labelled_edges[edgeLabel]).size();
			ind = rand->next() % allNodeLabels.size();
			nodeLabel = allNodeLabels[ind];
			// Choosing node label randomly among those available
			while (incr2 < allNodeLabels.size() && numChild != 0) {
				++incr2;
				int incr3 = 0;
				ind = rand->next() % numChild;
				nodeF = currNode->fwd_labelled_edges[edgeLabel][ind];
				// Find which edge satisfies the constraint
				while (g->nodes[nodeF]->labels.find(nodeLabel) == g->nodes[nodeF]->labels.end() && fwdCntr[nodeF][nodeLabel][edgeLabel] < 2) {
					incr3++;
					if (incr3 == numChild) {
						break;
					}
					ind = rand->next() % numChild;
					nodeF = currNode->fwd_labelled_edges[edgeLabel][ind];
				}

				// If such an edge exists, we get our next node (nodeF, and the new states)
				if (g->nodes[nodeF]->labels.find(nodeLabel) != g->nodes[nodeF]->labels.end()) {
					break;
				}

				ind = rand->next() % allNodeLabels.size();
				nodeLabel = allNodeLabels[ind];
			}
			if (incr2 != allNodeLabels.size()&& numChild != 0) {
				break;
			}

			incr++;
			if (incr == allEdgeLabels.size()) {
				break;
			}
			ind = rand->next() % allEdgeLabels.size();
			edgeLabel = allEdgeLabels[ind];
		}

		if (!penaltyflag) {
			lengthCounterF++;

			vector<state*> poss = edgeStateF->goTransition(edgeLabel, true);
			edgeStateF = poss[rand->next()%poss.size()];
			
			if (walkNumber_B.find(prev) != walkNumber_B.end()) {
				if (walkNumber_B[prev].find(nodeStateF) != walkNumber_B[prev].end()) {
					if (walkNumber_B[prev][nodeStateF].find(edgeStateF) != walkNumber_B[prev][nodeStateF].end()) {
						vector <int> matches =  walkNumber_B[prev][nodeStateF][edgeStateF];
						for (int i = 0; i < matches.size(); ++i) {
							if (matches[i] == walkCounterB) {
								
								for (int bwd_matches = 0; bwd_matches < bwd.size(); ++bwd_matches) {
									if (bwd[bwd_matches] == prev) {
										return 1;
									}
									if (fwd_set.find(bwd[bwd_matches]) != fwd_set.end()) {
										break;
									}
								}
							}
							else {
								for (int bwd_matches = 0; bwd_matches < bwd_walk[matches[i]].size(); ++bwd_matches) {
									if (bwd_walk[matches[i]][bwd_matches] == prev) {
										return 1;
									}
									if (fwd_set.find(bwd_walk[matches[i]][bwd_matches]) != fwd_set.end()) {
										break;
									}
								}

							}
						}
					}
				}
			}
			poss = nodeStateF->goTransition(nodeLabel, true);
			nodeStateF = poss[rand->next()%poss.size()];
			walkNumber_F[nodeF][nodeStateF][edgeStateF].push_back(walkCounterF);
		}
		if (penaltyflag || lengthCounterF == g->walkLength) {
			if (penaltyflag) fwdCntr[prev][prevNodeState->label][prevEdgeState->label]+=1;
			if (fwdCntr[src][prevNodeState->label][prevEdgeState->label] >= 2) {
				return 0;
			}
			nodeF = src; 
			nodeStateF = nodeAutomata->startState;
			edgeStateF = edgeAutomata->startState;

			walkCounterF++;
			lengthCounterF = 0;

			fwd_walk.push_back(fwd);
			fwd.clear();
			fwd_set.clear();
		}

        prevNode = g->nodes[nodeB];
		currNode = g->nodes[nodeB];

		prev = nodeB; 
		prevNodeState = nodeStateB; 
		prevEdgeState = edgeStateB;

		bwd.push_back(nodeB); 
		bwd_set.insert(nodeB);


		// cout<<edgeStateB->label<<endl;
		// cout<<nodeStateB->label<<endl;

		allEdgeLabels = edgeStateB->labelTransitions(false);
		allNodeLabels = nodeStateB->labelTransitions(false);

		ind = rand->next() % allEdgeLabels.size();
		edgeLabel = allEdgeLabels[ind];
		incr = 0;
		penaltyflag = false;
		while (true) { // loop till we find both edge and node satisfying
			// Finding edge label that satisfies.
			while (currNode->bwd_labelled_edges.find(edgeLabel) == currNode->bwd_labelled_edges.end()) {
				incr++;
				if (incr == allEdgeLabels.size()) {
					break;
				}
				ind = rand->next() % allEdgeLabels.size();
				edgeLabel = allEdgeLabels[ind];
			}
			// If we have checked for the edgelabel n times then break out, and PENALIZE the node on previous labels.
			if (incr == allEdgeLabels.size()) {
				penaltyflag = true;
				break;
			}

			// Find an edge and appropiate node label
			incr2 = 0;
			// cout<<allNodeLabels.size()<<endl;
			numChild = (currNode->bwd_labelled_edges[edgeLabel]).size();
			ind = rand->next() % allNodeLabels.size();
			nodeLabel = allNodeLabels[ind];
			// Choosing node label randomly among those available
			while (incr2 < allNodeLabels.size() && numChild!=0) {
				++incr2;
				int incr3 = 0;
				ind = rand->next() % numChild;
				nodeB = currNode->bwd_labelled_edges[edgeLabel][ind];
				// Find which edge satisfies the constraint
				while (g->nodes[nodeB]->labels.find(nodeLabel) == g->nodes[nodeB]->labels.end() && bwdCntr[nodeB][nodeLabel][edgeLabel] < 2) {
					incr3++;
					if (incr3 == numChild) {
						break;
					}
					ind = rand->next() % numChild;
					nodeB = currNode->bwd_labelled_edges[edgeLabel][ind];
				}

				// If such an edge exists, we get our next node (nodeF, and the new states)
				if (g->nodes[nodeB]->labels.find(nodeLabel) != g->nodes[nodeB]->labels.end()) {
					break;
				}

				ind = rand->next() % allNodeLabels.size();
				nodeLabel = allNodeLabels[ind];
			}
			if (incr2 != allNodeLabels.size() && numChild != 0) {
				break;
			}
			incr++;
			if (incr == allEdgeLabels.size()) {
				break;
			}
			ind = rand->next() % allEdgeLabels.size();
			edgeLabel = allEdgeLabels[ind];
		}
		if (!penaltyflag) {
			lengthCounterB++;

			vector<state*> poss = edgeStateB->goTransition(edgeLabel, false);
			edgeStateB = poss[rand->next()%poss.size()];
			if (walkNumber_F.find(prev) != walkNumber_F.end()) {
				if (walkNumber_F[prev].find(nodeStateB) != walkNumber_F[prev].end()) {
					if (walkNumber_F[prev][nodeStateB].find(edgeStateB) != walkNumber_F[prev][nodeStateB].end()) {
						vector <int> matches =  walkNumber_F[prev][nodeStateB][edgeStateB];
						for (int i = 0; i < matches.size(); ++i) {
							if (matches[i] == walkCounterF) {
								
								for (int fwd_matches = 0; fwd_matches < fwd.size(); ++fwd_matches) {
									if (fwd[fwd_matches] == prev) {
										return 1;
									}
									if (bwd_set.find(fwd[fwd_matches]) != bwd_set.end()) {
										break;
									}
								}
							}
							else {
								for (int fwd_matches = 0; fwd_matches < fwd_walk[matches[i]].size(); ++fwd_matches) {
									if (fwd_walk[matches[i]][fwd_matches] == prev) {
										return 1;
									}
									if (bwd_set.find(fwd_walk[matches[i]][fwd_matches]) != bwd_set.end()) {
										break;
									}
								}

							}
						}
					}
				}
			}

			//cout<<nodeLabel<<endl;
			poss = nodeStateB->goTransition(nodeLabel, false);
			nodeStateB = poss[rand->next()%poss.size()];
			walkNumber_B[nodeB][nodeStateB][edgeStateB].push_back(walkCounterB);
		}

		if (penaltyflag || lengthCounterB == g->walkLength) {
			if (penaltyflag) bwdCntr[prev][prevNodeState->label][prevEdgeState->label]+=1;
			
			if (bwdCntr[dst][prevNodeState->label][prevEdgeState->label] >= 2) {
				return 0;
			}
			nodeB = dst; 
			nodeStateB = nodeAutomata->finalState;
			edgeStateB = edgeAutomata->finalState;

			walkCounterB++;
			lengthCounterB = 0;

			bwd_walk.push_back(bwd);
			bwd.clear();
			bwd_set.clear();
		}
		

    }

	return 0;
}