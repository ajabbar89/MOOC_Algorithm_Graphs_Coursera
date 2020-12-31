#include <iostream>
#include <vector>
#include <limits.h>
#include <unordered_map>
#include <queue>

std::queue<int> q;
std::vector<bool> shortest_nodes;
std::unordered_map<int,std::vector<int>> adj_list;
std::vector<bool> reachable_list; 

typedef long long int long_t;
	
void relax(int u,int v, int w, std::vector<long_t> &dist,std::vector<int> &prev) {
	if((dist[u] != LLONG_MAX) && (dist[v] > (dist[u] + w))) {
			reachable_list[v] = true;
			dist[v] = dist[u] + w;
			prev[v] = u;
		}
}

void bellman_ford(int S,std::vector<std::vector<int>> &E, std::vector<long_t> &dist, std::vector<int> &prev,int n) {
	int u = S;
	dist[u] = 0;
	for(int i = 0; i < (n-1); i++) {
		for(int j = 0; j < E.size(); j++) {
			u = E[j][0];
			int v = E[j][1];
			int w = E[j][2];
			relax(u,v,w,dist,prev);
		}
	}

	//Doing the |V| the iteration to see if negative cycle exists. If negative cycle exists, at least one vertex will have change in its
	//dist. But to get the entire negative cycle we need to do BFS. That is because, based on the values of dist and W at |V| iteration
	//all the nodes in negative cycle may or may not change.
	for(int j = 0; j < E.size(); j++) {
		u = E[j][0];
		int v = E[j][1];
		int w = E[j][2];
		if((dist[u] != LLONG_MAX) && (dist[v] > (dist[u] + w))) {
			reachable_list[v] = true;
			q.push(v);
		}
	}
	std::vector<bool> visit_list;
	for(int i = 0; i <= n; i++){
		visit_list.push_back(false);
		shortest_nodes.push_back(false);
	}
	
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		visit_list[u] = true;
		shortest_nodes[u] = true;
		for(int i = 0; i < adj_list[u].size(); i++) {
			int v = adj_list[u][i];
			if(!visit_list[v]) {
				q.push(v);
				visit_list[v] = true;
				shortest_nodes[v] = true;
			}
		}
	}
	dist[S] = 0;
}

int main() {
	int n,m;
	std::cin>>n>>m;
	std::vector<long_t> dist;
	std::vector<int> prev;
	for(int i = 0; i <= n; i++) {
		dist.push_back(LLONG_MAX);
		prev.push_back(0); //parents of each node on its path to source.
		reachable_list.push_back(false);
	}
	std::vector<std::vector<int>> E;
	for(int i = 0; i < m; i++) {
		int u,v,w;
		std::cin>>u>>v>>w;
		E.push_back({u,v,w});
		adj_list[u].push_back(v);
	}
	int u;
	std::cin>>u;
	reachable_list[u] = true;
	bellman_ford(u,E,dist,prev,n);
	for(int i = 1; i <= n; i++) {
		if(shortest_nodes[i] == true)
			std::cout<<"-"<<std::endl;
		else if(reachable_list[i] == false)
				std::cout<<"*"<<std::endl;
		else
			std::cout<<dist[i]<<std::endl;
	}
	return 0;
}