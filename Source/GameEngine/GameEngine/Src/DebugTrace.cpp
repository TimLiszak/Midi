#include "StdAfx.h"
#include "DebugTrace.h"

void DebugTrace( const char *fmt, ... )
{
	// convert variable arguments to string
	char text[1024];
	va_list	ap;		
	va_start(ap, fmt);
    vsprintf_s(text, fmt, ap);
	va_end(ap);

	OutputDebugString( text );
}