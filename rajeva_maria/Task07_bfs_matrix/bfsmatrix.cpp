#include <iostream>
#include <vector>
#include <queue>
using namespace std; 



void BFS(int N,vector<vector<int>>& grafmatr)
{
	enum color {white,grey,black};
	vector <color> clr(N+1);
	queue <int> qu; 
	vector<int> parent(N+1);
	vector<int> way(N+1);
	for (int i=2;i<N+1;i++)
	{
		clr[i]=white;
		parent[i]=-1;
		way[i]=-1;
    }
	clr[1]=grey;
	qu.push(1);
	way[1]=0;
	parent[1]=0;
	while(!qu.empty())
	{
		int v=qu.front();
		for (int i=1; i<N+1; i++)
		{
			if ((grafmatr[v][i]==1)&&(clr[i]==white))
			{
			  clr[i]=grey;
			  qu.push(i);
			  way[i]=way[v]+1;
			  parent[i]=v;
			}
		}
		qu.pop();
	}
	for (int i=1; i<N+1;i++)
	{  if (way[i]==-1)
      cout<<i<<" distance "<<" "<<" no  parent "<<endl;
	   else cout<<i<<" distance "<<way[i]<<" parent "<<parent[i]<<endl;
	   
	}
}

int main()
{   
	int N;
	int M;
	cin>>N;
	vector<vector<int>> grafmatr(N+1);  
	cin>>M;
	for(int i=1;i<N+1;++i)
	{
		grafmatr[i].resize(N+1); 
	}
	for(int i=1;i<N+1;i++)
	{
		for (int j=1;j<N+1;j++)
		{
		     grafmatr[i][j]=0;
		}
	}
	for(int i=1;i<M+1;i++)
	{  
       int b;
	   int e;
	   cin>>b;
	   cin>>e;
	   grafmatr[b][e]=1; 
	}

	BFS(N,grafmatr);

	system("pause");
    return 0;
}
