#include <iostream>
#include <vector>

using namespace std;


enum color{white,grey,black};

void DFSVisit(int u,vector<vector <int>>&graflist,vector <color>&clr,vector<int> &time,vector<int>&timeover,vector<int>&parent,int N,int &t,vector<int>&sort,int &con)
{   
       clr[u]=grey;
        t++;
       time[u]=t; 
      for (size_t j=1;j<graflist[u].size();j++)
        {       
			   int i=graflist[u][j]; 
              if (clr[i]==white)
             
                        {
                                parent[i]=u; 
                                DFSVisit(i,graflist,clr,time,timeover,parent,N,t,sort,con);
                         }
			  if (clr[i]==grey)
			  { 
				  con=1;
				  return;
			  };
                }
                        clr[u]=black;
                       sort.push_back(u);
                       t++;
                       timeover[u]=t;
           
                }

void DFS(vector<vector <int>>&graflist, int N)
{   
	int con=0;  
	vector<int>sort; 
      sort.push_back(0);
      int t=0;
        vector <color>clr(N+1);
        vector<int> time(N+1);
        vector<int>timeover(N+1);
        vector<int>parent(N+1);
       for (int i=1;i<N+1;++i)
        {
               clr[i]=white;
                time[i]=0;
                timeover[i]=0;
                parent[i]=0;
        }
        
        for (int i=1; i<N+1;i++)
        {
               if (clr[i]==white)
                       DFSVisit(i,graflist,clr,time,timeover,parent,N,t,sort,con);
			   if (con==1) break;
			   }
		if (con==1) {cout<<"net recheniy"<<endl;}
		else {
        for (int i=sort.size()-1;i>0;--i)
        {       
              cout<<sort[i]<<' ';
        }
		}
}

int main()
{
	 int N,M;
        cin>>N;
        cin>>M;
        int a,b;
        vector<vector<int>> graflist(N+1);
		for (int i=1;i<N+1;++i)
			graflist[i].push_back(0);

        for (int i=1;i<M+1;++i)
        {
          cin>>a;
          cin>>b;
          graflist[a].push_back(b);
          
        }
  DFS(graflist,N);
 
		system("pause");
		return 0;
}