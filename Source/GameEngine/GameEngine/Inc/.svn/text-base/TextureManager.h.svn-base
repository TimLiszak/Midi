#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "Render2d.h"

class CTextureManager
{
public:
	void	Init();
	void	Term();
	CTexture*	BuildTexture( std::string FileName );

private:
	CTexture* 	LoadTextureBMP( std::string FileName, int wrap );
	std::map< std::string, CTexture* >	m_Textures;
};

#endif
