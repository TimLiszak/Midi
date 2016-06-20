#ifndef _FILE_VERSION_H_
#define _FILE_VERSION_H_

enum EFileVersion
{
	EFileVersion_Initial				= 0,
	EFileVersion_TileSetMapping			= 1,
	EFileVersion_TileProperties			= 2,
	EFileVersion_DoorKeyFix				= 3,
	EFileVersion_Sprite					= 4,
	EFileVersion_TileFlip				= 5,
	EFileVersion_TileProperties2		= 6,
    EFileVersion_TileSlopes             = 7,
    EFileVersion_DrawLayer              = 8,
    EFileVersion_LookAtRotator          = 9,
    EFileVersion_CameraScroll           = 10,
    EFileVersion_MoverStartTime         = 11,
    EFileVersion_LaserCollide           = 12,

	EFileVersion_Max
};

static const EFileVersion	CURRENT_FILE_VERSION = (EFileVersion)( EFileVersion_Max - 1 );

#endif
