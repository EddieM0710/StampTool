/**
 * @file gui/AlbumGenApp.h
 * @author Eddie Monroe ()
 * @brief This is the main instantiation class for the application
 * @version 0.1
 * @date 2021-02-25
 *
 * @copyright Copyright (c) 2021
 *
 **************************************************/

#ifndef _ALBUMGENERATORAPP_H_
#define _ALBUMGENERATORAPP_H_

 /*
  * Includes
  */
#include "wx/image.h"

#include "gui/AlbumGenFrame.h"

class Project;

  /**
   * @brief AlbumGenApp class declaration.
   * @details This is the main instantiation class for the application.  It
   * inherits from wxApp.
   */
class AlbumGenApp : public wxApp {
  DECLARE_CLASS( AlbumGenApp )
  DECLARE_EVENT_TABLE( )

public:
  // Constructor
  AlbumGenApp( );

  /**
   * @brief   Initialises member variables
   *
   **************************************************/
  void Init( );

  // Initialises the application
  virtual bool OnInit( );

  /**
   * @brief Cleanup for AlbumGenApp. Called on exit.
   */
  virtual int OnExit( );

  AlbumGenFrame* GetFrame( ) { return m_frame; };
  Project* GetProject(){ return m_project; };
  
private:
  AlbumGenFrame* m_frame;
  Project* m_project;
};

#endif
// _ALBUMGENERATORAPP_H_
