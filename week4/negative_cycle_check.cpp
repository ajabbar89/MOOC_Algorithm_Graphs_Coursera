#include <iostream>
#include <vector>
#include <limits.h>


int dist_change;

void relax(int u,int v, int w, std::vector<int> &dist) {
	if((dist[u] != INT_MAX) && (dist[v] > (dist[u] + w))) {
			dist_change = 1;
			dist[v] = dist[u] + w;
		}
}

int check_negative_cycle(int u,std::vector<std::vector<int>> &E, std::vector<int> &dist, int n) {
	dist[u] = 0;
	for(int i = 0; i < n; i++) {
		dist_change = 0;
		for(int j = 0; j < E.size(); j++) {
			u = E[j][0];
			int v = E[j][1];
			int w = E[j][2];
			relax(u,v,w,dist);
		}
		//std::cout<<"i = "<<i+1<<" dist_change = "<<dist_change<<std::endl;
	}
	return dist_change;
}

int main() {
	int n,m;
	std::cin>>n>>m;
	std::vector<int> dist;
	for(int i = 0; i <= n; i++) {
		dist.push_back(INT_MAX);
	}
	std::vector<std::vector<int>> E;
	for(int i = 0; i < m; i++) {
		int u,v,w;
		std::cin>>u>>v>>w;
		E.push_back({u,v,w});
	}
	int ret = check_negative_cycle(1,E,dist,n);
	if(!ret) {//Accounting for nodes in graph part of disconnected component where negative cycle presence was not checked
		for(int i = 1; i <= n; i++) {
			if(dist[i] == INT_MAX) {
				ret = check_negative_cycle(i,E,dist,n);
				if(ret)
					break;
			}
		}
	}
	std::cout<<ret;
	return 0;
}