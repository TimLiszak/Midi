#include "StdAfx.h"
#include "TextParser.h"
#include <cstring>

CTextParser::CTextParser( std::string InputString )
{
	m_pInputString = InputString.c_str();
	m_pParseContext = _strdup( m_pInputString );
}

std::string CTextParser::ParseToken()
{
	CHAR delims[] = " ";
	CHAR *pResult = NULL;
	pResult = strtok_s( NULL, delims, &m_pParseContext );

	if ( pResult != NULL )
	{
		std::string strResult = pResult;
		return strResult;
	}
	return "";
}

INT CTextParser::ParseInt()
{
	INT nValue = 0;
	std::string strToken = ParseToken();
	if ( strToken.size() > 0 )
	{
		nValue = atoi( strToken.c_str() );
	}
	return nValue;
}

FLOAT CTextParser::ParseFloat()
{
	FLOAT fValue = 0.0f;
	std::string strToken = ParseToken();
	if ( strToken.size() > 0 )
	{
		fValue = (FLOAT)atof( strToken.c_str() );
	}
	return fValue;
}

BOOL	CTextParser::CompareToken( CHAR* pToken, const CHAR* pString )
{
	return strcmp( pToken, pString ) == 0;
}
