/**
 * @file GuiUtils.h
 * @author Eddie Monroe
 * @brief 
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright ( c ) 2022
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
		int  	alignment = wxALIGN_LEFT | wxALIGN_TOP, 
		int  	indexAccel = -1  );

void DrawImage( wxDC& dc, wxString fileName, double x, double y, double w, double h );
wxImage* GetImageFromFilename( wxString filename );
       
#endif
