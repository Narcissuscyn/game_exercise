#include <iostream>
#include<queue>
#include<stack>
#include<sstream>
#include<fstream>
#include<string>
#include<stdlib.h>
#define Max 1000
#define MAX 1000000
#include"view1.h"

using namespace std;

//边结点的结构体
struct Edge
{
    int VerAdj;/*地点序号，从0开始编号*/
    string name;/*地点名称*/
    int cost;/*路长度，即边的权值*/
    Edge * link;/*指向下一个边结点的指针*/
};
//顶点表中结点的结构体
struct Vertex
{
    int VerNum;/*地点序号*/
    string name;/*地点名称*/
    string Information;/*地点信息介绍*/
    Edge * adjacent;/*边链表的头指针*/
};
//采用邻接表存储的Graph_List类定义
class Graph_List
{
private:
    Vertex * Head;/*顶点表头指针*/
    int graphsize;/*图中当前地点的个数*/
    int maxsize;/*图中地点个数的上限*/
public:
    Graph_List(int m_size,int g_size):graphsize(0)/*图的构造函数*/
    {
        maxsize = m_size;
        graphsize = g_size;
        //用数组实现顶点表，Head指向数组的第一个元素
        Head = new Vertex[maxsize];
        int i;
        for(i=0;i<graphsize;i++)//初始化顶点数组
        {
            Head[i].VerNum = i;
            Head[i].adjacent = NULL;
        }
    }

    ~Graph_List()/*图的析构函数*/
    {
        int i;
        for(i=0;i<graphsize;i++)//删除每个顶点的边链表
        {
            Edge * p = Head[i].adjacent;
            while(p!=NULL)//循环删除
            {
                Head[i].adjacent = p->link;
                delete p;//释放结点的空间
                p = Head[i].adjacent;
            }
        }
        delete[]Head;//释放顶点数组
    }

    Vertex * GetHead()const/*返回顶点表头指针*/
    {
        return Head;
    }

    int NumberOfVertices()const/*返回地图中地点个数*/
    {
        int sum = 0;
        for(int j=0;j<maxsize;j++)
        {
            if(Head[j].name.length()==0)
                continue;
            sum++;
        }
        return sum;
    }

    int NumberOfEdges()const/*返回地图中路的条数*/
    {
        int i;
        int sum = 0;//sum计数器记录路的条数
        for(i=0;i<graphsize;i++)//每个顶点的边链表
        {
            Edge * p = Head[i].adjacent;
            while(p!=NULL)//循环
            {
                sum++;//有一条边计数器加一
                p = p->link;//下一条边
            }
        }
        return sum/2;
    }

    string GetName(int num)/*返回编号所对应地点名字*/
    {
        int i;
        for(i=0;i<graphsize;i++){
                if(Head[i].VerNum==num){//找到编号在顶点表中的位置
                     return Head[i].name;
                }
        }
    }

    int GetWeight(const int & v1,const int & v2)/*查询路信息，返回指定边的权值*/
    {
        int v3=-1,v4=-1;
        for(int i=0;i<NumberOfVertices();i++)
        {
            if(Head[i].VerNum==v1)
                v3 = i;
            if(Head[i].VerNum==v2)
                v4 = i;
        }
        if(v1==v2)
            return 0;
        else if(v3==-1||v4==-1)
        {
            cout<<"您输入的编号有误，编号应为小于当前景点个数的非负整数"<<endl;
            return -1;
        }else
        {
            int i;
            for(i=0;i<graphsize;i++){
                if(Head[i].VerNum==v1)
                {
                    break;
                }
            }
            Edge * p = Head[i].adjacent;//v1的边链表头指针
            while(p!=NULL)
            {
                if(p->VerAdj==v2)//找到所查询的边
                    return p->cost;//返回边的权值，即距离
                p = p->link;
            }
            return 0;//此边不存在，返回0
        }
    }

    void InsertSpot(int num0,string name0,string inf0)/*用做初始化地点信息、添加地点*/
    {
        for(int i=0;i<=graphsize;i++)
        {
            if(Head[i].VerNum == num0)
            {
                Head[i].name = name0;//初始化地点名
                Head[i].Information = inf0;//初始化地点简介
            }
        }
    }

