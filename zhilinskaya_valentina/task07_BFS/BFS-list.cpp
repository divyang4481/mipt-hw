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
	vector<list<int> > _adj;
	int time;
public :
	TGraph (const vector< list<int> >& arr): _adj(arr) {}
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
			for(auto it=_adj[beg].begin(); it!=_adj[beg].end(); it++)
				if(Vertices[*it].Color==C_WHITE)
				{
					Vertices[*it].Color=C_GRAY;
					Vertices[*it].Depth=Vertices[beg].Depth+1;
					Vertices[*it].Parent=beg;

					d.push_back(*it);
					Vertices[*it].Color=C_BLACK;
				}
		}
	}
};
void test (const vector< list<int> >& _adj, int n) {
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
	ifstream in1;
	in1.open("in.txt");
	int n,k;
	int x,y;
	in1>>n>>k;
	vector< list<int> > lists(n);
	for(int i=0; i<k; ++i) {
		in1>>x>>y;
		lists[x-1].push_back(y-1);
	}

	test(lists, n);
	in1.close();
	int a;
	system("pause");
	return(0);
}