#include "StdAfx.h"
#include "TextureManager.h"

void CTextureManager::Init()
{
}

void CTextureManager::Term()
{
	std::map< std::string, CTexture* >::iterator it;
	for ( it = m_Textures.begin() ; it != m_Textures.end(); it++ )
	{
		CTexture* pTexture = (*it).second;

		delete pTexture;
	}
	m_Textures.empty();
}

CTexture* CTextureManager::LoadTextureBMP( std::string FileName, int wrap )
{
	if ( m_Textures[FileName] )
	{
		return m_Textures[FileName];
	}
	else
	{
		CTexture* pTexture = new CTexture();

		HBITMAP hBmp = (HBITMAP)LoadImage(NULL, (LPCTSTR)( "Data/" + FileName ).c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		BITMAP BM;
		GetObject( hBmp, sizeof(BM), &BM );

		if ( BM.bmBitsPixel != 24 &&
			 BM.bmBitsPixel != 32 )
		{
			return NULL;
		}

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		pTexture->fHeight = (FLOAT)BM.bmHeight;
		pTexture->fWidth = (FLOAT)BM.bmWidth;

		glGenTextures( 1, &pTexture->nTexId );
		glBindTexture( GL_TEXTURE_2D, pTexture->nTexId );
		//glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
		//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
		//glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
					   wrap ? (FLOAT)GL_REPEAT : (FLOAT)GL_CLAMP );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
					   wrap ? (FLOAT)GL_REPEAT : (FLOAT)GL_CLAMP );


		if ( BM.bmBitsPixel == 32 )
		{
			gluBuild2DMipmaps( GL_TEXTURE_2D, 4, BM.bmWidth, BM.bmHeight, 
					   GL_BGRA_EXT, GL_UNSIGNED_BYTE,
					   (LPVOID)((INT)BM.bmBits) );
		}
		else
		{
			gluBuild2DMipmaps( GL_TEXTURE_2D, 3, BM.bmWidth, BM.bmHeight, 
					   GL_BGR_EXT, GL_UNSIGNED_BYTE,
					   (LPVOID)((INT)BM.bmBits) );
		}

		m_Textures[ FileName ] = pTexture;

		return pTexture;														// Return True (All Good)
	}
}


