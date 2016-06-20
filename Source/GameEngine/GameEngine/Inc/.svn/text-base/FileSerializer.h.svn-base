
#ifndef _FILE_SERIALIZER_H_
#define _FILE_SERIALIZER_H_

class CFileInputSerializer : public CSerializer
{
public:
	virtual ~CFileInputSerializer() {}

	BOOL	Open( std::string Filename );
	void	Close();

	virtual INT		GetVersion() { return m_nVersion; }
	virtual BOOL	IsReading() { return TRUE; }
	virtual BOOL	IsWriting() { return FALSE; }

	virtual void	BulkSerialize( void* pData, UINT nSize );
private:
	std::ifstream	m_InputStream;
	UINT	m_Bytes;
	INT		m_nVersion;
};

class CFileOutputSerializer : public CSerializer
{
public:
	virtual ~CFileOutputSerializer() {}

	BOOL	Open( std::string Filename, INT nVersion );
	void	Close();

	virtual INT		GetVersion() { return m_nVersion; }
	virtual BOOL	IsReading() { return FALSE; }
	virtual BOOL	IsWriting() { return TRUE; }

	virtual void	BulkSerialize( void* pData, UINT nSize );

private:
	std::ofstream	m_OutputStream;
	UINT	m_Bytes;
	INT		m_nVersion;
};

#endif
