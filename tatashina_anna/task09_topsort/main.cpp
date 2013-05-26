#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;
enum clr {WHITE, GRAY, BLACK};  

void DFS_Visit(vector < vector <size_t> >& graph_list, vector <clr>& color, size_t& u, vector <int>& ans) {
        color[u] = GRAY;
        for (size_t i = 0; i < graph_list[u].size(); ++i) {
                if (color[graph_list[u][i]] == GRAY) {
					cout << "I have a cycke, I won't do topsort";
					exit(0);
				}
				if (color[graph_list[u][i]] == WHITE) 
                        DFS_Visit(graph_list, color, graph_list[u][i], ans);
        }
        ans.push_back (u);
		color[u] = BLACK;
}

void TopSort(vector < vector <size_t> >& graph_list, int s, vector <int>& ans) {
		ans.clear();
        vector <clr> color(graph_list.size());  

        for (size_t i = 1; i < graph_list.size(); ++i) {
                if (color[i] == WHITE)
                        DFS_Visit(graph_list, color, i, ans);
        }
        reverse (ans.begin(), ans.end());

        for (int i = 0; i < ans.size(); ++i)
                cout << ans[i] << endl;
}

int main() {

        int a, b, N, M;
        
        cin >> N >> M; // N - aa?oeiu, M - ?aa?a

        vector < vector <size_t> > graph_list(N + 1);
        vector <int> ans(N + 1);
        for (int i = 0; i < M; ++i) {
				cin >> a >> b;
                graph_list[a].push_back(b);
	    }

		TopSort(graph_list, 1, ans);

		return 0;

}