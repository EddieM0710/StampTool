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
        };

        /**
         * @brief Construct a new Album Design Object
         *
         * @param name
         **************************************************/
        LayoutBase( wxXmlNode* node ) : AlbumBase( node ) {
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

        bool ShowTitle( ) { return m_showTitle; };
        void SetShowTitle( bool show = false ) { m_showTitle = show; };

        bool ShowFrame( ) { return m_showFrame; };
        void SetShowFram( bool show = false ) { m_showFrame = show; };

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
        bool m_showTitle;
        bool m_showFrame;
    };
}
#endif
