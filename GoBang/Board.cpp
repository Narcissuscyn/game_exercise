
#include<iostream>
using namespace std;
#include<iomanip>
#include"GoBang.h"
static int Count=0;
void Checker::Display()
{
    cout<<"  ";
    for(int i=1;i<SIZE+1;i++)
    {
        cout<<setw(4)<<i;
    }
    cout<<endl;
SetUp();
for(int i=0;i<SIZE;i++)
{Setm();
SetM();
cout<<++Count<<" "<<endl;
}
Setm();
SetDown();
cout<<endl;
}
Checker::Checker()
{
    chess1="¡ð";
    chess2="¡ñ";
   for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
        board[i][j]="#";
}
void Checker::SetUp()
{cout<<lineHead[0];
    for(int i=0;i<SIZE;i++)
        cout<<lineMid1[0]<<lineMid2[0];
    cout<<lineMid1[0]<<lineTail[0];
    cout<<" "<<endl;
}
void Checker::Setm()
{
    for(int i=0;i<SIZE+2;i++)
    {
        cout<<shu<<"  ";
    }
    cout<<endl;
}
void Checker::SetM()
{
    cout<<lineHead[1];
    for(int i=0;i<SIZE;i++)
        {
if(board[Count][i]=="¡ð")
    cout<<lineMid1[1]<<"¡ð";
else if( board[Count][i]=="¡ñ")
    cout<<lineMid1[1]<<"¡ñ";
else
     cout<<lineMid1[1]<<lineMid2[1];
     }
    cout<<lineMid1[1]<<lineTail[1];
}
void Checker::SetDown()
{
    cout<<lineHead[2];
    for(int i=0;i<SIZE;i++)
 cout<<lineMid1[1]<<lineMid2[2];
 cout<<lineMid1[1]<<lineTail[2];
}
bool Checker:: Setchess(int row,int col,int chess)
 {
     if((row<1)||(row>15)||(col<1)||(col>15)||(chess<0)||(chess>1))return false;
  if(chess==0)board[row-1][col-1]="¡ð";
    if(chess==1)board[row-1][col-1]="¡ñ";
 }
bool Checker:: JudgeWin(char*ch)
{
for(int i=0;i<15;i++)
   {
        for(int j=0;j<15;j++)
{
if(board[i][j]==ch)
{
    int n=j+1;int counter=1;
while((n<15)&&(n>=0)&&(board[i][n]==ch)&&(counter<=5)){n++;counter++;}
    if(counter<5){n=j-1;while((n<15)&&(n>=0)&&(board[i][n]==ch)&&(counter<=5)){n--;counter++;}}
    if(counter==5)return true;

    n=i+1;counter=1;
    while((n<15)&&(n>=0)&&(board[n][j]==ch)&&(counter<=5)){n++;counter++;}
    if(counter<5){n=i-1;while((n<15)&&(n>=0)&&(board[n][j]==ch)&&(counter<=5)){n--;counter++;}}
   if(counter==5)return true;

  int m=i+1; n=j+1;counter=1;
  while((n<SIZE)&&(n>=0)&&(m<SIZE)&&(m>=0)&&(board[m][n]==ch)&&(counter<=5)){n++;m++;counter++;}
    if(counter<5){n=j-1;m=i-1;while((n<SIZE)&&(n>=0)&&(m<SIZE)&&(m>=0)&&(board[m][n]==ch)&&(counter<=5)){n--;m--;counter++;}}
   if(counter==5)return true;

  m=i+1; n=j-1;counter=1;
  while((n<SIZE)&&(n>=0)&&(m<SIZE)&&(m>=0)&&(board[m][n]==ch)&&(counter<=5)){n--;m++;counter++;}
    if(counter<5){n=j+1;m=i-1;while((n<SIZE)&&(n>=0)&&(m<SIZE)&&(m>=0)&&(board[m][n]==ch)&&(counter<=5)){n++;m--;counter++;}}
   if(counter==5)return true;
}
}
   }
   return false;
}
