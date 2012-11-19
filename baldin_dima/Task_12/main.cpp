
#include <iostream>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include <fstream>
using namespace std;

double Kahan(double *buf,int n)
{
    double sum,c,t,y;
    sum = 0.0;
    c = 0.0;
    for (int i=0;i<n;++i)
    {
        y = buf[i] - c;
        t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
     return sum;
}


class THeap
{
    private:
      double *buf;
      int Size;
      int Parent (int k)
      {
          return((k - 1) >> 1);
      }
      int LeftChild (int k)
      {
          return((k << 1) + 1);
      }
      int RightChild (int k)
      {
          return((k << 1) + 2);
      }
      void BuildHeap()
      {
          for (int i = Parent(Size - 1); i >= 0; --i)
            Heapify(i);
      }

      void Heapify(int k)
      {
          GoUp(k);
          GoDown(k);
      }
      void GoDown(int k)
      {
          int min = k, l = LeftChild(k), r = RightChild(k);
          if ((l < Size) && (buf[min] > buf[l]))
            min = l;
          if ((r < Size) && (buf[min] > buf[r]))
            min = r;
          if (min != k)
            {
                swap(buf[min],buf[k]);
                Heapify(min);
            }
      }
      void GoUp(int k)
      {
          if (k != 0)
          {
              if (buf[k]<buf[Parent(k)])
              {
                swap(buf[k],buf[Parent(k)]);
                GoUp(Parent(k));
              }
          }
      }
    public:
      THeap(double *Buf, int size)
      {
          buf = Buf;
          Size = size;
          BuildHeap();
      }
      int GetSize()
      {
          return(Size);
      }
      void DecSize()
      {
         Size--;
      }
      void HeapSort (double *mass, int n)
      {
          for (int i = GetSize();i > 0; i--)
            {
                swap(mass[0],mass[i-1]);
                DecSize();
                Heapify(0);
            }
      }
      void Delete(int k)
      {
          swap(buf[k],buf[Size-1]);
          DecSize();
          Heapify(k);
      }
      void Insert(double elem)
      {
          buf[Size++] = elem;
          Heapify(Size-1);
      }
      double Min()
      {
          return buf[0];
      }

};
double HeapSum(double *mass, int n)
      {
          THeap heap(mass, n);
          for (int i = 0;i<n-1;++i)
            {
              double sum = heap.Min();
              heap.Delete(0);
              sum += heap.Min();
              heap.Delete(0);
              heap.Insert(sum);
            }
          return mass[0];
      }
int main()
{

    int n;
    cin >> n;
    double *buf = (double*)malloc(n*sizeof(double));
    for (int i = 0;i<n;++i)
     cin >> buf[i];
    int t = clock() ;
    double sum = Kahan(buf, n);
    int t1 = clock();
    cout << sum <<" time " << (((t1-t)*1000)/CLOCKS_PER_SEC) << "\n";
    t = clock() ;
    sum = HeapSum(buf, n);
    t1 = clock();
    cout << sum <<" time " << (((t1-t)*1000)/CLOCKS_PER_SEC);
    free(buf);
    return 0;
}
