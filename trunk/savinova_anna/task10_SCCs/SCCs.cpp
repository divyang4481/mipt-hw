#include <iostream>
#include <list>
#include <vector>
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
        vector<Stat> S(Adj.size());
        int time = 0;
        for (int i = 1; i < Adj.size(); ++i)
        {
                if (S[i].Col() == WHITE)
                        DFSVisit(i, time, S, Adj, L);
        }
}

void DFSVisitAdjT(const int &u, int& time, vector<Stat> &S, vector< vector<int> > &Adj)
{
        S[u].Col() = GRAY;
        S[u].D() = time++;
        for (int i = 0; i < Adj[u].size(); ++i)
        {
                if (S[Adj[u][i]].Col() == WHITE)
                {
                        S[Adj[u][i]].P() = u;
                        DFSVisitAdjT(Adj[u][i], time, S, Adj);
                }
        }
        S[u].Col() = BLACK;
        S[u].F() = time++;
        cout << u << " ";
}

void DFSAdjT(vector< vector<int> > &Adj, list<int> &L)
{               
        vector<Stat> S(Adj.size());
        int time = 0;
        for (list<int>::iterator iter = L.begin(); iter != L.end(); ++iter)
        {
                if (S[*iter].Col() == WHITE)
                {
                        DFSVisitAdjT(*iter, time, S, Adj);
                        cout << endl;
                }
        }
}

void Transpose(vector< vector<int> > &Adj, vector< vector<int> > &AdjT)
{
        for (int i = 1; i < Adj.size(); ++i)
                for (int j = 0; j < Adj[i].size(); ++j)
                        AdjT[Adj[i][j]].push_back(i);
}
void SCCs(vector< vector<int> > &Adj)
{
        list<int> L;
        DFS(Adj, L);
        vector< vector<int> > AdjT(Adj.size());
        Transpose(Adj, AdjT);
        DFSAdjT(AdjT, L);        
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
        SCCs(Adj);
        return 0;
}
