#ifndef MAP_H
#define MAP_H
#include<string>
#include<iostream>

using namespace std;
struct VerEdge    // 边结点的结构体
{  friend class Map ;
   int VerName ; // 邻接顶点序号，用自然数编号
   string Name;
   string Introduce;
   int cost ;    // 边的权值
   VerEdge *next ;  // 指向下一个边结点的指针
} ;
struct VerHead   //顶点表中结点的结构体
{   friend class Map;
    string Name;
    string Introduce;
    int VerNumber;	// 顶点的名称
    VerEdge *link; // 边链表头指针
} ;
class Map
{
 private:
VerHead *Head;   // 顶点表头指针
int MapSize;   // 图中当前顶点的个数
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
