#include <vector>
#include <list>
#include <iostream>
using namespace std;

enum Colour {WHITE, GREY, BLACK};

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

void BFS(vector< vector<int> > &Adm, const int &n, const int &m)
{
        vector<Stat> S(n);
        S[1].Col() = GREY;
        S[1].D() = 0;
        list<int> Q;
        Q.push_back(1);
        while (!Q.empty())
        {
                int u = Q.front();
                for (int i = 0; i < n; ++i)
                {
                        if (Adm[u][i] && S[i].Col() == WHITE)
                        {
                                S[i].Col() = GREY;
                                S[i].D() = S[u].D() + 1;
                                S[i].P() = u;
                                Q.push_back(i);
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
        vector< vector<int> > Adm(N + 1);
        for (int i = 1; i <= N; ++i)
                Adm[i].resize(N + 1);
        for (int i = 0; i < M; ++i)
        {
                int x = 0, y = 0;
                cin >> x >> y;
                Adm[x][y] = 1;
        }
        BFS(Adm, N + 1, M);
        return 0;
}
