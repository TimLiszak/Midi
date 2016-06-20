
#ifndef _CAMERA_MANAGER_H_
#define _CAMERA_MANAGER_H_

#include "Camera.h"
#include "CoopCamera.h"

class CCameraManager
{
public:
	void	Init();
	void	Term();
	void	Update( const FLOAT fFrameTime );

	void		AddCamera( std::string CameraName, CCamera*	pCamera );
	void		RemoveCamera( std::string CameraName );
	CCamera*	GetCamera( std::string CameraName );
	void		ClearCurrentCamera();

	void		SetCurrentCamera( INT nIndex, std::string CameraName );
	void		TransitionToCamera( INT nIndex, std::string CameraName, FLOAT fTime );

	void		SetPreviousCamera();
	void		TransitionToPreviousCamera( FLOAT fTime );

	CCamera*	GetCurrentCamera( INT nIndex );
	std::string	GetCurrentCameraName( INT nIndex );

	VECTOR		GetCurrentScroll();
	FLOAT		GetCurrentZoom();

	void		SetCameraCut( BOOL bCut );

private:
	std::map< std::string, CCamera* >	m_CameraMap;
	void		SetCurrentCamera( CCamera* pCamera );
	void		TransitionToCamera( CCamera* pCamera, FLOAT fTime );

	class CCoopCamera*			m_pCoopCamera;
	class CTransitionCamera*	m_pTransitionCamera;
	BOOL						m_bTransition;

	CCamera*	m_pCurrentCamera;
};

inline std::string	CCameraManager::GetCurrentCameraName( INT nIndex )
{
	CCamera* pCamera = GetCurrentCamera( nIndex );
	if ( pCamera )
	{
		return pCamera->GetName();
	}
	return "None";
}

#endif
