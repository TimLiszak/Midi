#ifndef _SPRITE_MANAGER_H_
#define _SPRITE_MANAGER_H_

#include "Sprite.h"

class CSpriteManager
{
public:
	void	Init();
	void	Term();
	void	Update( const FLOAT fFrameTime );

	BOOL		IsValidSpriteFile( std::string FileName );
	CSprite*	LoadSprite( std::string FileName );

private:
	std::list< CSprite* >	m_Sprites;
};

#endif
