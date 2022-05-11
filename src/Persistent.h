/**
 * @file Persistent.h
 * @author Eddie Monroe (you@domain.com)
 * @brief Class to manage/read/write persistent parameters
 * @version 0.1
 * @date 2021-02-24
 *
 * @copyright Copyright (c) 2021
 *
 */

/**
 * 
 * @todo 1 make persistent data file live in the user config directory
 * 
 **************************************************/

#ifndef Persistent_H
#define Persistent_H

#include <wx/dynarray.h>
#include <wx/string.h>

/**
 * @brief Class to manage/read/write persistent parameters
 *
 */
class Persistent
{
  public:
    /**
     * @brief Construct a new Persistent object
     *
     */
    Persistent( );

    /**
     * @brief Destroy the Persistent object
     *
     */
    ~Persistent( ){ };


};

#endif