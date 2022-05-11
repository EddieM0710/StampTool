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

namespace Design {

    //!*********************************************************
    // Procedure::Load
    // *********************************************************
    double LayoutBase::GetXPos( )
    {
        return GetAttrDbl( AT_XPos );
    };

    void LayoutBase::SetXPos( double val )
    {
        SetAttrDbl( AT_XPos, val );
    };


    double LayoutBase::GetYPos( )
    {
        return GetAttrDbl( AT_YPos );
    };


    void LayoutBase::SetYPos( double val )
    {
        SetAttrDbl( AT_YPos, val );
    };


    double LayoutBase::GetWidth( )
    {
        return GetAttrDbl( AT_Width );
    };


    void LayoutBase::SetWidth( double val )
    {
        SetAttrDbl( AT_Width, val );
    };

    double LayoutBase::GetHeight( )
    {
        return GetAttrDbl( AT_Height );
    };

    void LayoutBase::SetHeight( double val )
    {
        SetAttrDbl( AT_Height, val );
    };


    double LayoutBase::GetMinWidth( )
    {
        return GetAttrDbl( AT_MinWidth );
    };


    void LayoutBase::SetMinWidth( double val )
    {
        SetAttrDbl( AT_MinWidth, val );
    };

    double LayoutBase::GetMinHeight( )
    {
        return GetAttrDbl( AT_MinHeight );
    };

    void LayoutBase::SetMinHeight( double val )
    {
        SetAttrDbl( AT_MinHeight, val );
    };

    void LayoutBase::ReportLayoutError( wxString funct, wxString err, bool fatal )
    {
        wxString funcStr = wxString::Format( "%s::%s", AttrNameStrings[ GetNodeType() ] , funct );
        wxString msgStr = wxString::Format( "InputLine: %d;  %s", GetLineNumber( ), err );
        ReportError( funcStr, msgStr, fatal );
    }

    void LayoutBase::ValidateChildType( int& nbrRows, int& nbrCols, int& nbrStamps )
    {
        // count the number of rows/cols planned
        nbrRows = 0;
        nbrCols = 0;
        nbrStamps = 0;

        for ( AlbumBaseList::iterator it = std::begin( m_layoutChildArray ); it != std::end( m_layoutChildArray ); ++it )
        {
            LayoutBase* child = ( LayoutBase* )( *it );
            AlbumBaseType childType = (AlbumBaseType)child->GetNodeType( );
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

    Title* LayoutBase::GetTitle( )
    {
        return ( Title* )FindFirstChild( "Title" );
    }

    double LayoutBase::GetTitleHeight( )
    {
        Title* title = GetTitle( );
        if ( title )
        {
            return title->GetAttrDbl( AT_Height );
        }
    }
}