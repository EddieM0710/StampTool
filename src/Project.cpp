#include "Project.h"
#include "defs.h"
#include <iostream>

bool Project::Load( wxString filename )
{
    m_filename = filename;

    if ( !m_ProjectDoc.Load( m_filename.c_str() ) )
    {
        ReportError( "Project::Load", "error loading Prokect xml file.", true );
    }

    wxXmlNode* projectRoot = m_ProjectDoc.GetRoot();
    wxString name = projectRoot->GetName();
    if ( name.Cmp( "Project" ) )
    {
        std::cout << "Initial node must be <Project>"
            << "\n";
        std::cout << "Found \"" << name << "\" instead.\n";
    }
    LoadAttributes( projectRoot );
}

bool Project::LoadAttributes( wxXmlNode* thisObject )
{
    const wxXmlAttribute* attr = thisObject->GetAttributes();
    while ( attr )
    {
        wxString name = attr->GetName();
        wxString val = attr->GetValue();
        if ( !name.Cmp( "OutputName" ) )
        {
            m_outputName = val;
        }
        else if ( !name.Cmp( "Layout" ) )
        {
            m_layout = val;
        }
        else if ( !name.Cmp( "ImagePath" ) )
        {
            m_imagePath = val;
        }
        else if ( !name.Cmp( "StampProperties" ) )
        {
            m_stampProperties = val;
        }
        attr = attr->GetNext();
    }
}
