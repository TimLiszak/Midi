#include "StdAfx.h"
#include "ReflectableEditor.h"
#include "Input.h"

void CReflectableEditor::Init()
{
	m_pObject = NULL;
	m_nSelectedMember = 0;
	m_fButtonHoldTime = 0.0f;
	m_bEditString = FALSE;
	m_strEditString = "";
	m_bSetPosition = FALSE;
	m_vPosition.Set( 0.0f, 0.0f );
}

void CReflectableEditor::Term()
{
}

void CReflectableEditor::Update( const FLOAT fFrameTime )
{
	if ( !m_pObject )
	{
		return;
	}
	static const INT	CHANGE_SPEED = 1;
	CKeyboard* pKey = GetGameEngine()->GetInput()->GetKeyboard();

	/*
	if( pKey->IsKeyTriggered( EKbKey_BACK ) && m_Stack.size() > 0 )
	{
		m_pObject = m_Stack.back();
		m_Stack.pop_back();
	}*/

	COLOUR_RGB ClrSelected( 0.8f, 0.8f, 0.0f );
	COLOUR_RGB ClrNormal( 0.8f, 0.8f, 0.8f );
	CReflectInfo *p_info = m_pObject->GetReflectInfo();
	CReflection *p_ref  = p_info->m_ref_table;


	if ( m_bSetPosition )
	{
		GetGameEngine()->GetDebugPrint()->SetPosition( m_vPosition );
	}
	GetGameEngine()->GetDebugPrint()->ChangeColour( ClrNormal );
	GetGameEngine()->GetDebugPrint()->Printf( "%s", p_info->m_ClassName.c_str() );

	INT	nKeyDownX = 0;
	INT	nKeyDownY = 0;
	INT	nKeyTriggeredX = 0;
	INT	nKeyTriggeredY = 0;
	BOOL bHeld = FALSE;

	if ( pKey->IsKeyDown( EKbKey_NUMPAD4 ) )
	{
		nKeyDownX = -CHANGE_SPEED;
		bHeld = TRUE;
	}
	if ( pKey->IsKeyDown( EKbKey_NUMPAD6 ) )
	{
		nKeyDownX = CHANGE_SPEED;
		bHeld = TRUE;
	}
	if ( pKey->IsKeyDown( EKbKey_NUMPAD2 ) )
	{
		nKeyDownY = CHANGE_SPEED;
		bHeld = TRUE;
	}
	if ( pKey->IsKeyDown( EKbKey_NUMPAD8 ) )
	{
		nKeyDownY = -CHANGE_SPEED;
		bHeld = TRUE;
	}
	if ( bHeld )
	{
		m_fButtonHoldTime += fFrameTime;
	}
	else
	{
		m_fButtonHoldTime = 0.0f;
	}

	if ( pKey->IsKeyTriggered( EKbKey_NUMPAD4 ) )
	{
		nKeyTriggeredX = -CHANGE_SPEED;
	}
	if ( pKey->IsKeyTriggered( EKbKey_NUMPAD6 ) )
	{
		nKeyTriggeredX = CHANGE_SPEED;
	}
	if ( pKey->IsKeyTriggered( EKbKey_NUMPAD2 ) )
	{
		nKeyTriggeredY = CHANGE_SPEED;
	}
	if ( pKey->IsKeyTriggered( EKbKey_NUMPAD8 ) )
	{
		nKeyTriggeredY = -CHANGE_SPEED;
	}

	BOOL bNext = FALSE;
	BOOL bPrev = FALSE;
	bPrev |= pKey->IsKeyTriggered( EKbKey_SUBTRACT );
	bNext |= pKey->IsKeyTriggered( EKbKey_ADD );
	
	if ( bPrev )
	{
		m_nSelectedMember--;
		if ( m_nSelectedMember < 0 )
		{
			m_nSelectedMember = p_info->m_num_refs - 1;
		}
        EndEditString();
	}
	else if ( bNext )
	{
		m_nSelectedMember++;
        EndEditString();
	}
	if ( m_nSelectedMember >= p_info->m_num_refs )
	{
		m_nSelectedMember = 0;
        EndEditString();
	}

	for (int i = 0; i < p_info->m_num_refs; i++) 
	{
		if ( i == m_nSelectedMember )
		{
			GetGameEngine()->GetDebugPrint()->ChangeColour( ClrSelected );
		}
		else
		{
			GetGameEngine()->GetDebugPrint()->ChangeColour( ClrNormal );
		}
		INT nIncX = 0;
		INT nIncY = 0;
		if ( m_fButtonHoldTime < 0.25f )
		{
			nIncX = nKeyTriggeredX;
			nIncY = nKeyTriggeredY;
		}
		else if ( m_fButtonHoldTime < 2.0f )
		{
			nIncX = nKeyDownX;
			nIncY = nKeyDownY;
		}
		else
		{
			nIncX = nKeyDownX * 5;
			nIncY = nKeyDownY * 5;
		}

		switch ( p_ref[i].GetType() ) 
		{
			case REF_INT:
			{
				INT Val = m_pObject->RGet<INT>( &p_ref[i] );
				GetGameEngine()->GetDebugPrint()->Printf( "%s %d", p_ref[i].m_name.c_str(), Val );

				if ( i == m_nSelectedMember ) 
				{
					Val += nIncX;
					p_ref[i].CheckLimits<INT>(Val);
					m_pObject->RSet<INT>( &p_ref[i], Val );
					m_pObject->PropertiesUpdated();
				}
			}
			break;
			case REF_UINT:
			{
				UINT Val = m_pObject->RGet<UINT>( &p_ref[i] );
				GetGameEngine()->GetDebugPrint()->Printf( "%s %d", p_ref[i].m_name.c_str(), Val );

				if ( i == m_nSelectedMember ) 
				{
					Val = (UINT)Math::Max( (INT)(Val + nIncX), 0 );
					p_ref[i].CheckLimits<UINT>(Val);
					m_pObject->RSet<UINT>( &p_ref[i], Val );
					m_pObject->PropertiesUpdated();
				}
			}
			break;
			case REF_FLOAT:
			{
				FLOAT Val = m_pObject->RGet<FLOAT>( &p_ref[i] );
				GetGameEngine()->GetDebugPrint()->Printf( "%s %.2f", p_ref[i].m_name.c_str(), Val );

				if ( i == m_nSelectedMember ) 
				{
					Val += nIncX * p_ref[i].m_fIncrement;
					p_ref[i].CheckLimits<FLOAT>(Val);
					m_pObject->RSet<FLOAT>( &p_ref[i], Val );
					m_pObject->PropertiesUpdated();
				}

			}
			break;
			case REF_VECTOR:
			{
				VECTOR Val = m_pObject->RGet<VECTOR>( &p_ref[i] );
				GetGameEngine()->GetDebugPrint()->Printf( "%s %.2f %.2f", p_ref[i].m_name.c_str(), Val.x, Val.y );

				if ( i == m_nSelectedMember ) 
				{
					Val.x += nIncX * p_ref[i].m_fIncrement;
					Val.y += nIncY * p_ref[i].m_fIncrement;
					p_ref[i].CheckLimits<FLOAT>(Val.x);
					p_ref[i].CheckLimits<FLOAT>(Val.y);
					m_pObject->RSet<VECTOR>( &p_ref[i], Val );
					m_pObject->PropertiesUpdated();
				}
			}
			break;
			case REF_INTVECTOR:
			{
				VECTOR Val = m_pObject->RGet<VECTOR>( &p_ref[i] );
				GetGameEngine()->GetDebugPrint()->Printf( "%s %.2f %.2f", p_ref[i].m_name.c_str(), Val.x, Val.y );

				if ( i == m_nSelectedMember ) 
				{
					Val.x += nIncX * p_ref[i].m_fIncrement;
					Val.y += nIncY * p_ref[i].m_fIncrement;
					p_ref[i].CheckLimits<FLOAT>(Val.x);
					p_ref[i].CheckLimits<FLOAT>(Val.y);
					m_pObject->RSet<VECTOR>( &p_ref[i], Val );
					m_pObject->PropertiesUpdated();
				}
			}
			break;

			case REF_STRING:
			{
				if ( i == m_nSelectedMember )
				{
                    BOOL bShift = pKey->IsKeyDown( EKbKey_SHIFT );
					INT nKeyChar = pKey->GetNextCharacter();
					while( nKeyChar > 0 )
					{
						if ( nKeyChar >= 'A' && nKeyChar <= 'Z' )
						{
                            if ( bShift )
                            {
                                AddToEditString( (CHAR)nKeyChar );
                            }
                            else
                            {
							    AddToEditString( 'a' + ( (CHAR)nKeyChar - 'A' ) );
                            }
						}
                        switch( nKeyChar )
                        {
                            case EKbKey_DASH:
                            {
                                AddToEditString( '_' );
                            }
                            break;
                            case EKbKey_PERIOD:
                            {
                                AddToEditString( '.' );
                            }
                            break;
                            case EKbKey_FORWARDSLASH: 
                            {
                                AddToEditString( '/' );
                            }
                            break;
                            case EKbKey_BACKSLASH: 
                            {
                                AddToEditString( '\\' );
                            }
                            break;

                        }
						nKeyChar = pKey->GetNextCharacter();
					}

                    if ( m_bEditString )
                    {
                        if ( pKey->IsKeyTriggered( EKbKey_RETURN ) )
                        {
                            m_pObject->RSet<std::string>( &p_ref[i], m_strEditString );
                            EndEditString();
                        }
                        if ( pKey->IsKeyTriggered( EKbKey_BACK ) )
                        {
                            if ( m_strEditString.size() > 0 )
                            {
                                m_strEditString = m_strEditString.substr( 0, m_strEditString.size() - 1 );
                            }
                        }
                    }
				}

				if ( m_bEditString )
				{
					std::string Val = m_pObject->RGet<std::string>( &p_ref[i] );
					GetGameEngine()->GetDebugPrint()->Printf( "%s %s", p_ref[i].m_name.c_str(), m_strEditString.c_str() );
				}
				else
				{
					std::string Val = m_pObject->RGet<std::string>( &p_ref[i] );
					GetGameEngine()->GetDebugPrint()->Printf( "%s %s", p_ref[i].m_name.c_str(), Val.c_str() );
				}
			}
			break;

			case REF_REFLECTABLE:
			{
				CReflectable* Val = m_pObject->RGet<CReflectable*>( &p_ref[i] );
				GetGameEngine()->GetDebugPrint()->Printf( "%s >>", p_ref[i].m_name.c_str() );

				if ( i == m_nSelectedMember )
				{
					if( pKey->IsKeyTriggered( EKbKey_RETURN ) )
					{
						m_Stack.push_back( m_pObject );
						m_pObject = Val;
					}
				}
			}
			break;
			
		}
	}
}

void CReflectableEditor::AddToEditString( CHAR ch )
{
    if ( !m_bEditString )
    {
        m_strEditString = "";
    }
    m_strEditString.push_back( ch );
    m_bEditString = TRUE;
    GetGameEngine()->DisableBackspaceQuit( TRUE );
}

void CReflectableEditor::EndEditString()
{
    GetGameEngine()->DisableBackspaceQuit( FALSE );
    m_bEditString = FALSE;
}

void CReflectableEditor::Render()
{
}

