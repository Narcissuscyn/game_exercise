#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<iomanip>
#include"Game.h"
#include<stdio.h>
using namespace std;
 Game::Game()
 {
 for(int i=0;i<4;i++)
 {
     for(int j=0;j<4;j++)
        a[i][j]=0;
 }
 number=2;
 }
void Game::set_number()
{
    int x[20],y[20];
      srand((unsigned int)time(NULL));
      int flag=rand()%2;
      if(flag==0)
        number=2;
      if(flag==1)
        number=4;
        int k=0;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(a[i][j]==0)
                   {
                       x[k]=i;
                       y[k]=j;
                       k++;
                   }
            }
        }
        int temp=rand()%k;
        a[x[temp]][y[temp]]=number;
}
bool Game::judge_win()
{
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
    {
        if(a[i][j]==2048)
            return true;}
    return false;
}
void Game::get_a(Game&G)
{
    //system("cls");
DIS*D;
D=new DIS;
D->display(G);
}
void Game::set_right()
{
    if(judge_right())
    {mul_right();
   move_right();set_number();}
 }
void Game::set_up()
{
    if(judge_up())
   {
       mul_up();
       move_up();
      set_number();
   }
}
void Game::set_down()
{if(judge_down())
{mul_down();
move_down();set_number();}
}
bool Game::judge_full()
{
for(int i=0;i<4;i++)
   {
        for(int j=0;j<4;j++)
{
    if(a[i][j]==0)return false;
}
   }
    for(int i=0;i<3;i++)
        {for(int j=0;j<4;j++)
       {
            if(a[i+1][j]==a[i][j])return false;
           }}
   for(int i=0;i<3;i++)
            for(int j=0;j<4;j++)
           {
               if(a[j][i]==a[j][i+1])return false;}
           return true;}
void Game::mul_right()
{int k;
    for(int i=0;i<4;i++)
    {
        for(int j=3;j>0;j--)
        {
            if(a[i][j]!=0)
            {
           for(k=j-1;k>=0;k--)
                 {
                    if(a[i][k]!=0)break;
                }
                 if((k>=0)&&k<=3)
          if(a[i][k]==a[i][j]){a[i][j]=a[i][j]+a[i][k];a[i][k]=0;}
            }}}}
void Game::move_right()
{
    for(int i=0;i<4;i++)
    {
        for(int j=1;j<4;j++)
        {
            if(a[i][j]==0)
            {
                int k=j;
                while(k>0)
                {
                    a[i][k]=a[i][k-1];
                    a[i][k-1]=0;
                    k--;
                }}}}}
 void Game::mul_left()
 {
     int k;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(a[i][j]!=0)
            {
           for(k=j+1;k<=3;k++)
                 {
                    if(a[i][k]!=0)break;
                }
                 if((k>=0)&&k<=3)
          if(a[i][k]==a[i][j]){a[i][j]=a[i][j]+a[i][k];a[i][k]=0;}
            }}}}
 void Game::move_left()
 {
     for(int i=0;i<4;i++)
    {
        for(int j=2;j>=0;j--)
        {
            if(a[i][j]==0)
            {
                int k=j;
                while(k<3)
                {
                    a[i][k]=a[i][k+1];
                    a[i][k+1]=0;
                    k++;
                }}}}}
 void Game::set_left()
 {if(judge_left())
     {mul_left();
     move_left();set_number();}
 }
void Game::mul_down()
{
    int k;
    for(int i=0;i<4;i++)
    {
        for(int j=3;j>0;j--)
        {
            if(a[j][i]!=0)
            {
           for(k=j-1;k>=0;k--)
                 {
                    if(a[k][i]!=0)break;
                }
                 if((k>=0)&&k<=3)
          if(a[k][i]==a[j][i]){a[j][i]=a[j][i]+a[k][i];a[k][i]=0;}
            }}}}
void Game::move_down()
{
    for(int i=0;i<4;i++)
    {
        for(int j=1;j<4;j++)
        {
            if(a[j][i]==0)
            {
                int k=j;
                while(k>0)
                {
                    a[k][i]=a[k-1][i];
                    a[k-1][i]=0;
                    k--;
                }}}}}
