/**
 * @file AutoStylesProp.h
 * @author Eddie Monroe
 * @brief
 * @version 0.1
 * @date 2022-02-16
 *
 * @copyright Copyright (c) 2022
 *
 **************************************************/
#ifndef AutoStylesProp_h
#define AutoStylesProp_h

#include "odt/ODTDefs.h"
#include <vector>


using namespace std;

namespace ODT {

    class TextStyle
    {
    public:
        TextStyle( ) {};
        ~TextStyle( ) {};

        inline wxString GetTextStyleName( ) { return  m_textStyleName; };
        inline void SetTextStyleName( wxString textStyleName ) { m_textStyleName = textStyleName; };
        inline wxString GetCodeName( ) { return m_codeName; };
        inline void SetCodeName( wxString codeName ) { m_codeName = codeName; };
        inline wxString GetJustify( ) { return m_justify; };
        inline void SetJustify( wxString justify ) { m_justify = justify; };
        inline bool GetBold( ) { return m_bold; };
        inline void SetBold( bool bold ) { m_bold = bold; };
        inline int GetFontSize( ) { return m_fontSize; };
        inline void SetFontSize( int fontSize ) { m_fontSize = fontSize; };
        inline wxString GetParentStyleName( ) { return m_parentStyleName; };
        inline void SetParentStyleName( wxString parentStyleName ) { m_parentStyleName = parentStyleName; };
        inline bool GetFoBreakBeforePage( ) { return m_foBreakBeforePage; };
        inline void SetFoBreakBeforePage( bool foBreakBeforePage ) { m_foBreakBeforePage = foBreakBeforePage; };
    private:
        wxString m_textStyleName;
        wxString m_parentStyleName;
        wxString m_codeName;
        wxString m_justify;
        bool m_bold;
        int m_fontSize;
        bool m_foBreakBeforePage;
    };

    typedef std::vector<TextStyle*> StyleList;

    class AutoStylesProp
    {
    public:
        AutoStylesProp( ) {};
        ~AutoStylesProp( ) {};

        TextStyle* FindStyleName( wxString name );

        TextStyle* FindStyle( wxString justify, bool bold, int fontSize );

        TextStyle* MakeStyle( wxString justify, bool bold, int fontSize,
            wxString codeName, bool foBreakBeforePage = false, wxString parentStyleName = "Frame_20_contents" );
        void DefinePrimaryTextStyles( );
        void WriteStyle( TextStyle* style );
        void WriteAll( );
    private:
        StyleList m_styles;

    };
}
#endif