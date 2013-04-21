#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

/*struct TNode {
    int num;
    char color;
    int distance;
    TNode* parent;
};*/

void BFS_matr(vector < vector <int> >& graph_matr, int s, int N) {
	enum clr {WHITE, GRAY, BLACK};	
	vector <clr> color(N);	
	vector <int> d(N);
	vector <int> parent(N);
	queue <int> q;
	
	for (int i = 0; i < N; ++i) {
		color[i] = WHITE;
		d[i] = -1;
		parent[i] = -1;
	}

	color[s] = GRAY;
	d[s] = 0;
	q.push(s);

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = 0; i < N; ++i) {
			if ((graph_matr[u][i] == 1) && (color[i] == WHITE)) {
				color[i] = GRAY;
				d[i] = d[u] + 1;
				parent[i] = u + 1;
				q.push(i);
			}
		}
		color[u] = BLACK;
	}	

	for (int i = 0; i < N; ++i)
		if ((d[i] == -1) || (parent[i] == -1))
			cout << "number: " << i << "  distance: " << 0 << ' ' << "  no parent" << endl;
		else
			cout << "number: " << i << "  distance: " << d[i] << "  parent: " << parent[i] << endl;

}

int main() {
	//vector <TNode> graph_list;
	int a, b, N, M;
	
	 cin >> N >> M; // N - вершины, M - ребра
	/*for (int i = 0; i < n; ++i) {
		graph_list[i].num = i + 1;
		graph_list[i].color = WHITE;
		graph_list[i].distance = 0;
		graph_list[i].parent = NULL;
	}
	*/
	vector < vector <int> > graph_matr(N);
	for (int i = 0; i < N; ++i)
		graph_matr[i].resize(N);

	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		graph_matr[a - 1][b - 1] = 1;
		graph_matr[b - 1][a - 1] = 1;
	}

	BFS_matr(graph_matr, 0, N);
	
//	cin >> N;
	return 0;

}
 