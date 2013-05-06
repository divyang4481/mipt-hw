#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <limits>
#include <fstream>


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
        int DiscoverTime;
        int FinishTime;
        Vertex ()
        {
            Depth = std::numeric_limits<int>::max();
            Parent = -1;
            Color = C_WHITE;
            DiscoverTime = -1;
            FinishTime = -1;
        }
};

typedef vector<Vertex> TVertices;
class TGraph
{
        vector<vector<bool> > _adj;
        int time;

        void DFSVisit(int a, TVertices& vertices, list<int>& list)
        {
            for (int i = 0; i < _adj.size(); ++i)
            {
                if (_adj[a][i] && (vertices[i].Color == C_WHITE))
                {
                    vertices[i].Color = C_GRAY;
                    vertices[i].DiscoverTime = ++time;
                    vertices[i].Parent = a;
                    DFSVisit(i, vertices, list);
                    vertices[i].FinishTime = ++time;
                    list.push_front(i+1);
                    vertices[i].Color = C_BLACK;
                }
            }
        }

    public :
        TGraph (const vector< vector<bool> >& arr): _adj(arr) {}
        void DFS (TVertices& vertices, list<int>& list)
        {
            vertices.resize(0);
            vertices.resize( _adj.size() );
            time = 0;
            for (int i=0; i<_adj.size(); ++i)
            {
                if (vertices[i].Color == C_WHITE)
                {
                    vertices[i].Color = C_GRAY;
                    vertices[i].DiscoverTime = ++time;
                    DFSVisit(i, vertices, list);
                    vertices[i].FinishTime = ++time;
                    list.push_front(i+1);
                    vertices[i].Color = C_BLACK;
                }
            }
        }
		TGraph Transp() const  
		{
			TGraph tmp(*this);
			for (int i = 0; i < _adj.size(); ++i) 
				for (int j = i + 1; j < _adj.size(); ++j) 
				{
					tmp._adj[i][j] = tmp._adj[j][i];
					tmp._adj[j][i] = _adj[i][j];
				}
			return tmp;
		}
		void SCC (vector< list<int> > &res) 
		{
			res.resize(0);
			list<int> tmp, lst;
			TVertices Vertices;
			DFS(Vertices, lst);
			TGraph g = Transp();
			Vertices.resize(0);
			Vertices.resize(_adj.size());
			time = 0;
			for (list<int>::iterator i = lst.begin(); i!=lst.end(); ++i) 
			{
				tmp.clear();
				if (Vertices[*i-1].Color == C_WHITE) 
				{
					Vertices[*i-1].Color = C_GRAY;
					Vertices[*i-1].DiscoverTime = ++time;
					g.DFSVisit(*i-1, Vertices, tmp);
					Vertices[*i-1].FinishTime = ++time;
					tmp.push_front(*i);
					Vertices[*i-1].Color = C_BLACK;
					res.push_back(tmp);
				}
        }
    }


};
void TopologicalSort (const vector< vector<bool> >& AdjMatrix, int n) 
{
    TGraph g(AdjMatrix);
    TVertices ts;
    list<int> sched;
    g.DFS(ts, sched);
    cout<<endl<<"TopSort: \n"<<endl;
    for (list<int>::iterator i = sched.begin(); i!=sched.end(); ++i) cout<<*i<<endl;
}
void SCC_test (const vector< vector<bool> >& AdjMatrix, int n) 
{
    TGraph g(AdjMatrix);
    TVertices ts;
    list<int> sched;
    g.DFS(ts, sched);
    cout<<endl<<"SCC: \n"<<endl;
    vector< list<int> > ts_scc;
    g.SCC(ts_scc);
    for (int i = 0; i < ts_scc.size(); ++i) 
	{
        for(list<int>::iterator j = ts_scc[i].begin(); j != ts_scc[i].end(); ++j) cout<<*j<<" ";
        cout<<endl;
    }
}
void for_SCC() 
{
	int n,m,x,y;
	ifstream in;
	in.open("in.txt");
	in >> n >> m;
    vector< vector<bool> > AdjMatrix(n);
	for(int i = 0; i < n; ++i) AdjMatrix[i].resize(n);
    for(int i = 0; i < m; ++i) {
        in >> x >> y;
        AdjMatrix[x-1][y-1]=1;
	}
	in.close();
    SCC_test(AdjMatrix, n);
}

int main()
{
	int n,m,x,y;
	cout << "SCC for our file 'in': \n";
	for_SCC();
	cout << "Inf for TopologicalSort (acyclic graph!): \n";
	cin>>n>>m;
	vector< vector<bool> > AdjMatrix(n);
    for(int i = 0; i < n; ++i) AdjMatrix[i].resize(n);
    for(int i = 0; i < m; ++i) {
        cin>>x>>y;
        AdjMatrix[x-1][y-1]=1;
    }
	TopologicalSort(AdjMatrix, n);
	system ("pause");
	return(0);
}