CTexture* CTextureManager::BuildTexture( std::string FileName )
{
	if ( m_Textures[FileName] )
	{
		return m_Textures[FileName];
	}
	else
	{
		// Check for 24-bit bitmap
		INT nSize = FileName.size();
		std::string strExt = FileName.substr( nSize - 4, nSize - 1 );
		if ( strExt == ".bmp" )
		{
			CTexture* pTexture = LoadTextureBMP( FileName, TRUE );
			if ( pTexture )
			{
				m_Textures[ FileName ] = pTexture;
				return pTexture;
			}
		}

		CTexture*	Texture = new CTexture();


		HDC			hdcTemp;												// The DC To Hold Our Bitmap
		HBITMAP		hbmpTemp;												// Holds The Bitmap Temporarily
		IPicture	*pPicture;												// IPicture Interface
		OLECHAR		wszPath[MAX_PATH+1];									// Full Path To Picture (WCHAR)
		char		szPath[MAX_PATH+1];										// Full Path To Picture
		long		lWidth;													// Width In Logical Units
		long		lHeight;												// Height In Logical Units
		long		lWidthPixels;											// Width In Pixels
		long		lHeightPixels;											// Height In Pixels
		GLint		glMaxTexDim ;											// Holds Maximum Texture Size

		GetCurrentDirectory(MAX_PATH, szPath);							// Get Our Working Directory
		strcat_s(szPath, MAX_PATH+1, "\\Data\\");											// Append "\" After The Working Directory
		strcat_s(szPath, MAX_PATH+1, FileName.c_str() );										// Append The PathName

		MultiByteToWideChar(CP_ACP, 0, szPath, -1, wszPath, MAX_PATH);		// Convert From ASCII To Unicode
		HRESULT hr = OleLoadPicturePath(wszPath, 0, 0, 0, IID_IPicture, (void**)&pPicture);

		if(FAILED(hr))														// If Loading Failed
		{
			ASSERT( FALSE );
			return NULL;													// Return False
		}

		hdcTemp = CreateCompatibleDC(GetDC(0));								// Create The Windows Compatible Device Context
		if(!hdcTemp)														// Did Creation Fail?
		{
			pPicture->Release();											// Decrements IPicture Reference Count
			ASSERT( FALSE );
			return NULL;													// Return False (Failure)
		}

		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);					// Get Maximum Texture Size Supported
		
		pPicture->get_Width(&lWidth);										// Get IPicture Width (Convert To Pixels)
		lWidthPixels	= MulDiv(lWidth, GetDeviceCaps(hdcTemp, LOGPIXELSX), 2540);
		pPicture->get_Height(&lHeight);										// Get IPicture Height (Convert To Pixels)
		lHeightPixels	= MulDiv(lHeight, GetDeviceCaps(hdcTemp, LOGPIXELSY), 2540);

		// Resize Image To Closest Power Of Two
		if (lWidthPixels <= glMaxTexDim) // Is Image Width Less Than Or Equal To Cards Limit
			lWidthPixels = 1 << (int)floor((log((double)lWidthPixels)/log(2.0f)) + 0.5f); 
		else  // Otherwise  Set Width To "Max Power Of Two" That The Card Can Handle
			lWidthPixels = glMaxTexDim;
	 
		if (lHeightPixels <= glMaxTexDim) // Is Image Height Greater Than Cards Limit
			lHeightPixels = 1 << (int)floor((log((double)lHeightPixels)/log(2.0f)) + 0.5f);
		else  // Otherwise  Set Height To "Max Power Of Two" That The Card Can Handle
			lHeightPixels = glMaxTexDim;
		
		//	Create A Temporary Bitmap
		BITMAPINFO	bi = {0};												// The Type Of Bitmap We Request
		DWORD		*pBits = 0;												// Pointer To The Bitmap Bits

		bi.bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);				// Set Structure Size
		bi.bmiHeader.biBitCount		= 32;									// 32 Bit
		bi.bmiHeader.biWidth		= lWidthPixels;							// Power Of Two Width
		bi.bmiHeader.biHeight		= lHeightPixels;						// Make Image Top Up (Positive Y-Axis)
		bi.bmiHeader.biCompression	= BI_RGB;								// RGB Encoding
		bi.bmiHeader.biPlanes		= 1;									// 1 Bitplane

		//	Creating A Bitmap This Way Allows Us To Specify Color Depth And Gives Us Imediate Access To The Bits
		hbmpTemp = CreateDIBSection(hdcTemp, &bi, DIB_RGB_COLORS, (void**)&pBits, 0, 0);
		
		if(!hbmpTemp)														// Did Creation Fail?
		{
			DeleteDC(hdcTemp);												// Delete The Device Context
			pPicture->Release();											// Decrements IPicture Reference Count
			ASSERT( FALSE );
			return NULL;													// Return False (Failure)
		}

		SelectObject(hdcTemp, hbmpTemp);									// Select Handle To Our Temp DC And Our Temp Bitmap Object

		// Render The IPicture On To The Bitmap
		pPicture->Render(hdcTemp, 0, 0, lWidthPixels, lHeightPixels, 0, lHeight, lWidth, -lHeight, 0);

		// Convert From BGR To RGB Format And Add An Alpha Value Of 255
		for(long i = 0; i < lWidthPixels * lHeightPixels; i++)				// Loop Through All Of The Pixels
		{
			BYTE* pPixel	= (BYTE*)(&pBits[i]);							// Grab The Current Pixel
			BYTE  temp		= pPixel[0];									// Store 1st Color In Temp Variable (Blue)
			pPixel[0]		= pPixel[2];									// Move Red Value To Correct Position (1st)
			pPixel[2]		= temp;											// Move Temp Value To Correct Blue Position (3rd)
			//pPixel[3]		= 255;
		}

		glGenTextures(1, &Texture->nTexId);											// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, Texture->nTexId );								// Bind To The Texture ID
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);		// (Modify This For The Type Of Filtering You Want)
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);     // (Modify This For The Type Of Filtering You Want)

		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (FLOAT)GL_REPEAT );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (FLOAT)GL_REPEAT );

		// (Modify This If You Want Mipmaps)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lWidthPixels, lHeightPixels, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBits);

		DeleteObject(hbmpTemp);												// Delete The Object
		DeleteDC(hdcTemp);													// Delete The Device Context

		pPicture->Release();												// Decrements IPicture Reference Count

		Texture->fHeight = (FLOAT)lHeightPixels;
		Texture->fWidth = (FLOAT)lWidthPixels;

		m_Textures[ FileName ] = Texture;

		return Texture;														// Return True (All Good)
	}
}
