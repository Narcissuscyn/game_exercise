#include <iostream>
#include<iomanip>
#include"ShuDu.h"
using namespace std;
//enum choice{Stop,Continue};
int main()
{
     ShuDu SD;
     SD.create();
     SD.display();

     cout<<"请选择功能：0-结束游戏 1-填值 2-修改元素值"<<endl;
     int choice;
     cin>>choice;
while(choice)
 {
         switch(choice)
     {
         case 0:break;
         case 1:
    {

 //  cout<<"请选择继续还是退出:0 or 1?"<<endl;
  // cin>>way;
  int way=1;
   while(way!=0)
   {
     SD.insert_value();
     SD.display();
     SD.writefile();
   cout<<"请选择继续填值还是退出:0 or 1?"<<endl;

   cin>>way;
   }
   break;
    }
     case 2:
    {
         cout<<"输入您要修改元素的行、列、值："<<endl;int m,n,q;cin>>m>>n>>q;
         SD.modify(m,n,q);break;
     }


     }
     cout<<"请选择功能：0-结束游戏 1-填值 2-修改元素值"<<endl;
     cin>>choice;
     }
     cout<<"游戏结束！"<<endl;
    return 0;
}
