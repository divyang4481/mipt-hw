#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;


void BFS_list(vector < vector <int> >& graph_list, int s, int N) {
        enum clr {WHITE, GRAY, BLACK};  
        vector <clr> color(N + 1);      
        vector <int> d(N + 1);
        vector <int> parent(N + 1);
        queue <int> q;
        
        for (size_t i = 1; i < graph_list.size(); ++i) {
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
                for (size_t i = 0; i < graph_list[u].size(); ++i) {
                        if (color[graph_list[u][i]] == WHITE) {
                                color[graph_list[u][i]] = GRAY;
                                d[graph_list[u][i]] = d[u] + 1;
                                parent[graph_list[u][i]] = u;
                                q.push(graph_list[u][i]);
                        }
                }
                color[u] = BLACK;
        }       

        for (size_t i = 1; i < graph_list.size(); ++i)
                if ((d[i] == -1) || (parent[i] == -1))
                        cout << "number: " << i << "  distance: " << d[i] << ' ' << "  no parent" << endl;
                else
                        cout << "number: " << i << "  distance: " << d[i] << "  parent: " << parent[i] << endl;

}

int main() {

        int a, b, N, M;
        
         cin >> N >> M; 

        vector < vector <int> > graph_list(N + 1);

        for (int i = 0; i < M; ++i) {
                cin >> a >> b;
                graph_list[a].push_back(b);
        }

        BFS_list(graph_list, 1, N);
        

        return 0;

}