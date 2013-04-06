#include <iostream>
#include <vector>
using namespace std; 

template <typename T>
class TVector 
{ T*buf;
  size_t size;
  size_t capacity;
public:
   typedef T* iterator;
   typedef const T* const_iterator
;   TVector()
   {
	   size=0;
	   capacity=1;
	   buf = new T[1];
   }
   
   int Size()
   {
   return size;
   }
   
   bool empty()
   {
   return (size==0);
   }

   void clear()
   {
   size=0; 
   }

   ~TVector()
   {
	   delete[] buf;
   }

   int Capacity()
   {
   return(capacity); 
   }
   
   T popback()
   {
   T t=buf[size-1];
   size--;
   return(t);
   }

   void pushback(T val)
   {
	   if (Capacity()==Size()) resize();
	   buf[size]=val;
	   size++;
	 }



   void resize()
   {   capacity=2*capacity;
	   T* newbuf=new T[capacity];
	   for (int i=0;i<size;i++)
            newbuf[i]=buf[i];
	   buf=newbuf;     
   }

   void reserve(T&n)
   {
	   while (capacity<n) resize();
   }

   iterator begin()
   {
	   return(buf);
   };
   iterator end()
   {
	   return (buf+size);
   };
   T& front()
   {
	   return(buf[0]);
   };
   T& back()
   {
	   return(buf[size-1]);
   };
   void swap(TVector &a, TVector &b)
   {
       T t=buf[a];
	   buf[a]=buf[b];
	   buf[b]=t;
   };
   void insert (iterator iter, T &n)
   {
       reserve(size+1);
	   ++size;
	   for (iter i=size;i!=iter;--i)
	   {
		   *i=*(i-1);
	   }
	   *iter=n;
   };
   void erase(iterator iter)
   {
	   for (iterator i=iter;i<end();++i) 
	   {
		   *i=*(i+1);
	   }
	   --size;
   };
   };

 int main () 
 {    TVector <int> A;
      A.pushback(54); 
	  cout<<A.popback()<<endl;
      cout<<A.Size()<<endl;
	  cout<<A.Capacity()<<endl;
	  cout<<A.empty()<<endl;
	  system("pause");
	  return 0;
 }