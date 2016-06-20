#include "StdAfx.h"
#include "FileReader.h"
#include <iostream>
using namespace std;

static const INT	LINE_BUFFER = 1024;

BOOL CFileReader::Open( const CHAR* pFilename )
{
	m_inputStream.open( pFilename );
	if( !m_inputStream ) 
	{
		cerr << "Error opening file: " << pFilename << endl;
		return FALSE;
	}

	return TRUE;
}

void CFileReader::Close()
{ 
	m_inputStream.close();
}

INT CFileReader::Read( CHAR* pBuffer, INT nSize )
{
	m_inputStream.read( pBuffer, nSize );
	return (INT)m_inputStream.gcount();
}

std::string CFileReader::ReadLine()
{
	CHAR Buf[ LINE_BUFFER ];
	m_inputStream.getline( Buf, LINE_BUFFER );
	return std::string( Buf );
}
