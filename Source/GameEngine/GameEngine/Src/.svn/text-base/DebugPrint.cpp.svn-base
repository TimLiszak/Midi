#include "StdAfx.h"
#include "DebugPrint.h"
#include "Render2d.h"

static const FLOAT	LINE_HEIGHT	= 0.05f;
static const FLOAT	COLUMN_WIDTH = 0.05f;
static const FLOAT	LEFT_MARGIN = 0.02f;
static const FLOAT	TOP_MARGIN = 0.1f;

void CDebugPrint::Init()
{
}

void CDebugPrint::Term()
{
}

void CDebugPrint::Update( const FLOAT fFrameTime )
{
	for (UINT i = 0; i < m_TimedMessages.size(); i++)
	{
		if ( m_TimedMessages[i].fTime > 0.0f )
		{
			m_TimedMessages[i].fTime -= fFrameTime;
			m_TimedMessages[i].fTime = Math::Max( m_TimedMessages[i].fTime, 0.0f );
		}
	}
}

void CDebugPrint::Render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glColor3f(0.0f,0.8f,0.0f);

	INT nCol = 0;
	INT nRow = 0;
	INT nTextCnt = 0;

	for (UINT i = 0; i < m_CommandQueue.size(); i++)
	{
		switch ( m_CommandQueue[i].eCommand )
		{
			case ECommand_Print:
			{
				VECTOR vPos = GetPosition( nCol, nRow );
				glRasterPos2f( vPos.x, vPos.y );
				CRender2d::Print( m_TextBuffer[nTextCnt].c_str() );
				nTextCnt++;
				nRow++;
			}
			break;

			case ECommand_Colour:
			{
				glColor3f( m_CommandQueue[i].Clr.r, m_CommandQueue[i].Clr.g, m_CommandQueue[i].Clr.b );
			}
			break;

			case ECommand_Position:
			{
				nCol = (INT)m_CommandQueue[i].vPosition.x;
				nRow = (INT)m_CommandQueue[i].vPosition.y;
			}
			break;
		}
	}
	m_TextBuffer.clear();
	m_CommandQueue.clear();


	glColor3f(0.0f,0.8f,0.0f);
	for (UINT i = 0; i < m_TimedMessages.size(); i++)
	{
		if ( m_TimedMessages[i].fTime > 0.0f )
		{
			VECTOR vPos = GetPosition( nCol, nRow );
			glRasterPos2f( vPos.x, vPos.y );
			CRender2d::Print( m_TimedMessages[i].strMesssage.c_str() );
			nRow++;
		}
	}
	
}

void CDebugPrint::Printf( const char *fmt, ... )
{
	// convert variable arguments to string
	char text[1024];
	va_list	ap;		
	va_start(ap, fmt);
    vsprintf_s(text, fmt, ap);
	va_end(ap);

	// store string in buffer
	std::string strText( text );
	m_TextBuffer.push_back( strText );


	SCommand sCommand;
	sCommand.eCommand = ECommand_Print;
	m_CommandQueue.push_back( sCommand );
}

void CDebugPrint::ShowMessage( VECTOR vPos, FLOAT fTime, const char *fmt, ... )
{
	// convert variable arguments to string
	char text[1024];
	va_list	ap;		
	va_start(ap, fmt);
    vsprintf_s(text, fmt, ap);
	va_end(ap);

	// store string in buffer
	STimedMessage msg;
	msg.strMesssage = text;
	msg.vPosition = vPos;
	msg.fTime = fTime;

	BOOL bFound = FALSE;
	for (UINT i = 0; i < m_TimedMessages.size(); i++)
	{
		if ( m_TimedMessages[i].fTime == 0.0f )
		{
			m_TimedMessages[i] = msg;
			bFound = TRUE;
			break;
		}
	}

	if ( !bFound )
	{
		m_TimedMessages.push_back( msg );
	}
}

VECTOR CDebugPrint::GetPosition( INT nCol, INT nRow )
{
	FLOAT fX = -1.0f + LEFT_MARGIN;
	FLOAT fY = 1.0f - TOP_MARGIN - LINE_HEIGHT;

	fY -= LINE_HEIGHT * nRow;
	fX += COLUMN_WIDTH * nCol;

	return VECTOR( fX, fY );
}

void CDebugPrint::ChangeColour( COLOUR_RGB Clr )
{
	SCommand sCommand;
	sCommand.eCommand = ECommand_Colour;
	sCommand.Clr = Clr;
	m_CommandQueue.push_back( sCommand );
}

void CDebugPrint::SetPosition( VECTOR vPos )
{
	SCommand sCommand;
	sCommand.eCommand = ECommand_Position;
	sCommand.vPosition = vPos;
	m_CommandQueue.push_back( sCommand );
}

VECTOR CDebugPrint::GetGridSize()
{
	return VECTOR( COLUMN_WIDTH, LINE_HEIGHT );
}
