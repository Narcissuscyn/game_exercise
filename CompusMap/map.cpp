#include<iostream>
#include<string>
#include<fstream>
#include"map.h"
#define MAX 58
#define COST 50000
#include<queue>
int visited[MAX];
using namespace std;
Map::Map()
{
    MapSize=5;
ifstream infile1,infile2;
int num,edge;
string name,introduce;
infile1.open("NumberScource.txt",ios::in);
infile2.open("EdgeScource.txt",ios::in);
if((!infile1)||(!infile2))
{
    cout<<"open error!"<<endl;
    return;
}
Head=new VerHead[MAX];
int i=0;
while(!infile1.eof())
{


    infile1>>num>>name>>introduce;
    Head[i].Introduce=introduce;
    Head[i].Name=name;
    Head[i].VerNumber=num;
    Head[i].link=0;
    i++;
}
while(!infile2.eof())
{
      int x,y,d;
    infile2>>x>>y>>d;
    InseartEdge(x,y,d);
    InseartEdge(y,x,d);
}
infile1.close();
infile2.close();
cout<<"success!"<<endl;
}
 void Map::InseartEdge(int& x,int& y,int& d)const
 {
     if(x>MapSize||y>MapSize)
     {
         cout<<"overflow the Mapsize!"<<endl;
         return;
     }
     VerEdge*temp=new VerEdge;
     temp->VerName=y;
     temp->cost=d;
     temp->next=0;
     VerEdge*ptr;
     int i=0;
     while(Head[i].VerNumber!=x)
     {
        i++;
     }
     ptr=Head[i].link;
     if(ptr!=0)
     {
         while(ptr->next!=0)
            ptr=ptr->next;
            ptr->next=temp;
     }
     else Head[i].link=temp;
 }
void Map::SearchMap(int x)
{
    cout<<"请选择遍历景点的方式：0-退出 1-DFS 2-BFS"<<endl;
int way;
cin>>way;
if(way<0||way>2)
{
    cout<<"输入有误！"<<endl;
    return;
}
switch(way)
{
    case 0:break;
    case 1:{DFS(1);break;}
    case 2:{BFS(1);break;}
}
}

bool Map::DFS(int x)
{
visited[x]=1;
int i=0;
while(Head[i].VerNumber!=x)
        i++;
VerEdge*ptr;
ptr=Head[i].link;
       cout<<x<<" ";
  while(ptr!=0)
       {
           if(visited[ptr->VerName]!=1)
              DFS(ptr->VerName);
              ptr=ptr->next;
       }
return true;
    }

