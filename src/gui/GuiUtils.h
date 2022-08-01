/**
 * @file GuiUtils.h
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 **************************************************/
#ifndef GUIUTILS_H_
#define GUIUTILS_H_

 /*
  * Includes
  */
#include "Defs.h"
#include "gui/GuiDefs.h"

void drawBorder( wxDC& dc, double x, double y, double width, double height  );
void DrawRectangle( wxDC& dc, double x, double y, double width, double height );
wxSize LogicalToDeviceRel( wxDC& dc, double x, double y );
void DrawTitle( wxDC& dc, wxString title, RealPoint pos, RealSize size );
void DrawLabel( wxDC& dc, const wxString& text,
		RealPoint pos,
        RealSize size,
		int  	alignment = wxALIGN_LEFT|wxALIGN_TOP,
		int  	indexAccel = -1  );
#endif
