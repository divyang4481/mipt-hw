#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;


void dfs (int u, vector <bool>& used, vector < vector <int> >& graph_list, vector <int>& ans) {
	used[u] = true;
	for (size_t i = 0; i < graph_list[u].size(); ++i) {
		int to = graph_list[u][i];
		if (!used[to])
			dfs (to, used, graph_list, ans);
	}
	ans.push_back (u);
}
 
void topological_sort(int N, vector <bool>& used, vector < vector <int> >& graph_list, vector <int>& ans) {
	for (int i = 0; i < N; ++i)
		used[i] = false;
	ans.clear();
	for (int i = 0; i < N; ++i)
		if (!used[i])
			dfs (i, used, graph_list, ans);
	reverse (ans.begin(), ans.end());

	for (int i = 0; i < ans.size(); ++i)
		cout << ans[i] + 1 << endl;
}


int main() {

    int a, b, N, M;
        
    cin >> N >> M; 

    vector < vector <int> > graph_list(N + 1);

	for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        graph_list[a - 1].push_back(b - 1);
    }

    vector <bool> used(N + 1);
	vector <int> ans(N + 1);
    
	topological_sort(N, used, graph_list, ans);
	

	return 0;

}