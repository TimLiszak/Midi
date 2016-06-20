#include "StdAfx.h"

#include "Workspace.h"

#include "GameEngine.h"
#include "..\resource.h"

#include "FileSerializer.h"


int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	UNUSED(hInstance);
	UNUSED(hPrevInstance);
	UNUSED(lpCmdLine);
	UNUSED(nCmdShow);

	CWorkspace* pGameMode = new CWorkspace();

	BOOL bSuccess = GetGameEngine()->Init( "", 1200, 800, IDR_MENU1 );
	if ( !bSuccess )
	{
		return 0;
	}

	GetGameEngine()->Run( pGameMode );

	GetGameEngine()->Term();
		
	return 0;							
}
