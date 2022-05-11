/**
 * @file XMLUtilities.h
 * @author Eddie Monroe ()
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 **************************************************/

#ifndef XMLIterator_H
#define XMLIterator_H

#include "wx/xml/xml.h"


// Class for iterating an XML heirarchy
class XMLIterator
{
  private:
    wxXmlNode* m_parent;      // pointer to parent of current element
    wxXmlNode* m_currElement; // pointer to the current element
    XMLIterator* m_iterator;   // iterator for children of this element
    bool m_decend;             // bool; true => iterate children
    bool m_firstDone; // bool; true if First has been called; if not true Next
                      // just returns null

  public:
    /**
     * XMLIterator - constructor for iterating an XML heirarchy
     *
     * @param   parent : is the xml element whose children will be
     * iterated.
     * @param   decend : false will iterate only the first level
     * childeren. - true (default) will iterate  heirarchy
     */
    XMLIterator( wxXmlNode* parent, bool decend = true );
    ~XMLIterator( );

    /**
     * Returns the first child or Null
     * @return {wxXmlNode*}  :
     */
    wxXmlNode* First( );

    /**
     *  Successively returns the next child or Null if finished.
     * @return {wxXmlNode*}  :
     */
    wxXmlNode* Next( );
};

bool IsNodeType( wxXmlNode* ele, NodeType type);
void IDElement( wxXmlNode* ele );


// NodeType FindNodeType(wxXmlNode *element);

void AddStamp( wxXmlNode* child );
void AddStamp( wxXmlNode* parent, wxXmlNode* child, int level = 0 );
wxXmlNode* MoveStamp( wxXmlNode* newParent, wxXmlNode* child );
void SortData( wxXmlNode* newRoot, wxXmlNode* child );

wxXmlNode* NewNode (wxXmlNode* parent, wxString name );
wxXmlNode* NewNode (wxXmlDocument* parent, wxString name );

wxXmlNode* FirstChildElement( wxXmlNode* node, wxString name );
wxXmlNode* GetNext( wxXmlNode* node, wxString name );

wxXmlAttribute* GetAttribute( wxXmlNode* node, wxString attrName );

wxString  GetAttributeValue( wxXmlNode* node, wxString attrName  );

wxXmlAttribute* SetAttribute( wxXmlNode* node, wxString name, wxString val);

void XMLDump(wxXmlDocument* doc);
void XMLDumpNode( wxXmlNode* node, wxString level );

#endif