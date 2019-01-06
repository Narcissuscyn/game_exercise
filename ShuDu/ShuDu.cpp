#include<iostream>
#include<fstream>
#include<cstdlib>
#include"ShuDu.h"
using namespace std;
ShuDu::ShuDu()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        shudoku[i][j]=0;
}
void ShuDu::create()
{

    int col,row, value;
    ifstream temp;
    cout<<"是否继续上次游戏:0 or 1 ?"<<endl;
    int t;cin>>t;
ifstream infile;
ofstream outfile;
if(t==0)
infile.open("sourse.txt",ios::in);
if(t==1)
    infile.open("sourse_1.txt",ios::in);
outfile.open("outcome.txt",ios::out);
if(!infile)
{
    cout<<"file open error!";
    exit(0);
}
while(!infile.eof())
{
    infile>>value;
    infile>>row;
    infile>>col;
    shudoku[row-1][col-1]=value;

}
for(int i=0;i<9;i++)
  {
       for(int j=0;j<9;j++)
       {


           outfile<<shudoku[i][j]<<" ";

       }
      outfile<<"\n";
  }
 infile.close();
 outfile.close();
}
void ShuDu::display()
{
    cout<<"============================================================================="<<endl;
 cout<<"     1    2    3    4    5    6    7    8    9"<<endl<<endl;

    cout<<"    -------------------------------------------"<<endl;
    for(int i=0;i<9;i++)
    {
        cout<<i+1<<"    ";
        for(int j=0;j<9;j++)
        {
            if(shudoku[i][j]!=0)
            cout<<shudoku[i][j]<<"    ";
            else cout<<"*"<<"    ";
        }
         cout<<endl;
        cout<<"    -------------------------------------------"<<endl;
       //
    }
    cout<<endl;
  cout<<"     1    2    3    4    5    6    7    8    9"<<endl;
   cout<<"==============================================================================="<<endl;
}
bool ShuDu::insert_value()
{
    bool flag=true;
    cout<<"请输入行、列：(1-9)"<<endl;
    int row,col,value;
    cin>>row>>col;
     if(row<=0||row>9||col<=0||col>9||value<=0||value>9)
    {
        cout<<"数字范围越界,操作失败！"<<endl<<endl;
        return false;
    }
 bool temp=Search(row-1,col-1);
 if(temp==true)
  {
     cout<<endl;
cout<<"请输入元素值：（1-9）"<<endl;
    cin>>value;
    if(shudoku[row-1][col-1]!=0)
    {
        cout<<"该处已经有值，不能再输入！"<<endl<<endl;
    }
    else
   {
        shudoku[row-1][col-1]=value;

    for(int i=0;i<9;i++)
    {
        if(i!=col-1)
        {
            if(shudoku[row-1][i]==value)
               {
                   cout<<"您输入的值不对，有重复,请重新输入！"<<endl<<endl;
                   flag=false;
               }

        }
    }
    if(flag)
   {
     for(int i=0;i<9;i++)
    {
        if(i!=row-1)
            if(shudoku[i][col-1]==value)
           {
               cout<<"您输入的值不对，有重复,请重新输入！"<<endl<<endl;
               flag=false;
           }
    }
   }
   if(flag)
   {

    int x,y;
    x=((row-1)/3)*3;
    y=((col-1)/3)*3;
     for(int i=x;i<x+3;i++)
        for(int j=y;j<y+3;j++)
     {
         if((i!=(row-1))&&(j!=(col-1)))
            if(shudoku[i][j]==value)

            {
                 cout<<"您输入的值不对，有重复,请重新输入！"<<endl<<endl;
                 flag=false;
            }
     }
   }
}
if(flag==false)
shudoku[row-1][col-1]=0;
if(flag==true)
{
   cout<<"是否保存当前记录以防止中途停止而使数据丢失？：0 or 1"<<endl;
   int  x;
   cin>>x;
   if(x!=0)
    {
 ofstream outfile;
   outfile.open("sourse_1.txt",ios::app);
   outfile<<value<<" "<<row<<" "<<col<<endl;
    outfile.close();
      }
}
  }
return flag;
}

void ShuDu::writefile()
{
    ofstream outfile;
    outfile.open("outcome.txt",ios::out);
    if(!outfile)
{
    cout<<"file open error!";
    exit(0);
}
for(int i=0;i<9;i++)
  {
       for(int j=0;j<9;j++)
       {


           outfile<<shudoku[i][j]<<"   ";

       }
      outfile<<"\n\n";
  }
  outfile.close();
}
bool ShuDu::Search(int x,int y)
{
    if(shudoku[x][y]!=0)
    {cout<<"此处已有元素，不能再输入"<<endl;

    return false;

    }
    int a[27],k=0;
    for(int i=0;i<9;i++)
        if(shudoku[x][i]!=0)
        a[k++]=shudoku[x][i];
    for(int j=0;j<9;j++)
         if(shudoku[j][y]!=0)
        a[k++]=shudoku[j][y];

    int m,n;
    m=(x/3)*3;
    n=(y/3)*3;
     for(int i=m;i<m+3;i++)
        for(int j=n;j<n+3;j++)
     {
          if(shudoku[i][j]!=0)
        a[k++]=shudoku[i][j];
     }
      cout<<"您当前可以输入的元素值如下："<<endl;
    for(int i=1;i<10;i++)
    {
       bool flag=true;
       for(int j=0;j<27;j++)
       {
          if(i==a[j])
            {flag=false;
               break;
            }
       }
       if(flag)cout<<i<<"  ";
    }
    return true;
}
bool ShuDu::modify(int x,int y,int value)
{
    if(x<=0||x>9||y<=0||y>9||value<=0||value>9)
    {
        cout<<"数字范围越界，操作失败！"<<endl;
        return false;
    }
    ifstream infile;
    infile.open("sourse.txt",ios::in);
    int a,b,c;
     infile>>a>>b>>c;
     int flag1=true;
    while(!infile.eof())
    {

    if(x==b&&y==c)
    {
        cout<<"此值为初始化值，不能修改!"<<endl;
        flag1=false;
     return false;

    }
     infile>>a>>b>>c;
    }
    if(flag1)
   {

   bool t=judge(x,y,value);
   if(t==false)
   {
       cout<<"此值修改不合法，有重复，修改失败！"<<endl;
       return false;
   }
    shudoku[x-1][y-1]=value;
   ofstream outfile;
   outfile.open("sourse_1.txt",ios::app);
   outfile<<value<<" "<<x<<" "<<y<<endl;
    outfile.close();
    return true;
   }

}bool ShuDu::judge(int x,int y,int value )
{
    bool flag=true;
     for(int i=0;i<9;i++)
    {
        if(i!=y-1)
        {
            if(shudoku[x-1][i]==value)
               {
                   cout<<"您输入的值不对，有重复,请重新输入！"<<endl<<endl;
                   flag=false;
               }

        }
    }
    if(flag)
   {
     for(int i=0;i<9;i++)
    {
        if(i!=x-1)
            if(shudoku[i][y-1]==value)
           {
               cout<<"您输入的值不对，有重复,请重新输入！"<<endl<<endl;
               flag=false;
           }
    }
   }
   if(flag)
   {

    int m,n;
    m=((x-1)/3)*3;
    n=((y-1)/3)*3;
     for(int i=m;i<m+3;i++)
        for(int j=n;j<n+3;j++)
     {
         if((i!=(x-1))&&(j!=(y-1)))
            if(shudoku[i][j]==value)

            {
                 cout<<"您输入的值不对，有重复,请重新输入！"<<endl<<endl;
                 flag=false;
            }
     }
   }
   return flag;
}
