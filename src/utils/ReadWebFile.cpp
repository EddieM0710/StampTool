
bool InputPriceData::ReadDataWeb( )
{
    isLoaded = false;
    wxInputStream* in = RetrieveData( true );
    if ( in )
    {
        ReadTextInStream( in, m_inputDataStrings );
        isLoaded = true;
    }
    return  isLoaded;
}

inline bool InputPriceData::IndexRangeValid( size_t startIndex, size_t endIndex )
{
    if ( startIndex < 0 ||
        startIndex <= m_count ||
        endIndex < 0 ||
        endIndex <= m_count ||
        endIndex > startIndex )
    {
        wxASSERT_MSG( false, wxT( " Data NULL" ) );
        return false;
    }
    return true;
};
wxInputStream* InputPriceData::RetrieveData( bool full = false )
{
    bool status = FALSE;
    if ( !m_parent->GetSymbol( ).IsEmpty( ) )
    {
        wxString outputsize = wxT( "full" );
        if ( !full )
        {
            outputsize = wxT( "compact" );
        };
        wxString urlString = wxT( "http://www.alphavantage.co/query?function=TIME_SERIES_DAILY&outputsize=" )
            + outputsize + wxT( "&symbol=" )
            + wxString::Format( "%s", m_parent->GetSymbol( ) )
            + wxT( "&apikey=8YT2SJBMO5JBI52N&datatype=csv " );


        wxString filename = GetFilename( );

        wxFile file( filename, wxFile::write );

        wxFileOutputStream outstream( file );

        wxURL url( urlString );
        if ( url.GetError( ) == wxURL_NOERR )
        {
            wxInputStream* in = url.GetInputStream( );
            wxStreamError err = in->GetLastError( );

            wxInputStream& inStream = in->Read( outstream );
            int i = in->GetSize( );
            i = in->GetLength( );
            i = in->TellI( );
            i = in->SeekI( 0 );
            wxTextInputStream text( *in );
            err = in->GetLastError( );
            wxString inLine = text.ReadLine( );//skip header
            err = in->GetLastError( );
            if ( !in->Eof( ) )
            {
                //read a line and parse it
                inLine = text.ReadLine( );
                err = in->GetLastError( );
            }
            return in;




        }
    }
    return ( wxInputStream* ) 0;
}
