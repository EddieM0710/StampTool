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

    Page::Page( wxXmlNode* node ) : LayoutBase( node )
    {
        SetNodeType( AT_Page );
        SetObjectName( AlbumBaseNames[ GetNodeType( ) ] );
        m_titleFrame = new TitleFrame( this );
        m_titleFrame->SetHeadingString( GetAttrStr( AT_Name ) );
        m_titleFrame->SetSubHeadingString( GetAttrStr( AT_SubTitle ) );
        // wxString orientation = GetAttrStr( AT_Orientation );
        // if ( orientation.IsEmpty( ) )
        // {
        //     orientation = GetOrientation( );
        // }
        // else
        // {
        //     orientation = GetOrientation( );
        // }

    };

    void Page::Init( )
    {
        Album* album = GetAlbum( );
        if ( album )
        {
            if ( Design::IsPortrait( GetOrientation( ) ) )
            {
                //SetBorder( m_border );
                // the page frame takes into account the pageMargins, the border is within this
                SetXPos( album->GetLeftPageMargin( ) );
                SetYPos( album->GetTopPageMargin( ) );
                SetWidth( album->GetWidth( ) - album->GetRightPageMargin( ) - album->GetLeftPageMargin( ) );
                SetHeight( album->GetHeight( ) - album->GetTopPageMargin( ) - album->GetBottomPageMargin( ) );
                SetTopPageMargin( album->GetTopPageMargin( ) );
                SetBottomPageMargin( album->GetBottomPageMargin( ) );
                SetRightPageMargin( album->GetRightPageMargin( ) );
                SetLeftPageMargin( album->GetLeftPageMargin( ) );
                SetBorderSize( album->GetBorderSize( ) );
            }
            else
            {
                //SetBorder( m_border );
                // the page frame takes into account the pageMargins, the border is within this
                SetXPos( album->GetTopPageMargin( ) );
                SetYPos( album->GetLeftPageMargin( ) );
                SetHeight( album->GetWidth( ) - album->GetRightPageMargin( ) - album->GetLeftPageMargin( ) );
                SetWidth( album->GetHeight( ) - album->GetTopPageMargin( ) - album->GetBottomPageMargin( ) );
                SetTopPageMargin( album->GetLeftPageMargin( ) );
                SetBottomPageMargin( album->GetRightPageMargin( ) );
                SetRightPageMargin( album->GetBottomPageMargin( ) );
                SetLeftPageMargin( album->GetTopPageMargin( ) );
                SetBorderSize( album->GetBorderSize( ) );
            }
        }
    }
    void Page::Draw( wxDC& dc, double x, double y )
    {
        dc.SetPen( *wxBLACK_PEN );

        SetClientDimensions( dc, x + GetXPos( ), y + GetYPos( ), GetWidth( ), GetHeight( ) );

        wxString borderName = GetBorderFileName( );
        double xPos = x + GetLeftPageMargin( );
        double yPos = y + GetTopPageMargin( );

        wxImage image = GetProject( )->GetImage( borderName );

        DrawImage( dc, image,
            xPos, yPos,
            GetWidth( ),
            GetHeight( ) );

        double leftPadding = 0;
        double rightPadding = 0;
        double topPadding = 0;
        double bottomPadding = 0;
        // if ( 1 )//row->GetShowFrame( ) ) 
        // {
        //     leftPadding = GetLeftContentMargin( );
        //     rightPadding = GetRightContentMargin( );
        //     topPadding = GetTopContentMargin( );
        //     bottomPadding = GetBottomContentMargin( );
        // }

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
            //AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->Draw( dc, xPos + leftPadding, yPos + topPadding );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }

    void Page::DrawPDF( wxPdfDocument* doc, double x, double y )
    {
        wxString borderName = GetBorderFileName( );

        double xPos = GetLeftPageMargin( );
        double yPos = GetTopPageMargin( );
        double width = GetAlbum( )->GetWidth( );
        double height = GetAlbum( )->GetHeight( );

        wxImage image = GetProject( )->GetImage( borderName );
        doc->Image( borderName, image, xPos, yPos,
            GetWidth( ),
            GetHeight( ) );

        if ( GetAlbum( )->GetOverSizePaper( ) )
        {
            wxPdfLineStyle currStyle = PDFLineStyle( doc, *wxBLACK, .2, defaultDash );

            if ( Design::IsPortrait( GetOrientation( ) ) )
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
        // if ( 1 )//row->GetShowFrame( ) ) 
        // {
        //     leftPadding = GetLeftContentMargin( );
        //     rightPadding = GetRightContentMargin( );
        //     topPadding = GetTopContentMargin( );
        //     bottomPadding = GetBottomContentMargin( );
        // }

        xPos = m_contentFrame.GetXPos( );
        yPos = m_contentFrame.GetYPos( );
        if ( GetShowTitle( ) )
        {

            GetTitleFrame( )->DrawPDF( doc, xPos, yPos );
            //  yPos += GetTitleFrame( )->GetHeight( );
        }

        // xPos = xPos + GetBorderSize( );
         //yPos = yPos + GetBorderSize( );
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


    TitleFrame* Page::GetTitleFrame( )
    {
        return m_titleFrame;
    };

    wxString  Page::GetTitleString( )
    {
        return m_titleFrame->GetHeadingString( );
    };

    void  Page::SetTitleString( wxString str )
    {
        SetAttrStr( AT_Name, str );
        m_titleFrame->SetHeadingString( str );
    };

    wxString  Page::GetSubTitleString( )
    {
        return m_titleFrame->GetHeadingString( );
    };

    void  Page::SetSubTitleString( wxString str )
    {
        SetAttrStr( AT_SubTitle, str );
        m_titleFrame->SetSubHeadingString( str );
    };

    void Page::LoadFonts( wxXmlNode* node )
    {
        wxXmlNode* fonts = Utils::FirstChildElement( node, "Fonts" );
        if ( fonts )
        {
            m_titleFrame->LoadFonts( fonts );
        }
    }

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


    void Page::Save( wxXmlNode* xmlNode )
    {
        SetAttribute( xmlNode, AT_Name );
        SetAttribute( xmlNode, AT_ShowTitle );
        SetAttribute( xmlNode, AT_ShowSubTitle );
        SetAttribute( xmlNode, AT_ShowSubTitle );
        SetAttribute( xmlNode, AT_SubTitle );
        SetAttribute( xmlNode, AT_ShowFrame );

        if ( !GetAlbum( )->IsDefaultOrientation( GetOrientation( ) ) )
        {
            SetAttribute( xmlNode, AT_Orientation );
        }
        else
        {
            DeleteAttribute( AttrNameStrings[ AT_Orientation ] );
        }
        SaveFonts( xmlNode );
    }

    void Page::SaveFonts( wxXmlNode* parent )
    {
        m_titleFrame->SaveFonts( parent );
    }

    void Page::SetContentFrame( )
    {
        m_contentFrame.SetXPos( GetXPos( ) + GetLeftContentMargin( ) + GetBorderSize( ) );
        m_contentFrame.SetYPos( GetYPos( ) + GetTopContentMargin( ) );
        m_contentFrame.SetWidth( GetWidth( )
            - GetLeftContentMargin( ) - GetRightContentMargin( )
            - 2 * GetBorderSize( ) );
        m_contentFrame.SetHeight( GetHeight( )
            - GetTopContentMargin( ) - GetBottomContentMargin( )
            - 2 * GetBorderSize( ) );
    }

    void Page::UpdateLayout( )
    {
        UpdateMinimumSize( );
        UpdateSizes( );
        UpdatePositions( );
    }

    bool Page::UpdateMinimumSize( )
    {

        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;

        // count the number of rows/cols planned
        ValidateChildType( nbrRows, nbrCols, nbrStamps );

        double minWidth = 0.0;
        double minHeight = 0.0;
        SetContentFrame( );

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );

            child->UpdateMinimumSize( );

            if ( nbrCols > 0 )
            {
                //positioning across the page
                //the min height of the page is the size of the tallest child 
                //the min width is the sum of the min widths of the children 
                if ( child->GetMinHeight( ) > minHeight )
                {
                    minHeight = child->GetMinHeight( );
                }
                minWidth += child->GetMinWidth( );
            }
            else
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

        if ( GetShowTitle( ) )
        {
            m_titleFrame->UpdateString( minWidth, minWidth );
            // Add the title height
            minHeight += GetTitleFrame( )->GetHeight( );
        }

        SetMinWidth( minWidth );
        SetMinHeight( minHeight );

        GetErrorArray( )->Empty( );

        return ( ValidateNode( ) != AT_FATAL );
    }

    void Page::UpdateSizes( )
    {
        //figure out how many rows or cols there are to calculate the child spacing
        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );


        // Set the height and width of each child row or column
        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            double leftPadding = 0;
            double rightPadding = 0;
            double topPadding = 0;
            double bottomPadding = 0;
            switch ( type )
            {
                case AT_Row:
                {
                    Row* row = ( Row* ) child;
                    row->SetWidth( GetWidth( ) - row->GetLeftContentMargin( ) - row->GetRightContentMargin( ) - 2 * GetBorderSize( ) );
                    break;
                }
                case AT_Col:
                {
                    Column* col = ( Column* ) child;
                    if ( col->GetShowTitle( ) )
                    {
                        col->SetHeight( GetHeight( ) - GetTitleFrame( )->GetHeight( ) - col->GetTopContentMargin( ) - col->GetBottomContentMargin( ) - 2 * GetBorderSize( ) );
                    }
                    else
                    {
                        col->SetHeight( GetHeight( ) - col->GetTopContentMargin( ) - col->GetBottomContentMargin( ) - 2 * GetBorderSize( ) );
                    }
                    break;
                }
            }
            child->UpdateSizes( );
            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }
    }


    void Page::UpdatePositions( )
    {
        int nbrRows = 0;
        int nbrCols = 0;
        int nbrStamps = 0;
        ValidateChildType( nbrRows, nbrCols, nbrStamps );

        double xPos = 0;
        double yPos = 0;
        //First calc title position  
        if ( GetShowTitle( ) )
        {
            GetTitleFrame( )->SetXPos( 0 + ( m_contentFrame.GetWidth( ) - GetTitleFrame( )->GetWidth( ) ) / 2 );
            GetTitleFrame( )->SetYPos( GetTopContentMargin( ) );//GetTitleFrame( )->GetHeight( ) );
            // allow for space above title, title height and that much again for nice spaing
            yPos = GetTitleFrame( )->GetHeight( ) + 3 * GetTopContentMargin( );
        }
        else
        {
            yPos = GetTopContentMargin( );
        }

        // if there are cols then we are positioning them across the page
        double spacing = 0;
        if ( nbrCols > 0 )
        {
            double totalExtraSpace = m_contentFrame.GetWidth( ) - GetMinWidth( );
            spacing = totalExtraSpace / ( nbrCols + nbrStamps + 1 );
        }
        else // we are positioning them down the page
        {
            double totalExtraSpace = m_contentFrame.GetHeight( )
                - GetMinHeight( )
                - GetTopContentMargin( )
                - GetBottomContentMargin( );
            spacing = totalExtraSpace / ( nbrRows + nbrStamps + 1 );

        }

        //figure out starting pos accounting for title if present
        if ( nbrRows > 0 )
        {
            if ( GetAlbum( )->IsDefaultOrientation( GetOrientation( ) ) )
            {
                yPos += spacing;//- GetTopPageMargin( ) - GetBorderSize( );
            }
            else
            {
                yPos += spacing;//- GetLeftPageMargin( ) - GetBorderSize( );
            }
        }
        else if ( nbrCols > 0 || nbrStamps > 0 )
        {
            xPos += spacing;
        }

        wxTreeItemIdValue cookie;
        wxTreeItemId parentID = GetTreeItemId( );
        wxTreeItemId childID = GetAlbumTreeCtrl( )->GetFirstChild( parentID, cookie );
        while ( childID.IsOk( ) )
        {
            AlbumBaseType type = ( AlbumBaseType ) GetAlbumTreeCtrl( )->GetItemType( childID );
            LayoutBase* child = ( LayoutBase* ) GetAlbumTreeCtrl( )->GetItemNode( childID );
            child->UpdatePositions( );

            if ( nbrRows > 0 )
            {
                child->SetXPos( 0 );
                child->SetYPos( yPos );
                yPos = yPos + spacing + child->GetHeight( );
            }
            else if ( nbrCols > 0 || nbrStamps > 0 )
            {
                child->SetXPos( xPos );
                child->SetYPos( 0 );
                xPos = xPos + spacing + child->GetWidth( );
            }

            childID = GetAlbumTreeCtrl( )->GetNextChild( parentID, cookie );
        }


    }

    NodeStatus Page::ValidateNode( )
    {

        NodeStatus status = AT_OK;
        if ( !HasChildren( ) )
        {

            GetErrorArray( )->Empty( );
            if ( GetHeight( ) <= 0.0 )
            {
                wxString str;
                str = wxString::Format( "Terminal leaf node must define the height. height:>>%7.2f<< \n", GetHeight( ) );
                GetErrorArray( )->Add( str );
                status = AT_FATAL;
            }
            if ( GetWidth( ) <= 0.0 )
            {
                wxString str;
                str = wxString::Format( "Terminal leaf node must define the width. width:>>%7.2f<< \n", GetWidth( ) );
                GetErrorArray( )->Add( str );
                status = AT_FATAL;
            }
        }
        if ( GetWidth( ) < GetMinWidth( ) )
        {
            wxString str;
            str = wxString::Format( "Children too big for page. width:%7.2f  min width:%7.2f\n", GetWidth( ), GetMinWidth( ) );
            GetErrorArray( )->Add( str );
            status = AT_WARNING;
            ReportLayoutError( " UpdateMinimumSize", "Children too big for page", true );
        }
        //            if ( m_pageFrame.GetHeight( ) < minHeight )
        if ( GetHeight( ) < GetMinHeight( ) )
        {
            wxString str;
            str = wxString::Format( "Children too big for page. height:%7.2f  min height:%7.2f\n", GetHeight( ), GetMinHeight( ) );
            GetErrorArray( )->Add( str );
            status = AT_WARNING;
            ReportLayoutError( " UpdateMinimumSize", "Children too big for page", true );
        }

        return status;
    }

}

