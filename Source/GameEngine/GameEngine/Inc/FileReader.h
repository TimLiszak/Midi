#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <fstream>

class CFileReader
{
public:
	BOOL	Open( const CHAR* pFilename );
	void	Close();

	INT			Read( CHAR* pBuffer, INT nSize );
	std::string	ReadLine();

	BOOL	EndOfFile();

private:
	std::ifstream	m_inputStream;
};

inline BOOL CFileReader::EndOfFile()
{
	return m_inputStream.eof();
}

#endif