    void InsertEdge(int v1,int v2,int weight)/*初始化时向地图中插入一条路*/
    {
        int k;
        int judge=0;
        for(k=0;k<graphsize;k++)
        {
            if(Head[k].VerNum==v1)
            {
                Edge * p = Head[v1].adjacent;
                Edge * q = new Edge();//将新边插入图中
                q->VerAdj = v2;
                q->cost = weight;
                q->link = NULL;
                if(p==NULL)//若v1的边链表为空，则直接将新边链到边链表的头指针
                {
                    Head[v1].adjacent=q;
                }
                else
                {
                    while(p->link!=NULL)
                    {
                        if(p->VerAdj==v2)//若边的两点已存在，则只需将权值加到边上
                        {
                            p->cost = weight;
                            break;
                        }
                        p = p->link;
                    }
                    if(p->link==NULL)//在起点的边链表中没有找到边中点，则在边链表尾链接新边
                        p->link = q;
                }
            }
        }
    }

    void GetInf(string name0)/*根据名称查询景点信息*/
    {
        int i;
        for(i=0;i<graphsize;i++){
            if(Head[i].name==name0){//找到该地点在顶点数组中的位置
                cout<<"地点编号："<<Head[i].VerNum<<endl;
                cout<<"地点名："<<Head[i].name<<endl;
                cout<<"简介："<<Head[i].Information<<endl;
                break;
            }
        }
        if(i==graphsize){//遍历了顶点数组仍没找到，此时i=graphsize
            cout<<"地图中没有这个地点"<<endl;
        }
    }

    void GetInf(int num)/*根据编号查询景点信息（函数重载）*/
    {
        int i;
        for(i=0;i<graphsize;i++){
            if(Head[i].VerNum==num){//找到该地点在顶点数组中的位置
                cout<<"地点编号："<<Head[i].VerNum<<endl;
                cout<<"地点名："<<Head[i].name<<endl;
                cout<<"简介："<<Head[i].Information<<endl;
                break;
            }
        }
        if(i==graphsize){//遍历了顶点数组仍没找到，此时i=graphsize
            cout<<"地图中没有这个地点"<<endl;
        }
    }

    void DeleteSpot(int &v)/*从地图中删除一个景点*/
    {
        for(int i=0;i<NumberOfVertices();i++){
            if(Head[i].VerNum==v){//找到要删除的顶点
                Edge * p = Head[i].adjacent;
                while(p->link!=NULL){//删除所有和此点相连的边
                    DEdge(p->VerAdj,v);//调用删边函数
                    DEdge(v,p->VerAdj);//调换参数，调用删边函数
                    p = p->link;
                }
                cout<<"地点:"<<GetName(v)<<" 已删除"<<endl;
                Head[i].name = "";
                Head[i].Information = "";
                Head[i].adjacent = NULL;
                break;
            }
        }
    }

    void DEdge(const int &v1,const int &v2)/*删除单向路的实现函数*/
    {
        Edge * p = Head[v1].adjacent;//p指向边起点的边链表头指针
        if(p->VerAdj==v2)//若第一个邻接顶点即为边终点，则直接删除边
        {
            Head[v1].adjacent=p->link;
            delete p;
        }
        if(p->link==NULL)//若此时边链表为空，则直接将边链表头指针赋为空
        {
            Head[v1].adjacent=NULL;
            delete p ;
        }
        while (p->link!=NULL)
        {
            if(p->link->VerAdj==v2)//找到边终点，修改指针
            {
                Edge * q = p->link;
                p->link = q->link;
                delete q;
            }
            else
                p = p->link;
        }
    }

    void DeleteEdge(const int &v1,const int &v2)/*从地图中删除一条路*/
    {
        DEdge(v1,v2);//双向删除
        DEdge(v2,v1);//双向删除
        cout<<GetName(v1)<<" 至 "<<GetName(v2)<<"的路已删除"<<endl;
        cout<<"删除操作后，当前地图中路径条数："<<NumberOfEdges()<<endl;
    }

