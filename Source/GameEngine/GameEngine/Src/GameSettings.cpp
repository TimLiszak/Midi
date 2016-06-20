#include "StdAfx.h"
#include "GameSettings.h"
#include "FileSerializer.h"
#include "Input.h"

enum EGameSettingsFileVersion
{
	EGameSettingsFileVersion_Initial		= 0,
	EGameSettingsFileVersion_Max
};
static const EGameSettingsFileVersion	CURRENT_SAVE_VERSION = (EGameSettingsFileVersion)( EGameSettingsFileVersion_Max - 1 );


static const CHAR* FILENAME = "Data/GameSettings.dat";

void CGameSettings::Init()
{
	m_eKeyConfig = EKeyConfig_Xbox;
	LoadFile();

	GetGameEngine()->GetInput()->GetGamepad(0)->SetKeyConfig( (EKeyConfig)m_eKeyConfig );
	GetGameEngine()->GetInput()->GetGamepad(1)->SetKeyConfig( (EKeyConfig)m_eKeyConfig );
}

void CGameSettings::Term()
{
}

void CGameSettings::SetKeyConfig( EKeyConfig eConfig )
{
	m_eKeyConfig = eConfig;
	GetGameEngine()->GetInput()->GetGamepad(0)->SetKeyConfig( (EKeyConfig)m_eKeyConfig );
	GetGameEngine()->GetInput()->GetGamepad(1)->SetKeyConfig( (EKeyConfig)m_eKeyConfig );

	SaveFile();
}

void CGameSettings::Serialize( CSerializer* Serializer )
{
	Serializer->Serialize( m_eKeyConfig );
}

void CGameSettings::LoadFile()
{
	CFileInputSerializer Serializer;
	BOOL bLoaded = Serializer.Open( FILENAME );

	if ( bLoaded )
	{
		this->Serialize( &Serializer );
		Serializer.Close();
	}
}

void CGameSettings::SaveFile()
{
	CFileOutputSerializer Serializer;
	BOOL bOpened = Serializer.Open( FILENAME, CURRENT_SAVE_VERSION );
	if ( bOpened )
	{
		this->Serialize( &Serializer );
		Serializer.Close();
	}
}
