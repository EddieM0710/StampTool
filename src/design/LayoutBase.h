/**
 * @file Layoutlayout/AlbumBase.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-04
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/

#ifndef LayoutBase_h
#define LayoutBase_h

#include <wx/string.h>

#include "Defs.h"
#include "design/AlbumBase.h"
#include "design/Frame.h"
#include "utils/XMLUtilities.h"

#include <wx/xml/xml.h>

namespace Design {


    class Title;

    /**
     * @brief Base class for all layout objects. The layout objects are
     * initialy loaded from the layout XML.
     *
     **************************************************/
    class LayoutBase : public AlbumBase
    {
    public:
        /**
         * @brief Unused; Construct a new Album Design Object object
         *
         **************************************************/
        LayoutBase( ) : AlbumBase( ) {
            SetTopContentPadding( 1.5 ) ;
            SetBottomContentPadding( 1.5 ) ;
            SetLeftContentPadding( 1.5 ) ;
            SetRightContentPadding( 1.5 ) ;

        };

        /**
         * @brief Construct a new Album Design Object
         *
         * @param name
         **************************************************/
        LayoutBase( wxXmlNode* node ) : AlbumBase( node ) {
            SetTopContentPadding( 2 ) ;
            SetBottomContentPadding( 2 ) ;
            SetLeftContentPadding( 2 ) ;
            SetRightContentPadding( 2 ) ;
        };


        virtual wxXmlNode* Write( wxXmlNode* parent ) = 0;

        double GetXPos( ) { return m_frame.GetXPos( ); };
        void SetXPos( double val ) { m_frame.SetXPos( val ); };
        double GetYPos( ) { return m_frame.GetYPos( ); };
        void SetYPos( double val ) { m_frame.SetYPos( val ); };
        double GetWidth( ) { return m_frame.GetWidth( ); };
        void SetWidth( double val ) { m_frame.SetWidth( val ); };
        double GetHeight( ) { return m_frame.GetHeight( ); };
        void SetHeight( double val ) { m_frame.SetHeight( val ); };
        double GetMinWidth( ) { return m_frame.GetMinWidth( ); };
        void SetMinWidth( double val ) { m_frame.SetMinWidth( val ); };
        double GetMinHeight( ) { return m_frame.GetMinHeight( ); };
        void SetMinHeight( double val ) { m_frame.SetMinHeight( val ); };

        wxString GetTitle( ) { return m_title; };
        void SetTitle( wxString title ) { m_title = title; UpdateTitleSize( ); };
        double GetTitleHeight( ) { return m_titleSize.y; };
        double GetTitleWidth( ) { return m_titleSize.x; };

        bool GetShowTitle(){ return String2Bool( GetAttrStr( AT_ShowTitle ) ); };
        void SetShowTitle( bool val ){ SetAttrStr( AT_ShowTitle, Bool2String( val) ); };

        bool GetShowFrame(){ return String2Bool( GetAttrStr( AT_ShowFrame ) ); };
        void SetShowFrame( bool val ){ SetAttrStr( AT_ShowFrame, Bool2String( val ) ); };

        bool GetShowID(){ return String2Bool( GetAttrStr( AT_ShowId ) ); };
        void SetShowID( bool val ){ SetAttrStr( AT_ShowId, Bool2String( val ) ); };

        double GetTopContentPadding( ) { GetAttrDbl( AT_TopContentPadding ); };
        void SetTopContentPadding(double val) { SetAttrDbl( AT_TopContentPadding, val ); };

        double GetBottomContentPadding( ) { GetAttrDbl( AT_BottomContentPadding ); };
        void SetBottomContentPadding(double val) { SetAttrDbl( AT_BottomContentPadding, val ); };

        double GetLeftContentPadding( ) { GetAttrDbl( AT_LeftContentPadding ); };
        void SetLeftContentPadding(double val) { SetAttrDbl( AT_LeftContentPadding, val ); };

        double GetRightContentPadding( ) { GetAttrDbl( AT_RightContentPadding ); };
        void SetRightContentPadding(double val) { SetAttrDbl( AT_RightContentPadding, val ); };

        void ValidateChildType( int& nbrRows, int& nbrCols, int& nbrStamps );
        void ReportLayoutError( wxString funct, wxString err, bool fatal = true );

        /**
         * @brief Calculate the column layout based on child parameters
         *
         * @return true
         * @return false
         **************************************************/
        virtual void UpdatePositions( ) = 0;

        /**
         * @brief UpdateMinimumSize
         * Calculates the minimum Height and width of the object. It drills down to
         * the lowest layout object with an actual size and begins calculating the
         * min size of its parents as it progresses back up the heirarchy.
         * @return true
         * @return false
         **************************************************/
        virtual bool UpdateMinimumSize( ) = 0;

        virtual void UpdateSizes( ) = 0;
        virtual void draw( wxDC& dc, double x, double y ) = 0;
        void UpdateTitleSize( );
        void WriteFrame( wxString loc, wxString name, wxString id, Frame* frame );
        void DumpLayout( double x, double y );
 

    protected:
        Frame m_frame;
        wxString m_title;
        wxRealPoint m_titleSize;

    };
}
#endif
