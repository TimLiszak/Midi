#include "StdAfx.h"
#include "SpriteManager.h"

void CSpriteManager::Init()
{
}

void CSpriteManager::Term()
{
	std::list< CSprite* >::iterator it;
	for ( it = m_Sprites.begin() ; it != m_Sprites.end(); it++ )
	{
		CSprite* pSprite = (*it);
		delete pSprite;
	}
	m_Sprites.empty();
}

void CSpriteManager::Update( const FLOAT fFrameTime )
{
	std::list< CSprite* >::iterator it;
	for ( it = m_Sprites.begin() ; it != m_Sprites.end(); it++ )
	{
		CSprite* pSprite = (*it);
		pSprite->Update( fFrameTime );
	}
}

BOOL CSpriteManager::IsValidSpriteFile( std::string FileName )
{
	INT nPos = FileName.size() - 1;
	std::string strExt = FileName.substr( nPos - 3, nPos );
	if ( strExt == ".spr" )
	{
		return TRUE;
	}
	return FALSE;
}

CSprite* CSpriteManager::LoadSprite( std::string FileName )
{
	if ( !IsValidSpriteFile( FileName ) )
	{
		return NULL;
	}

	CSprite* pSprite = new CSprite();

	pSprite->LoadFile( FileName );

	m_Sprites.push_back( pSprite );
	return pSprite;														// Return True (All Good)
}
