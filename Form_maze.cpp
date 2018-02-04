//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <maze_utility.h>
#include <people_for_maze.h>
#include "Form_maze.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TForm1 *Form1;
Maze m1;
People p1;
bool play;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        randomize();
        Canvas->Pen->Color=clRed;
        m1.CreateMaze(StrToInt(Edit1->Text)*2+1,StrToInt(Edit2->Text)*2+1);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
        if(StrToInt(Edit1->Text)>25||StrToInt(Edit2->Text)>35||
           StrToInt(Edit1->Text)<=1||StrToInt(Edit2->Text)<=1)
                return;
        Button1->Enabled=False;
        Button2->Enabled=False;
        Canvas->Brush->Color=Form1->Color;
        Canvas->FillRect(Rect(0,50,Form1->Width--,Form1->Height--));
        //for(int i=0;i<Form1->Width;i++)
        //        for(int j=50;j<Form1->Height;j++)
        //                Canvas->Pixels[i][j]=Form1->Color;
        m1.ReSize(StrToInt(Edit1->Text)*2+1,StrToInt(Edit2->Text)*2+1);
        Button2->Click();
        Button2->Enabled=True;

/*        Button1->Enabled=False;
        Edit1->Enabled=False;
        Edit2->Enabled=False;

        Button2->Click();
        Button2->Enabled=True;*/
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        long pass=0;
        bool temp2;
        Button2->Enabled=false;
        temp2=Button3->Enabled;
        Button3->Enabled=false;

        int temp=CheckBox1->Checked?TrackBar1->Position:0;
        for(int i=0;i<100&&pass==0;i++)
        {
                pass=m1.ReCreate(temp,TrackBar2->Position);
                CGauge1->Progress=i;
        }
        CGauge1->Progress=100;
        if(pass==0)
        {
                Label4->Caption="迷宮大小：失敗";
                Button3->Enabled=temp2;
                //m1.PrintMaze(Form1);
        }
        else
        {
                Label4->Caption="迷宮大小："+IntToStr(m1.GetStep(2)+m1.GetStep(3))+'/'+IntToStr((int)pass);
                Label8->Caption="完成度："+IntToStr(m1.GetStep(3))+'/'+IntToStr(m1.GetStep(1));
                Label3->Caption="計步器："+IntToStr(p1.GetStep());
                //p1.In(&m1,0,1);
                p1.Out();
                m1.PrintMaze(Form1);
                Button3->Enabled=true;
        }
        CGauge1->Progress=0;

        Button2->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        play=true;
        Canvas->MoveTo(X,Y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseUp(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        play=false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
        if(play)
                Canvas->LineTo(X,Y);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
        Button1->Enabled=True;
        Button2->Enabled=False;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2Change(TObject *Sender)
{
        Button1->Enabled=True;
        Button2->Enabled=False;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
                if(p1.Move(Key))
                {
                        Label3->Caption="計步器："+IntToStr(p1.GetStep());
                        Label4->Caption="迷宮大小："+IntToStr(m1.GetStep(2)+m1.GetStep(3))+'/'+IntToStr(m1.GetStep(0));
                        Label8->Caption="完成度："+IntToStr(m1.GetStep(3))+'/'+IntToStr(m1.GetStep(1));
                        m1.PrintMaze(Form1,p1.GetX()-1,p1.GetY()-1,p1.GetX()+1,p1.GetY()+1);
                }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        Button3->Enabled=false;
        p1.In(&m1,0,1);
        Label3->Caption="計步器："+IntToStr(p1.GetStep());
        m1.PrintMaze(Form1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormPaint(TObject *Sender)
{
        //Form1->Canvas->Refresh();
        m1.PrintMaze(Form1);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
        TrackBar1->Enabled=CheckBox1->Checked;    
}
//---------------------------------------------------------------------------




