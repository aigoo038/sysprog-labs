﻿// WindowsSocket.cpp: определяет процедуры инициализации для библиотеки DLL.
//

#include "pch.h"
#include "framework.h"
#include "WindowsSocket.h"
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CWindowsSocketApp, CWinApp)
END_MESSAGE_MAP()


CWindowsSocketApp::CWindowsSocketApp()
{
}


CWindowsSocketApp theApp;
extern "C" 
{
	__declspec(dllexport) bool StartThread(int evType)
	{
		AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
		AfxSocketInit();
		CSocket s;
		s.Create();

		if (s.Connect("127.0.0.1", 12345))
		{
			s.Send(LPCVOID(&evType), sizeof(evType));
			s.Close();
			return true;
		}
		else
		{
			s.Close();
			return false;
		}
	}


	__declspec(dllexport) bool StopThread(int evType)
	{
		AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
		AfxSocketInit();
		CSocket s;
		s.Create();

		if (s.Connect("127.0.0.1", 12345))
		{
			s.Send(LPCVOID(&evType), sizeof(evType));
			s.Close();
			return true;
		}
		else
		{
			s.Close();
			return false;
		}
	}


	_declspec(dllexport) bool __stdcall Send(int evType, int thId, const char* msg)
	{
		AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0);
		AfxSocketInit();
		CSocket s;
		s.Create();
		if (s.Connect("127.0.0.1", 12345))
		{
			s.Send(LPCVOID(&evType), sizeof(evType));
			s.Send(LPCVOID(&thId), sizeof(thId));
			s.Send(LPCVOID(&msg), sizeof(msg));
			s.Close();
			return true;
		}
		else
		{
			s.Close();
			return false;
		}
	}
}


BOOL CWindowsSocketApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}