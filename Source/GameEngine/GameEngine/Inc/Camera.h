
#ifndef _CAMERA_H_
#define _CAMERA_H_

class CCamera
{
public:
	virtual void	Update( const FLOAT fFrameTime, BOOL bIsCurrent ) = 0;
	virtual FLOAT	GetZoom() { return 1.0f; }
	virtual BOOL	GetLimits( VECTOR& vMin, VECTOR& vMax ) { return FALSE; }
	virtual VECTOR	GetScroll() = 0;
	virtual VECTOR	GetScrollNoLimit() { return GetScroll(); };
	virtual FLOAT	GetSpeed() { return 0.0f; }

	virtual BOOL	IsEventCamera() { return FALSE; }

	void		SetName( std::string Name ) { m_Name = Name; }
	std::string GetName() { return m_Name; }

private:
	std::string m_Name;
};

#endif
