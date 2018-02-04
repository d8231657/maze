//---------------------------------------------------------------------------
#include <vcl.h>
#include <time.h>
#pragma hdrstop
USERES("Maze.res");
USEFORM("Form_maze.cpp", Form1);
USEUNIT("People_for_maze.cpp");
USEUNIT("Maze_Utility.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------

