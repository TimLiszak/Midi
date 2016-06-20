
#ifndef _DEBUG_PRINT_H_
#define _DEBUG_PRINT_H_

class CDebugPrint
{
public:
	void	Init();
	void	Term();
	void	Update( const FLOAT fFrameTime );
	void	Render();

	void	Printf( const char *fmt, ... );
	void	ChangeColour( COLOUR_RGB Clr );
	void	SetPosition( VECTOR vPos );

	void	ShowMessage( VECTOR vPos, FLOAT fTime, const char *fmt, ... );

	VECTOR	GetGridSize();
private:
	VECTOR	GetPosition( INT nCol, INT nRow );

	enum ECommand
	{
		ECommand_Print,
		ECommand_Colour,
		ECommand_Position,
		
		ECommand_Max
	};
	struct SCommand
	{
		ECommand eCommand;
		COLOUR_RGB	Clr;
		VECTOR		vPosition;
	};

	struct STimedMessage
	{
		std::string	strMesssage;
		VECTOR vPosition;
		FLOAT fTime;
	};

	std::vector< SCommand > m_CommandQueue;
	std::vector< std::string > m_TextBuffer;
	std::vector< STimedMessage > m_TimedMessages;
};


#endif
