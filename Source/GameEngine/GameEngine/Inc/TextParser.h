#ifndef _TEXTPARSER_H_
#define _TEXTPARSER_H_

class CTextParser
{
public:
	static const INT	MAX_TOKEN_SIZE = 50;

	CTextParser( std::string InputString );

	std::string	ParseToken();
	INT			ParseInt();
	FLOAT		ParseFloat();

	BOOL	CompareToken( CHAR* pToken, const CHAR* pString );

private:
	CTextParser();
	const CHAR*	m_pInputString;
	CHAR*	m_pParseContext;
};

#endif