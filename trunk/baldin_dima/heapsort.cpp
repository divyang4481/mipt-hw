#include <iostream>
#include <stdlib.h>
using namespace std;

void insert(int *buf,int num_of_elem,int n)
{
    int new_elem;
    new_elem=buf[num_of_elem];
    int cur_num;
    while (num_of_elem<=n/2)
    {
        cur_num=2*num_of_elem;
        if ((cur_num<n)&&(buf[cur_num]<buf[cur_num+1]))
         ++cur_num;
        if (new_elem>=buf[cur_num]) break;
        buf[num_of_elem]=buf[cur_num];
        num_of_elem=cur_num;
    }
    buf[num_of_elem]=new_elem;
}
void HeapSort(int *buf, int n)
{
  int b;
  for (int i=n/2;i>=0;i--)
     insert(buf,i,n-1);
  for (int i=n-1;i>0;i--)
  {
      b=buf[i];buf[i]=buf[0];buf[0]=b;
      insert(buf,0,i-1);
  }
}
int main()
{
    int *buf;
    int n;
    cin >> n;
    buf=(int*)malloc(n*sizeof(int));
    for (int i=0;i<n;++i)
     cin >> buf[i];
    HeapSort(buf,n);
    for (int i=0;i<n;++i)
     cout << buf[i] << ' ';

    free(buf);

    return 0;
}
