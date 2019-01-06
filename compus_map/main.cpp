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

//�߽��Ľṹ��
struct Edge
{
    int VerAdj;/*�ص���ţ���0��ʼ���*/
    string name;/*�ص�����*/
    int cost;/*·���ȣ����ߵ�Ȩֵ*/
    Edge * link;/*ָ����һ���߽���ָ��*/
};
//������н��Ľṹ��
struct Vertex
{
    int VerNum;/*�ص����*/
    string name;/*�ص�����*/
    string Information;/*�ص���Ϣ����*/
    Edge * adjacent;/*�������ͷָ��*/
};
//�����ڽӱ�洢��Graph_List�ඨ��
class Graph_List
{
private:
    Vertex * Head;/*�����ͷָ��*/
    int graphsize;/*ͼ�е�ǰ�ص�ĸ���*/
    int maxsize;/*ͼ�еص����������*/
public:
    Graph_List(int m_size,int g_size):graphsize(0)/*ͼ�Ĺ��캯��*/
    {
        maxsize = m_size;
        graphsize = g_size;
        //������ʵ�ֶ����Headָ������ĵ�һ��Ԫ��
        Head = new Vertex[maxsize];
        int i;
        for(i=0;i<graphsize;i++)//��ʼ����������
        {
            Head[i].VerNum = i;
            Head[i].adjacent = NULL;
        }
    }

    ~Graph_List()/*ͼ����������*/
    {
        int i;
        for(i=0;i<graphsize;i++)//ɾ��ÿ������ı�����
        {
            Edge * p = Head[i].adjacent;
            while(p!=NULL)//ѭ��ɾ��
            {
                Head[i].adjacent = p->link;
                delete p;//�ͷŽ��Ŀռ�
                p = Head[i].adjacent;
            }
        }
        delete[]Head;//�ͷŶ�������
    }

    Vertex * GetHead()const/*���ض����ͷָ��*/
    {
        return Head;
    }

    int NumberOfVertices()const/*���ص�ͼ�еص����*/
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

    int NumberOfEdges()const/*���ص�ͼ��·������*/
    {
        int i;
        int sum = 0;//sum��������¼·������
        for(i=0;i<graphsize;i++)//ÿ������ı�����
        {
            Edge * p = Head[i].adjacent;
            while(p!=NULL)//ѭ��
            {
                sum++;//��һ���߼�������һ
                p = p->link;//��һ����
            }
        }
        return sum/2;
    }

    string GetName(int num)/*���ر������Ӧ�ص�����*/
    {
        int i;
        for(i=0;i<graphsize;i++){
                if(Head[i].VerNum==num){//�ҵ�����ڶ�����е�λ��
                     return Head[i].name;
                }
        }
    }

