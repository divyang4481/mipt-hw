// Двумерные массивы.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int** CreateMatr(int w, int h)
{
    
    int** buf=new int*[h];
    for (int i=0; i<h; ++i)
    {
        *(buf+i)=new int[w];
    }
    return buf;
}

void DeleteMatr(int** buf, int w, int h)
{
    for (int i=0; i<h; ++i)
    {
        delete[] *(buf+i);
    }
    delete[] buf;
}
void ReadMatr(int** &buf, int &w, int &h)
{
    
    scanf("%d %d",&w,&h);
    buf=CreateMatr(w,h);
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            scanf("%d", &buf[i][j]);
        }
    }
}

void WriteMatr(int** buf, int w, int h)
{
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            printf("%d\t", buf[i][j]);
        }
        printf("\n");
    }
}

void SumMatr(int** a, int** b, int** &c, int h, int w)
{
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            c[i][j]=a[i][j]+b[i][j];
        }
    }
}

int main()
{
    int WIDTH1=0, HEIGHT1=0, WIDTH2=0, HEIGHT2=0;
    int** Ar1;
    int** Ar2;
    int** Ar3;
    ReadMatr(Ar1,WIDTH1,HEIGHT1);
    ReadMatr(Ar2,WIDTH2,HEIGHT2);
    WriteMatr(Ar1,WIDTH1,HEIGHT1);    
    printf("\n");
    WriteMatr(Ar2,WIDTH2,HEIGHT2);
    printf("\n");
    Ar3=CreateMatr(WIDTH1,HEIGHT1);
    SumMatr(Ar1, Ar2, Ar3,WIDTH1,HEIGHT1);
     printf("\n");
    WriteMatr(Ar3,WIDTH1,HEIGHT1);
    DeleteMatr(Ar1,WIDTH1,HEIGHT1);
    DeleteMatr(Ar2,WIDTH2,HEIGHT2);
    return 0;
}