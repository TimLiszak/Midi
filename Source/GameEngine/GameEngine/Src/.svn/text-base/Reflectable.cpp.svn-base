#include "StdAfx.h"
#include "Reflectable.h"
#include "Actor.h"

void CReflectInfo::Register(EReflectionType type, const char* p_name, int offset)
{
	m_ref_table[m_num_refs].m_name = p_name;
	m_ref_table[m_num_refs].m_offset = offset;
	m_ref_table[m_num_refs++].m_type = type;
	//TRACE( "Register(%d, %s, %d)\n", type, p_name, offset);
}

void * CReflectable::GetMemberPointer(const char *p_member_name)
{
	CReflectInfo *p_info = GetReflectInfo();
	CReflection *p_ref = p_info->m_ref_table;
	for (int i = 0; i < p_info->m_num_refs; i++) {
		if ( p_ref[i].m_name == p_member_name ) 
		{
			return (void*)((int)this + (int)p_ref[i].m_offset);
		}
	}
	return NULL;
}

void*  CReflectable::GetMemberPointer(const CReflection* pReflection)
{
	return (void*)((int)this + (int)pReflection->m_offset);
}

CReflection* CReflectable::GetReflection(const char *p_member_name)
{
	CReflectInfo *p_info = GetReflectInfo();
	CReflection *p_ref = p_info->m_ref_table;
	for (int i = 0; i < p_info->m_num_refs; i++) {
		if ( p_ref[i].m_name == p_member_name ) 
		{
			return &p_ref[i];
		}
	}
	return NULL;
}

void CReflectable::DumpMembers()
{
	CReflectInfo *p_info = GetReflectInfo();
	CReflection *p_ref  = p_info->m_ref_table;
	for (int i = 0; i < p_info->m_num_refs; i++) 
	{
		void *p = (void*)((int)this + (int)p_ref[i].m_offset);
		TRACE( "%d,%s,", p_ref[i].m_type,p_ref[i].m_name.c_str() );

		switch ( p_ref[i].m_type ) 
		{
			case REF_INT:
				TRACE("%d",*(int*)p);
				break;
			case REF_FLOAT:
				TRACE("%f",*(float*)p);
				break;
		}
		TRACE("\n");	
	}
}
