//---------------------------------------------------------------------------
#ifndef People_for_mazeH
#define People_for_mazeH
//---------------------------------------------------------------------------
#endif
#include "Maze_Utility.h"
class People
{
        private:
                int x,y;
                int step;
                Maze *pointer;
        public:
                People(void);
                int In(const Maze *target,int x,int y);
                void Out(void);
                char Move(char);
                int GetX(void);
                int GetY(void);
                int GetStep(void);
};