    void InsertVertex() /*用户添加新景点*/
    {
         Vertex * p = new Vertex;
         cout<<"请输入要添加的景点的信息："<<endl;
         cout<<"请输入景点名称:"<<endl;
         cin>>p->name;
         cout<<"请输入景点编号（请避免和已有编号重复）:";
         cin>>p->VerNum;
         while(p->VerNum<=graphsize-1){
            cout<<"该编号已经存在，请重新输入"<<endl;
            cin>>p->VerNum;
         }
         cout<<"请输入对景点的介绍:"<<endl;
         cin>>p->Information;graphsize++;
         Head[graphsize-1].name = p->name;
         Head[graphsize-1].VerNum = p->VerNum;
         Head[graphsize-1].Information = p->Information;
         Head[graphsize-1].adjacent = NULL;
         cout<<endl;
         cout<<"新景点添加成功!"<<endl;
    }

    void InsertRoad()/*用户添加新路径*/
    {
        int v1,v2,dis;
        int a,b;
        string name1,name2;
        bool flag = true;
        while(flag){
            cout<<"请输入您要添加的道路的起点名称:"<<endl;
            cin>>name1;
            v1=-1;
           for(int i=0;i<graphsize;i++){
                if(Head[i].name==name1){
                    v1 = Head[i].VerNum;
                    a = i;
                    flag = false;
                    break;
                }
            }
            if(v1==-1){
                cout<<"您的输入有误！"<<endl;
            }
        }
        bool  boo = true;
        while(boo){
            cout<<"请输入您要添加的道路的终点名称:"<<endl;
            cin>>name2;
            v2=-1;
            for(int j=0;j<graphsize;j++){
                if(Head[j].name==name2){
                    v2 = Head[j].VerNum;
                    b = j;
                    boo = false;
                    break;
                }
            }
            if(v2==-1){
                cout<<"您的输入有误！"<<endl;
            }
        }
        cout<<"请输入您要添加的道路长度:"<<endl;
        cin>>dis;
        if(GetWeight(v1,v2)>0){
            cout<<"此道路在地图中原本就存在!"<<endl;
        }else{
             Edge * p = new Edge;
             p->name = name2;
             p->VerAdj = v2;
             p->cost = dis;
             p->link = NULL;
             Edge * q = Head[a].adjacent;
             if(q == NULL){
                Head[a].adjacent = p;
             }else{
                while(q->link != NULL){
                   q = q->link;
                }
                q->link = p;
             }
            Edge * g = new Edge;
            g->name = name1;
            g->VerAdj = v1;
            g->cost = dis;
            g->link = NULL;
            Edge * h = Head[b].adjacent;
            if(h==NULL){
                Head[b].adjacent = g;
            }else{
                while(h->link!=NULL){
                    h = h->link;
                }
                h->link = g;
            }

            cout<<name1<<" 和 "<<name2<<" 之间的道路添加成功!"<<endl;
        }
    }

    void Spot(string v){/*查询距离最近的景点*/
        int s=-1;
        int a=0;
        for(int i=0;i<graphsize;i++){
            if(Head[i].name==v){
                s = Head[i].VerNum;
                a = i;
            }
        }
        if(s==-1){
            cout<<"地图中没有该景点，将返回功能菜单，请重新选择!"<<endl;
            return;
        }
         int j=0;
         int minDis =10000;
         Edge * p = Head[a].adjacent;
         int *m = new int[8];
         for(int c=0;c<8;c++){
            m[c]=-1;
         }
         while(p!=NULL){
                if(p->cost<minDis){
                    minDis = p->cost;
                    j=0;
                    while(m[j]!=-1){
                        m[j] = -1;j++;
                    }
                    j=0;
                    m[j] = p->VerAdj;
                    j++;
                }else if(p->cost==minDis){
                    m[j]=p->VerAdj;
                    j++;
                }

                p=p->link;
         }
         cout<<"现在离您最近的景点有:";
         for(int k=0;k<8;k++){
            if(m[k]!=-1){
                cout<<Head[m[k]].name<<" ";
            }
         }
         cout<<endl;
         cout<<"最短距离为:"<<minDis<<"米"<<endl;
    }

