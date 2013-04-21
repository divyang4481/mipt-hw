#include <vector>
#include <list>
#include <iostream>
using namespace std;

enum Colour {WHITE, GRAY, BLACK};

class Stat
{
        Colour col;
        int p, d;
public:
        Stat()
        {
                col = WHITE;
                p = -1;
                d = -1;
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
};

void BFS(vector< vector<int> > &Adj)
{
        vector<Stat> S(Adj.size());
        S[1].Col() = GRAY;
        S[1].D() = 0;
        list<int> Q;
        Q.push_back(1);
        while (!Q.empty())
        {
                int u = Q.front();
                for (int i = 0; i < Adj[u].size(); ++i)
                {
                        if (S[Adj[u][i]].Col() == WHITE)
                        {
                                S[Adj[u][i]].Col() = GRAY;
                                S[Adj[u][i]].D() = S[u].D() + 1;
                                S[Adj[u][i]].P() = u;
                                Q.push_back(Adj[u][i]);
                        }
                }
                Q.pop_front();
                S[u].Col() = BLACK;
        }
        for (int i = 1; i < S.size(); ++i)
                cout << i << " Distance: " << S[i].D() << " Parent: " << S[i].P() << endl;
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
        BFS(Adj);
        return 0;
}
