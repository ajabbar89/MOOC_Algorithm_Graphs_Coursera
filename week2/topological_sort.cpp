#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>

//int clock = 0;
std::list<int> linear_order;

int explore(int u, std::unordered_map<int,std::vector<int>> &adj_list, std::vector<bool> &visit_list, std::vector<int> &pre_visit, std::vector<int> &post_visit) {
	visit_list[u] = true;
	/*
	clock +=1 ;
	pre_visit[u] = clock;
	*/
	//The idea is, if the vertex does not have an outgoing edge, then it must be removed from graph and pushed to the front of the linear 
	//order list. This basically means, we need to ensure that in adjacency list, this vertex is removed as the neighbor of any vertex
	//and it must be removed as one of the vertices(key) itself.
	if(adj_list.find(u) == adj_list.end()) {
		linear_order.push_front(u);
		return -1;
	}

	for(int i = 0; i < adj_list[u].size(); i++) {
		int node = adj_list[u][i];
		if(node == -1) 
			continue;
		if(visit_list[node] == false) {
			int ret = explore(node,adj_list,visit_list,pre_visit,post_visit);
			if(ret == -1)
				adj_list[u][i] = -1; //Equivalent of removing the vertex from the graph. Here, basically making the earlier value corresponding to the vertex -1
		}
	}

	adj_list.erase(u);
	linear_order.push_front(u);
	return -1;
	/*
	clock += 1;
	post_visit[u] = clock;
	*/
}

void dfs(std::unordered_map<int,std::vector<int>> &adj_list, std::vector<bool> &visit_list, std::vector<int> &pre_visit, std::vector<int> &post_visit, int n) {
	for(int i = 1; i <= n; i++) {
		if(visit_list[i] == false){
			explore(i,adj_list,visit_list,pre_visit,post_visit);
		}
	}
}

int main() {
	int n,m;
	std::cin>>n>>m;
	std::unordered_map<int,std::vector<int>> adj_list;
	std::vector<bool> visit_list;
	std::vector<int> pre_visit;
	std::vector<int> post_visit;
	for(int i = 0; i <= n; i++) {
		visit_list.push_back(false);
		pre_visit.push_back(0);
		post_visit.push_back(0);
	}
	for(int i = 0; i < m; i++) {
		int u,v;
		std::cin>>u>>v;
		adj_list[u].push_back(v);
	}
	dfs(adj_list,visit_list,pre_visit,post_visit,n);
	for(auto it = linear_order.begin(); it != linear_order.end(); ++it)
		std::cout<<*it<<" ";
	return 0;
}