#include<iostream>
#include"GoBang.h"
using namespace std;

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
    for(int i=0;i<SIZE;i++){
             cout<<lineMid1[1]<<lineMid2[1];
    for(int j=0;j<15;j++)
{
if(board[i][j]=="¡ð")
    cout<<lineMid1[1]<<"¡ð";
else if(board[i][j]=="¡ñ")
    cout<<lineMid1[1]<<"¡ñ";
else
     cout<<lineMid1[1]<<lineMid2[1];
}
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

int Checker::Search(int x,int y)
{
    if(board[x][y]=="¡ð")return 0;
    if(board[x][y]=="¡ñ")return 1;
}
