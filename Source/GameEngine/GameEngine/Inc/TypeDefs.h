
#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

const FLOAT EPSILON = 1.0e-6f;

#include "Vector2d.h"

struct SColour
{
	SColour() : r(0.0f), g(0.0f), b(0.0f) {}
	SColour( FLOAT r, FLOAT g, FLOAT b ) : r(r), g(g), b(b), a(1.0f) {}
	SColour( FLOAT r, FLOAT g, FLOAT b, FLOAT a ) : r(r), g(g), b(b), a(a) {}
	FLOAT r;
	FLOAT g;
	FLOAT b;
	FLOAT a;
};

typedef CVector2d	VECTOR;
typedef SColour		COLOUR_RGB;

#ifndef M_PI
#define M_PI	(3.1415926535f)
#endif

#define DEGREES(x) ((x) * 180.0f / M_PI)

#ifdef TRACE
#undef TRACE
#endif
#ifdef ASSERT
#undef ASSERT
#endif
#ifdef UNUSED
#undef UNUSED
#endif

#define TRACE			DebugTrace
#define ASSERT			assert
#define UNUSED(x)		(void)x
#endif

#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }
