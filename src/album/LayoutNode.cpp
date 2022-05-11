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
    double LayoutNode::GetXPos( )
    {
        return GetAttrDbl( AT_XPos );
    };

    void LayoutNode::SetXPos( double val )
    {
        SetAttrDbl( AT_XPos, val );
    };


    double LayoutNode::GetYPos( )
    {
        return GetAttrDbl( AT_YPos );
    };


    void LayoutNode::SetYPos( double val )
    {
        SetAttrDbl( AT_YPos, val );
    };


    double LayoutNode::GetWidth( )
    {
        return GetAttrDbl( AT_Width );
    };


    void LayoutNode::SetWidth( double val )
    {
        SetAttrDbl( AT_Width, val );
    };

    double LayoutNode::GetHeight( )
    {
        return GetAttrDbl( AT_Height );
    };

    void LayoutNode::SetHeight( double val )
    {
        SetAttrDbl( AT_Height, val );
    };


    double LayoutNode::GetMinWidth( )
    {
        return GetAttrDbl( AT_MinWidth );
    };


    void LayoutNode::SetMinWidth( double val )
    {
        SetAttrDbl( AT_MinWidth, val );
    };

    double LayoutNode::GetMinHeight( )
    {
        return GetAttrDbl( AT_MinHeight );
    };

    void LayoutNode::SetMinHeight( double val )
    {
        SetAttrDbl( AT_MinHeight, val );
    };

    void LayoutNode::ReportLayoutError( wxString funct, wxString err, bool fatal )
    {
        wxString funcStr = wxString::Format( "%s::%s", AttrNameStrings[ GetNodeType() ] , funct );
        wxString msgStr = wxString::Format( "InputLine: %d;  %s", GetLineNumber( ), err );
        ReportError( funcStr, msgStr, fatal );
    }

    void LayoutNode::ValidateChildType( int& nbrRows, int& nbrCols, int& nbrStamps )
    {
        // count the number of rows/cols planned
        nbrRows = 0;
        nbrCols = 0;
        nbrStamps = 0;

        for ( AlbumNodeList::iterator it = std::begin( m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutNode* child = ( LayoutNode* )( *it );
            AlbumNodeType childType = (AlbumNodeType)child->GetNodeType( );
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
            return title->GetAttrDbl( AT_Height );
        }
    }
}