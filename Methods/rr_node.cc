#ifndef Graph_H
#define Graph_H
#include "../Graph/Graph.cc"
#endif

#ifndef automata_H
#include "../parseRegEx/nodeAutomata.cc"
#define automata_H
#endif

#ifndef random_H
#define random_H
#include "../random/random.cc"
#endif

int RandomWalk(int src, int dst, Graph *g, automata *nodeAutomata, automata *edgeAutomata, Random *rand, int max_pen = 2)
{

	// walk number -> nodes visited in order
	vector<vector<int> > fwd_walk, bwd_walk;
	vector<int> temp;

	for (int walknumber = 0; walknumber < g->numWalks; ++walknumber)
	{
		fwd_walk.push_back(temp);
		bwd_walk.push_back(temp);
	}

	// node -> nodestate -> penalty
	unordered_map<int, unordered_map<state *, int> > fwdCntr, bwdCntr;

	// node -> nodestate -> walk numbers by which it has been reached
	unordered_map<int, unordered_map<state *, vector<int> > > walkNumber_F, walkNumber_B;

	int walkparity = 0;
	for (int walknumber = 0; walknumber < 2 * g->numWalks; ++walknumber)
	{

		// current walk content
		unordered_set<int> set;

		// Some helpful variables
		int prev;
		Node *prevNode;
		state *prevNodeState;

		if (walkparity == 0)
		{
			walkparity = 1;
			bool direction = true;

			//parameter initialization
			int node = src;
			state *nodeState = nodeAutomata->startState;
			Node *currNode = g->nodes[node];

			for (int lengthCounter = 0; lengthCounter < g->walkLength; ++lengthCounter)
			{
				walkNumber_F[node][nodeState].push_back(walknumber / 2);
				fwd_walk[walknumber / 2].push_back(node);
				set.insert(node);

				// If no nodes then fullpenalty on node
				int numChild = (currNode->allFwdEdges).size();
				if (numChild == 0)
				{
					if (node == src)
						return 0;
					fwdCntr[node][nodeState] += max_pen;
					break;
				}

				// Check for matching with already done backward walks
				if (walkNumber_B.find(node) != walkNumber_B.end())
				{
					if (walkNumber_B[node].find(nodeState) != walkNumber_B[node].end())
					{
						vector<int> matches = walkNumber_B[node][nodeState];
						for (int i = 0; i < matches.size(); ++i)
						{
							for (int bwd_matches = 0; bwd_matches < bwd_walk[matches[i]].size(); ++bwd_matches)
							{
								if (bwd_walk[matches[i]][bwd_matches] == node)
								{
									return 1;
								}
								if (set.find(bwd_walk[matches[i]][bwd_matches]) != set.end())
								{
									break;
								}
							}
						}
					}
				}

				// Saving current state in case we need to fall back on them
				prevNode = currNode;
				prev = node;
				prevNodeState = nodeState;

				// Find appropiate node label
				// 		All possible node labels
				vector<int> allNodeLabels = nodeState->labelTransitions(direction);
				if (allNodeLabels.size() == 0)
					break;

				// Randomly choosing next node
				bool flag = false;
				for (int k = 0; k < numChild; ++k)
				{

					int ind = rand->next() % numChild;
					node = prevNode->allFwdEdges[ind];
					currNode = g->nodes[node];

					// Simplicity condition
					if (set.find(node) != set.end())
						continue;

					for (int labelChecker = 0; labelChecker < allNodeLabels.size(); ++labelChecker)
					{

						int nodeLabel = allNodeLabels[labelChecker];

						vector<state *> possNewStates = prevNodeState->goTransition(nodeLabel, direction);
						ind = rand->next() % possNewStates.size();
						nodeState = possNewStates[ind];

						if (binary_search(currNode->labels.begin(),currNode->labels.end(), nodeLabel) && fwdCntr[node][nodeState] < max_pen)
						{
							flag = true;
							break;
						}
					}
					if (flag)
						break;
				}
				if (!flag)
				{
					if (++fwdCntr[prev][prevNodeState] == max_pen && prev == src)
						return 0;
					break;
				}
				else
				{
					fwdCntr[prev][prevNodeState] = -max_pen;
				}
			}
		}
		else
		{
			walkparity = 0;

			bool direction = false;
 
			//Parameter Initialization
			int node = dst;
			state *nodeState = nodeAutomata->finalState;
			Node *currNode = g->nodes[node];

			for (int lengthCounter = 0; lengthCounter < g->walkLength; ++lengthCounter)
			{
				walkNumber_B[node][nodeState].push_back(walknumber / 2);
				bwd_walk[walknumber / 2].push_back(node);
				set.insert(node);

				// If no nodes then fullpenalty on node
				int numChild = (currNode->allBwdEdges).size();
				if (numChild == 0)
				{
					if (node == dst)
						return 0;
					bwdCntr[node][nodeState] += max_pen;
					break;
				}

				// Check for matching with already done backward walks
				if (walkNumber_F.find(node) != walkNumber_F.end())
				{
					if (walkNumber_F[node].find(nodeState) != walkNumber_F[node].end())
					{
						vector<int> matches = walkNumber_F[node][nodeState];
						for (int i = 0; i < matches.size(); ++i)
						{
							for (int fwd_matches = 0; fwd_matches < fwd_walk[matches[i]].size(); ++fwd_matches)
							{
								if (fwd_walk[matches[i]][fwd_matches] == node)
									return 1;
								if (set.find(fwd_walk[matches[i]][fwd_matches]) != set.end())
									break;
							}
						}
					}
				}

				// Saving current state in case we need to fall back on them
				prevNode = currNode;
				prev = node;
				prevNodeState = nodeState;

				// Find appropiate node label
				// 		All possible node labels
				vector<int> allNodeLabels = nodeState->labelTransitions(direction);
				if (allNodeLabels.size() == 0)
					break;

				// Randomly choosing next node
				bool flag = false;
				for (int k = 0; k < numChild; ++k)
				{

					int ind = rand->next() % numChild;
					node = prevNode->allBwdEdges[ind];
					currNode = g->nodes[node];

					// Simplicity condition
					if (set.find(node) != set.end())
						continue;

					for (int labelChecker = 0; labelChecker < allNodeLabels.size(); ++labelChecker)
					{

						int nodeLabel = allNodeLabels[labelChecker];

						vector<state *> possNewStates = prevNodeState->goTransition(nodeLabel, direction);
						ind = rand->next() % possNewStates.size();
						nodeState = possNewStates[ind];

						if (binary_search(currNode->labels.begin(),currNode->labels.end(), nodeLabel) && bwdCntr[node][nodeState] < max_pen)
						{
							flag = true;
							break;
						}
					}
					if (flag)
						break;
				}
				if (!flag)
				{
					if (++bwdCntr[prev][prevNodeState] == max_pen && prev == dst)
						return 0;
					break;
				}
				else
				{
					bwdCntr[prev][prevNodeState] = -max_pen;
				}
			}
		}
	}
	return 0;
}