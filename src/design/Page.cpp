/**
 * @file Page.cpp
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
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

#include "Defs.h"

#include "design/Page.h"
#include "design/Album.h"
#include "design/TitleFrame.h"
#include "design/Row.h"
#include "design/Column.h"
#include "design/Stamp.h"
#include "design/AlbumVolume.h"
#include "gui/AlbumTreeCtrl.h"
#include "gui/GuiUtils.h"
#include "utils/Project.h"


namespace Design {

    //----------------

    Page::Page( wxXmlNode* node ) : LayoutBase( node )
    {
        SetNodeType( AT_Page );
        SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );
        m_titleFrame = new TitleFrame( this );
        m_titleFrame->SetHeadingString( GetAttrStr( AT_Name ) );
        m_titleFrame->SetSubHeadingString( GetAttrStr( AT_SubTitle ) );
        m_pageType = Design::PT_None;
    };

    //----------------

    void Page::Init( )
    {
        Album* album = GetAlbum( );
        PageDefaults* parameters = AlbumPageDefaults( );
        if ( parameters )
        {
            if ( Design::IsPortrait( Orientation( ) ) )
            {

                // the page frame takes into account the pageMargins, the border is within this
                SetTopPageMargin( parameters->TopMargin( ) );
                SetBottomPageMargin( parameters->BottomMargin( ) );
                SetRightPageMargin( parameters->RightMargin( ) );
                SetLeftPageMargin( parameters->LeftMargin( ) );
                SetXPos( parameters->LeftMargin( ) );
                SetYPos( parameters->TopMargin( ) );
                SetWidth( GetPageAttributeDbl( AT_PageWidth ) - parameters->RightMargin( ) - parameters->LeftMargin( ) );
                SetHeight( GetPageAttributeDbl( AT_PageHeight ) - parameters->TopMargin( ) - parameters->BottomMargin( ) );
                SetBorderSize( GetBorderSize( ) );
            }
            else
            {
                //SetBorder( m_border );
                // the page frame takes into account the pageMargins, the border is within this
                SetTopPageMargin( parameters->LeftMargin( ) );
                SetBottomPageMargin( parameters->RightMargin( ) );
                SetRightPageMargin( parameters->BottomMargin( ) );
                SetLeftPageMargin( parameters->TopMargin( ) );
                SetXPos( parameters->TopMargin( ) );
                SetYPos( parameters->LeftMargin( ) );
                SetHeight( GetPageAttributeDbl( AT_PageWidth ) - parameters->RightMargin( ) - parameters->LeftMargin( ) );
                SetWidth( GetPageAttributeDbl( AT_PageHeight ) - parameters->TopMargin( ) - parameters->BottomMargin( ) );

                SetBorderSize( GetBorderSize( ) );
            }
        }
    }

    //----------------


    double Page::GetPageAttributeDbl( Design::AlbumAttrType type )
    {
        wxString val = GetAttrStr( type );
        if ( val.IsEmpty( ) )
        {
            return  Design::AlbumPageDefaults( )->GetAttrDbl( type );
        }
        return  GetAttrDbl( type );
    }

    //----------------

    wxString Page::GetPageAttributeStr( Design::AlbumAttrType type )
    {
        wxString val = GetAttrStr( type );
        if ( val.IsEmpty( ) )
        {
            return  Design::AlbumPageDefaults( )->GetAttrStr( type );
        }
        return val;
    }

    //--------------

    bool Page::GetPageAttributeBool( Design::AlbumAttrType type, bool defVal )
    {
        wxString catStr = GetAttrStr( type );
        if ( catStr.IsEmpty( ) )
        {
            catStr = AlbumPageDefaults( )->GetAttrStr( type );
            if ( catStr.IsEmpty( ) )
            {
                return defVal;
            }
        }
        return String2Bool( catStr );
    }

    //----------------

    void Page::SetPageAttributeStr( Design::AlbumAttrType type, wxString val )
    {
        if ( IsDefaultVal( type, val ) )
        {
            DeleteAttribute( AttrNameStrings[ type ] );
        }
        else
        {
            SetAttrStr( type, val );
        }
    }

    //----------------

    void Page::SetPageAttributeDbl( Design::AlbumAttrType type, double val )
    {
        wxString str = wxString::Format( "%4.1f", val );
        SetPageAttributeStr( type, str );
    }

    //----------------

    void Page::SetPageAttributeBool( Design::AlbumAttrType type, bool val )
    {
        wxString str = Bool2String( val );
        SetPageAttributeStr( type, str );

    }

    //--------------

    bool Page::IsDefaultVal( AlbumAttrType type )
    {
        return AlbumPageDefaults( )->IsEqual( type, GetAttrStr( type ) );
    }

    //----------------

    bool Page::IsDefaultVal( AlbumAttrType type, wxString val )
    {
        return AlbumPageDefaults( )->IsEqual( type, val );
    }

    //----------------

    void Page::Draw( wxDC& dc, double x, double y )
    {
        dc.SetPen( *wxBLACK_PEN );
        SetClientDimensions( dc, x + m_contentFrame.GetXPos( ), y + m_contentFrame.GetYPos( ), GetWidth( ), GetHeight( ) );

        wxString borderName = GetBorderFileName( );
        double xPos = x + GetLeftPageMargin( );
        double yPos = y + GetTopPageMargin( );

        wxImage image = GetProject( )->GetImage( borderName );
        wxFont font = dc.GetFont( );

        DrawImage( dc, image,
            xPos, yPos,
            GetWidth( ),
            GetHeight( ) );

        double leftPadding = 0;
        double rightPadding = 0;
        double topPadding = 0;
        double bottomPadding = 0;

        xPos = m_contentFrame.GetXPos( );
        yPos = m_contentFrame.GetYPos( );
        if ( GetShowTitle( ) )
        {
            GetTitleFrame( )->Draw( dc, xPos, yPos );
        }

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->Draw( dc, xPos + leftPadding, yPos + topPadding );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    //----------------

    void Page::DrawPDF( wxPdfDocument* doc, double x, double y )
    {
        wxString borderName = GetBorderFileName( );

        double xPos = GetLeftPageMargin( );
        double yPos = GetTopPageMargin( );
        double width = AlbumPageDefaults( )->GetWidth( );
        double height = AlbumPageDefaults( )->GetHeight( );

        if ( GetShowBorder( ) )
        {
            wxImage image = GetProject( )->GetImage( borderName );
            doc->Image( borderName, image, xPos, yPos,
                GetWidth( ),
                GetHeight( ) );
        }

        if ( AlbumPageDefaults( )->OverSizePaper( ) )
        {
            wxPdfLineStyle currStyle = PDFLineStyle( doc, *wxBLACK, .2, defaultDash );

            if ( Design::IsPortrait( Orientation( ) ) )
            {
                doc->Line( 0, height, width, height );
                doc->Line( width, 0, width, height );
            }
            else
            {
                doc->Line( 0, width, height, width );
                doc->Line( height, 0, height, width );
            }
            doc->SetLineStyle( currStyle );
        }
        double leftPadding = 0;
        double rightPadding = 0;
        double topPadding = 0;
        double bottomPadding = 0;

        xPos = m_contentFrame.GetXPos( );
        yPos = m_contentFrame.GetYPos( );
        if ( GetShowTitle( ) )
        {
            GetTitleFrame( )->DrawPDF( doc, xPos, yPos );
        }

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            //AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->DrawPDF( doc, xPos + leftPadding, yPos + topPadding );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    //----------------

    TitleFrame* Page::GetTitleFrame( )
    {
        return m_titleFrame;
    };

    //----------------

    wxString  Page::GetTitleString( )
    {
        return m_titleFrame->GetHeadingString( );
    };

    //----------------

    void  Page::SetTitleString( wxString str )
    {
        SetAttrStr( AT_Name, str );
        m_titleFrame->SetHeadingString( str );
    };

    //----------------

    wxString  Page::GetSubTitleString( )
    {
        return m_titleFrame->GetHeadingString( );
    };

    //----------------

    void  Page::SetSubTitleString( wxString str )
    {
        SetAttrStr( AT_SubTitle, str );
        m_titleFrame->SetSubHeadingString( str );
    };

    //----------------

    void Page::LoadFonts( wxXmlNode* node )
    {
        wxXmlNode* fonts = Utils::FirstChildElement( node, "Fonts" );
        if ( fonts )
        {
            m_titleFrame->LoadFonts( fonts );
        }
    }

    //----------------

    void Page::ReportLayout( )
    {
        std::cout << "Layout for Page " << "\nPage ";
        //ReportLayout( );
        std::cout << "\nBase ";
        ReportLayoutFrame( );

        wxString str = wxString::Format( "Border Size:%7.2f\n ", GetBorderSize( ) );
        std::cout << str;
        str = wxString::Format( "Top PageMargin:%7.2f  Bottom PageMargin:%7.2f\n  Right PageMargin:%7.2f  c PageMargin:%7.2f\n",
            GetTopPageMargin( ), GetBottomPageMargin( ), GetRightPageMargin( ), GetLeftPageMargin( ) );
        std::cout << str;
    };

    //----------------

    void Page::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_ShowSubTitle );
        SetAttribute( xmlNode, AT_SubTitle );
        SetAttribute( xmlNode, AT_ShowFrame );

        if ( !AlbumPageDefaults( )->IsOrientation( Orientation( ) ) )
        {
            SetAttribute( xmlNode, AT_Orientation );
        }
        else
        {
            DeleteAttribute( AttrNameStrings[ AT_Orientation ] );
        }
        SaveFonts( xmlNode );
    }

    //----------------

    void Page::SaveFonts( wxXmlNode* parent )
    {
        m_titleFrame->SaveFonts( parent );
    }

    //----------------

    void Page::SetContentFrame( )
    {
        m_contentFrame.SetXPos( GetXPos( ) + GetBorderSize( ) );
        m_contentFrame.SetYPos( GetYPos( ) + GetBorderSize( ) );
        m_contentFrame.SetWidth( GetWidth( )
            //- GetLeftPageMargin( ) - GetRightPageMargin( )
            - 2 * GetBorderSize( ) );
        m_contentFrame.SetHeight( GetHeight( )
            // - GetTopPageMargin( ) - GetBottomPageMargin( )
            - 2 * GetBorderSize( ) );
    }

    //----------------

    void Page::UpdateLayout( )
    {
        UpdateMinimumSize( );
        UpdateSizes( );
        UpdatePositions( );
    }

    //----------------

    bool Page::UpdateMinimumSize( )
    {

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        m_pageType = Design::PT_None;
        SetXPos( GetLeftPageMargin( ) );
        SetYPos( GetTopPageMargin( ) );
        if ( Design::IsPortrait( Orientation( ) ) )
        {
            SetWidth( GetPageAttributeDbl( AT_PageWidth ) - GetRightPageMargin( ) - GetLeftPageMargin( ) );
            SetHeight( GetPageAttributeDbl( AT_PageHeight ) - GetTopPageMargin( ) - GetBottomPageMargin( ) );
        }
        else
        {
            SetWidth( GetPageAttributeDbl( AT_PageHeight ) - GetRightPageMargin( ) - GetLeftPageMargin( ) );
            SetHeight( GetPageAttributeDbl( AT_PageWidth ) - GetTopPageMargin( ) - GetBottomPageMargin( ) );
        }
        double minWidth = 0.0;
        double minHeight = 0.0;
        // the page LayoutBase m_frame contains the parameters for the page.
        // the actual content of the page is the area inside the border, i.e., the ContentFrame
        SetContentFrame( );

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );

            // set the page type based on the first row or col child
            if ( m_pageType == Design::PT_None )
            {
                if ( type == Design::AT_Row )
                {
                    // Rows have cols and cols have rows
                    // If we found a row this page is behaving like a column
                    // There should only be rows as first level children of this page
                    m_pageType = Design::PT_ColumnPage;
                }
                else if ( type == Design::AT_Col )
                {
                    m_pageType = Design::PT_RowPage;
                }
            }

            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            // calc the min size for this items children
            child->UpdateMinimumSize( );

            if ( m_pageType == Design::PT_RowPage )
            {
                //positioning across the page
                //the min height of the page is the size of the tallest child 
                //the min width is the sum of the min widths of the children 

                // keep the max min height
                if ( child->GetMinHeight( ) > minHeight )
                {
                    minHeight = child->GetMinHeight( );
                }
                // keep running total of min child width
                minWidth += child->GetMinWidth( );
            }
            else  // PT_ColumnPage 
            {
                // positioning down the page
                //the min width of the page is the size of the widest child 
                //the min height is the sum of the min heights of the children 
                if ( child->GetMinWidth( ) > minWidth )
                {
                    minWidth = child->GetMinWidth( );
                }
                minHeight += child->GetMinHeight( );
            }
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

        //if this item shows its title then add that to the min height
        GetTitleFrame( )->Init( );
        if ( GetShowTitle( ) )
        {
            m_titleFrame->UpdateString( minWidth, minWidth );
            // Add the title height
            minHeight += GetTitleFrame( )->GetHeight( );

            GetTitleFrame( )->SetYPos( 0 );
        }

        SetMinWidth( minWidth
            + GetTopContentMargin( )
            + GetBottomContentMargin( ) );
        SetMinHeight( minHeight
            + GetLeftContentMargin( )
            + GetRightContentMargin( ) );

        GetErrorArray( )->Empty( );

        return ( ValidateNode( ) != AT_FATAL );
    }

    //----------------

    void Page::UpdatePositions( )
    {
        // calc space used by children
         // this means looping through the children and getting the actual sizes 
         // of the children, not their calculated min size
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        LayoutBase* parent = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( parentID );
        int nbrChildren = parent->GetNbrChildren( );

        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        double actualWidth = 0;
        double actualHeight = 0;
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            if ( m_pageType == Design::PT_ColumnPage )
            {
                actualHeight += child->GetHeight( );
            }
            else
            {
                actualWidth += child->GetWidth( );
            }
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }

        double xPos = 0;
        double yPos = 0;
        //First calc title position  
        if ( GetShowTitle( ) )
        {
            double titleXPos = ( m_contentFrame.GetWidth( ) - GetTitleFrame( )->GetWidth( ) ) / 2;

            if ( titleXPos < 0 )
            {
                titleXPos = 0;
            }
            GetTitleFrame( )->SetXPos( titleXPos );

            GetTitleFrame( )->SetYPos( GetTopContentMargin( ) );

            // allow for space above title, title height and that much again for nice spaing
            yPos = GetTitleFrame( )->GetHeight( ) + 2 + GetTopContentMargin( );
        }
        else
        {
            GetTitleFrame( )->Init( );
            yPos = GetTopContentMargin( );
        }

        // if there are rows then we are positioning them down the page
        double spacing = 0;
        double totalExtraSpace = 0;
        if ( m_pageType == Design::PT_ColumnPage )
        {
            totalExtraSpace = m_contentFrame.GetHeight( )
                - actualHeight
                - GetTopContentMargin( )
                - GetBottomContentMargin( );
            if ( GetShowTitle( ) )
            {
                totalExtraSpace -= GetTitleFrame( )->GetHeight( );
            }

            spacing = totalExtraSpace / ( nbrChildren + 1 );
        }
        else // we are positioning them across the page
        {
            totalExtraSpace = m_contentFrame.GetWidth( ) - actualWidth;
            spacing = totalExtraSpace / ( nbrChildren + 1 );

        }

        //figure out starting pos accounting for title if present
        if ( m_pageType == Design::PT_ColumnPage )
        {
            yPos += spacing;
        }
        else //PT_RowPage || Stamp 
        {
            xPos += spacing;
        }

        childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->UpdatePositions( );

            if ( m_pageType == Design::PT_RowPage )
            {
                child->SetXPos( xPos );
                child->SetYPos( 0 );
                xPos = xPos + spacing + child->GetWidth( );
            }
            else // PT_ColumnPage
            {
                child->SetXPos( 0 );
                child->SetYPos( yPos );
                yPos = yPos + spacing + child->GetHeight( );
            }

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    //----------------

    void Page::UpdateSizes( )
    {
        // Set the height and width of each child row or column
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        LayoutBase* parent = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( parentID );
        int nbrChildren = parent->GetNbrChildren( );
        double padding = ( GetHeight( ) - 2 * GetBorderSize( ) - GetMinHeight( ) ) / ( 3 * nbrChildren - 1 );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            if ( m_pageType == PT_ColumnPage )
            {
                double childHeight = child->GetMinHeight( )
                    + 2 * padding
                    - GetTopContentMargin( )
                    - GetBottomContentMargin( );

                child->SetWidth( GetWidth( )
                    - child->GetLeftContentMargin( )
                    - child->GetRightContentMargin( )
                    - 2 * GetBorderSize( ) );
                // if ( child->GetShowTitle( ) )
                // {
                //     child->SetHeight( childHeight
                //         - GetTitleFrame( )->GetHeight( ); //allow for title
                // }
                // else
                // {
                child->SetHeight( childHeight );
                // }
            }
            else // PT_RowPage:
            {
                double childHeight = GetHeight( )
                    - child->GetTopContentMargin( )
                    - child->GetBottomContentMargin( )
                    - 2 * GetBorderSize( );
                child->SetWidth( child->GetMinWidth( )
                    + ( GetWidth( ) - GetMinWidth( ) ) / ( 2 * nbrChildren ) // instead of just min width, make it a little bigger
                    - GetLeftContentMargin( )
                    - GetRightContentMargin( )
                    - 2 * GetBorderSize( ) );
                if ( ( ( Row* ) child )->GetShowTitle( ) )
                {
                    child->SetHeight( childHeight
                        - GetTitleFrame( )->GetHeight( ) ); //allow for title
                }
                else
                {
                    child->SetHeight( childHeight );
                }
            }
            child->UpdateSizes( );

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    //----------------

    NodeStatus Page::ValidateNode( )
    {

        NodeStatus status = AT_OK;
        if ( !HasChildren( ) )
        {

            GetErrorArray( )->Empty( );
            if ( GetHeight( ) <= 0.0 )
            {
                wxString str;
                str = wxString::Format( "Terminal leaf node must define the height. height:>>%7.2f<< \n",
                    GetHeight( ) );
                GetErrorArray( )->Add( str );
                status = AT_FATAL;

            }
            if ( GetWidth( ) <= 0.0 )
            {
                wxString str;
                str = wxString::Format( "Terminal leaf node must define the width. width:>>%7.2f<< \n",
                    GetWidth( ) );
                GetErrorArray( )->Add( str );
                status = AT_FATAL;
            }
        }
        if ( GetWidth( ) < GetMinWidth( ) )
        {
            wxString str;
            str = wxString::Format( "Children too big for page. width:%7.2f  min width:%7.2f\n",
                GetWidth( ), GetMinWidth( ) );
            GetErrorArray( )->Add( str );
            status = AT_WARNING;
            // ReportLayoutError( " UpdateMinimumSize", "Children too big for page", true );
        }
        //            if ( m_pageFrame.GetHeight( ) < minHeight )
        if ( GetHeight( ) < GetMinHeight( ) )
        {
            wxString str;
            str = wxString::Format( "Children too big for page. height:%7.2f  min height:%7.2f\n",
                GetHeight( ), GetMinHeight( ) );
            GetErrorArray( )->Add( str );
            status = AT_WARNING;
            // ReportLayoutError( " UpdateMinimumSize", "Children too big for page", true );
        }
        m_nodeValid = status;
        wxTreeItemId id = GetTreeItemId( );
        if ( id.IsOk( ) )
        {
            if ( status == AT_FATAL )
            {
                GetAlbumTreeCtrl( )->SetItemBackgroundColour( id, *wxRED );
                std::cout << GetAlbumTreeCtrl( )->GetItemText( id ) << " Fatal\n";
            }
            else if ( status == AT_WARNING )
            {
                GetAlbumTreeCtrl( )->SetItemBackgroundColour( id, *wxYELLOW );
                std::cout << GetAlbumTreeCtrl( )->GetItemText( id ) << " Warning\n";
            }
            else
            {
                GetAlbumTreeCtrl( )->SetItemBackgroundColour( id, *wxWHITE );
                //std::cout << GetAlbumTreeCtrl( )->GetItemText( id ) << " OK\n";
            }
        }
        return status;
    }

    //----------------

}

