#include <iostream>
#include <vector>

using namespace std;


enum color{white,grey,black};

void DFSVisittransp(int u,vector<vector <int>>&graflist,vector <color>&clr,int N)
{   
       clr[u]=grey;
       
      for (int j=1;j<graflist[u].size();j++)
        {       
			   int i=graflist[u][j]; 
              if (clr[i]==white)
                        {
                               
                                DFSVisittransp(i,graflist,clr,N);
                         }
                }
                        clr[u]=black;
                        cout<<u<<" ";
                       
                
        
}

void DFStransp(vector<vector <int>>&graflist, int N, vector<int>f)
{   
      int t=0;
        vector <color>clr(N+1);
       
       
     for (int i=1;i<N+1;++i)
        
               clr[i]=white;
               
       for (int i=N; i>0;--i)
        {      
			  if (clr[f[i]]==white)
			  {
               DFSVisittransp(f[i],graflist,clr,N);
			   cout<<endl;
			  }
        }
     
}


void DFSVisit(int u,vector<vector <int>>&graflist,vector <color>&clr,vector<int> &timeover,int N,int &t)
{   
       clr[u]=grey;
       for (int j=1;j<graflist[u].size();j++)
        {       
			   int i=graflist[u][j]; 
              if (clr[i]==white)
                        {
                                
                                DFSVisit(i,graflist,clr,timeover,N,t);
                         }
                }
                        clr[u]=black;
                       t++;
                       timeover[t]=u;
                
        
}

void DFS(vector<vector <int>>&graflist, int N,vector<int>&f)
{   
      int t=0;
        vector <color>clr(N+1);
       
       for (int i=1;i<N+1;++i)
        {
               clr[i]=white;
                f[i]=0;
               
        }
        
        for (int i=1; i<N+1;i++)
        {
               if (clr[i]==white)
                       DFSVisit(i,graflist,clr,f,N,t);
        }
        
}

void Transp (vector<vector<int>>&graflist,int N)      
{   
	vector<vector<int>>grafnew(N+1);

	for (int i=1;i<N+1;i++)
	{
		grafnew[i].push_back(0);
	}
	for (int i=1; i<N+1;i++)
	for (int j=1; j<graflist[i].size();j++)
	  grafnew[graflist[i][j]].push_back(i);
	graflist=grafnew;
}
int main()
{    
	    int N,M;
        cin>>N;
        cin>>M;
        int a,b;
		vector<int>timeover(N+1);
		timeover[0]=0;
        vector<vector<int>> graflist(N+1);
		for (int i=1;i<N+1;++i)
			graflist[i].push_back(0);

        for (int i=1;i<M+1;++i)
        {
          cin>>a;
          cin>>b;
          graflist[a].push_back(b);
          
        } 
          DFS(graflist,N,timeover); 
		  Transp(graflist,N);
          DFStransp(graflist,N,timeover);
          system("pause");
		  return 0;
}