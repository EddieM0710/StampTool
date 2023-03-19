/**
 * @file gui/StampToolApp.h
 * @author Eddie Monroe ( )
 * @brief This is the main instantiation class for the application
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright ( c ) 2021
 * 
 * This file is part of StampTool.
 *
 * StampTool is free software: you can redistribute it and/or modify it under the 
 * terms of the GNU General Public License as published by the Free Software Foundation, 
 * either version 3 of the License, or any later version.
 *
 * StampTool is distributed in the hope that it will be useful, but WITHOUT ANY 
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with 
 * StampTool. If not, see <https://www.gnu.org/licenses/>.
 *
 **************************************************/

#ifndef _STAMPTOOLAPP_H_
#define _STAMPTOOLAPP_H_

 /*
  * Includes
  */
#include "wx/image.h"

#include "gui/StampToolFrame.h"

class ToolData;

/**
 * @brief StampToolApp class declaration.
 * @details This is the main instantiation class for the application.  It
 * inherits from wxApp.
 */
class StampToolApp : public wxApp { 
    DECLARE_CLASS( StampToolApp )
    DECLARE_EVENT_TABLE( )

public:
    // Constructor
    StampToolApp( );

    /**
     * @brief   Initialises member variables
     *
     **************************************************/
    void Init( );

    // Initialises the application
    virtual bool OnInit( );

    /**
     * @brief Cleanup for StampToolApp. Called on exit.
     */
    virtual int OnExit( );

    StampToolFrame* GetFrame( ) { return m_frame; };
    ToolData* GetToolData( ){ return m_toolData; };

private:
    StampToolFrame* m_frame;

    // global declaration of application data 
    ToolData* m_toolData;

};

#endif
// _STAMPTOOLAPP_H_
