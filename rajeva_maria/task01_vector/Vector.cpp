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
   typedef const T* const_iterator;
   TVector()
   {
	   size=0;
	   capacity=1;
	   buf = new T[1];
   }
    TVector(const TVector<T>& cop)
	{
		capacity=cop.capacity;
		size=0;
		buf = new T[capacity];
		for	(size_t i=0;i<cop.size;++i)
			Pushback(cop[i]);
	}

   const size_t Size() const
   {
   return size;
   }

   const bool Empty() const
   {
   return (size==0);
   }

   void Clear()
   {
   size=0; 
   }

   ~TVector()
   {
	   delete[] buf;
   }

   const int Capacity() const
   {
   return(capacity); 
   }
   T& operator[](int index) const
   {
	   return buf[index];
   }

   T Popback()
   {
   T t=buf[size-1];
   size--;
   return(t);
   }

   void Pushback(T val)
   {
	    if (capacity==size) Reserve(size+1);
        buf[size]=val;
		size++;
    }

 void Resize(size_t n)
   { 
	   if (n>size)
	   Reserve(n);
	   size=n;
   }

 void Reserve(size_t n)
   {
	   while (capacity<n)
	       capacity=2*capacity;
	   
	   T *buf1= new T[capacity];
	   for(size_t i=0;i<Size();++i)
	   buf1[i]=buf[i];
       delete[]buf;
	   buf=buf1;
	   
   }

   iterator Begin()
   {
	   return(buf);
   };

   const iterator Begin() const
   {
	   return(buf);
   };

   iterator End()
   {
	   return (buf+size);
   };

   const iterator End() const 
   {
	   return (buf+size);
   };

   T& Front()
   {
	   return(buf[0]);
   };
   const T& Front() const
   {
	   return(buf[0]);
   };

   T& Back()
   {
	   return(buf[size-1]);
   };

    const T & Back() const
   {
	   return(buf[size-1]);
   };

   void Swap(TVector &a)
   {
       swap(buf,a.buf);
	   swap(size,a.size);
	   swap(capacity,a.capacity);
   };

   void Insert (iterator iter, T &n)
   {
       if (size==capacity) Reserve(size+1);
	   ++size;
	   for (iterator i=End(); i!=iter;--i)
	   *i=*(i-1);
	    *(iter+1)=n;
   };

   void Erase(iterator iter)
   {
	   for (iterator i=iter;i!=End()-1;++i) 
	   {
		   *i=*(i+1);
	   }
	   --size;
   };

   TVector<T>&operator =(TVector<T>&cop)
   {
	   Clear();
	   for (size_t i=0;i<cop.Size();++i)
		   Pushback(cop[i]);
	       return *this;
   }
 
 };

struct TFoo {
  static int Created;
  static int Deleted;

  TFoo() { ++Created; }
  TFoo(const TFoo&) { ++Created; }
  ~TFoo() { ++Deleted; }
};

int TFoo::Created = 0;
int TFoo::Deleted = 0;

 int main () 
 {    
	  TVector <int> A;
	  cout<<A.Empty()<<endl;
      A.Resize(10);
	  cout<<"Capacity: "<<A.Capacity()<<' '<<"Size: "<<A.Size()<<endl;
	  A[0]=1001;
	  cout<<"A[0]: "<<A[0]<<endl;
	  cout<<"Empty: "<<A.Empty()<<endl;
	  A.Clear();
	  cout<<"Empty after Clear: "<<A.Empty()<<endl;
	  for (int i=0;i<10; ++i)
	       A.Pushback(i);
	  cout<<"elements:"<<endl;
      for( TVector<int>::iterator i=A.Begin();i!=A.End();i++)
	  cout<<*i<<' ';
      A.Popback();
	  cout<<endl;
	  cout <<"elements after Popback: "<<endl;
	  for( TVector<int>::iterator i=A.Begin();i!=A.End();i++)
	  cout<<*i<<' ';
	  cout<<endl;
      cout<<"Size: "<<A.Size()<<endl;
	  TVector<int> B=A;
	  cout<<"Check operator = (B elements ) : "<<endl;
      for( TVector<int>::iterator i=B.Begin();i!=B.End();i++)
	  cout<<*i<<' ';
	  A.Clear();
	  cout<<endl;
	  A.Swap(B);
	  cout<<"A elements after swap: "<<endl;
	  for( TVector<int>::iterator i=A.Begin();i!=A.End();i++)
	  cout<<*i<<' ';
	  cout<<endl<<"Front: "<<A.Front()<<' '<<"Back: "<<A.Back()<<endl;
	  TVector<int>::iterator i=A.Begin();
	  int n=105;
	  A.Insert(i,n);
	  cout<<"Insert: "<<endl;
	  for( TVector<int>::iterator i=A.Begin();i!=A.End();i++)
	  cout<<*i<<' ';
	  i=A.Begin();
	  cout<<endl;
	  A.Erase(i+5);
	  cout<<"Erase: "<<endl;
	   for( TVector<int>::iterator i=A.Begin();i!=A.End();i++)
	  cout<<*i<<' ';

	   {	   TVector<TFoo>C;}

        {
            TVector<TFoo> a;
            for (int i = 0; i < 10; ++i)
                a.Pushback(TFoo());

            TVector<TFoo> b = a;
            for (int i = 0; i < 10; ++i)
                b.Pushback(TFoo());

            a.Swap(b);

            TVector<TFoo> c;
            a = c;
        }
		const TVector<int> a (A);

         TVector<int> b(a);
  
       cout<<endl<<"created: "<<TFoo::Created<<endl;
	   cout<<"deleted: "<<TFoo::Deleted<<endl;
	   system("pause");
	  return 0;
 } 


