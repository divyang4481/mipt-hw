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
			Depth=std::numeric_limits<int>::max();
			Parent=-1;
			Color=C_WHITE;
			DiscoverTime=-1;
			FinishTime=-1;
		}
};
 
typedef vector<Vertex> Vertices;
class TGraph
{
		vector<list<int> > _adj;
		int time;
 
		void DFSVisit(int a, Vertices& vertices, list<int>& list)
		{
			for (auto it=_adj[a].begin(); it!=_adj[a].end(); ++it)
			{
				if (vertices[*it].Color == C_WHITE)
				{
					vertices[*it].Color = C_GRAY;
					vertices[*it].DiscoverTime = ++time;
					vertices[*it].Parent = a;
					DFSVisit(*it, vertices, list);
					vertices[*it].FinishTime = ++time;
					list.push_front(*it+1);
					vertices[*it].Color = C_BLACK;
				}
			}
		}
 
	public :
		TGraph (const vector< list<int> >& arr): _adj(arr) {}
 
		void DFS (Vertices& vertices, list<int>& list)
		{
			vertices.resize(0);
			vertices.resize( _adj.size() );
			time = 0;
			for (int i=0; i<_adj.size(); i++)
			{
				if (vertices[i].Color == C_WHITE)
				{
					vertices[i].Color= C_GRAY;
					vertices[i].DiscoverTime = ++time;
					DFSVisit(i, vertices, list);
					vertices[i].FinishTime = ++time;
					list.push_front(i+1);
					vertices[i].Color = C_BLACK;
				}
			}
		}
 
};
void test (const vector< list<int> >& _adj, int n) {
	TGraph g(_adj);
	Vertices ver;
	cout<<endl<<"DFS"<<endl;
	list<int> list;
	g.DFS(ver, list);
	for (int i=0; i<n; ++i) {
		cout<<"#"<<i+1<<" DT "<<ver[i].DiscoverTime<<" FT "<<ver[i].FinishTime;
		if (ver[i].Parent==-1)
			cout<<" Parent no (root)"<<endl;
		else
			cout<<" Parent "<<ver[i].Parent+1<<endl;
	}
}
 
int main() {
	ifstream in;
	in.open("in.txt");
	int n,k;
	int x,y;
	in >> n >> k;
	vector< list<int> > lists(n);
	for(int i = 0; i < k; ++i) {
		in >> x >> y;
		lists[x-1].push_back(y - 1);
	}
 
	test(lists, n);
	in.close();
	system ("pause");
	return(0);
}
