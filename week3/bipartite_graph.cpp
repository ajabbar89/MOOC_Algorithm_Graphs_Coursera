#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

enum class color {none,blue,red};

int is_bipartite = 1;

//The bipartite graph means an edge will always be connecting nodes of 2 different properties.
//Detecting a bipartite graph can be done from BFS by doing color data assignment to each vertex.
//And actively checking if any of the colored vertices which is connected to a vertex has the same color or not.
//If not, its not bipartite.
void bfs(int u,std::unordered_map<int,std::vector<int>> &adj_list, std::vector<int> &dist, std::vector<color> color_list,int n) {
	std::queue<int> q;
	dist[u] = 0;	
	q.push(u);
	color_list[u] = color::blue;
	while(!q.empty()) {
		int node = q.front();
		q.pop();
		for(int j = 0; j < adj_list[node].size(); j++) {
			int v = adj_list[node][j];
			if(color_list[v] == color_list[node]) {
				is_bipartite =0;
				return;
			}
			if(dist[v] == n) {
				dist[v] = dist[node] + 1;
				if(color_list[node] == color::blue)
					color_list[v] = color::red;
				else
					color_list[v] = color::blue;
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
	std::vector<color> color_list;
	for(int i = 0; i <= n; i++) {
		dist.push_back(n); //the highest distance from any one node to another will be < number of nodes.
		color_list.push_back(color::none);
	}
	//A BFS having 'u' as starting node will give us distance of 'v' from 'u' in dist[v]
	for(int i = 0; i < m; i++) {
		int n1,n2;
		std::cin>>n1>>n2;
		adj_list[n1].push_back(n2);
		adj_list[n2].push_back(n1);
	}
	for(int i = 1; i <= n; i++) {
		if(dist[i] == n)
			bfs(i,adj_list,dist,color_list,n);
	}
	std::cout<<is_bipartite;
	return 0;
}