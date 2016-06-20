#include "StdAfx.h"
#include "CameraManager.h"
#include "View.h"
#include "DebugCamera.h"
#include "PlayerCamera.h"
#include "TransitionCamera.h"
#include "CoopCamera.h"

void CCameraManager::Init()
{
	m_pCoopCamera = new CCoopCamera();
	m_CameraMap["debug"] = new CDebugCamera();
	m_bTransition = FALSE;
	m_pTransitionCamera = new CTransitionCamera();
	m_pCurrentCamera = m_pCoopCamera;
}

void CCameraManager::Term()
{
	delete m_pTransitionCamera;
	delete m_pCoopCamera;
	delete m_CameraMap["debug"];
	m_CameraMap.clear();
}

void CCameraManager::AddCamera( std::string CameraName, CCamera* pCamera )
{
	pCamera->SetName( CameraName );
	m_CameraMap[ CameraName ] = pCamera;
}

void CCameraManager::RemoveCamera( std::string CameraName )
{
	m_CameraMap[ CameraName ] = NULL;
}

void CCameraManager::Update( const FLOAT fFrameTime )
{
	if ( m_bTransition )
	{
		m_pTransitionCamera->Update( fFrameTime, TRUE );
		if ( m_pTransitionCamera->IsFinished() )
		{
			CCamera* pNext = m_pTransitionCamera->EndTransition();
			m_pCurrentCamera = pNext;
			m_bTransition = FALSE;
		}
	}

	std::map< std::string, CCamera* >::iterator it;
	for ( it = m_CameraMap.begin() ; it != m_CameraMap.end(); it++ )
	{
		CCamera* pCamera = (*it).second;
		if ( pCamera && pCamera != m_pCurrentCamera )
		{
			pCamera->Update( fFrameTime, FALSE );
		}
	}

	m_pCurrentCamera->Update( fFrameTime, TRUE );
}

CCamera* CCameraManager::GetCamera( std::string CameraName )
{
	return m_CameraMap[CameraName];
}

CCamera* CCameraManager::GetCurrentCamera( INT nIndex )
{
	return m_pCoopCamera->GetCamera( nIndex );
}

void CCameraManager::ClearCurrentCamera()
{
	m_pCoopCamera->SetCamera( 0, NULL );
	m_pCoopCamera->SetCamera( 1, NULL );
}

void CCameraManager::SetCurrentCamera( INT nIndex, std::string CameraName )
{
	CCamera* pCamera = GetCamera( CameraName );
	if ( pCamera->IsEventCamera() )
	{
		m_pCurrentCamera = pCamera;
	}
	else
	{
		m_pCoopCamera->SetCamera( nIndex, pCamera );
	}
}

void CCameraManager::TransitionToCamera( INT nIndex, std::string CameraName, FLOAT fTime )
{
	CCamera* pCamera = GetCamera( CameraName );
	if ( pCamera->IsEventCamera() )
	{
		if ( !m_bTransition )
		{
			CCamera* pCameraOld = m_pCoopCamera;
			ASSERT( pCameraOld != pCamera );
			ASSERT( pCameraOld );

			if ( pCamera )
			{
				m_pTransitionCamera->StartTransition( pCameraOld, pCamera, fTime );
				m_pCurrentCamera = m_pTransitionCamera;
				m_bTransition = TRUE;
			}
		}
	}
	else
	{
		SetCurrentCamera( nIndex, CameraName );
	}

}

void CCameraManager::SetPreviousCamera()
{
	GetGameEngine()->GetCameraManager()->SetCameraCut( TRUE );
	m_pCurrentCamera = m_pCoopCamera;
}

void CCameraManager::TransitionToPreviousCamera( FLOAT fTime )
{
	GetGameEngine()->GetCameraManager()->SetCameraCut( TRUE );
	m_pCurrentCamera = m_pCoopCamera;
}

VECTOR CCameraManager::GetCurrentScroll()
{
	if ( m_pCurrentCamera )
	{
        VECTOR vScroll = m_pCurrentCamera->GetScroll();
        vScroll += GetGameEngine()->GetView()->GetViewSize() * 0.5f;
		return vScroll;
	}
	return VECTOR( 0.0f, 0.0f );
}

FLOAT CCameraManager::GetCurrentZoom()
{
	if ( m_pCurrentCamera )
	{
		return m_pCurrentCamera->GetZoom();
	}
	return 1.0f;
}

void CCameraManager::SetCameraCut( BOOL bCut )
{
	m_pCoopCamera->SetCameraCut( bCut );
}
