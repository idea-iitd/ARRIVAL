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

int RandomWalk(int src, int dst, Graph* g, automata* nodeAutomata, automata* edgeAutomata, Random* rand, int max_pen =2) {

	// walk number -> nodes visited in order
	vector < vector < int > > fwd_walk, bwd_walk; 
	vector < int > temp;

	for (int walknumber = 0; walknumber < g->numWalks; ++walknumber) {
		fwd_walk.push_back(temp);
		bwd_walk.push_back(temp);
	}

	// node -> nodestate -> edgeStete -> penalty
	unordered_map < int, unordered_map < state*, unordered_map < state*, int > > > fwdCntr, bwdCntr;
	
	// node -> nodestate -> edgeState -> walk numbers by which it has been reached
	unordered_map < int, unordered_map < state*, unordered_map < state*,  vector < int > > > > walkNumber_F, walkNumber_B; 
	
	int walkparity = 0;
	for (int walknumber = 0; walknumber < 2*g->numWalks; ++walknumber){

		// current walk content
		unordered_set < int > set;

		// Some helpful variables
		int prev;
		Node* prevNode;
    	state* prevNodeState;
    	state* prevEdgeState;

		if (walkparity == 0) {
			walkparity = 1;
			bool direction = true;

			//parameter initialization
			int node = src;
    		state* nodeState = nodeAutomata->startState;
			state* edgeState = edgeAutomata->startState;
			Node* currNode = g->nodes[node];
		

			for (int lengthCounter = 0; lengthCounter < g->walkLength; ++lengthCounter) {
				walkNumber_F[node][nodeState][edgeState].push_back(walknumber/2);
				fwd_walk[walknumber/2].push_back(node);
				set.insert(node);

				// Saving current state in case we need to fall back on them
				prevNode = currNode;
				prev = node;
				prevNodeState = nodeState;
				prevEdgeState = edgeState;

				// If 0 edges from this node then max penalty to it and if it is source then return unreachable
				int numChild = currNode->allFwdEdges.size();
				if (numChild == 0) {
					if (node == src) return 0;
					fwdCntr[node][nodeState][prevEdgeState]+=max_pen;
					break;
				}
	
				// 	All possible node labels
				vector<int> allNodeLabels = nodeState->labelTransitions(direction);
				if (allNodeLabels.size() == 0) break;

				// All possible edge labels
				vector<int> allEdgeLabels = edgeState->labelTransitions(direction);
				if (allEdgeLabels.size() == 0) break;

				int ind;
				int edgeLabel;
				int incr = -1;
				while (++incr < allEdgeLabels.size()) {

					// Choose an appropriate edge
					ind = rand->next() % allEdgeLabels.size();
					edgeLabel = allEdgeLabels[ind];
					while (currNode->fwd_labelled_edges.find(edgeLabel) == currNode->fwd_labelled_edges.end()) {
						if (++incr == allEdgeLabels.size()) break;
						ind = rand->next() % allEdgeLabels.size();
						edgeLabel = allEdgeLabels[ind];
					}
					
					// If no suitable edge found, break
					if (incr == allEdgeLabels.size()) break;

					// If no nodes then the edgelabel is assumed faulty--This shall never happen but just in case
					numChild = (currNode->fwd_labelled_edges[edgeLabel]).size();
					if (numChild == 0) continue;

					// Get new edgeState
					vector < state* > possTransitions = prevEdgeState->goTransition(edgeLabel, direction);
					ind = rand-> next()%possTransitions.size();
					edgeState = possTransitions[ind];

					// Check for matching with already done backward walks, with new edge and old node states
					if (walkNumber_B.find(node) != walkNumber_B.end()) {
						if (walkNumber_B[node].find(nodeState) != walkNumber_B[node].end()) {
							if (walkNumber_B[node][nodeState].find(edgeState) != walkNumber_B[node][nodeState].end()) {
								vector <int> matches =  walkNumber_B[node][nodeState][edgeState];
								for (int i = 0; i < matches.size(); ++i) {
									for (int bwd_matches = 0; bwd_matches < bwd_walk[matches[i]].size(); ++bwd_matches) {
										if (bwd_walk[matches[i]][bwd_matches] == node) {
											return 1;
										}
										if (set.find(bwd_walk[matches[i]][bwd_matches]) != set.end()) {
											break;
										}
									}
								}
							}
						}
					}

					// Randomly choosing next node, numChild times
					bool flag = false;
					for (int k = 0; k < numChild; ++k) {
						int ind = rand->next() % numChild;
						node = prevNode->fwd_labelled_edges[edgeLabel][ind];
						currNode = g->nodes[node];

						// Simplicity condition
						if (set.find(node) != set.end()) continue;

						// Find if node satisfies any of the possible labels
						for (int labelChecker = 0; labelChecker < allNodeLabels.size(); ++labelChecker) {
							int nodeLabel = allNodeLabels[labelChecker];

							// Get corresponding new state, check for penalties
							vector<state*> possNewStates = prevNodeState->goTransition(nodeLabel, direction);
							ind = rand->next() % possNewStates.size();
							nodeState = possNewStates[ind];

							if (currNode->labels.find(nodeLabel) != currNode->labels.end() && fwdCntr[node][nodeState][edgeState] < max_pen){
								flag = true;
								break;
							}
						}
						if (flag) break;
					}
					if (flag) {
						fwdCntr[prev][prevNodeState][prevEdgeState] = -max_pen;
						break;
					}
				}
				if (incr == allEdgeLabels.size()) {
					if (++fwdCntr[prev][prevNodeState][prevEdgeState] == max_pen && prev == src) return 0;
					break;
				}
			}
			
		}
		else {
			walkparity = 0;
			bool direction = false;

			//parameter initialization
			int node = dst;
    		state* nodeState = nodeAutomata->finalState;
			state* edgeState = edgeAutomata->finalState;
			Node* currNode = g->nodes[node];
		

			for (int lengthCounter = 0; lengthCounter < g->walkLength; ++lengthCounter) {
				walkNumber_B[node][nodeState][edgeState].push_back(walknumber/2);
				bwd_walk[walknumber/2].push_back(node);
				set.insert(node);

				// Saving current state in case we need to fall back on them
				prevNode = currNode;
				prev = node;
				prevNodeState = nodeState;
				prevEdgeState = edgeState;

				// If 0 edges from this node then max penalty to it and if it is source then return unreachable
				int numChild = currNode->allBwdEdges.size();
				if (numChild == 0) {
					if (node == dst) return 0;
					bwdCntr[node][nodeState][prevEdgeState]+=max_pen;
					break;
				}
	
				// 	All possible node labels
				vector<int> allNodeLabels = nodeState->labelTransitions(direction);
				if (allNodeLabels.size() == 0) break;

				// All possible edge labels
				vector<int> allEdgeLabels = edgeState->labelTransitions(direction);
				if (allEdgeLabels.size() == 0) break;

				int ind;
				int edgeLabel;
				int incr = -1;
				while (++incr < allEdgeLabels.size()) {

					// Choose an appropriate edge
					ind = rand->next() % allEdgeLabels.size();
					edgeLabel = allEdgeLabels[ind];
					while (currNode->bwd_labelled_edges.find(edgeLabel) == currNode->bwd_labelled_edges.end()) {
						if (++incr == allEdgeLabels.size()) break;
						ind = rand->next() % allEdgeLabels.size();
						edgeLabel = allEdgeLabels[ind];
					}
					
					// If no suitable edge found, break
					if (incr == allEdgeLabels.size()) break;

					// If no nodes then the edgelabel is assumed faulty--This shall never happen but just in case
					numChild = (currNode->bwd_labelled_edges[edgeLabel]).size();
					if (numChild == 0) continue;

					// Get new edgeState
					vector < state* > possTransitions = prevEdgeState->goTransition(edgeLabel, direction);
					ind = rand-> next()%possTransitions.size();
					edgeState = possTransitions[ind];

					// Check for matching with already done backward walks, with new edge and old node states
					if (walkNumber_F.find(node) != walkNumber_F.end()) {
						if (walkNumber_F[node].find(nodeState) != walkNumber_F[node].end()) {
							if (walkNumber_F[node][nodeState].find(edgeState) != walkNumber_F[node][nodeState].end()) {
								vector <int> matches =  walkNumber_F[node][nodeState][edgeState];
								for (int i = 0; i < matches.size(); ++i) {
									for (int fwd_matches = 0; fwd_matches < fwd_walk[matches[i]].size(); ++fwd_matches) {
										if (fwd_walk[matches[i]][fwd_matches] == node) {
											return 1;
										}
										if (set.find(fwd_walk[matches[i]][fwd_matches]) != set.end()) {
											break;
										}
									}
								}
							}
						}
					}

					// Randomly choosing next node, numChild times
					bool flag = false;
					for (int k = 0; k < numChild; ++k) {
						int ind = rand->next() % numChild;
						node = prevNode->bwd_labelled_edges[edgeLabel][ind];
						currNode = g->nodes[node];

						// Simplicity condition
						if (set.find(node) != set.end()) continue;

						// Find if node satisfies any of the possible labels
						for (int labelChecker = 0; labelChecker < allNodeLabels.size(); ++labelChecker) {
							int nodeLabel = allNodeLabels[labelChecker];

							// Get corresponding new state, check for penalties
							vector<state*> possNewStates = prevNodeState->goTransition(nodeLabel, direction);
							ind = rand->next() % possNewStates.size();
							nodeState = possNewStates[ind];

							if (currNode->labels.find(nodeLabel) != currNode->labels.end() && bwdCntr[node][nodeState][edgeState] < max_pen){
								flag = true;
								break;
							}
						}
						if (flag) break;
					}
					if (flag) {
						bwdCntr[prev][prevNodeState][prevEdgeState] = -max_pen;
						break;
					}
				}
				if (incr == allEdgeLabels.size()) {
					if (++bwdCntr[prev][prevNodeState][prevEdgeState] == max_pen && prev == dst) return 0;
					break;
				}
			}
		}
	} 
	return 0;
}