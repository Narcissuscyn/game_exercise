
#include "iostream"
#include "cmath"
#include "View.h"
#include "string"
extern const char * TypeOfRoad;
using namespace std;
View::View(int r,int c,int x[],int y[],int sty[],string name[],int np):nPoint(np),row(r),colm(c)
{
    X=new int[nPoint];
    Y=new int[nPoint];
    style=new int[nPoint];
    Name=new string[nPoint];
    for(int i=0;i<nPoint;i++)
    {
        X[i]=x[i];
        Y[i]=y[i];
        Name[i]=name[i];
        style[i]=sty[i];

    }
    Jlu=new int*[r];
    for(int i=0;i<r;i++)
    {
        Jlu[i]=new int[c];
    }
    for(int i=0;i<r;i++)
    {
        for(int j=0;j<c;j++)
        {
            Jlu[i][j]=0;
        }
    }
    for(int i=0;i<nPoint;i++)
    {
        SetRoad(X[i],Y[i],style[i]);
    }
}
void View::Display()const
{
     cout<<"吉林大学地图"<<endl;
     for(int i=0;i<row;i++)
     {
         for(int j=0;j<colm;j++)
         {
             cout<<StyleOfRoad[ Jlu[i][j] ]<<" ";
         }
         cout<<endl;
     }
     for(int i=0;i<nPoint;i++)
     {
         cout<<StyleOfRoad[style[i]]<<":"<<Name[i]<<" ";
     }
     cout<<endl;

}

void View::SetRoad(int x,int y,int stye)
{
    if(x>=row || y>=colm)return;
    Jlu[x][y]=stye;
   // cout<<UP;
}
void View::GetRoad(int v1,int v2)
{
    GetRoad(X[v1],Y[v1],X[v2],Y[v2]);
}
void View::GetRoad(int x1,int y1,int x2,int y2)
{
    int line;
    int col;
    bool preLine;
    if(y2>y1)
    {
        line=RIGHT;
        if(x2<x1)
        {
          col=UP;
          preLine=0;
        }
        else
        {
          col=DOWN;
          preLine=1;
        }
    }
    else
    {
        line=LEFT;
        if(x2<x1)
        {
           col=UP;
           preLine=1;
        }
        else
        {
            col=DOWN;
            preLine=0;
        }
    }
    int Xdrt=(x2-x1)/abs(x2-x1);
    int Ydrt=(y2-y1)/abs(y2-y1);
    if(preLine)
    {
        int i;
        for(i=y1+Ydrt;i!=y2;i+=Ydrt)
        {
            SetRoad(x1,i,line);
        }
        Jlu[x1][i]=PLUS;
        for(int j=x1+Xdrt;j!=x2;j+=Xdrt)
        {
            SetRoad(j,i,col);
        }
    }
    else
    {
        int i;
        for(i=x1+Xdrt;i!=x2;i+=Xdrt)
        {
            SetRoad(i,y1,col);
        }
        Jlu[i][y1]=PLUS;
        for(int j=y1+Ydrt;j!=y2;j+=Ydrt)
        {
            SetRoad(i,j,line);
        }
    }



}
View::~View()
{
    for(int i=0;i<row;i++)
        delete[] Jlu[i];
    delete Jlu;
    delete X;
    delete Y;
    delete style;
    delete Name;
}
void View::ClearRoad()
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<colm;j++)
        {
            if(Jlu[i][j]>VOID && Jlu[i][j]<NAME_1)
                Jlu[i][j]=0;
        }
    }
}
void View::SetPoint(int v)
{

}
