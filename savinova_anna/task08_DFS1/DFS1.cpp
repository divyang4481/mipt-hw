#include <vector>
#include <iostream>
using namespace std;

enum Colour {WHITE, GREY, BLACK};

class Stat
{
        Colour col;
        int p, d, f;
public:
        Stat()
        {
                col = WHITE;
                p = -1;
                d = -1;
                f = -1;
        }
        Colour& Col()
        {
                return col;
        }
        int& P()
        {
                return p;
        }
        int& D()
        {
                return d;
        }
        int& F()
        {
                return f;
        }
};

void DFSVisit(const int &u, int& time, vector<Stat> &S, vector< vector<int> > &Adj)
{
        S[u].Col() = GREY;
        S[u].D() = time++;
        for (int i = 0; i < Adj[u].size(); ++i)
        {
                if (S[Adj[u][i]].Col() == WHITE)
                {
                        S[Adj[u][i]].P() = u;
                        DFSVisit(Adj[u][i], time, S, Adj);
                }
        }
        S[u].Col() = BLACK;
        S[u].F() = time++;
}

void DFS(vector< vector<int> > &Adj, const int &n, const int& m)
{
        int time = 0;
        vector<Stat> S(n);
        for (int i = 1; i < n; ++i)
        {
                if (S[i].Col() == WHITE)
                        DFSVisit(i, time, S, Adj);
        }
        for (int i = 1; i < S.size(); ++i)
                cout << i << " Discovered: " << S[i].D() << " Finished: " << S[i].F() << " Parent: " << S[i].P() << endl;
}
int main()
{
        int N = 0, M = 0;
        cin >> N >> M;
        vector< vector<int> > Adj(N + 1);
        for (int i = 0; i < M; ++i)
        {
                int x = 0, y = 0;
                cin >> x >> y;
                Adj[x].push_back(y);
        }
        DFS(Adj, N + 1, M);
        return 0;
}
