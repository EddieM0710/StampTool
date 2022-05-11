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
#include "tinyxml2.h"

using namespace tinyxml2;

class Node
{
  public:
    Node( ) { SetElement( (XMLElement *)0 ); };

    Node( XMLElement *ele ) { SetElement( ele ); };

    ~Node( ){ };

    void SetNodeType( NodeType type ) { m_nodeType = type; };
    NodeType GetNodeType( ) { return m_nodeType; };

    XMLElement *GetElement( ) { return m_Element; };
    void SetElement( XMLElement *node ) { m_Element = node; };

    virtual bool IsOK( ) = 0;


  private:
    XMLElement *m_Element;
    NodeType m_nodeType;
};

#endif