    void Print()/*输出地图中所有地点与地点编号的对应表*/
    {
        int j;
        cout<<"\t\t#---------------吉林大学 中心校区---------------#"<<endl;
        cout<<"\t\t\t景点编号\t\t景点名称"<<endl;
        for(j=0;j<maxsize;j++)
        {
            if(Head[j].name.length()==0)
                continue;
            cout<<"\t\t\t"<<Head[j].VerNum<<"\t\t\t"<<Head[j].name<<endl;
        }
        cout<<"\t\t#-----------------------------------------------#"<<endl;
        cout<<endl;
    }

    void Print1()/*修改函数用到的打印*/
    {
         for(int j=0;j<maxsize;j++)
        {
            if(Head[j].name.length()==0)
                continue;
            cout<<"\t\t\t"<<Head[j].VerNum<<"\t\t\t"<<Head[j].name<<endl;
        }
        cout<<endl;
    }

    void Modify()/*修改地图信息*/
    {
        Edge*ptr;

        cout<<"请选择您要修改的信息："<<endl<<endl;
        cout<<"0:退出"<<endl;
        cout<<"1:景点名字"<<endl;
        cout<<"2:两景点间的距离"<<endl;
        cout<<"3:景点的介绍："<<endl;
        cout<<"4:景点编号"<<endl<<endl;

        int n=-1;
        while(n<0||n>4)
        {
            cin>>n;
            if(n<0||n>4)

            cout<<"温馨提示：您输入的编号不对哦，请重新输入："<<endl;
        }
        string spotname;
        if(n!=0){

             cout<<"请输入将要编辑的景点名：";

        cin>>spotname;
        }

        cout<<endl;
        int flag=0;
        switch(n)
        {
            case 0:
                cout<<"退出成功！"<<endl;
                break;
            case 1: {
                cout<<"亲！您要修改成什么名字呢？请输入：";
                string Name;
                cin>>Name;
                for(int i=0;i<graphsize;i++)
                {
                    ptr=Head[i].adjacent;
                    while(ptr!=0)
                    {
                        if(ptr->name==spotname)
                        {
                            ptr->name=Name;
                            flag++;
                        }
                        ptr=ptr->link;

                    }
                    if(Head[i].name==spotname)
                    {
                        Head[i].name=Name;
                        flag++;
                    }
                }
                if(flag==0)
                {
                    cout<<"温馨提示：您输入的景点名不对哦！"<<endl<<endl;
                    return;
                }

                Print1();
                cout<<"恭喜您，修改成功！"<<endl<<endl;
                ptr=0;
                flag=0;
                break;
            }
         case 2:
            {
                cout<<"请输入"<<spotname<<"要到达的景点和两景点间的距离：";
                string n1,n2;
                n1=spotname;
                cin>>n2;
                int d;
                cin>>d;
                int v1=-1,v2=-1;
                for(int k=0;k<graphsize;k++)
                {
                    if(Head[k].name==n1)
                    v1=Head[k].VerNum;
                    if(Head[k].name==n2)
                    v2=Head[k].VerNum;
                }
                if(v1==-1||v2==-1)
                {
                    cout<<"温馨提示：您输入的景点名不对哦！"<<endl<<endl;
                    return;
                }
                InsertEdge(v1,v2,d);
                InsertEdge(v2,v1,d);
                ptr=0;
                cout<<"恭喜您，修改成功！"<<endl;
                break;
            }
        case 3: {
            cout<<"请输入您将修改的景点介绍："<<endl;
            string introduce;
            cin>>introduce;
            for(int i=0;i<graphsize;i++)
            {
                if(Head[i].name==spotname)
                {
                    Head[i].Information=introduce;
                    flag++;
                }
            }
            if(flag==0)
            {
                cout<<"温馨提示：您输入的景点名不对哦！"<<endl<<endl;
                return;
            }
            cout<<"恭喜您，修改成功！"<<endl;
            flag=0;
            break;
        }
        case 4:{
            cout<<"请输入您将修改的编号："<<endl;
            int num;
            cin>>num;
            for(int i=0;i<graphsize;i++)
            {
                ptr=Head[i].adjacent;
                while(ptr!=0)
                {
                    if(ptr->name==spotname)
                    {
                        ptr->VerAdj=num;
                        flag++;
                    }
                    ptr=ptr->link;
                }
                if(Head[i].name==spotname)
                {
                    Head[i].VerNum=num;
                    flag++;
                }
            }
            if(flag==0)
            {
                cout<<"温馨提示：您输入的景点名不对哦！"<<endl<<endl;
                return;
            }
            cout<<"恭喜您，修改成功！"<<endl;
            break;
            }
        }
    }

