#include "StdAfx.h"
#include "Serializer.h"
static const UINT	STR_BUFFER_SIZE = 1024;

void CSerializer::Serialize( std::string& strVal )
{
	UINT uLength = 0;
	CHAR Buf[STR_BUFFER_SIZE];

	if ( IsWriting() )
	{
		uLength = strVal.length() + 1;
		ASSERT( uLength < STR_BUFFER_SIZE );

		const char* pStr = strVal.c_str();
		strcpy_s( Buf, uLength, pStr );
	}

	Serialize( uLength );
	ASSERT( uLength < STR_BUFFER_SIZE );

	BulkSerialize( &Buf, uLength );

	if ( IsReading() )
	{
		strVal = Buf;
		ASSERT( strVal.length() + 1 == uLength );
	}
}

void CSerializer::Serialize( VECTOR& Val )
{
	Serialize( Val.x );
	Serialize( Val.y );
}