    int GetWeight(const int & v1,const int & v2)/*��ѯ·��Ϣ������ָ���ߵ�Ȩֵ*/
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
            cout<<"������ı�����󣬱��ӦΪС�ڵ�ǰ��������ķǸ�����"<<endl;
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
            Edge * p = Head[i].adjacent;//v1�ı�����ͷָ��
            while(p!=NULL)
            {
                if(p->VerAdj==v2)//�ҵ�����ѯ�ı�
                    return p->cost;//���رߵ�Ȩֵ��������
                p = p->link;
            }
            return 0;//�˱߲����ڣ�����0
        }
    }

    void InsertSpot(int num0,string name0,string inf0)/*������ʼ���ص���Ϣ����ӵص�*/
    {
        for(int i=0;i<=graphsize;i++)
        {
            if(Head[i].VerNum == num0)
            {
                Head[i].name = name0;//��ʼ���ص���
                Head[i].Information = inf0;//��ʼ���ص���
            }
        }
    }

    void InsertEdge(int v1,int v2,int weight)/*��ʼ��ʱ���ͼ�в���һ��·*/
    {
        int k;
        int judge=0;
        for(k=0;k<graphsize;k++)
        {
            if(Head[k].VerNum==v1)
            {
                Edge * p = Head[v1].adjacent;
                Edge * q = new Edge();//���±߲���ͼ��
                q->VerAdj = v2;
                q->cost = weight;
                q->link = NULL;
                if(p==NULL)//��v1�ı�����Ϊ�գ���ֱ�ӽ��±������������ͷָ��
                {
                    Head[v1].adjacent=q;
                }
                else
                {
                    while(p->link!=NULL)
                    {
                        if(p->VerAdj==v2)//���ߵ������Ѵ��ڣ���ֻ�轫Ȩֵ�ӵ�����
                        {
                            p->cost = weight;
                            break;
                        }
                        p = p->link;
                    }
                    if(p->link==NULL)//�����ı�������û���ҵ����е㣬���ڱ�����β�����±�
                        p->link = q;
                }
            }
        }
    }

    void GetInf(string name0)/*�������Ʋ�ѯ������Ϣ*/
    {
        int i;
        for(i=0;i<graphsize;i++){
            if(Head[i].name==name0){//�ҵ��õص��ڶ��������е�λ��
                cout<<"�ص��ţ�"<<Head[i].VerNum<<endl;
                cout<<"�ص�����"<<Head[i].name<<endl;
                cout<<"��飺"<<Head[i].Information<<endl;
                break;
            }
        }
        if(i==graphsize){//�����˶���������û�ҵ�����ʱi=graphsize
            cout<<"��ͼ��û������ص�"<<endl;
        }
    }

    void GetInf(int num)/*���ݱ�Ų�ѯ������Ϣ���������أ�*/
    {
        int i;
        for(i=0;i<graphsize;i++){
            if(Head[i].VerNum==num){//�ҵ��õص��ڶ��������е�λ��
                cout<<"�ص��ţ�"<<Head[i].VerNum<<endl;
                cout<<"�ص�����"<<Head[i].name<<endl;
                cout<<"��飺"<<Head[i].Information<<endl;
                break;
            }
        }
        if(i==graphsize){//�����˶���������û�ҵ�����ʱi=graphsize
            cout<<"��ͼ��û������ص�"<<endl;
        }
    }

    void DeleteSpot(int &v)/*�ӵ�ͼ��ɾ��һ������*/
    {
        for(int i=0;i<NumberOfVertices();i++){
            if(Head[i].VerNum==v){//�ҵ�Ҫɾ���Ķ���
                Edge * p = Head[i].adjacent;
                while(p->link!=NULL){//ɾ�����кʹ˵������ı�
                    DEdge(p->VerAdj,v);//����ɾ�ߺ���
                    DEdge(v,p->VerAdj);//��������������ɾ�ߺ���
                    p = p->link;
                }
                cout<<"�ص�:"<<GetName(v)<<" ��ɾ��"<<endl;
                Head[i].name = "";
                Head[i].Information = "";
                Head[i].adjacent = NULL;
                break;
            }
        }
    }

    void DEdge(const int &v1,const int &v2)/*ɾ������·��ʵ�ֺ���*/
    {
        Edge * p = Head[v1].adjacent;//pָ������ı�����ͷָ��
        if(p->VerAdj==v2)//����һ���ڽӶ��㼴Ϊ���յ㣬��ֱ��ɾ����
        {
            Head[v1].adjacent=p->link;
            delete p;
        }
        if(p->link==NULL)//����ʱ������Ϊ�գ���ֱ�ӽ�������ͷָ�븳Ϊ��
        {
            Head[v1].adjacent=NULL;
            delete p ;
        }
        while (p->link!=NULL)
        {
            if(p->link->VerAdj==v2)//�ҵ����յ㣬�޸�ָ��
            {
                Edge * q = p->link;
                p->link = q->link;
                delete q;
            }
            else
                p = p->link;
        }
    }

    void DeleteEdge(const int &v1,const int &v2)/*�ӵ�ͼ��ɾ��һ��·*/
    {
        DEdge(v1,v2);//˫��ɾ��
        DEdge(v2,v1);//˫��ɾ��
        cout<<GetName(v1)<<" �� "<<GetName(v2)<<"��·��ɾ��"<<endl;
        cout<<"ɾ�������󣬵�ǰ��ͼ��·��������"<<NumberOfEdges()<<endl;
    }

    void InsertVertex() /*�û�����¾���*/
    {
         Vertex * p = new Vertex;
         cout<<"������Ҫ��ӵľ������Ϣ��"<<endl;
         cout<<"�����뾰������:"<<endl;
         cin>>p->name;
         cout<<"�����뾰���ţ����������б���ظ���:";
         cin>>p->VerNum;
         while(p->VerNum<=graphsize-1){
            cout<<"�ñ���Ѿ����ڣ�����������"<<endl;
            cin>>p->VerNum;
         }
         cout<<"������Ծ���Ľ���:"<<endl;
         cin>>p->Information;graphsize++;
         Head[graphsize-1].name = p->name;
         Head[graphsize-1].VerNum = p->VerNum;
         Head[graphsize-1].Information = p->Information;
         Head[graphsize-1].adjacent = NULL;
         cout<<endl;
         cout<<"�¾�����ӳɹ�!"<<endl;
    }

    void InsertRoad()/*�û������·��*/
    {
        int v1,v2,dis;
        int a,b;
        string name1,name2;
        bool flag = true;
        while(flag){
            cout<<"��������Ҫ��ӵĵ�·���������:"<<endl;
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
                cout<<"������������"<<endl;
            }
        }
        bool  boo = true;
        while(boo){
            cout<<"��������Ҫ��ӵĵ�·���յ�����:"<<endl;
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
                cout<<"������������"<<endl;
            }
        }
        cout<<"��������Ҫ��ӵĵ�·����:"<<endl;
        cin>>dis;
        if(GetWeight(v1,v2)>0){
            cout<<"�˵�·�ڵ�ͼ��ԭ���ʹ���!"<<endl;
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

            cout<<name1<<" �� "<<name2<<" ֮��ĵ�·��ӳɹ�!"<<endl;
        }
    }

    void Spot(string v){/*��ѯ��������ľ���*/
        int s=-1;
        int a=0;
        for(int i=0;i<graphsize;i++){
            if(Head[i].name==v){
                s = Head[i].VerNum;
                a = i;
            }
        }
        if(s==-1){
            cout<<"��ͼ��û�иþ��㣬�����ع��ܲ˵���������ѡ��!"<<endl;
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
         cout<<"������������ľ�����:";
         for(int k=0;k<8;k++){
            if(m[k]!=-1){
                cout<<Head[m[k]].name<<" ";
            }
         }
         cout<<endl;
         cout<<"��̾���Ϊ:"<<minDis<<"��"<<endl;
    }

    void Print()/*�����ͼ�����еص���ص��ŵĶ�Ӧ��*/
    {
        int j;
        cout<<"\t\t#---------------���ִ�ѧ ����У��---------------#"<<endl;
        cout<<"\t\t\t������\t\t��������"<<endl;
        for(j=0;j<maxsize;j++)
        {
            if(Head[j].name.length()==0)
                continue;
            cout<<"\t\t\t"<<Head[j].VerNum<<"\t\t\t"<<Head[j].name<<endl;
        }
        cout<<"\t\t#-----------------------------------------------#"<<endl;
        cout<<endl;
    }

    void Print1()/*�޸ĺ����õ��Ĵ�ӡ*/
    {
         for(int j=0;j<maxsize;j++)
        {
            if(Head[j].name.length()==0)
                continue;
            cout<<"\t\t\t"<<Head[j].VerNum<<"\t\t\t"<<Head[j].name<<endl;
        }
        cout<<endl;
    }

    void Modify()/*�޸ĵ�ͼ��Ϣ*/
    {
        Edge*ptr;

        cout<<"��ѡ����Ҫ�޸ĵ���Ϣ��"<<endl<<endl;
        cout<<"0:�˳�"<<endl;
        cout<<"1:��������"<<endl;
        cout<<"2:�������ľ���"<<endl;
        cout<<"3:����Ľ��ܣ�"<<endl;
        cout<<"4:������"<<endl<<endl;

        int n=-1;
        while(n<0||n>4)
        {
            cin>>n;
            if(n<0||n>4)

            cout<<"��ܰ��ʾ��������ı�Ų���Ŷ�����������룺"<<endl;
        }
        string spotname;
        if(n!=0){

             cout<<"�����뽫Ҫ�༭�ľ�������";

        cin>>spotname;
        }

        cout<<endl;
        int flag=0;
        switch(n)
        {
            case 0:
                cout<<"�˳��ɹ���"<<endl;
                break;
            case 1: {
                cout<<"�ף���Ҫ�޸ĳ�ʲô�����أ������룺";
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
                    cout<<"��ܰ��ʾ��������ľ���������Ŷ��"<<endl<<endl;
                    return;
                }

                Print1();
                cout<<"��ϲ�����޸ĳɹ���"<<endl<<endl;
                ptr=0;
                flag=0;
                break;
            }
         case 2:
            {
                cout<<"������"<<spotname<<"Ҫ����ľ�����������ľ��룺";
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
                    cout<<"��ܰ��ʾ��������ľ���������Ŷ��"<<endl<<endl;
                    return;
                }
                InsertEdge(v1,v2,d);
                InsertEdge(v2,v1,d);
                ptr=0;
                cout<<"��ϲ�����޸ĳɹ���"<<endl;
                break;
            }
        case 3: {
            cout<<"�����������޸ĵľ�����ܣ�"<<endl;
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
                cout<<"��ܰ��ʾ��������ľ���������Ŷ��"<<endl<<endl;
                return;
            }
            cout<<"��ϲ�����޸ĳɹ���"<<endl;
            flag=0;
            break;
        }
        case 4:{
            cout<<"�����������޸ĵı�ţ�"<<endl;
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
                cout<<"��ܰ��ʾ��������ľ���������Ŷ��"<<endl<<endl;
                return;
            }
            cout<<"��ϲ�����޸ĳɹ���"<<endl;
            break;
            }
        }
    }

    void Shortest(int x)/*���������������·����ѯ*/
    {
        string start,destination;
        if(x==2)
        {
        cout<<"������������ƣ�";
        cin>>start;
        cout<<endl<<"�������յ����ƣ�";
        cin>>destination;
        }
        else
        {
            start="����";
            cout<<endl<<"�������ڶ��ţ��������յ����ƣ�";
        cin>>destination;
        }
        if(start==destination){cout<<"��ܰ��ʾ����������յ����������������������ѡ����"<<endl;return;}
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
            cout<<"��ܰ��ʾ��������ľ���������"<<endl<<endl;
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
        cout << "��" << Head[v1].name << "��" << Head[v2].name << "�����·��Ϊ��"<<endl<<endl;
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
                cout<<start<<"��"<<destination<<"����̾���Ϊ��"<<dist[i]<<"��"<<endl;
                cout<<"����ʱ���ԼΪ "<<dist[i]/50.0<<"����"<<endl<<endl;
                break;
            }
        }
    }


