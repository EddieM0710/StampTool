
#ifndef IconDefs_h
#define IconDefs_h

#include "catalog/CatalogDefs.h"
#include "design/DesignDefs.h"

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

namespace Design {
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

    extern Design::IconID AlbumImageSelection[ Design::AT_NbrAlbumTypes ][ Catalog::ST_NbrCheckedStatusTypes ];

};
namespace Catalog
{
    typedef enum
    {
        Icon_StampUnknown = 0,
        Icon_Stamp = Icon_StampUnknown,
        Icon_StampMissing,
        Icon_StampSelected = Icon_StampMissing,
        Icon_StampOrdered,
        Icon_StampOwn,
        Icon_StampOwnVariant,
        Icon_StampExclude,
        Icon_StampUnknownBlock,
        Icon_StampBlock = Icon_StampUnknownBlock,
        Icon_StampMissingBlock,
        Icon_StampBlockSelected = Icon_StampMissingBlock,
        Icon_StampOrderedBlock,
        Icon_StampOwnBlock,
        Icon_StampOwnVariantBlock,
        Icon_StampExcludeBlock,
        Icon_StampUnknownMiniSheet,
        Icon_StampMiniSheet = Icon_StampUnknownMiniSheet,
        Icon_StampMissingMiniSheet,
        Icon_StampMiniSheetSelected = Icon_StampMissingMiniSheet,
        Icon_StampOrderedMiniSheet,
        Icon_StampOwnMiniSheet,
        Icon_StampOwnVariantMiniSheet,
        Icon_StampExcludeMiniSheet,
        Icon_StampUnknownSouvenirSheet,
        Icon_StampSouvenirSheet = Icon_StampUnknownSouvenirSheet,
        Icon_StampMissingSouvenirSheet,
        Icon_StampSouvenirSheetSelected = Icon_StampMissingSouvenirSheet,
        Icon_StampOrderedSouvenirSheet,
        Icon_StampOwnSouvenirSheet,
        Icon_StampOwnVariantSouvenirSheet,
        Icon_StampExcludeSouvenirSheet,
        Icon_Folder
    } IconID;

    extern Catalog::IconID CatalogImageSelection[ Catalog::FT_NbrTypes ][ Catalog::ST_NbrInventoryStatusTypes ];
};
wxImageList* CreateAlbumImageList( );
wxImageList* CreateAlbumStateImageList( bool del );
wxImageList* CreateCatalogImageList( );
wxImageList* CreateCatalogStateImageList( bool del );

#endif