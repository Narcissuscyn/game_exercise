#include <iostream>
#include"Game.h"
using namespace std;

int main()
{

Game G;
G.set_number();
G.get_a(G);
char choice;
cin>>choice;
while(choice!='N')
{
     switch(choice)
     {
         case 'A':{G.set_left();break;}
         case 'D':{G.set_right();break;}
         case 'W':{G.set_up();break;}
         case 'S':{G.set_down();break;}
     }
     if(G.judge_win()){cout<<"you win! game over!"<<endl;return 0;}

     G.get_a(G);

     if(G.judge_full()){cout<<endl<<"you loss! game over!"<<endl;return 0;}
cin>>choice;
}
    return 0;
}