void display()/*��ӡͼ�λ���ͼ*/
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
    Graph_List photo(100,58);//����һ�����������30���ص㡢��ʼ��20���ص�ĵ�ͼ

    /*���ļ���ʼ����*/
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

    /*���ļ���ʼ��·*/
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

    system("COLOR 8b");//�ı������ɫ

    /*����ϵͳ*/
    int choice;
    bool isTrue = true;
    cout<<"\t\t\t����!��ӭʹ�ü��ִ�ѧ����У��У԰����ϵͳ"<<endl<<endl;
    photo.display();
    cout<<endl<<endl;
    cout<<"\t\t\t���ִ�ѧ����У���ص���ص��Ŷ�Ӧ��"<<endl;
    photo.Print();
    cout<<"\t\t��ͼ�е�ǰ���������"<<photo.NumberOfVertices()<<endl;
    cout<<"\t\t��ͼ�е�ǰ·��������"<<photo.NumberOfEdges()<<endl;
    cout<<endl;
    while(isTrue)
    {
         cout<<"\t\t**************************************************"<<endl;
         cout<<"\t\t*       1.�鿴ĳ������Ϣ.                        *"<<endl;
         cout<<"\t\t*       2.��������������·�߲�ѯ.              *"<<endl;
         cout<<"\t\t*       3.��ѯ����������ľ���.                  *"<<endl;
         cout<<"\t\t*       4.���ŵ����⾰�����·�߲�ѯ.            *"<<endl;
         cout<<"\t\t*       5.�༭��ͼ��Ϣ.                          *"<<endl;
         cout<<"\t\t*       6.�˳�����ϵͳ.                          *"<<endl;
         cout<<"\t\t**************************************************"<<endl;

         cout<<"��ѡ���ܣ�"<<endl;
         cin>>choice;
         switch(choice){
            case 1:{
                int a;
                cout <<"��ѡ��:1.���������Ʋ�ѯ.2.�������Ų�ѯ."<<endl;
                cin>>a;
                switch(a){
                    case 1:{
                        string sname;
                        cout<<"�����뾰������:"<<endl;
                        cin>>sname;
                        photo.GetInf(sname);
                        break;
                    }
                    case 2:{
                        int num;
                        photo.Print();
                        cout<<"����ݶ�Ӧ�����뾰��ı��:"<<endl;
                        cin>>num;
                        photo.GetInf(num);
                        break;
                   }
                    default:{
                        cout<<"�밴��ʾ����"<<endl;
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
                cout<<"����������������λ��:"<<endl;
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
                cout<<"��ѡ��Ե�ͼ��Ϣ�Ĳ���:1.���.2.ɾ��.3.�޸�."<<endl;
                cin>>b;
                switch(b){
                    case 1:{
                        int c;
                        cout<<"��ѡ����Ҫ���:1.����.2.��·."<<endl;
                        cin>>c;
                        if(c==1)
                        {
                            int d;
                            photo.InsertVertex();
                            cout<<"�ص���ص��Ŷ�Ӧ����£�"<<endl;
                            photo.Print();
                            cout<<"�������Ƿ�Ҫ���¾������һ��·��?1.��2.��"<<endl;
                            cin>>d;
                            if(d==1){
                                photo.InsertRoad();
                            }else if(d==2){
                                cout<<"����������!"<<endl;
                            }else{
                                cout<<"�밴��ʾ����"<<endl;
                            }
                        }else if(c==2)
                        {
                           photo.InsertRoad();
                           cout<<endl;
                        }else
                        {
                            cout<<"�밴��ʾ����"<<endl;
                        }
                        break;
                    }
                    case 2:{
                        int d;
                        cout<<"��ѡ����Ҫɾ��:1.����.2.��·"<<endl;
                        cin>>d;
                        if(d==1)
                        {
                            int v0;
                            photo.Print();
                            cout<<"����ݶ�Ӧ��������Ҫɾ���ľ�����:"<<endl;
                            cin>>v0;
                            if(v0>=0&&v0<photo.NumberOfVertices())
                            {
                                photo.DeleteSpot(v0);
                            }
                            else
                            {
                                cout<<"�ñ�ŵľ��㲻���ڣ��޷�ɾ��"<<endl;
                            }
                        }else if(d==2)
                        {
                           int v3,v4;
                           photo.Print();
                           cout<<"����ݶ�Ӧ��������Ҫɾ���ĵ�·�������յ���:"<<endl;
                           cin>>v3>>v4;
                           if(photo.GetWeight(v3,v4)==0){
                                cout<<photo.GetName(v3)<<" �� "<<photo.GetName(v4)<<"֮�䲻����ֱ��·�����޷�ɾ��"<<endl;
                           }else{
                                photo.DeleteEdge(v3,v4);
                           }
                        }
                        else
                        {
                            cout<<"�밴��ʾ����"<<endl;
                        }
                        break;
                    }
                    case 3:{
                       photo.Modify();
                       break;
                    }
                    default:{
                        cout<<"�밴��ʾ����"<<endl;
                        break;
                    }
                }
                break;
            }
            case 6:
                cout<<"��л��ʹ�ü��ִ�ѧ����ϵͳ���ټ���"<<endl;
                isTrue = false;
                break;
            default:
                cout<<"δ����ʾ���룬������ѡ����"<<endl;
                break;
         }
    }
    /*���޸���Ϣд���ļ�*/
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
        cout<<"������Ϣ�ѱ���"<<endl;
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
        cout<<"·����Ϣ�ѱ���"<<endl;
        outfile2.close();
    }
    else
    {
        cerr<<"can't open"<<filename<<endl;
    }

    return 0;
}


/*
ʵ�����ݼ�Ҫ��
��Ƽ��ִ�ѧ����У��У԰����ϵͳ�����У���ڽ������·�Ȼ�����Ϣ��ά������Ϊ���ÿ����ṩ��ѯ����
��1����¼У���ڸ����������Ϣ�����ơ����š���顢����λ�õȣ�
��2����¼����֮��ĵ�·��Ϣ��������������롢����ʱ��������Ϣ��
��3�����ݵ���������Ǽ���������ļ����룻
��4���ṩ��У԰������Ϣ�ı༭���磺��ӡ�ɾ�����޸ĵȣ��Ĺ��ܣ�
��5��Ϊ���ÿ����ṩͼ�����⾰�������Ϣ�Ĳ�ѯ�����ṩ���ֲ�ѯ��ʽ����
��6��Ϊ���ÿ����ṩ��У�ſڵ�ͼ�����⾰�����·��ѯ�����ؾ�����̵����߷�����
��7��Ϊ���ÿ����ṩͼ�����⾰������·��ѯ�����ؾ�����̵����߷�����
*/























