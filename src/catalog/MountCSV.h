/**
 * @file CSV.h
 * @author Eddie Monroe ( )
 * @brief This file contains the class that reads .csv files
 * and loads them into an XML structure.
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
 */

#ifndef MountCSV_H
#define MountCSV_H


#include "wx/xml/xml.h"
 //#include <wx/dynarray.h>
#include <wx/filename.h>
#include <wx/string.h>

#include <wx/txtstrm.h>
#include <wx/wfstream.h>
#include <vector>



namespace Catalog {

    typedef enum {
        MT_Year = 0,
        MT_ID,
        MT_Name,
        MT_SingleMount,
        MT_MultipleMount,
        MT_BlockMount,
        MT_SheetMount,
        MT_NbrDatatypes
    }MountDataTypes;

    extern wxString MountDataTypeNames[ MT_NbrDatatypes ];

    typedef std::vector<wxString> StringArray;
    typedef std::vector<MountDataTypes> DataTypesArray;

#define MaxNbrCSVCols 50

    /**
     * @brief read/write .csv files.
     *
     */
    class MountCSVData
    {
    public:


        /**
         * @brief Construct a new MountCSVData object
         *
         */
        MountCSVData( void ) { };

        /**
         * @brief Destroy the MountCSVData object
         *
         */
        ~MountCSVData( void ) { };

        /**
         * @brief Return the number of columes
         *
         * @return int   Return the number of columns
         */
        int NbrColNames( void ) { return m_csvColName.size( ); };

        /**
         * @brief Get the Col Name object
         *
         * @param  col ; index for the column number
         * @return wxString ; returns th column name
         */
        wxString GetColName( int col ) { return m_csvColName.at( col ); };

        /**
         * @brief Adds a Col Name to the col string array
         *
         * @param  name    the name of the new colun to add
         * @return size_t  the col index to which this string was assigned
         */
        void SetColName( wxString name ) { return m_csvColName.push_back( name ); };

        /**
         * @brief Opens the file for read and does appropriate initializations
         *
         * @param  filename ; full path to the file to be read
         * @return true ; true on successful open
         */
        bool ReadDataFile( wxString& filename );

        /**
         * @brief Try to fix the input line if it has embedded quotes and commas.
         *
         * @details Colnect csv export files seem to be good but opening in Office Calc/Excel then
         * saving it back to a csv file frequently screws things up.
         *
         * @param  line :line to be fixed
         */
        bool FixUpLine( wxString& line, int lineNbr );

        /**
         * @brief Read the csv file line by line.
         *
         * @details This saves the read data into an XML tree structure.
         * the text input stream is what is read but some status
         * checking needs to be done and passing in the fil stream
         * was the quick easy way to handle it.
         *
         * @param  file   file stream for the input file
         * @param  text   Text Stream for the input file
         * @return true   if the file was succesfully read otherwise false.

         */
        bool ReadTextInStream( wxFileInputStream& file, wxTextInputStream& text );

        /**
         * @brief look thru the col string array and return the corresponding index
         *
         * @param  colName : col name to search for.
         * @return int : index of colName; wxNOT_FOUND if not found
         */
         //int FindCol( wxString& colName ) { m_csvColName.Index( colName ); };

         /**
          * @brief Create a map of csv col names to DataTypes ( Defs.h )
          *
          */
        void MakeColMap( void );

        /**
         * @brief looks through the stamp catalog codes ( DT_Catalog_Codes )
         * and returns the ID for a stamp number entry that starts "Sn:US".
         *
         * @details this needs to be modified to return the id for any given
         * catalog code in the list
         *
         * @param  catCodes  the string of catalogs
         * @param  id        returns the id of the stamp
         * @return true      true if an id was found else false
         */
        bool GetIDNbr( wxString catCodes, wxString& id );


        /**
         * @brief entry point of file read
         *
         * @param  filename file name to read
         * @param  nodeData toplevel XML node to store the data
         */
        bool DoLoad( wxString& filename, wxXmlNode* nodeData );



    private:
        wxString m_filename;
        StringArray m_csvColName;
        DataTypesArray m_csvColMap;
        wxXmlNode* m_nodeData;
        int m_lineCnt;
    };

}
#endif