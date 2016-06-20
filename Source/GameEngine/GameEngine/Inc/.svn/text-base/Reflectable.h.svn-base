#ifndef _REFLECTABLE_H_
#define _REFLECTABLE_H_

#define	MAX_REF 32
#define MAX_ID_LEN 128

#define INIT_REFLECT( TYPE ) \
	{ \
		InitReflect< TYPE >( #TYPE ); \
	}

#define REFLECTION_INFO	static CReflectInfo m_ref_info; \
	virtual CReflectInfo * GetReflectInfo() {return &m_ref_info;} \
	void RegisterMembers(CReflectInfo* p_info); 

#define REGISTER( TYPE, MEMBER )	p_info->Register(TYPE,#MEMBER,(int)((long)&MEMBER-(long)this))
#define REGISTER_LIMIT( TYPE, MEMBER, LIMITX, LIMITY ) \
	{ \
		p_info->Register(TYPE,#MEMBER,(int)((long)&MEMBER-(long)this)); \
		GetReflection( #MEMBER )->SetLimits( VECTOR( LIMITX, LIMITY ) ); \
	} 
#define REGISTER_ALL( TYPE, MEMBER, LIMITX, LIMITY, INC ) \
	{ \
		p_info->Register(TYPE,#MEMBER,(int)((long)&MEMBER-(long)this)); \
		GetReflection( #MEMBER )->SetLimits( VECTOR( LIMITX, LIMITY ) ); \
		GetReflection( #MEMBER )->m_fIncrement = INC; \
	} 
#define REGISTER_INC( TYPE, MEMBER, INC ) \
	{ \
		p_info->Register(TYPE,#MEMBER,(int)((long)&MEMBER-(long)this)); \
		GetReflection( #MEMBER )->m_fIncrement = INC; \
	} \


enum	EReflectionType
{
	REF_INT,
	REF_UINT,
	REF_FLOAT,
	REF_VECTOR,
	REF_INTVECTOR,
	REF_STRING,
	REF_REFLECTABLE,

	EReflectionType_Max
};

class CReflection
{
public:
	CReflection() : m_bHasLimits(FALSE), m_fIncrement(1.0f) {}

	inline EReflectionType	GetType() { return m_type; }
	inline void	SetLimits( VECTOR vLimit ) 
	{ 
		m_vLimits = vLimit;
		m_bHasLimits = TRUE;
	}

	template <typename T> 
	void	CheckLimits(T& Val);

	std::string		m_name;
	EReflectionType m_type;
	int				m_offset;
	BOOL			m_bHasLimits;
	VECTOR			m_vLimits;
	FLOAT			m_fIncrement;
};

class	CReflectInfo
{
public:
	void Register(EReflectionType type, const char* p_name, int offset);
	int	m_num_refs;
	CReflection	m_ref_table[MAX_REF];
	std::string m_ClassName;
};

// Base type for all object that are to be reflected
class	CReflectable
{
public:
	void	RegisterMembers(CReflectInfo* p_info) { UNUSED(p_info); };
	void *  GetMemberPointer(const char *p_member_name);
	void *  GetMemberPointer(const CReflection* pReflection);
	CReflection*	GetReflection(const char *p_member_name);

	template <typename T> 
	T		RGet(const char *p_member_name);
	template <typename T> 
	T		RGet(const CReflection* pReflection);

	template <typename T> 
	void	RSet(const char *p_member_name,T value);
	template <typename T> 
	void	RSet(const CReflection* pReflection, T value);

	void	DumpMembers();
	virtual CReflectInfo * GetReflectInfo()=0;

	virtual void	PropertiesUpdated() {}
};

template <class T>
void InitReflect( const char* strClassName ) 
{ 
	strClassName++; // skip 'C'
	T Obj;
	(&Obj)->RegisterMembers(&T::m_ref_info); 
	T::m_ref_info.m_ClassName = strClassName;
}

template <typename T>
T CReflectable::RGet(const char *p_member_name)
{
	return *(T*)GetMemberPointer(p_member_name);
}

template <typename T>
void CReflectable::RSet(const char *p_member_name, T value)
{
	*(T*)GetMemberPointer(p_member_name) = value;
}

template <typename T> 
T CReflectable::RGet(const CReflection* pReflection)
{
	return *(T*)GetMemberPointer(pReflection);
}

template <typename T>
void CReflectable::RSet(const CReflection* pReflection, T value)
{
	*(T*)GetMemberPointer(pReflection) = value;
}

template <typename T> 
void CReflection::CheckLimits(T& Val)
{
	if ( m_bHasLimits )
	{
		Val = Math::Clamp<T>( Val, (T)m_vLimits.x, (T)m_vLimits.y );
	}
}

#endif
