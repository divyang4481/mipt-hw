#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;
enum clr {WHITE, GRAY, BLACK};	

void DFS_Visit(vector < vector <int> >& graph_matr, vector <clr>& color, vector <int>& d, vector <int>& p, vector <int>& f, int& time, int& u) {
	color[u] = GRAY;
	d[u] = time++;
	for (int i = 0; i < graph_matr.size(); ++i) {
		if ((graph_matr[u][i] == 1) && (color[i] == WHITE)) {
			p[i] = u;
			DFS_Visit(graph_matr, color, d, p, f, time, i);
		}
	}
	color[u] = BLACK;
	f[u] = time++;
}

void DFS_matr(vector < vector <int> >& graph_matr, int s) {

	vector <clr> color(graph_matr.size());	
	vector <int> d, p, f;
	for (int i = 0; i < graph_matr.size(); ++i) {
		d.push_back(-1);
		p.push_back(-1);
		f.push_back(-1);
	}
	int time = 0;

	for (int i = 1; i < graph_matr.size(); ++i) {
		if (color[i] == WHITE)
			DFS_Visit(graph_matr, color, d, p, f, time, i);
	}
	for (int i = 1; i < graph_matr.size(); ++i)
		cout << "number: " << i << "  discovered: " << d[i] << " finished" << f[i] << "  parent: " << p[i] << endl;
}

int main() {

	int a, b, N, M;
	
	cin >> N >> M; // N - вершины, M - ребра

	vector < vector <int> > graph_matr(N + 1);
	for (int i = 1; i < N + 1; ++i)
		graph_matr[i].resize(N + 1);

	for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        graph_matr[a][b] = 1;
        graph_matr[b][a] = 1;
    }

    DFS_matr(graph_matr, 1);

	return 0;

}
 