#ifndef SHUDU_H
#define SHUDU_H
class ShuDu
{
private:
 int shudoku[9][9];
public:
    ShuDu();
    ~ShuDu(){}
void create();
void display();
void writefile();
bool insert_value();
bool Search(int x,int y);
bool modify(int x,int y,int value);
bool judge(int x,int y,int value );
};
#endif // SHUDU_H
