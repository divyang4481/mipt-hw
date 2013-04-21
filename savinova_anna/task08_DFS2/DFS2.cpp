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

void DFSVisit(const int &u, int& time, vector<Stat> &S, vector< vector<int> > &Adm)
{
        S[u].Col() = GREY;
        S[u].D() = time++;
        for (int i = 0; i < Adm.size(); ++i)
        {
                if (Adm[u][i] && S[i].Col() == WHITE)
                {
                        S[i].P() = u;
                        DFSVisit(i, time, S, Adm);
                }
        }
        S[u].Col() = BLACK;
        S[u].F() = time++;
}

void DFS(vector< vector<int> > &Adm)
{
        int time = 0;
        vector<Stat> S(Adm.size());
        for (int i = 1; i < Adm.size(); ++i)
        {
                if (S[i].Col() == WHITE)
                        DFSVisit(i, time, S, Adm);
        }
        for (int i = 1; i < S.size(); ++i)
                cout << i << " Discovered: " << S[i].D() << " Finished: " << S[i].F() << " Parent: " << S[i].P() << endl;
}
int main()
{
        int N = 0, M = 0;
        cin >> N >> M;
        vector< vector<int> > Adm(N + 1);
        for (int i = 1; i <= N; ++i)
                Adm[i].resize(N + 1);
        for (int i = 0; i < M; ++i)
        {
                int x = 0, y = 0;
                cin >> x >> y;
                Adm[x][y] = 1;
        }
        DFS(Adm);
        return 0;
}
