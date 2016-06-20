
#ifndef _SERIALIZER_H_
#define _SERIALIZER_H_

class CSerializable
{
public:
	virtual void	Serialize( class CSerializer* Serializer ) = 0;
};


class CSerializer
{
public:
	virtual ~CSerializer() {}

	virtual INT		GetVersion() = 0;
	virtual BOOL	IsReading() = 0;
	virtual BOOL	IsWriting() = 0;
	virtual void	BulkSerialize( void* pData, UINT nSize ) = 0;
	
	inline void		Serialize( CHAR& Val ) { BulkSerialize( &Val, sizeof(CHAR) ); }
	inline void		Serialize( BYTE& Val ) { BulkSerialize( &Val, sizeof(BYTE) ); }
	inline void		Serialize( SHORT& Val ) { BulkSerialize( &Val, sizeof(SHORT) ); }
	inline void		Serialize( USHORT& Val ) { BulkSerialize( &Val, sizeof(USHORT) ); }
	inline void		Serialize( INT& Val ) { BulkSerialize( &Val, sizeof(INT) ); }
	inline void		Serialize( UINT& Val ) { BulkSerialize( &Val, sizeof(UINT) ); }
	inline void		Serialize( LONG& Val ) { BulkSerialize( &Val, sizeof(LONG) ); }
	inline void		Serialize( ULONG& Val ) { BulkSerialize( &Val, sizeof(ULONG) ); }
	inline void		Serialize( FLOAT& Val ) { BulkSerialize( &Val, sizeof(FLOAT) ); }
	inline void		Serialize( DOUBLE& Val ) { BulkSerialize( &Val, sizeof(DOUBLE) ); }
	inline void		Serialize( CSerializable& Val ) { Val.Serialize( this ); }

	void	Serialize( VECTOR& Val );
	void	Serialize( std::string& strVal );

	template <typename T> 
	void	Serialize( std::list<T>& Val );
	template <typename T> 
	void	Serialize( std::vector<T>& Val );

};

template <typename T> 
void CSerializer::Serialize( std::list<T>& Val )
{
	if ( IsReading() )
	{
		Val.clear();

		UINT uLength = 0;
		Serialize( uLength );

		for (UINT i = 0; i < uLength; i++)
		{
			T NewItem;
			Serialize( NewItem );
			Val.push_back( NewItem );
		}
	}
	else if ( IsWriting() )
	{
		UINT uLength = Val.size();
		Serialize( uLength );

		std::list<T>::iterator it;
		for ( it = Val.begin() ; it != Val.end(); it++ )
		{
			Serialize( (*it) );
		}
	}
}

template <typename T> 
void CSerializer::Serialize( std::vector<T>& Val )
{
	if ( IsReading() )
	{
		Val.clear();

		UINT uLength = 0;
		Serialize( uLength );

		for (UINT i = 0; i < uLength; i++)
		{
			T NewItem;
			Serialize( NewItem );
			Val.push_back( NewItem );
		}
	}
	else if ( IsWriting() )
	{
		UINT uLength = Val.size();
		Serialize( uLength );

		std::vector<T>::iterator it;
		for ( it = Val.begin() ; it != Val.end(); it++ )
		{
			Serialize( (*it) );
		}
	}
}


#endif