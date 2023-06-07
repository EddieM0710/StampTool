
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/string.h>

#include "catalog/StampMount.h"
#include "catalog/CSV.h"
#include "utils/XMLUtilities.h"
namespace Catalog {

    Mounts mounts[ NbrStampMounts ] = {
{"Mn        23x20mm",23,20, "Mini Regular Issues"},
{"Str       215x20mm",215,20,""},
{"EH        25x22mm",25,22,"Horizontal Regular Issue"},
{"E         25x22mm",25,22,"Horizontal Coils"},
{"Str       215x22mm",215,22,""},
{"Mn Vert   20x23mm",20,23,"Mini Regular Issues"},
{"Str       215x24mm",215,24,""},
{"EV        22x25mm",22,25,"Vertical Regular Issue"},
{"J         40x25mm", 40, 25, "Horizontal Commemorative"},
{"Str       67x25mm",67,25,"U.S.Coil Strips "},
{"Str       215x25mm",215,25,""},
{"Str       260x25mm",260,25,""},
{"T         25x27mm",25,27,"Famous American and Champions of Liberty"},
{"N         40x27mm",40,27,"United Nations "},
{"U         33x27mm",33,27,"United Nations & Germany"},
{"Str       215x27mm",215,27,""},
{"Str       215x28mm",215,28,""},
{"Str       215x30mm",215,30,""},
{"Str       293x30mm",293,30,""},
{"S         31x31mm",31,31,"Square Commemorative"},
{"AH        41x31mm", 41,31, "Horizontal Semi-Jumbo Commemorative"},
{"C         50x31mm",50,31,"Horizontal Jumbo Commemoratives"},
{"Str       215x31mm",215,31,""},
{"Str       215x33mm",215,33,""},
{"DH        52x36mm",52,36,"Federal Duck Stamps"},
{"Str       215x36mm",215,36,""},
{"Str       215x39mm",215,39,""},
{"JV        25x40mm", 25,40, "Vertical Commemorative"},
{"Str       260x40mm",260,40,""},
{"AV        31x41mm", 31,41, "Vertical Semi-Jumbo"},
{"Str       215x41mm",215,41,""},
{"Str       215x44mm",215,44,""},
{"Str       260x46mm",260,46,""},
{"Str       215x48mm",215,48,""},
{"CV        31x50mm",31,50,"Vertical Jumbo Commemoratives"},
{"Str       215x50mm",215,50,""},
{"Str       215x52mm",215,52,""},
{"Blk       57x55mm",57,55,"Regular Issue Plate Blocks"},
{"Blk       106x55mm",106,55,"Commemorative Plate Blocks"},
{"Str       260x55mm",260,55,""},
{"Blk       105x57mm",105,57,"Modern Plate Blocks "},
{"Blk       105x57mm",105,57,"Modern Plate Blocks"},
{"Str       215x57mm",215,57,""},
{"Str       260x59mm",260,59,""},
{"Str       215x61mm",215,61,""},
{"Str       240x63mm",240,63,""},
{"Str       243x66mm",243,66,""},
{"Str       240x68mm",240,68,""},
{"Blk       127x70mm",127,70,"Jumbo Plate Blocks "},
{"Str       264x70mm",264,70,""},
{"Str       240x74mm",240,74,""},
{"Str       264x76mm",264,76,""},
{"Str       240x80mm",240,80,""},
{"Str       240x82mm",240,82,""},
{"Blk       89x83mm",89,83,""},
{"Str       240x84mm",240,84,""},
{"Blk       140x89mm",140,89,"Postal Cards and Souvenir Sheets"},
{"Str       240x89mm",240,89,""},
{"Blk       111x91mm",111,91,""},
{"Mn Sh     264x91mm",264,91,""},
{"Blk       165x94mm",165,94,"for First Day Covers "},
{"Mn Sh     264x96mm",264,96,""},
{"Blk       240x100mm",240,100,""},
{"Mn Sh     264x105mm",264,105,""},
{"Mn Sh     264x107mm",264,107,""},
{"Mn Sh     264x109mm",264,109,""},
{"Mn Sh     264x111mm",264,111,""},
{"Mn Sh     264x115mm",264,115,""},
{"Mn Sh     264x117mm",264,117,""},
{"Blk       240x120mm",240,120,""},
{"Mn Sh     264x121mm",264,121,""},
{"Mn Sh     264x127mm",264,127,""},
{"Sh        229x131mm",229,131,""},
{"Mn Sh     264x131mm",264,131,""},
{"Mn Sh     264x135mm",264,135,""},
{"Mn Sh     264x137mm",264,137,""},
{"Mn Sh     264x139mm",264,139,""},
{"Mn Sh     264x143mm",264,143,""},
{"Sh        187x144mm",187,144,"for U.N.Flags Sheetlets"},
{"Sh        203x146mm",203,146,""},
{"Mn Sh     264x147mm",264,147,""},
{"Mn Sh     264x151mm",264,151,""},
{"Sh        204x153mm",204,153,"White Plains S/S"},
{"Blk       260x158mm",260,158,""},
{"Mn Sh     264x163mm",264,163,""},
{"Mn Sh     264x167mm",264,167,""},
{"Mn Sh     264x171mm",264,171,""},
{"Mn Sh     264x175mm",264,175,""},
{"Blk       2178x181mm",178,181,""},
{"Mn Sh     264x181mm",264,181,""},
{"Mn Sh     264x188mm",264,188,""},
{"Blk       2148x196mm",148,196,""},
{"Mn Sh     264x198mm",264,198,""},
{"Sh        192x201mm",192,201,"For U.S.Classics Mini - Sheets"},
{"Mn Sh     264x201mm",264,201,"Classics Mini-Sheets"},
{"Blk       2120x207mm",120,207,""},
{"Sh        264x215mm",264,215,""},
{"Sh        280x228mm",280,228,""},
{"Sh        191x229mm",191,229,""},
{"Sh        265x231mm",265,231,"for U.S.Full Sheets& Souvenir Cards"},
// "J 40x25mm", 40, 25, "Horizontal Commemorative",
// "JV 25x40mm", 25,40, "Vertical Commemorative",
// "AH 41x31mm", 41,31, "Horizontal Semi-Jumbo Commemorative",
// "AV 31x41mm", 31,41, "Vertical Semi-Jumbo",
// "S 31x31mm", 31,31, "Square Commemorative",
// "Mini 23x20mm",23,20, "Mini Regular Issues",
// "Mini Vertical 20x23mm",20,23, "Mini Regular Issues",
// "EH 25x22mm", 25,22, "Horizontal Regular Issue",
// "E22x25mm", 22,25, "Vertical Regular Issue",
// "DH 52x36mm", 52,36, "Federal Duck Stamps",
// "E 25x22mm", 25,22, "Horizontal Coils",
// "C 50x31mm", 50,31, "Horizontal Jumbo Commemoratives",
// "CV31x50mm", 31,50, "Vertical Jumbo Commemoratives",
// "T 25x27mm", 25,27, "Famous American and Champions of Liberty",
// "N 40x27mm", 40,27, "United Nations ",
// "U 33x27mm", 33,27, "United Nations & Germany",
// "Blocks 57x55mm", 57,55, "Regular Issue Plate Blocks",
// "Strips 67x25mm", 67,25, "U.S.Coil Strips ",
// "Blocks 105x57mm", 105,57, "Modern Plate Blocks ",
// "Blocks 105x57mm", 105,57, "Modern Plate Blocks",
// "Blocks 106x55mm", 106,55, "Commemorative Plate Blocks ",
// "Blocks 127x70mm", 127,70, "Jumbo Plate Blocks ",
// "Blocks 140x89mm", 140,89, "Postal Cards and Souvenir Sheets",
// "Blocks 165x94mm", 165,94, "for First Day Covers ",
// "Sh     187x144mm", 187,144, "for U.N.Flags Sheetlets",
// "Sh     192x201mm", 192,201, "For U.S.Classics Mini - Sheets",
// "Sh     265x231mm", 265,231, "for U.S.Full Sheets& Souvenir Cards",
// "Blocks 89x83mm", 89,83, "",
// "Blocks 111x91mm", 111,91, "",
// "Blocks 120x207mm", 120,207, "",
// "Blocks 127x70mm", 127,70, "",
// "Blocks 140x89mm", 140,89, "",
// "Blocks 148x196mm", 148,196, "",
// "Blocks 178x181mm", 178,181, "",
// "Sh     191x229mm", 191,229, "",
// "Sh     203x146mm", 203,146, "",
// "Sh     204x153mm", 204,153, "White Plains S/S",
// "Strips 215x20mm", 215,20, "",
// "Strips 215x22mm", 215,22, "",
// "Strips 215x24mm", 215,24, "",
// "Strips 215x25mm", 215,25, "",
// "Strips 215x27mm", 215,27, "",
// "Strips 215x28mm", 215,28, "",
// "Strips 215x30mm", 215,30, "",
// "Strips 215x31mm", 215,31, "",
// "Strips 215x33mm", 215,33, "",
// "Strips 215x36mm", 215,36, "",
// "Strips 215x39mm", 215,39, "",
// "Strips 215x41mm", 215,41, "",
// "Strips 215x44mm", 215,44, "",
// "Strips 215x48mm", 215,48, "",
// "Strips 215x50mm", 215,50, "",
// "Strips 215x52mm", 215,52, "",
// "Strips 215x57mm", 215,57, "",
// "Strips 215x61mm", 215,61, "",
// "Sh     229x131mm", 229,131, "",
// "Strips 240x63mm", 240,63, "",
// "Strips 240x68mm", 240,68, "",
// "Strips 240x74mm", 240,74, "",
// "Strips 240x80mm", 240,80, "",
// "Strips 240x82mm", 240,82, "",
// "Strips 240x84mm", 240,84, "",
// "Strips 240x89mm", 240,89, "",
// "Blocks 240x100mm", 240,100, "",
// "Blocks 240x120mm", 240,120, "",
// "Strips 243x66mm", 243,66, "",
// "Blocks 260x158mm", 260,158, "",
// "Strips 260x25mm", 260,25, "",
// "Strips 260x40mm", 260,40, "",
// "Strips 260x46mm", 260,46, "",
// "Strips 260x55mm", 260,55, "",
// "Strips 260x59mm", 260,59, "",
// "Strips 264x70mm", 264,70, "",
// "Strips 264x76mm", 264,76, "",
// "Mn Sh       264x91mm", 264,91, "",
// "Mn Sh       264x96mm", 264,96, "",
// "Mn Sh       264x105mm", 264,105, "",
// "Mn Sh       264x107mm", 264,107, "",
// "Mn Sh       264x109mm", 264,109, "",
// "Mn Sh       264x111mm", 264,111, "",
// "Mn Sh       264x115mm", 264,115, "",
// "Mn Sh       264x117mm", 264,117, "",
// "Mn Sh       264x121mm", 264,121, "",
// "Mn Sh       264x127mm", 264,127, "",
// "Mn Sh       264x131mm", 264,131, "",
// "Mn Sh       264x135mm", 264,135, "",
// "Mn Sh       264x137mm", 264,137, "",
// "Mn Sh       264x139mm", 264,139, "",
// "Mn Sh       264x143mm", 264,143, "",
// "Mn Sh       264x147mm", 264,147, "",
// "Mn Sh       264x151mm", 264,151, "",
// "Mn Sh       264x163mm", 264,163, "",
// "Mn Sh       264x167mm", 264,167, "",
// "Mn Sh       264x171mm", 264,171, "",
// "Mn Sh        264x175mm", 264,175, "",
// "Mn Sh        264x181mm", 264,181, "",
// "Mn Sh        264x188mm", 264,188, "",
// "Mn Sh        264x198mm", 264,198, "",
// "Mn Sh        264x201mm", 264,201, "Classics Mini-Sheets",
// "Sh     264x215mm", 264,215, "",
// "Sh     265x231mm", 265,231, "",
// "Sh     280x228mm", 280,228, "",
// "Strips 293x30mm", 293,30, ""
    };


