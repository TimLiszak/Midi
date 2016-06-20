
#ifndef _VECTOR_2D_H_
#define _VECTOR_2D_H_

class CVector2d
{
public:
	CVector2d() : x(0.0f), y(0.0f) {}
	CVector2d( DOUBLE x, DOUBLE y ) : x((FLOAT)x), y((FLOAT)y) {}
	CVector2d( FLOAT x, FLOAT y ) : x(x), y(y) {}
	CVector2d( INT x, INT y ) : x((FLOAT)x), y((FLOAT)y) {}
	FLOAT x;
	FLOAT y;

	inline BOOL IsZero( const FLOAT fTolerance = EPSILON ) const
	{
		return x >= -EPSILON && x <= EPSILON &&
			   y >= -EPSILON && y <= EPSILON;
	}

	inline void	Set( DOUBLE _x, DOUBLE _y )
	{
		x = (FLOAT)_x;
		y = (FLOAT)_y;
	}

	inline void	Set( FLOAT _x, FLOAT _y )
	{
		x = _x;
		y = _y;
	}

	inline void	Set( INT _x, INT _y )
	{
		x = (FLOAT)_x;
		y = (FLOAT)_y;
	}

	inline CVector2d operator*(const FLOAT& f) const
	{
		CVector2d Result;
		Result.x = this->x * f;
		Result.y = this->y * f;
		return Result;
	}

	inline CVector2d operator/(const FLOAT& f) const
	{
		CVector2d Result;
		Result.x = this->x / f;
		Result.y = this->y / f;
		return Result;
	}

	inline CVector2d operator-(const CVector2d& vec) const
	{
		CVector2d Result;
		Result.x = this->x - vec.x;
		Result.y = this->y - vec.y;
		return Result;
	}

	inline CVector2d operator+(const CVector2d& vec) const
	{
		CVector2d Result;
		Result.x = this->x + vec.x;
		Result.y = this->y + vec.y;
		return Result;
	}

	inline CVector2d operator=(const CVector2d& vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		return *this;
	}

	inline void operator+=( const CVector2d& vec )
	{
		this->x += vec.x;
		this->y += vec.y;
	}

	inline CVector2d operator-()
	{
		CVector2d Result;
		Result.x = -this->x;
		Result.y = -this->y;
		return Result;
	}

	inline void operator-=( const CVector2d& vec )
	{
		this->x -= vec.x;
		this->y -= vec.y;
	}

	inline void operator*=( const FLOAT& f )
	{
		this->x *= f;
		this->y *= f;
	}

	inline FLOAT & operator[]( const UINT i )
	{
		switch(i)
		{
		case 0:
			return this->x;
		default:
			return this->y;
		}
	}

	inline const FLOAT & operator[]( const UINT i ) const
	{
		switch(i)
		{
		case 0:
			return this->x;
		default:
			return this->y;
		}
	}

	inline BOOL operator!=(const CVector2d& vec)
	{
		return this->x != vec.x || this->y != vec.y;
	}

	inline FLOAT GetLengthSquared() const
	{
		return ( x * x + y * y );
	}

	inline FLOAT GetLength() const
	{
		return sqrt( GetLengthSquared() );
	}

	inline CVector2d Normalize() const
	{
		FLOAT fLength = GetLength();
		CVector2d vNormalized;
		vNormalized.x = x / fLength;
		vNormalized.y = y / fLength;
		return vNormalized;
	}
	
};

#endif
