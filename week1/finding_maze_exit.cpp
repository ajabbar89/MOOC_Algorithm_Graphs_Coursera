#include <iostream>
#include <vector>
#include <unordered_map>

int reachable_uv = 0;

void explore(int u, int v, std::unordered_map<int,std::vector<int>> &adj_list, std::vector<bool> &visit_list) {
	visit_list[u] = true;
	for(int i = 0; i < adj_list[u].size(); i++) {
		int node = adj_list[u][i];
		if(visit_list[node] == false) {
			visit_list[node] = true;
			if(node == v)
				reachable_uv = 1;
			explore(node,v,adj_list,visit_list);
		}
	}
}


int main() {
	int n,m;
	std::cin>>n>>m;
	std::unordered_map<int,std::vector<int>> adj_list; //Using a hash table to create adjacency list, ie, for each vertex, creating a list of 
	// its neighbors. 
	std::vector<bool> visit_list;
	for(int i = 0; i <= n; i++) {
		visit_list.push_back(false); //O(V)
	}
	for(int i = 0; i < m ; i++) {
		int u,v;
		std::cin>>u>>v;
		adj_list[u].push_back(v); //O(E)
		adj_list[v].push_back(u);
	}
	int start,finish;
	std::cin>>start>>finish;
	explore(start,finish,adj_list,visit_list); //O(deg)
	std::cout<<reachable_uv;
	return 0;
}
