#ifndef _MATHDEFS_H_
#define _MATHDEFS_H_

namespace Math
{
	const FLOAT PI			= 3.141592654f;
	const FLOAT INV_PI		= 0.318309886f;
	const FLOAT INV_2PI		= 0.159154943f;
	
	template<class T> inline T Abs( T Value1 )
	{
		return ( ( Value1 < 0 ) ? -Value1 : Value1 );
	}

	inline FLOAT Degree2Radian( FLOAT fDegree )
	{
		return fDegree * PI / 180.0f;
	}

	inline FLOAT Radian2Degree( FLOAT fDegree )
	{
		return fDegree * 180.0f / PI;
	}

	inline FLOAT Sin( FLOAT fRadians )
	{
		return sin( fRadians );
	}

	inline FLOAT Cos( FLOAT fRadians )
	{
		return cos( fRadians );
	}

	inline FLOAT SinD( FLOAT fDegrees )
	{
		return sin( Degree2Radian( fDegrees ) );
	}

	inline FLOAT CosD( FLOAT fDegrees )
	{
		return cos( Degree2Radian( fDegrees ) );
	}

	inline FLOAT ATan( FLOAT fX, FLOAT fY )
	{
		if ( fY > 0 )
		{
			return atan( fX / fY );
		}
		else if ( fY < 0 )
		{
			return atan( fX / fY ) + PI;
		}
		else
		{
			return INV_PI;
		}

	}	

	inline FLOAT ATanD( FLOAT fX, FLOAT fY )
	{
		return Radian2Degree( ATan( fX, fY ) );
	}

	template<class T> inline T Clamp( T Value, T Min, T Max )
	{
		return ( ( Value >= Max ) ? Max : ( Value <= Min ? Min : Value ) );
	}

	template<class T> inline T Min( T Value1, T Value2 )
	{
		return ( ( Value1 <= Value2 ) ? Value1 : Value2 );
	}

	template<class T> inline T Max( T Value1, T Value2 )
	{
		return ( ( Value1 >= Value2 ) ? Value1 : Value2 );
	}

	inline VECTOR GetDirectionD( FLOAT fAngle )
	{
		VECTOR vDir( Math::SinD( fAngle ), Math::CosD( fAngle ) );
		return vDir;
	}

	inline VECTOR GetDirection( FLOAT fAngle )
	{
		VECTOR vDir( Math::Sin( fAngle ), Math::Cos( fAngle ) );
		return vDir;
	}

	inline FLOAT FitAngle( FLOAT fAngle )
	{
		FLOAT fWindings = (FLOAT)(INT)(fAngle * INV_2PI);
		FLOAT fRemainder = fAngle - 2.0f * PI * fWindings;

		if ( fRemainder >= PI )
		{
			fRemainder -= 2.0f * PI;
		}
		else if ( fRemainder < -PI )
		{
			fRemainder += 2.0f * PI;
		}
		return fRemainder;
	}
	
	inline FLOAT FitAngleD( FLOAT fAngle )
	{
		FLOAT fWindings = (FLOAT)(INT)(fAngle / 360.0f);
		FLOAT fRemainder = fAngle - 360.0f * fWindings;

		if ( fRemainder >= 180.0f )
		{
			fRemainder -= 360.0f;
		}
		else if ( fRemainder < -180.0f )
		{
			fRemainder += 360.0f;
		}
		return fRemainder;
	}

};

#endif