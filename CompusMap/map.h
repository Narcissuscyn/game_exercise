#ifndef MAP_H
#define MAP_H
#include<string>
#include<iostream>

using namespace std;
struct VerEdge    // �߽��Ľṹ��
{  friend class Map ;
   int VerName ; // �ڽӶ�����ţ�����Ȼ�����
   string Name;
   string Introduce;
   int cost ;    // �ߵ�Ȩֵ
   VerEdge *next ;  // ָ����һ���߽���ָ��
} ;
struct VerHead   //������н��Ľṹ��
{   friend class Map;
    string Name;
    string Introduce;
    int VerNumber;	// ���������
    VerEdge *link; // ������ͷָ��
} ;
class Map
{
 private:
VerHead *Head;   // �����ͷָ��
int MapSize;   // ͼ�е�ǰ����ĸ���
public:
    Map();
    Map(int x):MapSize(x){Head=0;}
    void y();
    int GetMapSize(){return MapSize;}
    void Display(int x);
    int GetDistance(int x,int y);
    string GetName();
    void DeleteEdge();
    void AddSport();
    void DeleteSport(int x);
    void DisplaySport(int x);
    void SearchMap(int x);
    bool IsEmpty(){if(MapSize==0)return false;}
    void InseartEdge(int& x,int& y,int& d)const;
    bool DFS(int x);
    bool BFS(int x);
    void ShortestPath();
    string GetName(int x);
    void Modify();
    void ModifyRoad(const string name1,const string name2,int d);
};
#endif // MAP_H
