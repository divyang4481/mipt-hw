#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;
typedef vector<vector<int>> Vg;

void dfs (int u, vector <bool>& used, Vg& graph, vector <int>& ans) {
        used[u] = true;
        for (size_t i = 0; i < graph[u].size(); ++i) {
                int to = graph[u][i];
                if (!used[to])
                        dfs (to, used, graph, ans);
        }
        ans.push_back (u);
}

void dfs_T (int u, vector <bool>& used, Vg& graphT, vector <int>& comp) {
        used[u] = true;
        comp.push_back (u);
                for (size_t i = 0; i < graphT[u].size(); ++i) {
					int to = graphT[u][i];
					if (!used[to])
                        dfs_T (to, used, graphT, comp);
        }
        
}

void scc (int N, Vg& graph, Vg& graphT) {
    vector <bool> used(N + 1);
    vector <int> ans(N + 1);
    vector <int> comp(N + 1);
    used.assign (N + 1, false);
    ans.clear();
    comp.clear();
    for (int i = 0; i < N; ++i)
            if (!used[i])
                    dfs (i, used, graph, ans);

    used.assign (N + 1, false);
    int ada = ans.size() - 1;
    for (; ada >= 0; ada--) {
            if (!used[ans[ada]]) {
                    dfs_T(ans[ada], used, graphT, comp);
                    for (int j = 0; j < comp.size(); j++)
                            cout << comp[j] + 1 << ' ';
                    cout << endl;
                    comp.clear();
            }
    }
}


 int main() {

    int a, b, N, M;
        
    cin >> N >> M; 

    Vg graph(N + 1);
    Vg graphT(N + 1);

    for (int i = 0; i < M; ++i) {
        cin >> a >> b;
        graph[a - 1].push_back(b - 1);
        graphT[b - 1].push_back(a - 1);
    }

    scc(N, graph, graphT);

    return 0;

}