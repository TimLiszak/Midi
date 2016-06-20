
#include "StdAfx.h"
#include "Render2d.h"
using namespace Math;

static const CRender2d::UV	NormalUV(0.0f, 0.0f, 1.0f, 1.0f);

GLuint CRender2d::uFontBase;		// Base Display List For The Font Set
BOOL CRender2d::m_bEnableTexture = FALSE;

void CRender2d::BuildFont( HDC hDC )
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	uFontBase = glGenLists(96);								// Storage For 96 Characters

	font = CreateFont(	-14,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_NORMAL,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Courier New");					// Font Name

	oldfont = (HFONT)SelectObject(hDC, font);           // Selects The Font We Want
	wglUseFontBitmaps(hDC, 32, 96, uFontBase);				// Builds 96 Characters Starting At Character 32
	SelectObject(hDC, oldfont);							// Selects The Font We Want
	DeleteObject(font);									// Delete The Font
}

void CRender2d::KillFont()									// Delete The Font List
{
	glDeleteLists(uFontBase, 96);							// Delete All 96 Characters
}

void CRender2d::Print(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
	    vsprintf_s(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(uFontBase - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display List Bits
}

void	CRender2d::Init2dRender( VECTOR vSize )
{
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_TEXTURE_2D );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0, vSize.x, vSize.y, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//FLOAT fZoom = 2.0f;
	//glScalef( 1.0f / fZoom, 1.0f / fZoom, 1.0f );
	//glTranslatef( vSize.x * 0.5f * ( fZoom - 1.0f ), vSize.y * 0.5f * ( fZoom - 1.0f ), 0.0f );
}

void	CRender2d::ClearScreen( COLOUR_RGB clr )
{
	glClearColor(clr.r, clr.g, clr.b, 0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void	CRender2d::DrawPoint( VECTOR vPoint1, COLOUR_RGB clr )
{
	glBegin(GL_POINTS);
		glColor4f(clr.r, clr.g, clr.b, clr.a);
		glVertex2f(vPoint1.x, vPoint1.y);
	glEnd();
}

void	CRender2d::DrawLine( VECTOR vPoint1, VECTOR vPoint2, COLOUR_RGB clr, FLOAT fWidth )
{
	glLineWidth( fWidth );
	glBegin(GL_LINES);
		glColor4f(clr.r, clr.g, clr.b, clr.a);
		glVertex2f(vPoint1.x, vPoint1.y);
		glVertex2f(vPoint2.x, vPoint2.y);
	glEnd();
	glLineWidth( 1.0f );
}


void	CRender2d::DrawRect( VECTOR vPosition, VECTOR vExtents, FLOAT fRotation, COLOUR_RGB clr )
{
	glPushMatrix();
	glTranslatef( vPosition.x, vPosition.y, 0.0f );
	glRotatef( fRotation, 0.0f, 0.0f, 1.0f );

	glBegin(GL_LINE_LOOP);
		glColor4f(clr.r, clr.g, clr.b, clr.a);
		glVertex2f( (-vExtents.x), (-vExtents.y));
		glVertex2f( (-vExtents.x),  (vExtents.y));
		glVertex2f(  (vExtents.x),  (vExtents.y));
		glVertex2f(  (vExtents.x), (-vExtents.y));
	glEnd();
	glPopMatrix();
}

void	CRender2d::DrawRectFill( VECTOR vPosition, VECTOR vExtents, FLOAT fRotation, COLOUR_RGB clr, const UV* pUV )
{
	const UV* _pUV = &NormalUV;
	if ( pUV )
	{
		_pUV = pUV;
	}

	glPushMatrix();
	glTranslatef( vPosition.x, vPosition.y, 0.0f );
	glRotatef( fRotation, 0.0f, 0.0f, 1.0f );

	glBegin(GL_QUADS);
		glColor4f(clr.r, clr.g, clr.b, clr.a);

		glTexCoord2f( _pUV->u0, _pUV->v1 ); 
		glVertex2f( (-vExtents.x), (-vExtents.y));

		glTexCoord2f( _pUV->u0, _pUV->v0 ); 
		glVertex2f( (-vExtents.x),  (vExtents.y));

		glTexCoord2f( _pUV->u1, _pUV->v0 ); 
		glVertex2f(  (vExtents.x),  (vExtents.y));

		glTexCoord2f( _pUV->u1, _pUV->v1 ); 
		glVertex2f(  (vExtents.x), (-vExtents.y));
	glEnd();
	glPopMatrix();
}

void	CRender2d::DrawRectOutline( VECTOR vPosition, VECTOR vExtents, FLOAT fRotation, COLOUR_RGB clr, COLOUR_RGB clr2 )
{
	DrawRectFill( vPosition, vExtents, fRotation, clr );
	DrawRect( vPosition, vExtents, fRotation, clr2 );
}

void	CRender2d::DrawCircle( VECTOR vPoint, FLOAT fRadius, COLOUR_RGB clr )
{
	glBegin(GL_LINE_LOOP);
		glColor4f(clr.r, clr.g, clr.b, clr.a);
		for (INT nAngle = 0; nAngle < 360; nAngle += 20 )
		{
			glVertex2f( vPoint.x + CosD( (FLOAT)nAngle ) * fRadius, vPoint.y + SinD( (FLOAT)nAngle ) * fRadius);
		}
	glEnd();
}

void CRender2d::DrawCircleFill( VECTOR vPoint, FLOAT fRadius, COLOUR_RGB clr )
{
	glBegin(GL_TRIANGLE_FAN);
		glColor4f(clr.r, clr.g, clr.b, clr.a);
		glVertex2f(vPoint.x, vPoint.y);
		for (INT nAngle = 0; nAngle <= 360; nAngle += 20 )
		{
			glVertex2f( vPoint.x + CosD( (FLOAT)nAngle ) * fRadius, vPoint.y + SinD( (FLOAT)nAngle ) * fRadius);
		}
	glEnd();
}

void CRender2d::DrawCircleOutline( VECTOR vPoint, FLOAT fRadius, COLOUR_RGB clr, COLOUR_RGB clr2 )
{
	DrawCircleFill( vPoint, fRadius, clr );
	DrawCircle( vPoint, fRadius, clr2 );
}

void CRender2d::DrawEllipse( VECTOR vPoint, VECTOR vExtents, COLOUR_RGB clr )
{
	glBegin(GL_LINE_LOOP);
		glColor4f(clr.r, clr.g, clr.b, clr.a);
		for (INT nAngle = 0; nAngle < 360; nAngle += 20 )
		{
			glVertex2f( vPoint.x + CosD( (FLOAT)nAngle ) * vExtents.x, vPoint.y + SinD( (FLOAT)nAngle ) * vExtents.y);
		}
	glEnd();
}

void CRender2d::DrawEllipseFill( VECTOR vPoint, VECTOR vExtents, COLOUR_RGB clr )
{
	glBegin(GL_TRIANGLE_FAN);
		glColor4f(clr.r, clr.g, clr.b, clr.a);
		glVertex2f(vPoint.x, vPoint.y);
		for (INT nAngle = 0; nAngle <= 360; nAngle += 20 )
		{
			glVertex2f( vPoint.x + CosD( (FLOAT)nAngle ) * vExtents.x, vPoint.y + SinD( (FLOAT)nAngle ) * vExtents.y );
		}
	glEnd();
}

void CRender2d::DrawEllipseOutline( VECTOR vPoint, VECTOR vExtents, COLOUR_RGB clr, COLOUR_RGB clr2 )
{
	DrawEllipseFill( vPoint, vExtents, clr );
	DrawEllipse( vPoint, vExtents, clr2 );
}

void CRender2d::DrawTriangle( VECTOR vPoint1, VECTOR vPoint2, VECTOR vPoint3, COLOUR_RGB clr )
{
	glPushMatrix();

	glBegin( GL_TRIANGLES );
		glColor4f(clr.r, clr.g, clr.b, clr.a);
		glVertex2f( vPoint1.x, vPoint1.y );
		glVertex2f( vPoint2.x, vPoint2.y );
		glVertex2f( vPoint3.x, vPoint3.y );
	glEnd();
	glPopMatrix();
}

void CRender2d::DrawRect2( VECTOR vPoint1, VECTOR vPoint2, FLOAT fWidth, COLOUR_RGB clr )
{
	FLOAT fX = vPoint2.x - vPoint1.x;
	FLOAT fY = vPoint2.y - vPoint1.y;
	FLOAT fAngle = fX != 0.0f ? atan(fY / fX) : (3.141592f / 2.0f);
	FLOAT fLength = sqrt(fX * fX + fY * fY);
	VECTOR vPos = ( vPoint2 + vPoint1 ) * 0.5f;

	fAngle = Math::Radian2Degree( fAngle );

	DrawRect( vPos, VECTOR(fLength * 0.5f, fWidth), fAngle, clr );
}

void CRender2d::BindTexture( CTexture* pTexture )
{
	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, pTexture->nTexId );
	m_bEnableTexture = TRUE;
}

void CRender2d::EndTexture()
{
	glDisable( GL_TEXTURE_2D );
	m_bEnableTexture = FALSE;
}

void CRender2d::PushMatrix()
{
	glPushMatrix();
}

void CRender2d::PopMatrix()
{
	glPopMatrix();
}

void CRender2d::Translate(VECTOR Trs)
{
	glTranslatef(Trs.x, Trs.y, 0.0f);
}