void Map::y()
{
VerEdge*ptr;
int i=0;
while(i<MapSize)
{
    ptr=Head[i].link;
    cout<<Head[i].VerNumber<<"-"<<Head[i].Name<<":";
    while(ptr!=0)
    {
        cout<<ptr->VerName<<"-"<<GetName(ptr->VerName);

        ptr=ptr->next;
    }
    cout<<endl;
    i++;
}
}
bool Map::BFS(int x)
{
    int visit[MapSize];
    for(int i=0;i<=MapSize;i++)
    {
        visit[i]=0;
    }

        queue<int>Q;
        Q.push(x);
        VerEdge*temp;
      int i=0;
        while(!Q.empty())
        {
           int y=Q.front();
           Q.pop();
           if(visit[y]!=1)
            cout<<y<<" ";
           visit[y]=1;
           temp=Head[i].link;
           while(temp!=0)
           {
               Q.push(temp->VerName);
               temp=temp->next;
           }
        i++;
        }

}
string Map::GetName(int x)
{
    int i=0;
    while(Head[i].VerNumber!=x)
    {
        i++;
    }
    return Head[i].Name;
}
void Map::DisplaySport(int x)
{
    cout<<"                           scene display"<<endl;
    int i=0;
    while((i<MapSize)&&(Head[i].VerNumber!=x))
    {
        i++;
    }
        cout<<"景点编号："<<x<<endl;
        cout<<"景点名称："<<Head[i].Name<<endl;

    cout<<"景点介绍："<<Head[i].Introduce<<endl;

}
void Map::DeleteSport(int x)
{
    VerEdge*temp,*ptr;
    int k=0;
    while(k<MapSize)
    {
        ptr=Head[k].link;
        temp=ptr;
        if(ptr==0){k++;continue;}
        if(ptr!=0)
        {
            if(ptr->VerName==x)
                Head[k].link=ptr->next;
            else
            {
                while(ptr!=0)
                {
                    if(ptr->VerName==x)break;
                    temp=ptr;
                    ptr=ptr->next;
                }
                if(ptr!=0)
                {
                    temp->next=ptr->next;
                    delete ptr;
                }
            }

        }
        k++;
    }
    int i=0;
    while(Head[i].VerNumber!=x)i++;
    temp=Head[i].link;
    ptr=temp;
    while(temp!=0)
    {
        ptr=temp;
        temp=temp->next;
        delete ptr;
        ptr=temp;
   }
    while(i<MapSize)
    {
        Head[i].link=Head[i+1].link;
        Head[i].VerNumber=Head[i+1].VerNumber;
        Head[i].Name=Head[i+1].Name;
    i++;
    }
    MapSize--;
    cout<<"删除景点"<<x<<" 成功！ "<<endl;
}
void Map::AddSport()
{
    cout<<"请输入您要添加的景点名："<<endl;
    string name;
    cin>>name;
    MapSize++;
    Head[MapSize-1].VerNumber=MapSize;
    Head[MapSize-1].Name=name;
    cout<<"景点"<<name<<"添加成功！"<<endl;
}
void Map::DeleteEdge()
{
    cout<<"请输入您要删除的起点和终点："<<endl;
    string name1,name2;
    int num1,num2;
cin>>name1>>name2;
int i,j;
for(i=0;i<MapSize;i++)
{
    if(Head[i].Name==name1){num1=Head[i].VerNumber;break;}
}
for(j=0;j<MapSize;j++)
{
    if(Head[j].Name==name2){num2=Head[j].VerNumber;break;}
}
if(Head[i].Name!=name1)
{
    cout<<"没有景点"<<name1<<endl;
    return;
}
if(Head[j].Name!=name2)
{
    cout<<"没有景点"<<name2<<endl;
    return;
}
VerEdge*ptr=0,*temp=0;
ptr=Head[i].link;
if(ptr==0)
{
    cout<<"此路径不存在!"<<endl;
    return;
}
else
{
    if((ptr->VerName)==num2)
    {
        Head[i].link=ptr->next;
        delete ptr;
        return;
    }
    while(ptr!=0)
    {
        if((ptr->VerName)==num2)break;
        temp=ptr;
        ptr=ptr->next;
    }

    if(ptr!=0)
    {
        temp->next=ptr->next;
        delete ptr;
    }
    else{cout<<"此路径不存在！"<<endl;return;}
}
cout<<"删除"<<name1<<"-"<<name2<<"之间的路径成功！"<<endl;
}
int Map::GetDistance(int x,int y)
{
    int i=0;
    while(Head[i].VerNumber!=x)
        i++;
        if(i>=MapSize){cout<<"没有此路径！"<<endl;return 0;}
    VerEdge*temp=0;
    temp=Head[i].link;
    while(temp!=0)
    {
        if(temp->VerName==y)break;
        temp=temp->next;
    }
    if(temp->VerName==y)
        {
            return temp->cost;
        }
        else{cout<<"没有此路径！"<<endl;
        return 0;}
}
void Map::Display(int x)
{

    switch(x)
    {
    case 0:break;
    case 1:{
        cout <<"请输入您要查询的景点名："<<endl;
        string name;
        cin>>name;
        int i=0;
        while((Head[i].Name!=name)&&(i<MapSize))
        {
            i++;
        }
        if(i>=MapSize)
            {
                cout<<"没有此景点！"<<endl;
        return;
        }
        int x=Head[i].VerNumber;
        DisplaySport(x);
        break;
        }
    case 2:
        {
          ShortestPath();
            break;
        }
    case 3:
        {
            cout<<"请输入修改密码："<<endl;
            string code,str="123456";
            cin>>code;
            if(code!=str){cout<<"修改密码错误，无法修改！"<<endl;return;}
        cout<<"请输入您要修改的信息：0-退出 1-修改景点信息 2-修改道路信息 "<<endl;
        int way;
        cin>>way;
        switch(way)
        {
        case 0:break;
        case 1:
            {
                 Modify();
                 break;
        }
        case 2:
            {cout<<"请输入您要修改的路径顶点和路径长度：";
            string name1,name2;int d;
            cin>>name1>>name2>>d;
         ModifyRoad(name1,name2,d);
         ModifyRoad(name2,name1,d);
          break;
           }
        }
        break;
    }


}
}
void Map::ShortestPath()
{
    cout<<"请输入您要查询的起点和终点："<<endl;
    string name1,name2;
    int num1,num2;
    cin>>name1>>name2;
    int path[MapSize];
    int visit[MapSize];
    int dist[MapSize];
    for(int i=0;i<MapSize;i++)
    {
        visit[i]=0;
        path[i]=0;
        dist[i]=COST;
    }
    int i=0;
    while((Head[i].Name!=name1)&&(i<MapSize))i++;
    if(i<MapSize)num1=Head[i].VerNumber;
    i=0;
    while((Head[i].Name!=name2)&&(i<MapSize))i++;
    if(i<MapSize)num2=Head[i].VerNumber;
    int ldist;

}

