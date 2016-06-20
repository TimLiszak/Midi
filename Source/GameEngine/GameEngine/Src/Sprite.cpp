#include "StdAfx.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "FileReader.h"
#include "TextParser.h"
#include "SpriteInfo.h"
#include "Actor.h"

CSprite::CSprite()
{
}

void CSprite::Update( const FLOAT fFrameTime )
{
	if ( fFrameTime > 0 )
	{
		std::map< std::string, SAnimation >::iterator it;
		for ( it = m_Animations.begin() ; it != m_Animations.end(); it++ )
		{
			// Animation
			SAnimation& sAnimation = (*it).second;

			if ( sAnimation.bPlayAnimation )
			{
				sAnimation.nCurrentFrame++;
				if ( sAnimation.nCurrentFrame >= (INT)sAnimation.sFrames.size() )
				{
					sAnimation.nCurrentFrame = 0;
				}

				// Movement
				if ( sAnimation.fMoveTime > 0.0f )
				{
					sAnimation.fCurrentMoveTime += fFrameTime;
					if ( sAnimation.fCurrentMoveTime >= sAnimation.fMoveTime )
					{
						sAnimation.fCurrentMoveTime = sAnimation.fMoveTime;
					}
				}
			}
		}
	}
}

void CSprite::LoadFile( std::string Filename )
{
	CFileReader FileReader;
	
	if ( FileReader.Open( ( "Data/" + Filename ).c_str() ) )
	{
		while( !FileReader.EndOfFile() )
		{
			std::string strLine = FileReader.ReadLine();

			CTextParser TextParser( strLine );
			std::string Token = TextParser.ParseToken();
			if ( Token.size() == 0 ) break;  // no more tokens

			if ( Token == "Animation" )
			{
				std::string AnimName = TextParser.ParseToken();
				LoadAnimation( FileReader, AnimName );
			}
		}
	}
	else
	{
		ASSERT(FALSE);
	}
}

void CSprite::LoadAnimation( CFileReader& FileReader, std::string AnimName )
{
	SAnimation sAnimation;

	while( !FileReader.EndOfFile() )
	{
		std::string strLine = FileReader.ReadLine();

		CTextParser TextParser( strLine );
		std::string Token = TextParser.ParseToken();
		if ( Token.size() == 0 ) break;  // no more tokens

		if ( Token == "End" )
		{
			break;
		}
		else if ( Token == "Size" )
		{
			sAnimation.vSize.x = TextParser.ParseFloat();
			sAnimation.vSize.y = TextParser.ParseFloat();
		}
		else if ( Token == "Offset" )
		{
			sAnimation.vOffset.x = TextParser.ParseFloat();
			sAnimation.vOffset.y = TextParser.ParseFloat();
		}
		else if ( Token == "HorizFlip" )
		{
			sAnimation.bHorizFlip = TRUE;
		}
		else if ( Token == "VertFlip" )
		{
			sAnimation.bVertFlip = TRUE;
		}
		else if ( Token == "PlayAnimation" )
		{
			sAnimation.bPlayAnimation = TRUE;
		}
		else if ( Token == "Hidden" )
		{
			sAnimation.bVisible = FALSE;
		}
		else if ( Token == "Movement" )
		{
			sAnimation.vMovement.x = TextParser.ParseFloat();
			sAnimation.vMovement.y = TextParser.ParseFloat();
			sAnimation.fMoveTime = TextParser.ParseFloat();
		}
		else
		{
			SFrame sFrame;
			sFrame.fTime = TextParser.ParseFloat();

			sFrame.pTexture = GetGameEngine()->GetTextureManager()->BuildTexture( Token );
			if ( sFrame.pTexture )
			{
				sAnimation.sFrames.push_back( sFrame );
			}
		}
	}

	m_Animations[AnimName] = sAnimation;
	m_Order.push_back( &m_Animations[AnimName] );
}

CSprite::SAnimation* CSprite::GetAnimation( std::string AnimationName )
{
	return &m_Animations[AnimationName];
}

void CSprite::Render( const CActor* pActor, const CSpriteInfo* pSpriteInfo )
{
	std::list< SAnimation* >::iterator it;
	for ( it = m_Order.begin() ; it != m_Order.end(); it++ )
	{
		SAnimation& sAnimation = *(*it);
		if ( !sAnimation.bVisible )
		{
			continue;
		}

		CTexture* pTexture = sAnimation.sFrames[sAnimation.nCurrentFrame].pTexture;
		CRender2d::UV sUV;
		VECTOR vExtents = pActor->GetExtents();
		VECTOR vOffset = pActor->GetExtents();
		vExtents.x *= sAnimation.vSize.x;
		vExtents.y *= sAnimation.vSize.y;

		FLOAT fOffsetX = sAnimation.vOffset.x;
		FLOAT fOffsetY = sAnimation.vOffset.y;

		if ( sAnimation.fMoveTime > 0.0f )
		{
			fOffsetX += sAnimation.vMovement.x * ( sAnimation.fCurrentMoveTime / sAnimation.fMoveTime );
			fOffsetY += sAnimation.vMovement.y * ( sAnimation.fCurrentMoveTime / sAnimation.fMoveTime );
		}

		vOffset.x *= fOffsetX;
		vOffset.y *= fOffsetY;

		if ( pSpriteInfo->bTile )
		{
			sUV.u0 = pSpriteInfo->fTexCoordU0;
			sUV.u1 = ( vExtents.x * 2.0f ) / pTexture->fWidth + ( pSpriteInfo->fTexCoordU1 - 1.0f );
			sUV.v0 = pSpriteInfo->fTexCoordV0;
			sUV.v1 = ( vExtents.y * 2.0f ) / pTexture->fHeight + ( pSpriteInfo->fTexCoordV1 - 1.0f );
		}
		else
		{
			sUV.u0 = pSpriteInfo->fTexCoordU0;
			sUV.u1 = pSpriteInfo->fTexCoordU1;
			sUV.v0 = pSpriteInfo->fTexCoordV0;
			sUV.v1 = pSpriteInfo->fTexCoordV1;
		}
		if ( pSpriteInfo->bHorizFlip ^ sAnimation.bHorizFlip )
		{
			sUV.u1 = -sUV.u1;
			vOffset.x = -vOffset.x;
		}
		if ( pSpriteInfo->bVertFlip ^ sAnimation.bVertFlip )
		{
			sUV.v1 = -sUV.v1;
			vOffset.y = -vOffset.y;
		}

		CRender2d::BindTexture( pTexture );
		CRender2d::DrawRectFill( pActor->GetPosition() + vOffset, vExtents, 0.0f, COLOUR_RGB(1.0f, 1.0f, 1.0f), &sUV );
		CRender2d::EndTexture();
	}
}
