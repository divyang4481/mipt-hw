#include <iostream>
#include <vector>
#include <queue>
using namespace std; 
enum color{white,grey,black};

void DFSVisit(int u,vector<vector <int>>&grafmatr,vector <color>&clr,vector<int> &time,vector<int>timeover,vector<int>parent,int N,int &t)
{    
	clr[u]=grey;
	t++;
	time[u]=t;

}

void DFS(vector<vector <int>>&grafmatr, int N)
{   
	int t=0;
	vector <color>clr;
	vector<int> time;
	vector<int>timeover;
	vector<int>parent;
	for (int i=1;i<N+1;i++)
	{
		time[i]=0;
		clr[i]=white;
		parent[1]=0;
	}
	for (int i=1; i<N+1;i++)
	{
		if (clr[i]=white)
			DFSVisit(i,grafmatr,clr,time,timeover,parent,N,t);
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
		return 0;
}
