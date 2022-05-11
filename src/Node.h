/**
 * @file Node.h
 * @author Eddie Monroe ()
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 **************************************************/

#ifndef Node_h
#define Node_h

#include "Defs.h"
#include "wx/xml/xml.h"

//

class Node
{
  public:
    Node( ) { SetElement( (wxXmlNode *)0 ); };

    Node( wxXmlNode *ele ) { SetElement( ele ); };

    ~Node( ){ };

    void SetNodeType( NodeType type ) { m_nodeType = type; };
    NodeType GetNodeType( ) { return m_nodeType; };

    wxXmlNode *GetElement( ) { return m_Element; };
    void SetElement( wxXmlNode *node ) { m_Element = node; };

    virtual bool IsOK( ) = 0;


  private:
    wxXmlNode *m_Element;
    NodeType m_nodeType;
};

#endif