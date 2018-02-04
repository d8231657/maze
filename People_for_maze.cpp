//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "People_for_maze.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
People::People(void)
{
        pointer=NULL;
}
int People::In(const Maze *target,int x,int y)
{
        if(pointer==NULL)
        {
                pointer=(Maze *)target;
                this->x=x;
                this->y=y;
                if(pointer->PeopleIn(this->x,this->y))
                {
                        step=0;
                        return 1;
                }
                else
                {
                        pointer=NULL;
                        return 0;
                }
        }
        else
                return 0;
}
void People::Out(void)
{
        if(pointer)
        {
                pointer->PeopleOut();
                pointer=NULL;
        }
}
char People::Move(char key)
{
        if(pointer==NULL)
                return  0;
        int newx=x,newy=y;
        switch(key)
        {
                case 37://left
                        newy--;
                        //if(newy<0)return 0;
                        break;
                case 38://up
                        newx--;
                        //if(newx<0)return 0;
                        break;
                case 39://right
                        newy++;
                        //if(newy>=pointer->width)return 0;
                        break;
                case 40://down
                        newx++;
                        //if(newx>=pointer->length)return 0;
                        break;
                default:
                        return 0;
        }
        //if(pointer->pointer[newx][newy]!=1&&
        //   pointer->pointer[newx][newy]!=2)
        //{
                if(pointer->PeopleMove(x,y,newx,newy)==0)
                        return 0;
                x=newx;
                y=newy;
                step++;
                return 1;
        //}
        //else
        //        return 0;
}
int People::GetX(void)
{
        return x;
}
int People::GetY(void)
{
        return y;
}
int People::GetStep(void)
{
        return step;
}
