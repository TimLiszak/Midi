
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Render2d.h"
#include "FileReader.h"
class CSpriteInfo;
class CActor;

class CSprite
{
public:


	struct SFrame
	{
		CTexture*	pTexture;
		FLOAT		fTime;
	};

	struct SAnimation
	{
		SAnimation() :
			nCurrentFrame(0),
			bHorizFlip(FALSE),
			bVertFlip(FALSE),
			fCurrentMoveTime( 0.0f ),
			bVisible(TRUE),
			bPlayAnimation(FALSE)
		{
			vSize.Set( 1.0f, 1.0f );
			vOffset.Set( 0.0f, 0.0f );
			vMovement.Set( 0.0f, 0.0f );
			fMoveTime = 0.0f;
		}

		std::vector< SFrame >	sFrames;
		VECTOR	vSize;
		VECTOR	vOffset;
		VECTOR	vMovement;
		FLOAT	fMoveTime;
		BOOL	bHorizFlip;
		BOOL	bVertFlip;

		BOOL	bVisible;
		BOOL	bPlayAnimation;
		INT		nCurrentFrame;
		FLOAT	fCurrentMoveTime;
	};

	CSprite();

	void	Update( const FLOAT fFrameTime );

	void	LoadFile( std::string Filename );

	void	Render( const CActor* pActor, const CSpriteInfo* pSpriteInfo );
	SAnimation*	GetAnimation( std::string AnimationName );


private:

	void	LoadAnimation( CFileReader& FileReader, std::string AnimName );
	std::map< std::string, SAnimation > m_Animations;
	std::list< SAnimation* > m_Order;
	
};

#endif