    StampMountData::StampMountData( )
    {
        m_mountDoc = 0;
        // wxString mountFile = "StampMount.csv";
        // bool res = LoadMountCSV( mountFile );
    };

    wxXmlDocument* StampMountData::NewMountDocument( )
    {
        delete m_mountDoc;
        m_mountDoc = new wxXmlDocument( );
        return m_mountDoc;
    };

    wxXmlDocument* StampMountData::LoadMountCSV( wxString filename )
    {
        if ( !m_mountDoc )
        {
            NewMountDocument( );
        }

        MountCSVData* csv = new MountCSVData( );
        wxXmlNode* docRoot = m_mountDoc->GetRoot( );
        if ( !docRoot )
        {
            docRoot = Utils::NewNode( m_mountDoc, "Item" );
        }
        wxFileName name( filename );
        Utils::SetAttrStr( docRoot, "Name", name.GetName( ) );
        // name.MakeRelativeTo( "." );
       // Utils::SetAttrStr( docRoot, "ImagePath", "" );//name.GetPath( ) );

        bool status = false;
        status = csv->DoLoad( filename, m_mountDoc->GetRoot( ) );
        FixUpHyphenID( m_mountDoc );
        //        Utils::XMLDump( m_mountDoc );
        m_mountDoc->Save( "StampMounts.xml" );
        //  SetDirty( );
        delete csv;
        return m_mountDoc;
    };


