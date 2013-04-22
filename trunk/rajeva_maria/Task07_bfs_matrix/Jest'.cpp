#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std; 



void BFS(int N)
{
	enum color {white,grey,black};
	vector <color> clr(N+1);
	queue <int> qu(N+1); 
	vector<int> parent(N+1);
	vector<int> way(N+1);
	for (int i=1;i<N+1;i++)
	{
		clr[i]=white;
		parent[i]=-1;
		d[i]=-1;
    }


}

int main()
{   
	int N;
	int M;
	cin>>N;
	vector<vector<int>> grafmatr(N+1);  
	cin>>M;
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


	return 0;
}
