
		wxString urlString = wxT("http://www.google.com/finance/historical?q=")
			+ wxString::Format("%s", m_parent->GetSymbol())
			+ wxString::Format("&startdate=%s+%d%%2C+%d", startDate.GetMonthName(startDate.GetMonth(), wxDateTime::Name_Abbr), (int)startDate.GetDay(),(int)startDate.GetYear())
			+ wxString::Format("&enddate=%s+%d%%2C+%d", endDate.GetMonthName(endDate.GetMonth(), wxDateTime::Name_Abbr), (int)endDate.GetDay(), (int)endDate.GetYear())
			+ wxString::Format("&output=csv");
		wxURL url( urlString );
		if( url.GetError( )==wxURL_NOERR )
        {

            wxInputStream *in = url.GetInputStream( );
            wxURLError err = url.GetError( );
            if( in && in->IsOk( ) )
            {
                if ( ReadTextInStream( in ) )
                {
                    status = true;
                }
            }
            else
            {
                status = false;// error getting data
            }
            delete in;

        }
        else
        {
            status = false;// error getting data
        }