    void Shortest(int x)/*任意两景点间的最短路径查询*/
    {
        string start,destination;
        if(x==2)
        {
        cout<<"请输入起点名称：";
        cin>>start;
        cout<<endl<<"请输入终点名称：";
        cin>>destination;
        }
        else
        {
            start="东门";
            cout<<endl<<"您现在在东门，请输入终点名称：";
        cin>>destination;
        }
        if(start==destination){cout<<"温馨提示：您输入的终点名和起点名重名，请重新选择功能"<<endl;return;}
        int v1=-1,v2=-1;
        for(int k=0;k<graphsize;k++)
        {
            if(Head[k].name==start)
                v1=k;
            if(Head[k].name==destination)
                v2=k;
        }
        if(v1==-1||v2==-1)
        {
            cout<<"温馨提示：您输入的景点名有误！"<<endl<<endl;
            return;
        }
        int temp,u=v1,ldist;
        int*path=new int[graphsize];
        int *dist=new int[graphsize];
        int *visited=new int[graphsize];
        for(int i=0;i<graphsize;i++)
        {
            path[i]=-1;
            dist[i]=MAX;
            visited[i]=0;
        }
        visited[v1]=1;
        dist[v1]=0;
        Edge*ptr=0;
        for(int i=0;i<graphsize;i++)
        {
            if(Head[i].VerNum==v1)
            {
                ptr=Head[i].adjacent;
                break;
            }
        }
        cout<<endl;
        for(int i=0;i<graphsize-1;i++)
        {
            while(ptr!=0)
            {
                temp=ptr->VerAdj;
                if((visited[temp]!=1)&&(dist[u]+ptr->cost<dist[temp]))
                {
                    dist[temp]=dist[u]+ptr->cost;
                    path[temp]=u;
                }
                ptr=ptr->link;
            }
            ldist=MAX;
            for(int j=0;j<graphsize;j++)
            {
                if((dist[j]>0)&&(dist[j]<ldist)&&(visited[j]==0))
                {
                    ldist=dist[j];
                    u=j;
                }
            }
            visited[u]=1;
            for(int i=0;i<graphsize;i++)
            {
                if(Head[i].VerNum==u)
                {
                    ptr=Head[i].adjacent;
                    break;
                }
            }
        }
        cout<<endl;
        int* shortpath = new int[graphsize];
        int j = 0;
        int i = path[v2];
        while (i != v1)
        {
            shortpath[j++] = i;
            i = path[i];
        }
        cout << "从" << Head[v1].name << "到" << Head[v2].name << "的最短路径为："<<endl<<endl;
        cout << Head[v1].name << "->";
        for (int k = j-1; k >= 0; k--)
        {
            cout << Head[shortpath[k]].name << "->";
        }
        cout << Head[v2].name<<endl;

        for(int i=0;i<graphsize ;i++)
        {
            if(Head[i].name==destination)
            {
                cout<<start<<"到"<<destination<<"的最短距离为："<<dist[i]<<"米"<<endl;
                cout<<"步行时间大约为 "<<dist[i]/50.0<<"分钟"<<endl<<endl;
                break;
            }
        }
    }


void display()/*打印图形化地图*/
{
    ifstream in("map.txt",ios::in);
    int npoint;
    in>>npoint;
    string name[100];
    int _x[100],_y[100],_st[100];
    int style[100];
    for(int i=0;i<npoint;i++)
    {
        in>>name[i];
        in>>_x[i]>>_y[i]>>style[i];
    }
    View v(20,26,_x,_y,style,name,npoint);
    v.Display();
}

};

