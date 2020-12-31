#include <iostream>
#include <unordered_map>
#include <vector>

int cc_list_val = 0;

void explore(int u, std::unordered_map<int,std::vector<int>> &adj_list, std::vector<bool> &visit_list, std::vector<int> &cc_list) {
	visit_list[u] = true;
	cc_list[u] = cc_list_val;
	for(int i = 0; i < adj_list[u].size(); i++) {
		int node = adj_list[u][i];
		if(visit_list[node] == false) {
			visit_list[node] = true;
			explore(node,adj_list,visit_list,cc_list);
		}
	}
}

void dfs(std::unordered_map<int,std::vector<int>> &adj_list, std::vector<bool> &visit_list, std::vector<int> &cc_list, int n) {
	for(int i = 1; i <= n; i++) {
		if(visit_list[i] == false){
			explore(i,adj_list,visit_list,cc_list);
			cc_list_val += 1;
		}
	}
}

int main() {
	int n,m;
	std::cin>>n>>m;
	std::unordered_map<int,std::vector<int>> adj_list;
	std::vector<bool> visit_list;
	std::vector<int> cc_list;
	for(int i = 0; i <= n; i++) {
		visit_list.push_back(false);
		cc_list.push_back(-1);
	}
	for(int i = 0; i < m; i++) {
		int u,v;
		std::cin>>u>>v;
		adj_list[u].push_back(v);
		adj_list[v].push_back(u);
	}
	dfs(adj_list,visit_list,cc_list,n);
	/*for(int i = 0; i <= n; i++) {
		std::cout<<"visit_list["<<i<<"] = "<<visit_list[i]<<", cc_list["<<i<<"] = "<<cc_list[i]<<std::endl;
	}*/
	std::cout<<cc_list_val;
	return 0;
}