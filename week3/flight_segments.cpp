#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

void bfs(int u,std::unordered_map<int,std::vector<int>> &adj_list, std::vector<int> &dist, int n) {
	std::queue<int> q;
	dist[u] = 0;	
	q.push(u);
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		for(int j = 0; j < adj_list[node].size(); j++) {
			int v = adj_list[node][j];
			if(dist[v] == n) {
				dist[v] = dist[node] + 1;
				q.push(v);
			}
		}
	}
}

int main() {
	int n,m;
	std::cin>>n>>m;
	std::unordered_map<int,std::vector<int>> adj_list;
	std::vector<int> dist;
	for(int i = 0; i <= n; i++) {
		dist.push_back(n); //the highest distance from any one node to another will be < number of nodes.
	}
	//A BFS having 'u' as starting node will give us distance of 'v' from 'u' in dist[v]
	for(int i = 0; i < m; i++) {
		int n1,n2;
		std::cin>>n1>>n2;
		adj_list[n1].push_back(n2);
		adj_list[n2].push_back(n1);
	}
	int u,v;
	std::cin>>u>>v;
	bfs(u,adj_list,dist,n);
	if(dist[v] == n)
		std::cout<<-1;
	else
		std::cout<<dist[v];
	return 0;
}