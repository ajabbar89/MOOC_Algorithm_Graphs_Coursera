#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <algorithm>

int counter = 1;

std::vector<int> pre_visit;
std::vector<int> post_visit;
	

void explore(int u, std::unordered_map<int,std::vector<int>> &adj_list,std::vector<bool> &visit_list) {
	visit_list[u] = true;
	
	pre_visit[u] = counter;
	counter += 1;
	
	
	for(int i = 0; i < adj_list[u].size(); i++) {
		int node = adj_list[u][i];
		if(visit_list[node] == false) 
			explore(node,adj_list,visit_list);
	}
	post_visit[u] = counter;
	counter += 1;
	
}

void dfs(std::unordered_map<int,std::vector<int>> &adj_list_rev,std::vector<bool> &visit_list_rev, int n) {
	for(int i = 1; i <= n; i++) {
		if(visit_list_rev[i] == false) {
			explore(i,adj_list_rev,visit_list_rev);
		}
	}
}

int main() {
	int n,m;
	std::cin>>n>>m;
	std::unordered_map<int,std::vector<int>> adj_list;
	std::unordered_map<int,std::vector<int>> adj_list_rev;
	std::vector<bool> visit_list;
	std::vector<bool> visit_list_rev;
	for(int i = 0; i <= n; i++) {
		visit_list.push_back(false);
		visit_list_rev.push_back(false);
		pre_visit.push_back(0);
		post_visit.push_back(0);
	}
	for(int i = 0; i < m; i++) {
		int u,v;
		std::cin>>u>>v;
		adj_list[u].push_back(v);
		adj_list_rev[v].push_back(u);
	}
	dfs(adj_list_rev,visit_list_rev,n);
	int num_connected_components = 0;

	std::vector<int> vertices; //Defining a vector of vertices 0, 1, 2...n

	for(int i = 0; i <= n; i++)
		vertices.push_back(i);

	sort(vertices.begin()+1,vertices.end(),[&](int x,int y) { return post_visit[x] > post_visit[y];}); //Arranging the vertices in decreasing order
	//of their post order values using a lambda function. Using begin+1 since the vector of vertices start from 0...n
	
	/*for(int i = 0; i <= n; i++) {
		std::cout<<"post_visit["<<i<<"] = "<<post_visit[i]<<std::endl;
		std::cout<<"vertices["<<i<<"] = "<<vertices[i]<<std::endl;
	}
	*/

	for(int i = 1; i < vertices.size(); i++) {
		if(visit_list[vertices[i]] == false) {
			explore(vertices[i],adj_list,visit_list);
			num_connected_components++;
		}
	}

	std::cout<<num_connected_components;
	return 0;
}