    wxString StampMountData::Find( wxString id )
    {
        wxXmlNode* node = m_mountDoc->GetRoot( );
        //   std::cout << "Looking for " << id << "\n";
        return Find( node, id );
    }

    wxString StampMountData::Find( wxXmlNode* node, wxString id )
    {
        int count = 0;
        wxXmlNode* child = node->GetChildren( );
        while ( child )
        {
            wxXmlNodeType type = child->GetType( );
            wxString nodeName = child->GetName( );

            wxString val = "";
            val = child->GetAttribute( Catalog::MountDataTypeNames[ MT_ID ], val );
            //std::cout << val << " f1 ";
            count++;
            if ( !val.Cmp( id ) )
            {
                //std::cout << "Found One " << val;
                wxString val = child->GetAttribute( Catalog::MountDataTypeNames[ MT_SingleMount ], val );
                //std::cout << ",  " << val << "\n";
                return val;
            }

            if ( child->GetChildren( ) )
            {
                val = Find( child, id );
                if ( !val.IsEmpty( ) )
                {
                    return val;
                }
            }
            if ( count > 12 )
            {
                //std::cout << "\n";
                count = 0;
            }
            child = child->GetNext( );
        }
        return "";
    }

    void StampMountData::FixUpHyphenID( wxXmlDocument* doc )
    {
        wxXmlNode* node = doc->GetRoot( );
        wxString level = "";
        FixUpHyphenID( node, level );
    }
    void StampMountData::FixUpHyphenID( wxXmlNode* node, wxString level )
    {
        level += "  ";
        wxXmlNode* child = node->GetChildren( );
        int count = 0;
        while ( child )
        {
            wxXmlNodeType type = child->GetType( );
            wxString nodeName = child->GetName( );

            //            std::cout << level << nodeName << "  ";

            wxXmlAttribute* attr = child->GetAttributes( );
            while ( attr )
            {
                wxString name = attr->GetName( );
                wxString val = attr->GetValue( );
                //                std::cout << level << "   " << name << ":" << val << "\n";
                attr = attr->GetNext( );
            }
            wxString val = "";
            val = child->GetAttribute( Catalog::MountDataTypeNames[ MT_ID ], val );
            int pos = val.Find( "-" );
            wxString prefix = "Sn:US_";
            if ( pos != wxNOT_FOUND )
            {
                wxString startStr = val.Mid( 0, pos );
                int startLen = startStr.Length( );
                wxString lastStr = val.Mid( pos + 1 );
                int lastLen = lastStr.Length( );
                wxString last = startStr.Mid( 0, startLen - lastLen ) + lastStr;
                // std::cout << val << " " << startStr << " " << last << "\n";
                val = prefix + startStr;
                std::cout << val << " i1 ";
                count++;
                Utils::SetAttrStr( child, Catalog::MountDataTypeNames[ MT_ID ], val );
                int begin;
                startStr.ToInt( &begin );
                begin++;
                int end;
                lastStr.ToInt( &end );
                wxXmlNode* prevNode = child;
                wxString year = "";
                year = child->GetAttribute( Catalog::MountDataTypeNames[ MT_Year ], year );

                //wxString id = "";
                //id = child->GetAttribute( Catalog::MountDataTypeNames[ MT_ID ], id );

                wxString name = "";
                name = child->GetAttribute( Catalog::MountDataTypeNames[ MT_Name ], name );

                wxString single = "";
                single = child->GetAttribute( Catalog::MountDataTypeNames[ MT_SingleMount ], single );

                wxString mult = "";
                mult = child->GetAttribute( Catalog::MountDataTypeNames[ MT_MultipleMount ], mult );

                wxString block = "";
                block = child->GetAttribute( Catalog::MountDataTypeNames[ MT_BlockMount ], block );

                wxString sheet = "";
                sheet = child->GetAttribute( Catalog::MountDataTypeNames[ MT_SheetMount ], sheet );

                for ( int i = begin; i <= end; i++ )
                {

                    wxXmlNode* newNode = new wxXmlNode( 0, wxXML_ELEMENT_NODE, "Item" );
                    newNode->AddAttribute( Catalog::MountDataTypeNames[ MT_Year ], year );
                    wxString id;
                    id = id.Format( "%s%d", prefix, i );
                    std::cout << id << " i2 ";
                    count++;
                    newNode->AddAttribute( Catalog::MountDataTypeNames[ MT_ID ], id );

                    newNode->AddAttribute( Catalog::MountDataTypeNames[ MT_Name ], name );
                    newNode->AddAttribute( Catalog::MountDataTypeNames[ MT_SingleMount ], single );
                    newNode->AddAttribute( Catalog::MountDataTypeNames[ MT_MultipleMount ], mult );
                    newNode->AddAttribute( Catalog::MountDataTypeNames[ MT_BlockMount ], block );
                    newNode->AddAttribute( Catalog::MountDataTypeNames[ MT_SheetMount ], sheet );
                    node->InsertChildAfter( newNode, prevNode );
                    prevNode = newNode;
                }
            }
            else
            {
                wxString id = prefix + val;
                std::cout << id << " i3 ";
                count++;
                Utils::SetAttrStr( child, Catalog::MountDataTypeNames[ MT_ID ], id );
            }

            //            std::cout << "\n";
            if ( child->GetChildren( ) )
            {
                FixUpHyphenID( child, level );
            }
            if ( count > 15 )
            {
                std::cout << "\n";
                count = 0;
            }
            //}
            child = child->GetNext( );
        }
    }


    wxXmlDocument* StampMountData::LoadXML( )
    {

        bool ok = false;

        if ( !m_mountDoc )
        {
            m_mountDoc = new wxXmlDocument( );
        }

        wxString cwd = wxGetCwd( );
        //ok = m_stampDoc->Load( filename );
        wxFileInputStream stream( "US_StampMounts.xml" );
        if ( !stream.IsOk( ) )
        {
            std::cout << "Stream Create Failed.\n\n";
            return 0;
        }
        if ( !m_mountDoc->Load( stream ) )
        {
            std::cout << " Stream  Failed." << std::endl << std::endl;
            return 0;
        }
        return m_mountDoc;
    }

};