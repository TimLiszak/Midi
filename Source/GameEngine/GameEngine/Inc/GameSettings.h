#ifndef _GAME_SETTINGS_H_
#define _GAME_SETTINGS_H_

#include "Gamepad.h"

class CGameSettings
{
public:
	void	Init();
	void	Term();

	void	SetKeyConfig( EKeyConfig eConfig );

	virtual void	Serialize( CSerializer* Serializer );

private:
	void	LoadFile();
	void	SaveFile();

	INT		m_eKeyConfig;

};

#endif
