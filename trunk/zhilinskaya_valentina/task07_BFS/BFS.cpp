#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <limits>

using namespace std;

enum TColor
{
    C_WHITE,
    C_GRAY,
    C_BLACK
};
struct Vertex
{
        int Depth;
        int Parent;
        TColor Color;
        Vertex ()
        {
            Depth=std::numeric_limits<int>::max();
            Parent=-1;
            Color=C_WHITE;
        }
};

typedef vector<Vertex> Vertices;
class TGraph
{
        vector<vector<bool> > _adj;
        int time;
    public :
        TGraph (const vector< vector<bool> >& arr): _adj(arr) {}

       void BFS(int a, Vertices& Vertices) const
       {
            int n=_adj.size();
            Vertices.resize(0);
            Vertices.resize(n);

            deque<int> d;
            d.push_back(a);
            Vertices[a].Color=C_GRAY;
            Vertices[a].Depth=0;
            while(!d.empty())
            {
                int beg = d.front();
                d.pop_front();
                Vertices[beg].Color=C_BLACK;
                for(int i=0; i<n; ++i)
                {
                    if( (Vertices[i].Color==C_WHITE) && (_adj[beg][i]) )
                    {
                        Vertices[i].Color=C_GRAY;
                        Vertices[i].Depth=Vertices[beg].Depth+1;
                        Vertices[i].Parent=beg;

                        d.push_back(i);
                        Vertices[i].Color=C_BLACK;
                    }
                }
            }
        }
};
void test (const vector<vector<bool> >& _adj, int n) {
    TGraph graph(_adj);
    Vertices ver;
    graph.BFS(0, ver);
    cout <<"depth "<<ver[0].Depth<<endl;
    for (int i=1; i<n; ++i) {
        if (ver[i].Depth != numeric_limits<int>::max()) {
            cout<<"#"<<i+1<<"depth "<<ver[i].Depth<<" parent "<<ver[i].Parent+1<<endl;
        } else {
            cout<<"#"<<i+1<<"no way to the vertex\n";
        }
    }
}
int main() {
    int n,k;
    int x,y;
    cin>>n>>k;
    vector< vector<bool> > matrix(n);
    for(int i=0; i<n; ++i) matrix[i].resize(n);
    for(int i=0; i<k; ++i) {
        cin>>x>>y;
        matrix[x-1][y-1]=1;
    }

    test(matrix, n);
	system("PAUSE");
    return(0);
}

