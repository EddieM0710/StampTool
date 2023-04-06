/*
 * @file IconDefs.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-08-01
 *
 * @copyright Copyright ( c ) 2022
 *
 * This file is part of StampTool.
 *
 * StampTool is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or any later version.
 *
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 *
 */
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
#include "art/menu.xpm"

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
        Icon_Folder,
        Icon_Menu
    } IconID;
    /*
      * @brief AlbumImageSelection[ Design::AT_NbrAlbumTypes ][ Catalog::ST_NbrCheckedStatusTypes ];
     Select different icon for each album base type and selected status
      *
      */
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
    /*
     * @brief  CatalogImageSelection[ Catalog::FT_NbrTypes ][ Catalog::ST_NbrInventoryStatusTypes ];
  Select different icon for each stamp format type and inventory status
     *
     */
    extern Catalog::IconID CatalogImageSelection[ Catalog::FT_NbrTypes ][ Catalog::ST_NbrInventoryStatusTypes ];
};
/*
 * @brief Create an Icon List object for the Album
 *
 * @return wxImageList*
 */
wxImageList* CreateAlbumImageList( );

/*
 * @brief Create an icon List for each checked state
 *
 * @param del
 * @return wxImageList*
 */
wxImageList* CreateAlbumStateImageList( );

/*
 * @brief Create a Catalog Image List object
 *
 * @return wxImageList*
 */
wxImageList* CreateCatalogImageList( );

/*
 * @brief Create a Catalog State Image List object
 *
 * @param del
 * @return wxImageList*
 */
wxImageList* CreateCatalogStateImageList( );

#endif