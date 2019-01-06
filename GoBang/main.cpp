#include<iostream>
using namespace std;
#include"GoBang.h"
int main()
{
  Checker*game;
  game=new ManGB;
game->Setchess(2,6,0);
game->Setchess(3,5,1);
game->Setchess(4,4,1);
game->Setchess(5,3,1);
game->Setchess(6,2,1);
//game->Setchess(5,7,1);
//game->Setchess(2,5,0);
//game->Setchess(5,5,1);
//game->Setchess(6,5,0);
game->Display();
//cout<<game->JudgeWin(game->GetChess2())<<endl;

    return 0;
}
