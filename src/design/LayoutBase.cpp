/**
 * @file LayoutBase.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#include "design/AlbumBase.h"


#include "LayoutBase.h"
#include "design/TitlePage.h"
#include "design/Page.h"
#include "design/Title.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "gui/AlbumImagePanel.h"

namespace Design {

    void LayoutBase::UpdateTitleSize()
    {
        GetAlbumImagePanel()->GetTextExtent(m_title);
    }
    void LayoutBase::ReportLayoutError( wxString funct, wxString err, bool fatal )
    {
        wxString funcStr = wxString::Format( "%s::%s", AttrNameStrings[ GetNodeType( ) ], funct );
        wxString msgStr = wxString::Format( "InputLine: %d;  %s", GetLineNumber( ), err );
        ReportError( funcStr, msgStr, fatal );
    }

    void LayoutBase::ValidateChildType( int& nbrRows, int& nbrCols, int& nbrStamps )
    {
        // count the number of rows/cols planned
        nbrRows = 0;
        nbrCols = 0;
        nbrStamps = 0;

        for ( ChildList::iterator it = BeginChildList( ); it != EndChildList( ); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );
            AlbumBaseType childType = ( AlbumBaseType )child->GetNodeType( );
            switch ( childType )
            {
            case AT_Row:
            {
                nbrRows++;
                break;
            }
            case AT_Col:
            {
                nbrCols++;
                break;
            }
            case AT_Stamp:
            {
                nbrStamps++;
                break;
            }
            }
        }
        if ( ( nbrRows > 0 ) && ( nbrCols > 0 ) )
        {
            ReportLayoutError( "ValidateChildType", "Only Rows or Columns are allowed as the children, not both" );
        }
    }
}