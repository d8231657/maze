//---------------------------------------------------------------------------
#ifndef Maze_UtilityH
#define Maze_UtilityH
#include<stdlib.h>

class Maze
{
        private:
                int length,width;
                int step,steped,steping;
                long space;
                char** pointer;//-1:出口
                               //0:路
                               //1:牆壁
                               //2:邊界
                               //3:人
                               //4:路徑
                               //5:腳印
                void Lineing(int x,int y,int pro2,int step);
        public:
                Maze(void);
                Maze(int,int);
                ~Maze(void);
                void CreateMaze(int,int);
                long ReCreate(int,int);
                void ReSize(int,int);
                void PrintMaze(TForm *,int x1=-1,int y1=-1,int x2=-1,int y2=-1);
                int PeopleIn(int x,int y);
                void PeopleOut(void);
                char PeopleMove(int x1,int y1,int x2,int y2);
                int GetStep(char i);
};

//---------------------------------------------------------------------------
#endif
