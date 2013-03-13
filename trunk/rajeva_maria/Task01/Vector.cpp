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
   TVector()
   {
	   size=0;
	   capacity=1;
	   buf = new T[1];
   }
   
   int size()
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

   int capacity
   {
   return(capacity); 
   }
   
   void popback()
   {
   size--;
   }

   void resize
   {   capacity=2*capacity;
	   T* newbuf=new T[capacity];
	   for (i=0;i<size;i++)
            newbuf[i]=buf[i];
	   buf=newbuf;     
   }
 int main () 
 {
 }