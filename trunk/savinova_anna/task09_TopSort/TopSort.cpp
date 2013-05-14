#include <list>
#include <vector>
#include <iostream>
using namespace std;

enum Colour {WHITE, GRAY, BLACK};

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

void DFSVisit(const int &u, int& time, vector<Stat> &S, vector< vector<int> > &Adj, list<int> &L)
{
        S[u].Col() = GRAY;
        S[u].D() = time++;
        for (int i = 0; i < Adj[u].size(); ++i)
        {
                if (S[Adj[u][i]].Col() == GRAY)
                {
                        Adj[0].push_back(1);
                        return;
                }
                if (S[Adj[u][i]].Col() == WHITE)
                {
                        S[Adj[u][i]].P() = u;
                        DFSVisit(Adj[u][i], time, S, Adj, L);
                }
        }
        S[u].Col() = BLACK;
        S[u].F() = time++;
        L.push_front(u);
}

void DFS(vector< vector<int> > &Adj, list<int> &L)
{
        int time = 0;
        vector<Stat> S(Adj.size());
        for (int i = 1; i < Adj.size(); ++i)
        {
                if (Adj[0].size() != 0)
                        return;
                if (S[i].Col() == WHITE)
                        DFSVisit(i, time, S, Adj, L);
        }
}
void TopologicalSort(vector< vector<int> > &Adj)
{
        list<int> L;
        DFS(Adj, L);
        if (Adj[0].size() != 0)
                cout << "No solution" << endl;
        else
                for (list<int>::iterator it = L.begin(); it != L.end(); ++it)
                        cout << *it << " ";
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
        TopologicalSort(Adj);
        return 0;
}