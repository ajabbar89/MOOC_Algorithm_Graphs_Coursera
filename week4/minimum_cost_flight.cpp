#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits.h>
#include <utility> //for std::pair STL for making pairs between dist of vertex and vertex index. This is needed in priority_queue to
				   //keep track of the vertex index with minimum distance.

typedef long long int long_t;

typedef struct {
	int v;
	long_t w;
}vertex_weight;

typedef std::pair<long_t,int> ipair; //This is to have both vertex index and its distance tracked in priority queue.

void dijkstra(int u,std::unordered_map<int,std::vector<vertex_weight>> &adj_list, std::vector<long_t> &dist,int n) {
	
	std::priority_queue<ipair,std::vector<ipair>,std::greater<ipair>> pq; //std::greater ensures we have a min heap.
	dist[u] = 0;
	pq.push(std::make_pair(dist[u],u)); //The pair made here is pair of vertex and its dist value, in this case <dist[u],u>

	while(!pq.empty()) {
		u = pq.top().second; //Extracting the vertex with min dist value
		pq.pop();
		for(int i = 0; i < adj_list[u].size(); i++) {
			vertex_weight v_w = adj_list[u][i];
			int v = v_w.v;
			long_t w = v_w.w;
			if(dist[v] > (dist[u] + w)) {
				dist[v] = dist[u] + w;
				pq.push(std::make_pair(dist[v],v));
			}
		}
	}
}

int main() {
	int n,m;
	std::cin>>n>>m;
	std::vector<long_t> dist;
	std::unordered_map<int,std::vector<vertex_weight>> adj_list; //The vector of structs here will have the destination vertex from the vertex 
	//which is the key and the weight along the outgoing edge from the key.
	for(int i = 0; i <= n; i++) {
		dist.push_back(LLONG_MAX);
	}
	for(int i = 0; i < m; i++) {
		int u,v;
		long_t w;
		std::cin>>u>>v>>w;
		vertex_weight v_w;
		v_w.v = v;
		v_w.w = w;
		adj_list[u].push_back(v_w);
	}
	int u,v;
	std::cin>>u>>v;
	dijkstra(u,adj_list,dist,n);
	if(dist[v] == LLONG_MAX)
		std::cout<<-1;
	else
		std::cout<<dist[v];
	return 0;
}