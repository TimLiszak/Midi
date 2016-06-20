#include "StdAfx.h"
#include "FileSerializer.h"
using namespace std;

BOOL CFileInputSerializer::Open( std::string Filename )
{
	m_Bytes = 0;
	m_InputStream.open( Filename.c_str(), ios::in | ios::binary );
	if ( !m_InputStream.fail() )
	{
		Serialize( m_nVersion );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CFileInputSerializer::Close()
{
	TRACE( "Bytes Read %d\n", m_Bytes );
	m_InputStream.close();
}

void CFileInputSerializer::BulkSerialize( void* pData, UINT nSize )
{
	m_Bytes += nSize;

	ASSERT( !m_InputStream.eof() );
	m_InputStream.read( (char*)pData, nSize );

	UINT nBytesRead;
	nBytesRead = (UINT)m_InputStream.gcount();
	ASSERT( nSize == nBytesRead );
	ASSERT( !m_InputStream.eof() );
	ASSERT( !m_InputStream.bad() );
	ASSERT( !m_InputStream.fail() );
}

BOOL CFileOutputSerializer::Open( std::string Filename, INT nVersion )
{
	m_nVersion = nVersion;
	m_Bytes = 0;
	m_OutputStream.open( Filename.c_str(), ios::out | ios::binary );
	if ( !m_OutputStream.fail() )
	{
		Serialize( m_nVersion );
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CFileOutputSerializer::Close()
{
	TRACE( "Bytes Written %d\n", m_Bytes );
	m_OutputStream.close();
}

void CFileOutputSerializer::BulkSerialize( void* pData, UINT nSize )
{
	m_Bytes += nSize;

	m_OutputStream.write( (const char*)pData, nSize );
	ASSERT( !m_OutputStream.bad() );
	ASSERT( !m_OutputStream.fail() );
}

