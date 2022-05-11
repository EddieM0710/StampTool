/**
 * @file LayoutNode.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#include "album/AlbumNode.h"


#include "LayoutNode.h"
#include "album/TitlePage.h"
#include "album/Page.h"
#include "album/Title.h"
#include "album/Row.h"
#include "album/Column.h"
#include "album/Stamp.h"

namespace Layout {


    //!*********************************************************
    // Procedure::Load
    // *********************************************************

    void LayoutNode::ReportLayoutError( wxString funct, wxString err, bool fatal )
    {
        wxString funcStr = wxString::Format( "%s::%s", GetObjectName( ), funct );
        wxString msgStr = wxString::Format( "InputLine: %d;  %s", GetLineNbr( ), err );
        ReportError( funcStr, msgStr, fatal );
    }

    void LayoutNode::ValidateChildType( int& nbrRows, int& nbrCols, int& nbrStamps )
    {
        // count the number of rows/cols planned
        nbrRows = 0;
        nbrCols = 0;
        nbrStamps = 0;
        for ( int i = 0; i < ObjectArrayCount( ); i++ )
        {
            wxString childType = ChildItem( i )->GetObjectName( );
            if ( !childType.Cmp( "Row" ) )
            {
                nbrRows++;
            }
            else if ( !childType.Cmp( "Column" ) )
            {
                nbrCols++;
            }
            else if ( !childType.Cmp( "Stamp" ) )
            {
                nbrStamps++;
            }
        }
        if ( ( nbrRows > 0 ) && ( nbrCols > 0 ) )
        {
            ReportLayoutError( "ValidateChildType", "Only Rows or Columns are allowed as the children, not both" );
        }
        // if ( ( nbrRows <= 0 ) && ( nbrCols <= 0 ) && ( nbrStamps <= 0 )  )
        // {
        //     ReportLayoutError( "ValidateChildType", "Must have at least one row or Column") ;
        // }

    }

    Title* LayoutNode::GetTitle( )
    {
        return ( Title* )FindFirstChild( "Title" );
    }

    double LayoutNode::GetTitleHeight( )
    {
        Title* title = GetTitle( );
        if ( title )
        {
            return title->GetAttrValDbl( "height" );
        }
    }
}