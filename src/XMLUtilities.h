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

#include "tinyxml2.h"

using namespace tinyxml2;

// Class for iterating an XML heirarchy
class XMLIterator
{
  private:
    XMLElement* m_parent;      // pointer to parent of current element
    XMLElement* m_currElement; // pointer to the current element
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
    XMLIterator( XMLElement* parent, bool decend = true );
    ~XMLIterator( );

    /**
     * Returns the first child or Null
     * @return {XMLElement*}  :
     */
    XMLElement* First( );

    /**
     *  Successively returns the next child or Null if finished.
     * @return {XMLElement*}  :
     */
    XMLElement* Next( );
};

bool IsNodeType( XMLElement* ele, NodeType type);
void IDElement( XMLElement* ele );


// NodeType FindNodeType(XMLElement *element);

void AddStamp( XMLElement* child );
void AddStamp( XMLElement* parent, XMLElement* child, int level = 0 );
XMLElement* MoveStamp( XMLElement* newParent, XMLElement* child );
void SortData( XMLElement* newRoot, XMLElement* child );


#endif