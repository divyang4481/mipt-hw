#include<queue>
#include<iostream>
#include<vector>
#include<list>

using namespace std;

void BFS(int N, vector<vector<int>>&graflist)
{ 
	enum color {white,grey}	;
	vector <color> clr(N+1);
	queue<int>qu;
	vector<int>parent(N+1);
	vector<int>way(N+1);
  for(int i=2;i<N+1;++i)
  {
    clr[i]=white;
	way[i]=-1;
	parent[i]=-1;
  }
  clr[1]=grey;
  qu.push(1);
  way[1]=0;
  parent[1]=0;
  while (!(qu.empty()))
  {
	  int v=qu.front();
	  int r=graflist[v].size();
	  for (int j=0;j<r;++j)
	  {    
          int num=graflist[v][j];
		  if (clr[num]==white) 
		  {
			 clr[num]=grey;
			 way[num]=way[v]+1;
			 parent[num]=v;
			 qu.push(num);
		  }
		  
	  }
	  qu.pop();
  }
  for (int i=1;i<N+1;i++)
  {
	  if (way[i]==-1) cout<<i<<" no parents"<<" no way"<<endl;
	  else cout<<i<<" parent: "<<parent[i]<<" way: "<<way[i]<<endl;
  }
}

int main()
{   int N,M;
	cin>>N;
	cin>>M;
	int a,b;
	vector<vector<int>> graflist(N+1);
	/*for (int i=1; i<N+1;i++)
	{graflist[i][0]=0;}*/
	for (int i=1;i<M+1;++i)
	
	{
	  cin>>a;
	  cin>>b;
	  graflist[a].push_back(b);
	  
	}
	
    BFS(N,graflist);
	system("pause");
		return 0;
}