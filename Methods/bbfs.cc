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

#include <set>

int bbfs(int src, int dst, Graph* g, int query_type, vector<int> query_labels) {

    timespec start, finish;

	clock_gettime(CLOCK_MONOTONIC, &start);

	if (query_type == 2) {//this will not change since loops can be flattened in this
		set<int> isReached_F;
		set<int> isReached_B;
		sort(query_labels.begin(),query_labels.end());
		isReached_F.insert(src);
		isReached_B.insert(dst);
		vector<int> queue_F;
		queue_F.push_back(src);
		vector<int> queue_B;
		queue_B.push_back(dst);
		while(queue_F.size() > 0 && queue_B.size()>0) {
			int u = queue_F[0];
			queue_F.erase(queue_F.begin());
			vector<int> edges = g->nodes[u]->allFwdEdges;
			for (int i=0;i<edges.size();i++)
			{	
				int e = edges[i];
				int l1,l2;
				l1 = 0;
				l2 = 0;
				while(l1<(g->nodes[e]->labels).size() && l2< query_labels.size() )
				{
					if ((g->nodes[e]->labels)[l1] < query_labels[l2])
						l1++;
					else if ((g->nodes[e]->labels)[l1] > query_labels[l2])
						l2++;
					else
					{
						if (isReached_B.find(e)!=isReached_B.end()) {
							return 1;
						}
						if (isReached_F.find(e)==isReached_F.end()) {
							isReached_F.insert(e);
							queue_F.push_back(e);
						}
						break;
					}
				}
			}

			int v = queue_B[0];
			queue_B.erase(queue_B.begin());
			vector<int> back_edges = g->nodes[v]->allFwdEdges;
			for (int i = 0;i< back_edges.size();i++)
			{
				int e = back_edges[i];
				int l1,l2;
				l1 = 0;
				l2 = 0;
				while(l1<(g->nodes[e]->labels).size() && l2< query_labels.size() )
				{
					if ((g->nodes[e]->labels)[l1] < query_labels[l2])
						l1++;
					else if ((g->nodes[e]->labels)[l1] > query_labels[l2])
						l2++;
					else
					{
						if (isReached_F.find(e)!=isReached_F.end()) {
							return 1;
						}
						if (isReached_B.find(e)==isReached_B.end()) {
							isReached_B.insert(e);
							queue_B.push_back(e);
						}
						break;
					}
				}
			}
		}
	}
	else if (query_type == 3) {

		int depth_F = 0;
		int depth_B = 0;

		unordered_set<int> sofar;

		vector<pair<int,unordered_set<int> > > queue_F;
		vector<pair<int,unordered_set<int> > > queue_B;

		unordered_map<int, unordered_map<int, unordered_map<int, vector<int> > > > fwd;//current node -> label number -> node in path -> ordered vector of path number
		unordered_map<int, unordered_map<int, unordered_map<int, vector<int> > > > bwd;

		unordered_map<int, unordered_map<int,int> > numPaths_F;
		unordered_map<int, unordered_map<int,int> > numPaths_B;

		queue_F.push_back(make_pair(src,sofar));
		queue_B.push_back(make_pair(dst,sofar));

		while(queue_F.size() > 0 && queue_B.size()>0) {
			clock_gettime(CLOCK_MONOTONIC, &finish);
			if ((finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec)/pow(10,9) > 50) return 2;

			int u = queue_F[0].first;
			sofar = queue_F[0].second;
			queue_F.erase(queue_F.begin());
			vector<int> edges = g->nodes[u]->allFwdEdges;
			int l = sofar.size()%query_labels.size();
			sofar.insert(u);

			for (int i=0;i<edges.size();i++) {
				int e = edges[i];
				if (sofar.find(e) != sofar.end()) {//Condition forward path has cycle
					continue;
				}

				vector<int> labels = g->nodes[e]->labels;
				if (binary_search(labels.begin(),labels.end(),query_labels[l])) {

				
					if (bwd.find(e) == bwd.end()) {//No meeting with backward
					
						int nums = numPaths_F[e][l];
						unordered_set<int>::iterator it;
						for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the forward hash for back to find 
							fwd[e][l][*it].push_back(nums);
						}
						numPaths_F[e][l]=nums + 1;
						
						queue_F.push_back(make_pair(e,sofar));
						
					}
					else{//Meeting with backward walk
						if (bwd[e].find(l) != bwd[e].end()) {
							int nums = numPaths_B[e][l];
							unordered_set<int> goners;
							unordered_set<int>::iterator it;
							for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the goner set, in the end take size of goner set to be lt numPaths 
								if (goners.size() == nums) {
									break;
								}
								if (bwd[e][l].find(*it) != bwd[e][l].end()) {
									for (int i = 0; i < bwd[e][l][*it].size();i++) {
										if (goners.size() == nums) {
											break;
										}
										goners.insert(bwd[e][l][*it][i]);
									}
								}
							}
							if (goners.size() < nums) {
								return 1;
							}
						}
						int nums = numPaths_F[e][l];
						unordered_set<int>::iterator it;
						for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the forward hash for back to find 
							fwd[e][l][*it].push_back(nums);
						}
						numPaths_F[e][l]=nums + 1;
						queue_F.push_back(make_pair(e,sofar));
					}
				}
			}
			
			int v = queue_B[0].first;
			sofar = queue_B[0].second;

			queue_B.erase(queue_B.begin());
			edges = g->nodes[v]->allBwdEdges;

			l = query_labels.size() - sofar.size()%query_labels.size() - 1;
			sofar.insert(v);
			for (int i=0;i<edges.size();i++) {
				int e = edges[i];
				if (sofar.find(e) != sofar.end()) {//Condition forward path has cycle
					continue;
				}
				vector<int> labels = g->nodes[e]->labels;
				if (binary_search(labels.begin(),labels.end(),query_labels[l])) {
					if (fwd.find(e) == fwd.end()) {//No meeting with forward
						
						int nums = numPaths_B[e][l];
						unordered_set<int>::iterator it;
						for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the forward hash for back to find 
							bwd[e][l][*it].push_back(nums);
						}
						numPaths_B[e][l]=nums + 1;
						queue_B.push_back(make_pair(e,sofar));
					}
					else{//Meeting with forward walk
						if (fwd[e].find(l) != fwd[e].end()) {// Label should be same
							int nums = numPaths_F[e][l];
							unordered_set<int> goners;
							unordered_set<int>::iterator it;
							for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the goner set, in the end take size of goner set to be lt numPaths 
								if (goners.size() == nums) {
									break;
								}
								if (fwd[e][l].find(*it) != fwd[e][l].end()) {
									for (int i = 0; i < fwd[e][l][*it].size();i++) {
										if (goners.size() == nums) {
											break;
										}
										goners.insert(fwd[e][l][*it][i]);
									}
								}
							}
							if (goners.size() < nums) {
								return 1;
							}
						}
						int nums = numPaths_B[e][l];
						unordered_set<int>::iterator it;
						for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the forward hash for back to find 
							bwd[e][l][*it].push_back(nums);
						}
						numPaths_B[e][l]=nums + 1;
						queue_B.push_back(make_pair(e,sofar));
					}
				}
				
			}
		}
		return 0;
	}
	else{//query type 4
		int depth_F = 0;
		int depth_B = 0;
		unordered_set<int> sofar;

		vector<pair<int,pair<unordered_set<int>,int> > > queue_F;
		vector<pair<int,pair<unordered_set<int>,int> > > queue_B;

		unordered_map<int, unordered_map<int, unordered_map<int, vector<int> > > > fwd;//current node -> label number -> node in path -> ordered vector of path number
		unordered_map<int, unordered_map<int, unordered_map<int, vector<int> > > > bwd;

		unordered_map<int, unordered_map<int,int> > numPaths_F;
		unordered_map<int, unordered_map<int,int> > numPaths_B;

		int l = 0;

		queue_F.push_back(make_pair(src,make_pair(sofar,l)));
		queue_B.push_back(make_pair(dst,make_pair(sofar,query_labels.size()-1)));

		while(queue_F.size() > 0&& queue_B.size()>0) {

			clock_gettime(CLOCK_MONOTONIC, &finish);

			if ((finish.tv_sec - start.tv_sec) + (finish.tv_nsec - start.tv_nsec)/pow(10,9) > 50) return 2;

			int u = queue_F[0].first;
			sofar = queue_F[0].second.first;
			l = queue_F[0].second.second;
			queue_F.erase(queue_F.begin());
			vector<int> edges = g->nodes[u]->allFwdEdges;
			sofar.insert(u);
			for (int i=0;i<edges.size();i++) {
				int e = edges[i];
				if (sofar.find(e) != sofar.end()) {//Condition forward path has cycle
					continue;
				}
				vector<int> labels = g->nodes[e]->labels;
				if (binary_search(labels.begin(),labels.end(),query_labels[l])) {
					if (bwd.find(e) == bwd.end()) {//No meeting with backward
						int nums = numPaths_F[e][l];

						unordered_set<int>::iterator it;
						for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the forward hash for back to find 
							fwd[e][l][*it].push_back(nums);
						}
						numPaths_F[e][l]=nums + 1;
						
						queue_F.push_back(make_pair(e,make_pair(sofar,l)));
						
					}
					else{//Meeting with backward walk
						if (bwd[e].find(l) != bwd[e].end()) {
							int nums = numPaths_B[e][l];
							unordered_set<int> goners;
							unordered_set<int>::iterator it;
							for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the goner set, in the end take size of goner set to be lt numPaths 
								if (goners.size() == nums) {
									break;
								}
								if (bwd[e][l].find(*it) != bwd[e][l].end()) {
									for (int i = 0; i < bwd[e][l][*it].size();i++) {
										if (goners.size() == nums) {
											break;
										}
										goners.insert(bwd[e][l][*it][i]);
									}
								}
							}
							if (goners.size() < nums) {
								return 1;
							}
						}
						int nums = numPaths_F[e][l];
						unordered_set<int>::iterator it;
						for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the forward hash for back to find 
							fwd[e][l][*it].push_back(nums);
						}
						numPaths_F[e][l]=nums + 1;
						queue_F.push_back(make_pair(e,make_pair(sofar,l)));
					}
				}
			}
			l++;
			for (int i=0;i<edges.size();i++) {
				int e = edges[i];
				if (sofar.find(e) != sofar.end()) {//Condition forward path has cycle
					continue;
				}
				vector<int> labels = g->nodes[e]->labels;
				if (binary_search(labels.begin(),labels.end(),query_labels[l])) {
					if (bwd.find(e) == bwd.end()) {//No meeting with backward
						int nums = numPaths_F[e][l];
						unordered_set<int>::iterator it;
						for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the forward hash for back to find 
							fwd[e][l][*it].push_back(nums);
						}
						numPaths_F[e][l]=nums + 1;
						
						queue_F.push_back(make_pair(e,make_pair(sofar,l)));
						
					}
					else{//Meeting with backward walk
						if (bwd[e].find(l) != bwd[e].end()) {
							int nums = numPaths_B[e][l];
							unordered_set<int> goners;
							unordered_set<int>::iterator it;
							for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the goner set, in the end take size of goner set to be lt numPaths 
								if (goners.size() == nums) {
									break;
								}
								if (bwd[e][l].find(*it) != bwd[e][l].end()) {
									for (int i = 0; i < bwd[e][l][*it].size();i++) {
										if (goners.size() == nums) {
											break;
										}
										goners.insert(bwd[e][l][*it][i]);
									}
								}
							}
							if (goners.size() < nums) {
								return 1;
							}
						}
						int nums = numPaths_F[e][l];
						unordered_set<int>::iterator it;
						for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the forward hash for back to find 
							fwd[e][l][*it].push_back(nums);
						}
						numPaths_F[e][l]=nums + 1;
						queue_F.push_back(make_pair(e,make_pair(sofar,l)));
					}
				}
			}
			int v = queue_B[0].first;
			sofar = queue_B[0].second.first;
			l = queue_B[0].second.second;
			if (sofar.size() > depth_B) {
				depth_B = sofar.size();
			}
			queue_B.erase(queue_B.begin());
			edges = g->nodes[v]->allBwdEdges;
			sofar.insert(v);
			for (int i=0;i<edges.size();i++) {
				int e = edges[i];
				if (sofar.find(e) != sofar.end()) {//Condition forward path has cycle
					continue;
				}
				vector<int> labels = g->nodes[e]->labels;
				if (binary_search(labels.begin(),labels.end(),query_labels[l])) {
					if (fwd.find(e) == fwd.end()) {//No meeting with forward
						int nums = numPaths_B[e][l];
						unordered_set<int>::iterator it;
						for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the forward hash for back to find 
							bwd[e][l][*it].push_back(nums);
						}
						numPaths_B[e][l]=nums + 1;
						queue_B.push_back(make_pair(e,make_pair(sofar,l)));
					}
					else{//Meeting with forward walk
						if (fwd[e].find(l) != fwd[e].end()) {// Label should be same
							int nums = numPaths_F[e][l];
							unordered_set<int> goners;
							unordered_set<int>::iterator it;
							for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the goner set, in the end take size of goner set to be lt numPaths 
								if (goners.size() == nums) {
									break;
								}
								if (fwd[e][l].find(*it) != fwd[e][l].end()) {
									for (int i = 0; i < fwd[e][l][*it].size();i++) {
										if (goners.size() == nums) {
											break;
										}
										goners.insert(fwd[e][l][*it][i]);
									}
								}
							}
							if (goners.size() < nums) {
								return 1;
							}
						}
						int nums = numPaths_B[e][l];
						unordered_set<int>::iterator it;
						for (it = sofar.begin(); it!=sofar.end(); ++it) { //insert all in the forward hash for back to find 
							bwd[e][l][*it].push_back(nums);
						}
						numPaths_B[e][l]=nums + 1;
						queue_B.push_back(make_pair(e,make_pair(sofar,l)));
					}
				}
				
			}
			l--;
			for (int i=0;i<edges.size();i++) {
				int e = edges[i];
				if (sofar.find(e) != sofar.end()) {//Condition forward path has cycle
					continue;
				}
				vector<int> labels = g->nodes[e]->labels;
				if (binary_search(labels.begin(),labels.end(),query_labels[l])) {
					if (fwd.find(e) == fwd.end()) {//No meeting with forward
						
						int nums = numPaths_B[e][l];
						unordered_set<int>::iterator it;
						for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the forward hash for back to find 
							bwd[e][l][*it].push_back(nums);
						}
						numPaths_B[e][l]=nums + 1;
						queue_B.push_back(make_pair(e,make_pair(sofar,l)));
					}
					else{//Meeting with forward walk
						if (fwd[e].find(l) != fwd[e].end()) {// Label should be same
							int nums = numPaths_F[e][l];
							unordered_set<int> goners;
							unordered_set<int>::iterator it;
							for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the goner set, in the end take size of goner set to be lt numPaths 
								if (goners.size() == nums) {
									break;
								}
								if (fwd[e][l].find(*it) != fwd[e][l].end()) {
									for (int i = 0; i < fwd[e][l][*it].size();i++) {
										if (goners.size() == nums) {
											break;
										}
										goners.insert(fwd[e][l][*it][i]);
									}
								}
							}
							if (goners.size() < nums) {
								return 1;
							}
						}
						int nums = numPaths_B[e][l];
						unordered_set<int>::iterator it;
						for (it = sofar.begin();it!=sofar.end();++it) { //insert all in the forward hash for back to find 
							bwd[e][l][*it].push_back(nums);
						}
						numPaths_B[e][l]=nums + 1;
						queue_B.push_back(make_pair(e,make_pair(sofar,l)));
					}
				}
				
			}


		}
		return 0;
	}
	return 0;
}