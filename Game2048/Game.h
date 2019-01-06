#ifndef GAME_H
#define GAME_H
class Game
{
private:
   int a[4][4];
    int number;
public:
    friend class DIS;
    void set_number();
    Game();
    void set_right();
    void set_left();
    void set_up();
    void set_down();
    void get_a(Game&G);
    bool judge_win();
    bool judge_full();
    void mul_right();
    void move_right();
    void mul_left();
    void move_left();
    void mul_up();
    void move_up();
    void move_down();
    void mul_down();
    bool judge_right();
    bool judge_left();
    bool judge_down();
    bool judge_up();
    };
     class DIS
{
    char dis;
public:
    DIS(char ch='*'){dis=ch;}
virtual void display(Game&G);
};
class DIS1:public DIS
{
public:
    DIS1():DIS('%'){};
};
class DIS2:public DIS
{
public:
    DIS2():DIS('#'){};
};
#endif // GAME_H
