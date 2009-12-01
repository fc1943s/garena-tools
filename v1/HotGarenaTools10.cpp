#include <vcl.h>
#pragma hdrstop

USEFORM("UFormMain.cpp", FormMain);

WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		SetApplicationMainFormOnTaskBar(Application, true);
		Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->Run();
	}
	catch(Exception & exception)
	{
		Application->ShowException(&exception);
	}
	catch(...)
	{
		try
		{
			throw Exception("");
		}
		catch(Exception & exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
