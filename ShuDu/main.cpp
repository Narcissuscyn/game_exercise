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

     cout<<"��ѡ���ܣ�0-������Ϸ 1-��ֵ 2-�޸�Ԫ��ֵ"<<endl;
     int choice;
     cin>>choice;
while(choice)
 {
         switch(choice)
     {
         case 0:break;
         case 1:
    {

 //  cout<<"��ѡ����������˳�:0 or 1?"<<endl;
  // cin>>way;
  int way=1;
   while(way!=0)
   {
     SD.insert_value();
     SD.display();
     SD.writefile();
   cout<<"��ѡ�������ֵ�����˳�:0 or 1?"<<endl;

   cin>>way;
   }
   break;
    }
     case 2:
    {
         cout<<"������Ҫ�޸�Ԫ�ص��С��С�ֵ��"<<endl;int m,n,q;cin>>m>>n>>q;
         SD.modify(m,n,q);break;
     }


     }
     cout<<"��ѡ���ܣ�0-������Ϸ 1-��ֵ 2-�޸�Ԫ��ֵ"<<endl;
     cin>>choice;
     }
     cout<<"��Ϸ������"<<endl;
    return 0;
}
