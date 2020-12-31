#include <iostream>
#include <unordered_map>
#include <vector>

int cycle_exists = 0;

void explore(int u, int v,std::unordered_map<int,std::vector<int>> &adj_list, std::vector<bool> &visit_list) {
	visit_list[u] = true;
	for(int i = 0; i < adj_list[u].size(); i++) {
		int node = adj_list[u][i];
		if(node == v) {
			cycle_exists = 1;
			return;
		}
		if(visit_list[node] == false) {
			explore(node,v,adj_list,visit_list);
		}
	}
}

int main() {
	int n,m;
	std::cin>>n>>m;
	std::unordered_map<int,std::vector<int>> adj_list;
	std::vector<bool> visit_list;
	for(int i = 0; i <= n; i++)
		visit_list.push_back(false);
	for(int i = 0; i < m; i++) {
		int u,v;
		std::cin>>u>>v;
		adj_list[u].push_back(v);
	}
	for(int i = 1; i <= n; i++) {
		explore(i,i,adj_list,visit_list);
	}
	std::cout<<cycle_exists;
	return 0;
}