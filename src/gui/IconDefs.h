
#ifndef IconDefs_h
#define IconDefs_h

#include "catalog/CatalogDefs.h"
#include "album/AlbumDefs.h"

#include "art/StampBlack.xpm"
#include "art/StampBlue.xpm"
#include "art/StampBrown.xpm"
#include "art/StampGreen.xpm"
#include "art/StampPurple.xpm"
#include "art/StampRed.xpm"
#include "art/StampYellow.xpm"

#include "art/StampBlackBlock.xpm"
#include "art/StampBlueBlock.xpm"
#include "art/StampBrownBlock.xpm"
#include "art/StampGreenBlock.xpm"
#include "art/StampPurpleBlock.xpm"
#include "art/StampRedBlock.xpm"
#include "art/StampYellowBlock.xpm"

#include "art/StampBlackMiniSheet.xpm"
#include "art/StampBlueMiniSheet.xpm"
#include "art/StampBrownMiniSheet.xpm"
#include "art/StampGreenMiniSheet.xpm"
#include "art/StampPurpleMiniSheet.xpm"
#include "art/StampRedMiniSheet.xpm"
#include "art/StampYellowMiniSheet.xpm"

#include "art/StampBlackSouvenirSheet.xpm"
#include "art/StampBlueSouvenirSheet.xpm"
#include "art/StampBrownSouvenirSheet.xpm"
#include "art/StampGreenSouvenirSheet.xpm"
#include "art/StampPurpleSouvenirSheet.xpm"
#include "art/StampRedSouvenirSheet.xpm"
#include "art/StampYellowSouvenirSheet.xpm"
#include "art/folder.xpm"

#include "art/unchecked.xpm"
#include "art/checked.xpm"


typedef enum
{
    Icon_Stamp = 0,
    Icon_StampSelected,
    Icon_StampBlock,
    Icon_StampBlockSelected,
    Icon_StampMiniSheet,
    Icon_StampMiniSheetSelected,
    Icon_StampSouvenirSheet,
    Icon_StampSouvenirSheetSelected,
    Icon_Folder
} IconID;

extern IconID AlbumImageSelection[ Layout::AT_NbrAlbumTypes ][ 2 ];
extern IconID CatalogImageSelection[ Catalog::FT_NbrTypes ][ 2 ] ;

wxImageList* CreateAlbumImageList( );
wxImageList* CreateAlbumStateImageList( bool del );
wxImageList* CreateCatalogImageList( );
wxImageList* CreateCatalogStateImageList(bool del);

#endif