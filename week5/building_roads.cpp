#include <iostream>
#include <math.h>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <iomanip>

typedef struct {
	int i;
	int j;
	double dist;
}edge; //i,j are the respective point indices and dist is distance between them

typedef struct {
	int x;
	int y;
	int parent;
	int rank;
}node;

/**	To build roads connecting points. Seems like Kruskal is better suited to this problem as only points are given.
* 	So, we are not sure about which all points are to be in an undirected connected graph. So, better to first 
*	generate edges, sort them and use Kruskals. Even if we generate edges, we are again unsure which all edges could go from
*	each point as all sorts of possibilities are here. So, instead picking the smallest edge and then applying Kruskal's make sense.
*/

bool Compare(edge e1, edge e2) {
	return e1.dist < e2.dist;
}


int find(int i,std::vector<node> &nodes) {
	if(i != nodes[i].parent) {
		nodes[i].parent = find(nodes[i].parent,nodes);
	}
	return nodes[i].parent;
}

void Union(int u, int v, std::vector<node> &nodes) {
	int u_p = find(u,nodes);
	int v_p = find(v,nodes);
	if(u_p != v_p) {
		if(nodes[u_p].rank > nodes[v_p].rank) {
			nodes[v_p].parent = u_p;
		}
		else {
			nodes[u_p].parent = v_p;
			if(nodes[u_p].rank == nodes[v_p].rank)
				nodes[v_p].rank += 1;
		}
	}
}

double kruskals(std::vector<int> &x, std::vector<int> &y, int n) {
	std::vector<node> nodes;
	std::vector<edge> edges;
	double min_dist = 0.0;
	//creating a vector of edges.
	for(int i = 0; i < n; i++) {
		for(int j = i+1; j < n; j++) {
			edges.push_back({i,j,sqrt((pow((x[i]-x[j]),2) + pow((y[i]-y[j]),2)))});
		}
	}
	for(int i = 0; i < n; i++) {
		nodes.push_back({x[i],y[i],i,0});
	}//This is equivalent to makeset as each node has a unique parent and rank.
	sort(edges.begin(),edges.end(),Compare);
	for(int i = 0; i < edges.size(); i++) {
		int u = edges[i].i; int v = edges[i].j;
		if(find(u,nodes) != find(v,nodes)) {
			Union(u,v,nodes);
			min_dist += edges[i].dist;
		}
	}
	return min_dist;
}

int main() {
	int n;
	std::cin>>n;
	std::vector<int> x;
	std::vector<int> y;
	for(int i = 0; i < n; i++) {
		int _x,_y;
		std::cin>>_x>>_y;
		x.push_back(_x);
		y.push_back(_y);
	}
	double distance = kruskals(x,y,n);
	std::cout<<std::setprecision(10)<<distance;
	return 0;
}