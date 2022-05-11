/**
 * @file AlbumGeneratorApp.h
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

#include "AlbumGeneratorFrame.h"

  /**
   * @brief AlbumGeneratorApp class declaration.
   * @details This is the main instantiation class for the application.  It
   * inherits from wxApp.
   */
class AlbumGeneratorApp : public wxApp {
  DECLARE_CLASS( AlbumGeneratorApp )
  DECLARE_EVENT_TABLE( )

public:
  // Constructor
  AlbumGeneratorApp( );

  /**
   * @brief   Initialises member variables
   *
   **************************************************/
  void Init( );

  // Initialises the application
  virtual bool OnInit( );

  /**
   * @brief Cleanup for AlbumGeneratorApp. Called on exit.
   */
  virtual int OnExit( );

  AlbumGeneratorFrame* GetFrame( ) { return m_frame; };

private:
  AlbumGeneratorFrame* m_frame;
};

#endif
// _ALBUMGENERATORAPP_H_
