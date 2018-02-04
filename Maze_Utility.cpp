//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Maze_Utility.h"
Maze::Maze(void)
{
        return;
}
Maze::Maze(int i,int j)
{
        CreateMaze(i,j);
}
void Maze::CreateMaze(int i,int j)
{
        length=i;
        width=j;
        space=step=steped=steping=0;
        pointer=new char*[length];
        for(i=0;i<length;i++)
        {
                pointer[i]=new char[width];
                for(j=0;j<width;j++)
                {
                        Application->ProcessMessages();
                        pointer[i][j]=0;
                }
                pointer[i][0]=pointer[i][width-1]=2;
        }
        for(i=0;i<width;i++)
        {
                Application->ProcessMessages();
                pointer[0][i]=pointer[length-1][i]=2;
        }
        pointer[0][1]=0;
        pointer[length-1][width-2]=-1;
        /*int pass;
        do
                pass=ReCreate();
        while(pass==0);*/
}
void Maze::ReSize(int x,int y)
{
        for(int i=0;i<length;i++)
        {
                delete pointer[i];
        }
        delete pointer;
        length=x;
        width=y;
        space=step=steped=steping=0;
        pointer=new char*[x];
        for(int i=0;i<length;i++)
        {
                pointer[i]=new char[width];
                for(int j=0;j<width;j++)
                {
                        Application->ProcessMessages();
                        pointer[i][j]=0;
                }
                pointer[i][0]=pointer[i][width-1]=2;
        }
        for(int i=0;i<width;i++)
        {
                Application->ProcessMessages();
                pointer[0][i]=pointer[length-1][i]=2;
        }
        pointer[0][1]=0;
        pointer[length-1][width-2]=-1;
}
Maze::~Maze()
{
        for(int i=0;i<length;i++)
        {
                delete pointer[i];
        }
        delete pointer;
}
long Maze::ReCreate(int pro,int pro2)
{
        char **temp;
        Maze tempmaze(length,width);
        temp=tempmaze.pointer;
        tempmaze=*this;
        //temp=new char[sizeof(char)*length*width];
        //temp=(char *)malloc(sizeof(char)*length*width);
        for(int i=0;i<length;i++)
                for(int j=0;j<width;j++)
                        temp[i][j]=pointer[i][j];
        if(length==0||width==0)
        {
                //free(temp);
                tempmaze.pointer=temp;
                return 0;
        }
        for(int i=1;i<length-1;i++)
                for(int j=1;j<width-1;j++)
                        pointer[i][j]=1;
        for(int i=0;i<width;i++)
        {
                Application->ProcessMessages();
                pointer[0][i]=pointer[length-1][i]=2;
        }
        for(int i=0;i<length;i++)
        {
                Application->ProcessMessages();
                pointer[i][0]=pointer[i][width-1]=2;
        }
        pointer[0][1]=0;
        pointer[length-1][width-2]=-1;
        pointer[1][1]=0;
        Lineing(1,1,pro2,0);
        space=0;
        for(int i=0;i<length;i++)
                for(int j=0;j<width;j++)
                {
                        Application->ProcessMessages();
                        if(pointer[i][j]==0)
                                space++;
                }
        if(pointer[length-2][width-2]==0&&pro==0)
        {
                //delete temp;
                //free(temp);
                steped=0;
                steping=0;
                tempmaze.pointer=temp;
                return(space);
        }
        if(pointer[length-2][width-2]==0
           &&space>(length*width)*(pro-10)/100
           &&space<(length*width)*pro/100)
        {
                //delete temp;
                //free(temp);
                steped=0;
                steping=0;
                tempmaze.pointer=temp;
                return(space);
        }
        else
        {
                *this=tempmaze;
                for(int i=0;i<length;i++)
                        for(int j=0;j<width;j++)
                                pointer[i][j]=temp[i][j];
                //delete temp;
                //free(temp);
                tempmaze.pointer=temp;
                return 0;
        }
}
void Maze::Lineing(int x,int y,int pro,int step)
{
        step++;
        int counter=0;
        Application->ProcessMessages();
        for(int i=0;i<2;i++)
                for(int j=-1;j<2;j+=2)
                        if(pointer[x+i*j][y+!i*j]==0)
                                counter++;
        if(counter>1)
        {
                        pointer[x][y]=1;
                        return;
        }
        int r=random(3);
        int s=0;
        for(int i=0;i<2;i++)
                for(int j=-1;j<2;j+=2)
                {
                        if(pointer[x+i*j][y+!i*j]==1)
                        {
                                if(s==r)
                                {
                                        pointer[x+i*j][y+!i*j]=0;
                                        Lineing(x+i*j,y+!i*j,pro,step);
                                }
                                else
                                {
                                        if((pointer[x+i*j][y+!i*j]=(char)((random(pro)<10)?0:1))==0)
                                                Lineing(x+i*j,y+!i*j,pro,step);
                                }
                                s++;
                        }

                }
        if(x==length-2&&y==width-2)
                this->step=step+1;
}
void Maze::PrintMaze(TForm * form,int x1,int y1,int x2,int y2)
{
        if(y2==-1)
        {
                x1=y1=0;
                x2=length-1;
                y2=width-1;
        }
        if(x1<0||y1<0||x2>=length||y2>=width)
        {
                x1=y1=0;
                x2=length-1;
                y2=width-1;
                //return;
        }
        for(int i=x1,I=50+x1*10;i<=x2;i++,I+=10)
                for(int j=y1,J=50+y1*10;j<=y2;j++,J+=10)
                {
                        Application->ProcessMessages();

                        //for(int k=0;k<10;k++)
                          //      for(int l=0;l<10;l++)
                            //            form->Canvas->[j*10+l+50][i*10+k+50]=clWhite;
                        switch(pointer[i][j])
                        {
                                case -1:
                                case 0:
                                        form->Canvas->Brush->Color=clWhite;
                                        break;
                                case 1:
                                case 2:
                                        form->Canvas->Brush->Color=clBlack;
                                        break;
                                case 3:
                                        form->Canvas->Brush->Color=clRed;
                                        break;
                                case 4:
                                        form->Canvas->Brush->Color=clGreen;
                                        break;
                                case 5:
                                        form->Canvas->Brush->Color=clBlue;
                                        break;
                                default:
                                        form->Canvas->Brush->Color=clBlack;
                                        break;
                        }
                        form->Canvas->FillRect(Rect(J,I,10+J,10+I));

                        /*if(pointer[i][j]<1)
                                for(int k=0;k<10;k++)
                                        for(int l=0;l<10;l++)
                                                form->Canvas->Pixels[j*10+l+50][i*10+k+50]=clWhite;
                        else
                                for(int k=0;k<10;k++)
                                        for(int l=0;l<10;l++)
                                                form->Canvas->Pixels[j*10+l+50][i*10+k+50]=clBlack;*/
                }
}
int Maze::PeopleIn(int x,int y)
{
        if(pointer[x][y]!=1&&pointer[x][y]!=2)
        {
                pointer[x][y]=3;
                return 1;
        }
        else
                return 0;
}
void Maze::PeopleOut(void)
{
        for(int i=0;i<length;i++)
                for(int j=0;j<width;j++)
                        if(pointer[i][j]==3)
                                pointer[i][j]=0;
        pointer[length-1][width-2]=-1;
}
char Maze::PeopleMove(int x1,int y1,int x2,int y2)
{
        if(x2<0||x2>=length||y2<0||y2>=width)
                return 0;
        if(pointer[x2][y2]==1||pointer[x2][y2]==2)
                return 0;
        switch(pointer[x2][y2])
        {
                case 5:
                        steped--;
                case -1:
                case 0:
                //case 5:
                        pointer[x1][y1]=4;
                        steping++;
                        break;
                case 4:
                        pointer[x1][y1]=5;
                        steping--;
                        steped++;
                        break;
                default:
                        return 0;
        }
        pointer[x2][y2]=3;
        return 1;
}
int Maze::GetStep(char i)
{
        switch(i)
        {
                case 0:
                        return space;
                case 1:
                        return step;
                case 2:
                        return steped;
                case 3:
                        return steping;
                default:
                        return step;
        }
}
 //---------------------------------------------------------------------------
#pragma package(smart_init)
