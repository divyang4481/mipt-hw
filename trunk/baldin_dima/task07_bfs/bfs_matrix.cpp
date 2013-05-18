#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>
using namespace std;
enum clr {WHITE, GRAY,BLACK};

void read_graph(vector< vector <int> > &graph,
	vector < clr > &colour,
	vector < int > &parent,
	vector < int > &length)
{
	
	size_t n,m;
	scanf("%u %u", &n, &m);
	graph.resize(n);
	for (vector< vector <int> >::iterator it = graph.begin(); it < graph.end(); ++it)
		(*it).resize(n,0);
	colour.resize(n, WHITE);
	parent.resize(n,-1);
	length.resize(n,-1);
	size_t a,b;
	for ( size_t i = 0; i < m; ++i)
	{
		scanf("%u %u", &a, &b);
		graph[a-1][b-1] = 1;
	}
	
}
void bfs(vector< vector <int> > &graph,
	vector < clr > &colour,
	vector < int > &parent,
	vector < int > &length)
{
	colour[0] = GRAY;
	queue< int > q;
	int cur = 0;
	q.push(cur);
	for (;q.size()!=0;)
	{
		cur = q.front();
		q.pop();
		for (size_t i = 0; i < graph[cur].size(); ++i)
		{
			if ((colour[i] == WHITE) && (graph[cur][i] == 1))
			{
				parent[i] = cur;
				length[i] = length[cur] + 1;
				colour[i] = GRAY;
				q.push(i);
			}
		}
		colour[cur] = BLACK;
	}

}
void print_vector(vector< vector <int> > &graph,
	vector < int > &parent,
	vector < int > &length)
{
	
	for (size_t i = 0; i < parent.size(); ++i)
	{
		printf("vertex %u parent %d length %d\n", i + 1, parent[i] + 1, (parent[i] == -1) ? length[i]: length[i] + 1);
	}
	
}
int main()
{
	vector < vector<int> > graph;
	vector < clr > colour;
	vector < int > parent;
	vector < int > length;
	read_graph(graph, colour, parent, length);
	bfs(graph, colour, parent, length);
	print_vector(graph, parent, length);
	return 0;
}