void Map::Modify()
{
        char ch;
        cout<<"请输入您要修改的景点名称:"<<endl;
        string name;
        cin>>name;
        int i=0;
for(i=0;i<MapSize;i++)
{
    if(Head[i].Name==name)
        break;
}

        if(i>=MapSize){cout<<"没有此景点！"<<endl;return;}
        int num3=Head[i].VerNumber;
        cout<<"是否修改景点的名字：Y or N"<<endl;
        cin>>ch;
    if((ch!='Y')&&(ch!='N'))
    {cout<<"输入有误！"<<endl;return;}
    if(ch=='N')return;
     VerEdge*temp=0;string name1;
    if(ch=='Y')
    {
        cout<<"输入修改后的名称："<<endl;
        cin>>name1;
        Head[i].Name=name1;
       int j=0;
        while(j<MapSize)
        {
            temp=Head[j].link;
            while(temp!=0)
            {
                if(temp->VerName==num3)temp->Name=name1;
                temp=temp->next;
            }
            j++;
        }

    }
     cout<<"是否修改景点的编号：Y or N"<<endl;
     cin>>ch;
     if((ch!='Y')&&(ch!='N'))
    {cout<<"输入有误！"<<endl;return;}
    int num;
    if(ch=='Y')
     {
         cout<<"请输入修改后的编号：";

         cin>>num;
         Head[i].VerNumber=num;
          int k=0;
        while(k<MapSize)
        {
            temp=Head[k].link;
            while(temp!=0)
            {
                if(temp->VerName==num3)temp->VerName=num;
                temp=temp->next;
            }
            k++;
        }
     }
     cout<<"修改成功！"<<endl;
     DisplaySport(num);
}

void Map::ModifyRoad(const string name1,const string name2,int d)
{
int i=0,j=0;
int num1,num2;
while((Head[i].Name!=name1)&&(i<MapSize))
{
    i++;

}
num1=Head[i].VerNumber;
while((Head[j].Name!=name2)&&(j<MapSize))
{
    j++;

}
 num2=Head[j].VerNumber;
if((i>MapSize)||(j>MapSize))
{
    cout<<"没有此景点！"<<endl;return;
}
VerEdge*temp=0;
temp=Head[i].link;
while(temp!=0)
{
    if(temp->VerName==num2)
    {
        temp->cost=d;
        return;
          }
temp=temp->next;
}
cout<<"没有此路径！"<<endl;
}