void Game::move_up()
{
    for(int i=0;i<4;i++)
    {
        for(int j=2;j>=0;j--)
        {
            if(a[j][i]==0)
            {
                int k=j;
                while(k<3)
                {
                    a[k][i]=a[k+1][i];
                    a[k+1][i]=0;
                    k++;
                }}}}}
void Game::mul_up()
{
    int k;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(a[j][i]!=0)
            {
           for(k=j+1;k<4;k++)
                 {
                    if(a[k][i]!=0)break;
                }
                if((k>=0)&&k<=3)
           {
                if(a[k][i]==a[j][i]){a[j][i]=a[j][i]+a[k][i];a[k][i]=0;}
           }
            }}}}
bool Game::judge_right()
{
    for(int i=0;i<4;i++)
      {
           for(int j=0;j<3;j++)
         {
             if(a[i][j]!=0)
             {
                 int k=j;
                 while(k<4){if(a[i][k]==0)return true;k++;}
                 if(a[i][j]==a[i][j+1])return true;
                 if((a[i][j]==a[i][j+2])&&(a[i][j+1]==0)&&((j+2)<4))return true;
                 if((j==0)&&(a[i][j]==a[i][j+3])&&(a[i][j+1]==0)&&(a[i][j+2]==0))return true;
             }}}
      return false;
}
bool Game::judge_left()
{
for(int i=0;i<4;i++)
      {
           for(int j=3;j>0;j--)
         {
             if(a[i][j]!=0)
             {
                 int k=j;
                 while(k>=0){if(a[i][k]==0)return true;k--;}
                 if(a[i][j]==a[i][j-1])return true;
                 if((a[i][j]==a[i][j-2])&&(a[i][j-1]==0)&&((j-2)>=0))return true;
                 if((j==3)&&(a[i][j]==a[i][j-3])&&(a[i][j-1]==0)&&(a[i][j-2]==0))return true;
             }}}
      return false;}
bool Game::judge_down()
{
for(int i=0;i<4;i++)
      {for(int j=0;j<3;j++)
         {if(a[j][i]!=0)
             { int k=j+1;
                 while(k<4){if(a[k][i]==0)return true;k++;}
                 if(a[j][i]==a[j+1][i])return true;
                 if((a[j][i]==a[j+2][i])&&(a[j+1][i]==0)&&((j+2)<4))return true;
                 if((j==0)&&(a[j][i]==a[j+3][i])&&(a[j+1][i]==0)&&(a[j+2][i]==0))return true;
             }}}
      return false;}
bool Game::judge_up()
{
for(int i=0;i<4;i++)
      {for(int j=3;j>0;j--)
         {if(a[j][i]!=0)
             {int k=j-1;
                 while(k>=0){if(a[k][i]==0)return true;k--;}
                 if(a[j][i]==a[j-1][i])return true;
                 if((a[j][i]==a[j-2][i])&&(a[j-1][i]==0)&&((j-2)>=0))return true;
                 if((j==3)&&(a[j][i]==a[j-3][i])&&(a[j-1][i]==0)&&(a[j-2][i]==0))return true;
             }}}
      return false;
}

void DIS::display(Game&G)
{
    system("cls");
    cout<<endl;
    cout<<"               GAME PLAY           "<<endl<<endl;
    for(int i=0;i<4;i++)
    {
        cout<<"      "<<dis;
        for(int i=0;i<13;i++)
            cout<<dis<<" ";
        cout<<dis<<dis;
        if(i==0)cout<<"         请选择滑动方式（N->退出 ）";
        if(i==1)cout<<"         A->左滑";
        if(i==2)cout<<"         D->右滑";
        if(i==3)cout<<"         W->上滑";
        cout<<endl;
    cout<<"      "<<dis<<"      "<<dis<<"      "<<dis<<"      "<<dis<<"      "<<dis<<endl<<"      "<<dis;
        for(int j=0;j<4;j++)
        {
           if(G.a[i][j]!=0)
            cout<<" "<<setw(4)<<G.a[i][j]<<" "<<dis;
            if(G.a[i][j]==0)
               cout<<"      "<<dis;
        }
        cout<<endl;
    }
  cout<<"      "<<dis;
        for(int i=0;i<13;i++)
            cout<<dis<<" ";
        cout<<dis<<dis;
  cout<<"         S->下滑";
  cout<<endl<<endl;
}