int main()
{
    Graph_List photo(100,58);//构造一个最大能容纳30个地点、初始有20个地点的地图

    /*读文件初始化点*/
    string file0name = "name.txt";
    ifstream infile(file0name);
    if(!infile)
    {
        cerr<<"can't open "<<file0name<<endl;
        return 1;
    }
    string oneline;
    int num;
    string name,inf;
    while(getline(infile,oneline))
    {
        istringstream s(oneline);
        s>>num;
        s>>name;
        s>>inf;
        photo.InsertSpot(num,name,inf);
    }
    infile.close();

    /*读文件初始化路*/
    string filename = "path.txt";
    ifstream infile2(filename);
    if(!infile2)
    {
        cerr<<"can't open "<<filename<<endl;
        return 1;
    }
    string oneline2;
    while(getline(infile2,oneline2))
    {
        istringstream s(oneline2);
        int startname,endname;
        int cost;
        s>>startname;
        s>>endname;
        s>>cost;
        photo.InsertEdge(startname,endname,cost);
    }
    infile2.close();

    system("COLOR 8b");//改变界面颜色

    /*进入系统*/
    int choice;
    bool isTrue = true;
    cout<<"\t\t\t您好!欢迎使用吉林大学中心校区校园导游系统"<<endl<<endl;
    photo.display();
    cout<<endl<<endl;
    cout<<"\t\t\t吉林大学中心校区地点与地点编号对应表"<<endl;
    photo.Print();
    cout<<"\t\t地图中当前景点个数："<<photo.NumberOfVertices()<<endl;
    cout<<"\t\t地图中当前路径条数："<<photo.NumberOfEdges()<<endl;
    cout<<endl;
    while(isTrue)
    {
         cout<<"\t\t**************************************************"<<endl;
         cout<<"\t\t*       1.查看某景点信息.                        *"<<endl;
         cout<<"\t\t*       2.任意两景点间最短路线查询.              *"<<endl;
         cout<<"\t\t*       3.查询距离您最近的景点.                  *"<<endl;
         cout<<"\t\t*       4.东门到任意景点最短路线查询.            *"<<endl;
         cout<<"\t\t*       5.编辑地图信息.                          *"<<endl;
         cout<<"\t\t*       6.退出导游系统.                          *"<<endl;
         cout<<"\t\t**************************************************"<<endl;

         cout<<"请选择功能："<<endl;
         cin>>choice;
         switch(choice){
            case 1:{
                int a;
                cout <<"请选择:1.按景点名称查询.2.按景点编号查询."<<endl;
                cin>>a;
                switch(a){
                    case 1:{
                        string sname;
                        cout<<"请输入景点名称:"<<endl;
                        cin>>sname;
                        photo.GetInf(sname);
                        break;
                    }
                    case 2:{
                        int num;
                        photo.Print();
                        cout<<"请根据对应表输入景点的编号:"<<endl;
                        cin>>num;
                        photo.GetInf(num);
                        break;
                   }
                    default:{
                        cout<<"请按提示输入"<<endl;
                        break;
                    }
                }
                break;
            }
            case 2:{
                photo.Shortest(choice);
                break;
            }
            case 3:{
                string name;
                cout<<"请输入您现在所在位置:"<<endl;
                cin>>name;
                photo.Spot(name);
                break;
            }
            case 4:{
                photo.Shortest(choice);
                break;
            }
            case 5:{
                int b;
                cout<<"请选择对地图信息的操作:1.添加.2.删除.3.修改."<<endl;
                cin>>b;
                switch(b){
                    case 1:{
                        int c;
                        cout<<"请选择您要添加:1.景点.2.道路."<<endl;
                        cin>>c;
                        if(c==1)
                        {
                            int d;
                            photo.InsertVertex();
                            cout<<"地点与地点编号对应表更新："<<endl;
                            photo.Print();
                            cout<<"请问您是否要对新景点添加一条路径?1.是2.否"<<endl;
                            cin>>d;
                            if(d==1){
                                photo.InsertRoad();
                            }else if(d==2){
                                cout<<"返回主界面!"<<endl;
                            }else{
                                cout<<"请按提示输入"<<endl;
                            }
                        }else if(c==2)
                        {
                           photo.InsertRoad();
                           cout<<endl;
                        }else
                        {
                            cout<<"请按提示输入"<<endl;
                        }
                        break;
                    }
                    case 2:{
                        int d;
                        cout<<"请选择您要删除:1.景点.2.道路"<<endl;
                        cin>>d;
                        if(d==1)
                        {
                            int v0;
                            photo.Print();
                            cout<<"请根据对应表输入您要删除的景点编号:"<<endl;
                            cin>>v0;
                            if(v0>=0&&v0<photo.NumberOfVertices())
                            {
                                photo.DeleteSpot(v0);
                            }
                            else
                            {
                                cout<<"该编号的景点不存在，无法删除"<<endl;
                            }
                        }else if(d==2)
                        {
                           int v3,v4;
                           photo.Print();
                           cout<<"请根据对应表输入您要删除的道路的起点和终点编号:"<<endl;
                           cin>>v3>>v4;
                           if(photo.GetWeight(v3,v4)==0){
                                cout<<photo.GetName(v3)<<" 和 "<<photo.GetName(v4)<<"之间不存在直接路径，无法删除"<<endl;
                           }else{
                                photo.DeleteEdge(v3,v4);
                           }
                        }
                        else
                        {
                            cout<<"请按提示输入"<<endl;
                        }
                        break;
                    }
                    case 3:{
                       photo.Modify();
                       break;
                    }
                    default:{
                        cout<<"请按提示输入"<<endl;
                        break;
                    }
                }
                break;
            }
            case 6:
                cout<<"感谢您使用吉林大学导游系统，再见。"<<endl;
                isTrue = false;
                break;
            default:
                cout<<"未按提示输入，请重新选择功能"<<endl;
                break;
         }
    }
    /*将修改信息写回文件*/
    ofstream outfile;
    outfile.open(file0name);
    if(outfile.is_open())
    {
        for(int i=0;i<photo.NumberOfVertices();i++)
        {
            if(photo.GetHead()[i].adjacent==NULL)
                continue;
            else
            {
                outfile<<photo.GetHead()[i].VerNum;
                outfile<<" ";
                outfile<<photo.GetHead()[i].name;
                outfile<<" ";
                outfile<<photo.GetHead()[i].Information<<endl;
            }
        }
        cout<<"景点信息已保存"<<endl;
        outfile.close();
    }
    else
    {
        cerr<<"can't open"<<file0name<<endl;
    }

    ofstream outfile2;
    outfile2.open(filename);
    if(outfile2.is_open())
    {
        for(int i=0;i<photo.NumberOfVertices();i++)
        {
            if(photo.GetHead()[i].adjacent==NULL)
                continue;
            else
            {
                Edge * p = photo.GetHead()[i].adjacent;
                while(p!=NULL)
                {
                    outfile2<<photo.GetHead()[i].VerNum;
                    outfile2<<" ";
                    outfile2<<p->VerAdj;
                    outfile2<<" ";
                    outfile2<<p->cost<<endl;
                    p = p->link;
                }
            }
        }
        cout<<"路径信息已保存"<<endl;
        outfile2.close();
    }
    else
    {
        cerr<<"can't open"<<filename<<endl;
    }

    return 0;
}


/*
实验内容及要求：
设计吉林大学中心校区校园导游系统，完成校区内建筑物、道路等基本信息的维护，并为来访客人提供查询服务。
（1）记录校区内各建筑物的信息：名称、代号、简介、所在位置等；
（2）记录景点之间的道路信息，包括：两点距离、所需时间等相关信息；
（3）数据的输入可以是键盘输入或文件导入；
（4）提供对校园景点信息的编辑（如：添加、删除、修改等）的功能；
（5）为来访客人提供图中任意景点相关信息的查询（可提供多种查询方式）；
（6）为来访客人提供从校门口到图中任意景点的问路查询，返回距离最短的行走方案；
（7）为来访客人提供图中任意景点间的问路查询，返回距离最短的行走方案；
*/























