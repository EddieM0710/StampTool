/**
 * @file FilterDialog.cpp
 * @author Eddie Monroe ()
 * @brief 
 * @version 0.1
 * @date 2021-02-25
 * 
 * @copyright Copyright (c) 2021
 * 
 **************************************************/


// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

 
 

#include "Filter.h"

 
 

/*
 * FilterDialog type definition
 */

IMPLEMENT_DYNAMIC_CLASS( FilterDialog, wxDialog )
; // silly business; The above macro screws up the formatter

/*
 * FilterDialog event table definition
 */

BEGIN_EVENT_TABLE( FilterDialog, wxDialog )

 // FilterDialog event table entries
EVT_CHOICE( ID_CHOICE, FilterDialog::OnChoiceSelected )
EVT_CHOICE( ID_CHOICE1, FilterDialog::OnChoice1Selected )
EVT_LISTBOX_DCLICK( ID_CHECKLISTBOX1,
                    FilterDialog::OnChecklistbox1DoubleClicked )
EVT_LISTBOX_DCLICK( ID_CHECKLISTBOX, FilterDialog::OnChecklistboxDoubleClicked )
 // FilterDialog event table entries

END_EVENT_TABLE( )
;  // silly business; The above macro screws up the formatter

/*
 * FilterDialog constructors
 */

FilterDialog::FilterDialog( void )
{
    Init( );
}

FilterDialog::FilterDialog( wxWindow* parent, wxWindowID id,
                            const wxString& caption, const wxPoint& pos,
                            const wxSize& size, long style )
{
    Init( );
    Create( parent, id, caption, pos, size, style );
}

/*
 * Filter creator
 */

bool FilterDialog::Create( wxWindow* parent, wxWindowID id,
                           const wxString& caption, const wxPoint& pos,
                           const wxSize& size, long style )
{
     // FilterDialog creation
    SetExtraStyle( wxWS_EX_VALIDATE_RECURSIVELY | wxWS_EX_BLOCK_EVENTS );
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls( );
    if ( GetSizer( ) )
    {
        GetSizer( )->SetSizeHints( this );
    }
    Centre( );
     // FilterDialog creation
    return true;
}

/*
 * FilterDialog destructor
 */

FilterDialog::~FilterDialog( void )
{
     // FilterDialog destruction
     // FilterDialog destruction
}

/*
 * Member initialisation
 */

void FilterDialog::Init( )
{
     // FilterDialog member initialisation
     // FilterDialog member initialisation
}

/*
 * Control creation for Filter
 */

void FilterDialog::CreateControls( )
{
     // FilterDialog content construction

    FilterDialog* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer( wxVERTICAL );
    itemDialog1->SetSizer( itemBoxSizer2 );

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer1, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,
                        5 );

    wxStaticText* itemStaticText1
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "Year from" ),
                            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( itemStaticText1, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                        5 );

    wxArrayString itemChoice2Strings;
    itemChoice2Strings.Add( _( "1800" ) );
    itemChoice2Strings.Add( _( "1801" ) );
    itemChoice2Strings.Add( _( "1802" ) );
    itemChoice2Strings.Add( _( "1803" ) );
    itemChoice2Strings.Add( _( "1804" ) );
    itemChoice2Strings.Add( _( "1805" ) );
    itemChoice2Strings.Add( _( "1806" ) );
    itemChoice2Strings.Add( _( "1807" ) );
    itemChoice2Strings.Add( _( "1808" ) );
    itemChoice2Strings.Add( _( "1809" ) );
    itemChoice2Strings.Add( _( "1810" ) );
    itemChoice2Strings.Add( _( "1811" ) );
    itemChoice2Strings.Add( _( "1812" ) );
    itemChoice2Strings.Add( _( "1813" ) );
    itemChoice2Strings.Add( _( "1814" ) );
    itemChoice2Strings.Add( _( "1815" ) );
    itemChoice2Strings.Add( _( "1816" ) );
    itemChoice2Strings.Add( _( "1817" ) );
    itemChoice2Strings.Add( _( "1818" ) );
    itemChoice2Strings.Add( _( "1819" ) );
    itemChoice2Strings.Add( _( "1820" ) );
    itemChoice2Strings.Add( _( "1821" ) );
    itemChoice2Strings.Add( _( "1822" ) );
    itemChoice2Strings.Add( _( "1823" ) );
    itemChoice2Strings.Add( _( "1824" ) );
    itemChoice2Strings.Add( _( "1825" ) );
    itemChoice2Strings.Add( _( "1826" ) );
    itemChoice2Strings.Add( _( "1827" ) );
    itemChoice2Strings.Add( _( "1828" ) );
    itemChoice2Strings.Add( _( "1829" ) );
    itemChoice2Strings.Add( _( "1830" ) );
    itemChoice2Strings.Add( _( "1831" ) );
    itemChoice2Strings.Add( _( "1832" ) );
    itemChoice2Strings.Add( _( "1833" ) );
    itemChoice2Strings.Add( _( "1834" ) );
    itemChoice2Strings.Add( _( "1835" ) );
    itemChoice2Strings.Add( _( "1836" ) );
    itemChoice2Strings.Add( _( "1837" ) );
    itemChoice2Strings.Add( _( "1838" ) );
    itemChoice2Strings.Add( _( "1839" ) );
    itemChoice2Strings.Add( _( "1840" ) );
    itemChoice2Strings.Add( _( "1841" ) );
    itemChoice2Strings.Add( _( "1842" ) );
    itemChoice2Strings.Add( _( "1843" ) );
    itemChoice2Strings.Add( _( "1844" ) );
    itemChoice2Strings.Add( _( "1845" ) );
    itemChoice2Strings.Add( _( "1846" ) );
    itemChoice2Strings.Add( _( "1847" ) );
    itemChoice2Strings.Add( _( "1848" ) );
    itemChoice2Strings.Add( _( "1849" ) );
    itemChoice2Strings.Add( _( "1850" ) );
    itemChoice2Strings.Add( _( "1851" ) );
    itemChoice2Strings.Add( _( "1852" ) );
    itemChoice2Strings.Add( _( "1853" ) );
    itemChoice2Strings.Add( _( "1854" ) );
    itemChoice2Strings.Add( _( "1855" ) );
    itemChoice2Strings.Add( _( "1856" ) );
    itemChoice2Strings.Add( _( "1857" ) );
    itemChoice2Strings.Add( _( "1858" ) );
    itemChoice2Strings.Add( _( "1859" ) );
    itemChoice2Strings.Add( _( "1860" ) );
    itemChoice2Strings.Add( _( "1861" ) );
    itemChoice2Strings.Add( _( "1862" ) );
    itemChoice2Strings.Add( _( "1863" ) );
    itemChoice2Strings.Add( _( "1864" ) );
    itemChoice2Strings.Add( _( "1865" ) );
    itemChoice2Strings.Add( _( "1866" ) );
    itemChoice2Strings.Add( _( "1867" ) );
    itemChoice2Strings.Add( _( "1868" ) );
    itemChoice2Strings.Add( _( "1869" ) );
    itemChoice2Strings.Add( _( "1870" ) );
    itemChoice2Strings.Add( _( "1871" ) );
    itemChoice2Strings.Add( _( "1872" ) );
    itemChoice2Strings.Add( _( "1873" ) );
    itemChoice2Strings.Add( _( "1874" ) );
    itemChoice2Strings.Add( _( "1875" ) );
    itemChoice2Strings.Add( _( "1876" ) );
    itemChoice2Strings.Add( _( "1877" ) );
    itemChoice2Strings.Add( _( "1878" ) );
    itemChoice2Strings.Add( _( "1879" ) );
    itemChoice2Strings.Add( _( "1880" ) );
    itemChoice2Strings.Add( _( "1881" ) );
    itemChoice2Strings.Add( _( "1882" ) );
    itemChoice2Strings.Add( _( "1883" ) );
    itemChoice2Strings.Add( _( "1884" ) );
    itemChoice2Strings.Add( _( "1885" ) );
    itemChoice2Strings.Add( _( "1886" ) );
    itemChoice2Strings.Add( _( "1887" ) );
    itemChoice2Strings.Add( _( "1888" ) );
    itemChoice2Strings.Add( _( "1889" ) );
    itemChoice2Strings.Add( _( "1890" ) );
    itemChoice2Strings.Add( _( "1891" ) );
    itemChoice2Strings.Add( _( "1892" ) );
    itemChoice2Strings.Add( _( "1893" ) );
    itemChoice2Strings.Add( _( "1894" ) );
    itemChoice2Strings.Add( _( "1895" ) );
    itemChoice2Strings.Add( _( "1896" ) );
    itemChoice2Strings.Add( _( "1897" ) );
    itemChoice2Strings.Add( _( "1898" ) );
    itemChoice2Strings.Add( _( "1899" ) );
    itemChoice2Strings.Add( _( "1900" ) );
    itemChoice2Strings.Add( _( "1901" ) );
    itemChoice2Strings.Add( _( "1902" ) );
    itemChoice2Strings.Add( _( "1903" ) );
    itemChoice2Strings.Add( _( "1904" ) );
    itemChoice2Strings.Add( _( "1905" ) );
    itemChoice2Strings.Add( _( "1906" ) );
    itemChoice2Strings.Add( _( "1907" ) );
    itemChoice2Strings.Add( _( "1908" ) );
    itemChoice2Strings.Add( _( "1909" ) );
    itemChoice2Strings.Add( _( "1910" ) );
    itemChoice2Strings.Add( _( "1911" ) );
    itemChoice2Strings.Add( _( "1912" ) );
    itemChoice2Strings.Add( _( "1913" ) );
    itemChoice2Strings.Add( _( "1914" ) );
    itemChoice2Strings.Add( _( "1915" ) );
    itemChoice2Strings.Add( _( "1916" ) );
    itemChoice2Strings.Add( _( "1917" ) );
    itemChoice2Strings.Add( _( "1918" ) );
    itemChoice2Strings.Add( _( "1919" ) );
    itemChoice2Strings.Add( _( "1920" ) );
    itemChoice2Strings.Add( _( "1921" ) );
    itemChoice2Strings.Add( _( "1922" ) );
    itemChoice2Strings.Add( _( "1923" ) );
    itemChoice2Strings.Add( _( "1924" ) );
    itemChoice2Strings.Add( _( "1925" ) );
    itemChoice2Strings.Add( _( "1926" ) );
    itemChoice2Strings.Add( _( "1927" ) );
    itemChoice2Strings.Add( _( "1928" ) );
    itemChoice2Strings.Add( _( "1929" ) );
    itemChoice2Strings.Add( _( "1930" ) );
    itemChoice2Strings.Add( _( "1931" ) );
    itemChoice2Strings.Add( _( "1932" ) );
    itemChoice2Strings.Add( _( "1933" ) );
    itemChoice2Strings.Add( _( "1934" ) );
    itemChoice2Strings.Add( _( "1935" ) );
    itemChoice2Strings.Add( _( "1936" ) );
    itemChoice2Strings.Add( _( "1937" ) );
    itemChoice2Strings.Add( _( "1938" ) );
    itemChoice2Strings.Add( _( "1939" ) );
    itemChoice2Strings.Add( _( "1940" ) );
    itemChoice2Strings.Add( _( "1941" ) );
    itemChoice2Strings.Add( _( "1942" ) );
    itemChoice2Strings.Add( _( "1943" ) );
    itemChoice2Strings.Add( _( "1944" ) );
    itemChoice2Strings.Add( _( "1945" ) );
    itemChoice2Strings.Add( _( "1946" ) );
    itemChoice2Strings.Add( _( "1947" ) );
    itemChoice2Strings.Add( _( "1948" ) );
    itemChoice2Strings.Add( _( "1949" ) );
    itemChoice2Strings.Add( _( "1950" ) );
    itemChoice2Strings.Add( _( "1951" ) );
    itemChoice2Strings.Add( _( "1952" ) );
    itemChoice2Strings.Add( _( "1953" ) );
    itemChoice2Strings.Add( _( "1954" ) );
    itemChoice2Strings.Add( _( "1955" ) );
    itemChoice2Strings.Add( _( "1956" ) );
    itemChoice2Strings.Add( _( "1957" ) );
    itemChoice2Strings.Add( _( "1958" ) );
    itemChoice2Strings.Add( _( "1959" ) );
    itemChoice2Strings.Add( _( "1960" ) );
    itemChoice2Strings.Add( _( "1961" ) );
    itemChoice2Strings.Add( _( "1962" ) );
    itemChoice2Strings.Add( _( "1963" ) );
    itemChoice2Strings.Add( _( "1964" ) );
    itemChoice2Strings.Add( _( "1965" ) );
    itemChoice2Strings.Add( _( "1966" ) );
    itemChoice2Strings.Add( _( "1967" ) );
    itemChoice2Strings.Add( _( "1968" ) );
    itemChoice2Strings.Add( _( "1969" ) );
    itemChoice2Strings.Add( _( "1970" ) );
    itemChoice2Strings.Add( _( "1971" ) );
    itemChoice2Strings.Add( _( "1972" ) );
    itemChoice2Strings.Add( _( "1973" ) );
    itemChoice2Strings.Add( _( "1974" ) );
    itemChoice2Strings.Add( _( "1975" ) );
    itemChoice2Strings.Add( _( "1976" ) );
    itemChoice2Strings.Add( _( "1977" ) );
    itemChoice2Strings.Add( _( "1978" ) );
    itemChoice2Strings.Add( _( "1979" ) );
    itemChoice2Strings.Add( _( "1980" ) );
    itemChoice2Strings.Add( _( "1981" ) );
    itemChoice2Strings.Add( _( "1982" ) );
    itemChoice2Strings.Add( _( "1983" ) );
    itemChoice2Strings.Add( _( "1984" ) );
    itemChoice2Strings.Add( _( "1985" ) );
    itemChoice2Strings.Add( _( "1986" ) );
    itemChoice2Strings.Add( _( "1987" ) );
    itemChoice2Strings.Add( _( "1988" ) );
    itemChoice2Strings.Add( _( "1989" ) );
    itemChoice2Strings.Add( _( "1990" ) );
    itemChoice2Strings.Add( _( "1991" ) );
    itemChoice2Strings.Add( _( "1992" ) );
    itemChoice2Strings.Add( _( "1993" ) );
    itemChoice2Strings.Add( _( "1994" ) );
    itemChoice2Strings.Add( _( "1995" ) );
    itemChoice2Strings.Add( _( "1996" ) );
    itemChoice2Strings.Add( _( "1997" ) );
    itemChoice2Strings.Add( _( "1998" ) );
    itemChoice2Strings.Add( _( "1999" ) );
    itemChoice2Strings.Add( _( "2000" ) );
    itemChoice2Strings.Add( _( "2001" ) );
    itemChoice2Strings.Add( _( "2002" ) );
    itemChoice2Strings.Add( _( "2003" ) );
    itemChoice2Strings.Add( _( "2004" ) );
    itemChoice2Strings.Add( _( "2005" ) );
    itemChoice2Strings.Add( _( "2006" ) );
    itemChoice2Strings.Add( _( "2007" ) );
    itemChoice2Strings.Add( _( "2008" ) );
    itemChoice2Strings.Add( _( "2009" ) );
    itemChoice2Strings.Add( _( "2010" ) );
    itemChoice2Strings.Add( _( "2011" ) );
    itemChoice2Strings.Add( _( "2012" ) );
    itemChoice2Strings.Add( _( "2013" ) );
    itemChoice2Strings.Add( _( "2014" ) );
    itemChoice2Strings.Add( _( "2015" ) );
    itemChoice2Strings.Add( _( "2016" ) );
    itemChoice2Strings.Add( _( "2017" ) );
    itemChoice2Strings.Add( _( "2018" ) );
    itemChoice2Strings.Add( _( "2019" ) );
    itemChoice2Strings.Add( _( "2020" ) );
    itemChoice2Strings.Add( _( "2021" ) );
    itemChoice2Strings.Add( _( "2022" ) );
    itemChoice2Strings.Add( _( "2023" ) );
    itemChoice2Strings.Add( _( "2024" ) );
    wxChoice* itemChoice2
        = new wxChoice( itemDialog1, ID_CHOICE, wxDefaultPosition,
                        wxDefaultSize, itemChoice2Strings, 0 );
    itemBoxSizer1->Add( itemChoice2, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxStaticText* itemStaticText3
        = new wxStaticText( itemDialog1, wxID_STATIC, _( "to" ),
                            wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer1->Add( itemStaticText3, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                        5 );

    wxArrayString itemChoice4Strings;
    itemChoice4Strings.Add( _( "1800" ) );
    itemChoice4Strings.Add( _( "1801" ) );
    itemChoice4Strings.Add( _( "1802" ) );
    itemChoice4Strings.Add( _( "1803" ) );
    itemChoice4Strings.Add( _( "1804" ) );
    itemChoice4Strings.Add( _( "1805" ) );
    itemChoice4Strings.Add( _( "1806" ) );
    itemChoice4Strings.Add( _( "1807" ) );
    itemChoice4Strings.Add( _( "1808" ) );
    itemChoice4Strings.Add( _( "1809" ) );
    itemChoice4Strings.Add( _( "1810" ) );
    itemChoice4Strings.Add( _( "1811" ) );
    itemChoice4Strings.Add( _( "1812" ) );
    itemChoice4Strings.Add( _( "1813" ) );
    itemChoice4Strings.Add( _( "1814" ) );
    itemChoice4Strings.Add( _( "1815" ) );
    itemChoice4Strings.Add( _( "1816" ) );
    itemChoice4Strings.Add( _( "1817" ) );
    itemChoice4Strings.Add( _( "1818" ) );
    itemChoice4Strings.Add( _( "1819" ) );
    itemChoice4Strings.Add( _( "1820" ) );
    itemChoice4Strings.Add( _( "1821" ) );
    itemChoice4Strings.Add( _( "1822" ) );
    itemChoice4Strings.Add( _( "1823" ) );
    itemChoice4Strings.Add( _( "1824" ) );
    itemChoice4Strings.Add( _( "1825" ) );
    itemChoice4Strings.Add( _( "1826" ) );
    itemChoice4Strings.Add( _( "1827" ) );
    itemChoice4Strings.Add( _( "1828" ) );
    itemChoice4Strings.Add( _( "1829" ) );
    itemChoice4Strings.Add( _( "1830" ) );
    itemChoice4Strings.Add( _( "1831" ) );
    itemChoice4Strings.Add( _( "1832" ) );
    itemChoice4Strings.Add( _( "1833" ) );
    itemChoice4Strings.Add( _( "1834" ) );
    itemChoice4Strings.Add( _( "1835" ) );
    itemChoice4Strings.Add( _( "1836" ) );
    itemChoice4Strings.Add( _( "1837" ) );
    itemChoice4Strings.Add( _( "1838" ) );
    itemChoice4Strings.Add( _( "1839" ) );
    itemChoice4Strings.Add( _( "1840" ) );
    itemChoice4Strings.Add( _( "1841" ) );
    itemChoice4Strings.Add( _( "1842" ) );
    itemChoice4Strings.Add( _( "1843" ) );
    itemChoice4Strings.Add( _( "1844" ) );
    itemChoice4Strings.Add( _( "1845" ) );
    itemChoice4Strings.Add( _( "1846" ) );
    itemChoice4Strings.Add( _( "1847" ) );
    itemChoice4Strings.Add( _( "1848" ) );
    itemChoice4Strings.Add( _( "1849" ) );
    itemChoice4Strings.Add( _( "1850" ) );
    itemChoice4Strings.Add( _( "1851" ) );
    itemChoice4Strings.Add( _( "1852" ) );
    itemChoice4Strings.Add( _( "1853" ) );
    itemChoice4Strings.Add( _( "1854" ) );
    itemChoice4Strings.Add( _( "1855" ) );
    itemChoice4Strings.Add( _( "1856" ) );
    itemChoice4Strings.Add( _( "1857" ) );
    itemChoice4Strings.Add( _( "1858" ) );
    itemChoice4Strings.Add( _( "1859" ) );
    itemChoice4Strings.Add( _( "1860" ) );
    itemChoice4Strings.Add( _( "1861" ) );
    itemChoice4Strings.Add( _( "1862" ) );
    itemChoice4Strings.Add( _( "1863" ) );
    itemChoice4Strings.Add( _( "1864" ) );
    itemChoice4Strings.Add( _( "1865" ) );
    itemChoice4Strings.Add( _( "1866" ) );
    itemChoice4Strings.Add( _( "1867" ) );
    itemChoice4Strings.Add( _( "1868" ) );
    itemChoice4Strings.Add( _( "1869" ) );
    itemChoice4Strings.Add( _( "1870" ) );
    itemChoice4Strings.Add( _( "1871" ) );
    itemChoice4Strings.Add( _( "1872" ) );
    itemChoice4Strings.Add( _( "1873" ) );
    itemChoice4Strings.Add( _( "1874" ) );
    itemChoice4Strings.Add( _( "1875" ) );
    itemChoice4Strings.Add( _( "1876" ) );
    itemChoice4Strings.Add( _( "1877" ) );
    itemChoice4Strings.Add( _( "1878" ) );
    itemChoice4Strings.Add( _( "1879" ) );
    itemChoice4Strings.Add( _( "1880" ) );
    itemChoice4Strings.Add( _( "1881" ) );
    itemChoice4Strings.Add( _( "1882" ) );
    itemChoice4Strings.Add( _( "1883" ) );
    itemChoice4Strings.Add( _( "1884" ) );
    itemChoice4Strings.Add( _( "1885" ) );
    itemChoice4Strings.Add( _( "1886" ) );
    itemChoice4Strings.Add( _( "1887" ) );
    itemChoice4Strings.Add( _( "1888" ) );
    itemChoice4Strings.Add( _( "1889" ) );
    itemChoice4Strings.Add( _( "1890" ) );
    itemChoice4Strings.Add( _( "1891" ) );
    itemChoice4Strings.Add( _( "1892" ) );
    itemChoice4Strings.Add( _( "1893" ) );
    itemChoice4Strings.Add( _( "1894" ) );
    itemChoice4Strings.Add( _( "1895" ) );
    itemChoice4Strings.Add( _( "1896" ) );
    itemChoice4Strings.Add( _( "1897" ) );
    itemChoice4Strings.Add( _( "1898" ) );
    itemChoice4Strings.Add( _( "1899" ) );
    itemChoice4Strings.Add( _( "1900" ) );
    itemChoice4Strings.Add( _( "1901" ) );
    itemChoice4Strings.Add( _( "1902" ) );
    itemChoice4Strings.Add( _( "1903" ) );
    itemChoice4Strings.Add( _( "1904" ) );
    itemChoice4Strings.Add( _( "1905" ) );
    itemChoice4Strings.Add( _( "1906" ) );
    itemChoice4Strings.Add( _( "1907" ) );
    itemChoice4Strings.Add( _( "1908" ) );
    itemChoice4Strings.Add( _( "1909" ) );
    itemChoice4Strings.Add( _( "1910" ) );
    itemChoice4Strings.Add( _( "1911" ) );
    itemChoice4Strings.Add( _( "1912" ) );
    itemChoice4Strings.Add( _( "1913" ) );
    itemChoice4Strings.Add( _( "1914" ) );
    itemChoice4Strings.Add( _( "1915" ) );
    itemChoice4Strings.Add( _( "1916" ) );
    itemChoice4Strings.Add( _( "1917" ) );
    itemChoice4Strings.Add( _( "1918" ) );
    itemChoice4Strings.Add( _( "1919" ) );
    itemChoice4Strings.Add( _( "1920" ) );
    itemChoice4Strings.Add( _( "1921" ) );
    itemChoice4Strings.Add( _( "1922" ) );
    itemChoice4Strings.Add( _( "1923" ) );
    itemChoice4Strings.Add( _( "1924" ) );
    itemChoice4Strings.Add( _( "1925" ) );
    itemChoice4Strings.Add( _( "1926" ) );
    itemChoice4Strings.Add( _( "1927" ) );
    itemChoice4Strings.Add( _( "1928" ) );
    itemChoice4Strings.Add( _( "1929" ) );
    itemChoice4Strings.Add( _( "1930" ) );
    itemChoice4Strings.Add( _( "1931" ) );
    itemChoice4Strings.Add( _( "1932" ) );
    itemChoice4Strings.Add( _( "1933" ) );
    itemChoice4Strings.Add( _( "1934" ) );
    itemChoice4Strings.Add( _( "1935" ) );
    itemChoice4Strings.Add( _( "1936" ) );
    itemChoice4Strings.Add( _( "1937" ) );
    itemChoice4Strings.Add( _( "1938" ) );
    itemChoice4Strings.Add( _( "1939" ) );
    itemChoice4Strings.Add( _( "1940" ) );
    itemChoice4Strings.Add( _( "1941" ) );
    itemChoice4Strings.Add( _( "1942" ) );
    itemChoice4Strings.Add( _( "1943" ) );
    itemChoice4Strings.Add( _( "1944" ) );
    itemChoice4Strings.Add( _( "1945" ) );
    itemChoice4Strings.Add( _( "1946" ) );
    itemChoice4Strings.Add( _( "1947" ) );
    itemChoice4Strings.Add( _( "1948" ) );
    itemChoice4Strings.Add( _( "1949" ) );
    itemChoice4Strings.Add( _( "1950" ) );
    itemChoice4Strings.Add( _( "1951" ) );
    itemChoice4Strings.Add( _( "1952" ) );
    itemChoice4Strings.Add( _( "1953" ) );
    itemChoice4Strings.Add( _( "1954" ) );
    itemChoice4Strings.Add( _( "1955" ) );
    itemChoice4Strings.Add( _( "1956" ) );
    itemChoice4Strings.Add( _( "1957" ) );
    itemChoice4Strings.Add( _( "1958" ) );
    itemChoice4Strings.Add( _( "1959" ) );
    itemChoice4Strings.Add( _( "1960" ) );
    itemChoice4Strings.Add( _( "1961" ) );
    itemChoice4Strings.Add( _( "1962" ) );
    itemChoice4Strings.Add( _( "1963" ) );
    itemChoice4Strings.Add( _( "1964" ) );
    itemChoice4Strings.Add( _( "1965" ) );
    itemChoice4Strings.Add( _( "1966" ) );
    itemChoice4Strings.Add( _( "1967" ) );
    itemChoice4Strings.Add( _( "1968" ) );
    itemChoice4Strings.Add( _( "1969" ) );
    itemChoice4Strings.Add( _( "1970" ) );
    itemChoice4Strings.Add( _( "1971" ) );
    itemChoice4Strings.Add( _( "1972" ) );
    itemChoice4Strings.Add( _( "1973" ) );
    itemChoice4Strings.Add( _( "1974" ) );
    itemChoice4Strings.Add( _( "1975" ) );
    itemChoice4Strings.Add( _( "1976" ) );
    itemChoice4Strings.Add( _( "1977" ) );
    itemChoice4Strings.Add( _( "1978" ) );
    itemChoice4Strings.Add( _( "1979" ) );
    itemChoice4Strings.Add( _( "1980" ) );
    itemChoice4Strings.Add( _( "1981" ) );
    itemChoice4Strings.Add( _( "1982" ) );
    itemChoice4Strings.Add( _( "1983" ) );
    itemChoice4Strings.Add( _( "1984" ) );
    itemChoice4Strings.Add( _( "1985" ) );
    itemChoice4Strings.Add( _( "1986" ) );
    itemChoice4Strings.Add( _( "1987" ) );
    itemChoice4Strings.Add( _( "1988" ) );
    itemChoice4Strings.Add( _( "1989" ) );
    itemChoice4Strings.Add( _( "1990" ) );
    itemChoice4Strings.Add( _( "1991" ) );
    itemChoice4Strings.Add( _( "1992" ) );
    itemChoice4Strings.Add( _( "1993" ) );
    itemChoice4Strings.Add( _( "1994" ) );
    itemChoice4Strings.Add( _( "1995" ) );
    itemChoice4Strings.Add( _( "1996" ) );
    itemChoice4Strings.Add( _( "1997" ) );
    itemChoice4Strings.Add( _( "1998" ) );
    itemChoice4Strings.Add( _( "1999" ) );
    itemChoice4Strings.Add( _( "2000" ) );
    itemChoice4Strings.Add( _( "2001" ) );
    itemChoice4Strings.Add( _( "2002" ) );
    itemChoice4Strings.Add( _( "2003" ) );
    itemChoice4Strings.Add( _( "2004" ) );
    itemChoice4Strings.Add( _( "2005" ) );
    itemChoice4Strings.Add( _( "2006" ) );
    itemChoice4Strings.Add( _( "2007" ) );
    itemChoice4Strings.Add( _( "2008" ) );
    itemChoice4Strings.Add( _( "2009" ) );
    itemChoice4Strings.Add( _( "2010" ) );
    itemChoice4Strings.Add( _( "2011" ) );
    itemChoice4Strings.Add( _( "2012" ) );
    itemChoice4Strings.Add( _( "2013" ) );
    itemChoice4Strings.Add( _( "2014" ) );
    itemChoice4Strings.Add( _( "2015" ) );
    itemChoice4Strings.Add( _( "2016" ) );
    itemChoice4Strings.Add( _( "2017" ) );
    itemChoice4Strings.Add( _( "2018" ) );
    itemChoice4Strings.Add( _( "2019" ) );
    itemChoice4Strings.Add( _( "2020" ) );
    itemChoice4Strings.Add( _( "2021" ) );
    itemChoice4Strings.Add( _( "2022" ) );
    itemChoice4Strings.Add( _( "2023" ) );
    itemChoice4Strings.Add( _( "2024" ) );
    wxChoice* itemChoice4
        = new wxChoice( itemDialog1, ID_CHOICE1, wxDefaultPosition,
                        wxDefaultSize, itemChoice4Strings, 0 );
    itemBoxSizer1->Add( itemChoice4, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5 );

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer( wxHORIZONTAL );
    itemBoxSizer2->Add( itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL | wxALL,
                        5 );

    wxArrayString itemCheckListBox4Strings;
    itemCheckListBox4Strings.Add( _( "Booklet" ) );
    itemCheckListBox4Strings.Add( _( "Booklet Pane:" ) );
    itemCheckListBox4Strings.Add( _( "Gutter Pair" ) );
    itemCheckListBox4Strings.Add( _( "Mini Sheet" ) );
    itemCheckListBox4Strings.Add( _( "Se-tenant" ) );
    itemCheckListBox4Strings.Add( _( "Souvenir Sheet:" ) );
    itemCheckListBox4Strings.Add( _( "Stamp" ) );
    itemCheckListBox4Strings.Add( _( "Stamp with Attached Label" ) );
    itemCheckListBox4Strings.Add(
        wxGetTranslation( wxString( wxT( "T" ) ) + (wxChar)0x00EA
                          + wxT( "te-b" ) + (wxChar)0x00EA + wxT( "che" ) ) );
    itemCheckListBox4Strings.Add( _( "Unknown" ) );
    wxCheckListBox* itemCheckListBox4 = new wxCheckListBox(
        itemDialog1, ID_CHECKLISTBOX1, wxDefaultPosition, wxDefaultSize,
        itemCheckListBox4Strings, wxLB_SINGLE );
    itemBoxSizer3->Add( itemCheckListBox4, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                        5 );

    wxArrayString itemCheckListBox5Strings;
    itemCheckListBox5Strings.Add( _( "Air Post " ) );
    itemCheckListBox5Strings.Add( _( "Air Post Official " ) );
    itemCheckListBox5Strings.Add( _( "Air Post Semi-Postal " ) );
    itemCheckListBox5Strings.Add( _( "ATM labels" ) );
    itemCheckListBox5Strings.Add( _( "Cinderella " ) );
    itemCheckListBox5Strings.Add( _( "Commemorative " ) );
    itemCheckListBox5Strings.Add( _( "Definitive " ) );
    itemCheckListBox5Strings.Add( _( "Hunting Permit " ) );
    itemCheckListBox5Strings.Add( _( "Illegal         " ) );
    itemCheckListBox5Strings.Add( _( "Insured Letter " ) );
    itemCheckListBox5Strings.Add( _( "Military " ) );
    itemCheckListBox5Strings.Add( _( "Newspaper " ) );
    itemCheckListBox5Strings.Add( _( "Official" ) );
    itemCheckListBox5Strings.Add( _( "Parcel Post " ) );
    itemCheckListBox5Strings.Add( _( "Personal Delivery " ) );
    itemCheckListBox5Strings.Add( _( "Personalized " ) );
    itemCheckListBox5Strings.Add( _( "Postage Due " ) );
    itemCheckListBox5Strings.Add( _( "Postal Tax " ) );
    itemCheckListBox5Strings.Add( _( "Precancelled " ) );
    itemCheckListBox5Strings.Add( _( "Private " ) );
    itemCheckListBox5Strings.Add( _( "Regional " ) );
    itemCheckListBox5Strings.Add( _( "Registration " ) );
    itemCheckListBox5Strings.Add( _( "Revenue" ) );
    itemCheckListBox5Strings.Add( _( "Semi-Postal    " ) );
    itemCheckListBox5Strings.Add( _( "War Tax " ) );
    wxCheckListBox* itemCheckListBox5 = new wxCheckListBox(
        itemDialog1, ID_CHECKLISTBOX, wxDefaultPosition, wxDefaultSize,
        itemCheckListBox5Strings, wxLB_SINGLE );
    itemBoxSizer3->Add( itemCheckListBox5, 0, wxALIGN_CENTER_VERTICAL | wxALL,
                        5 );

     // FilterDialog content construction
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE
 */

void FilterDialog::OnChoiceSelected( wxCommandEvent& event )
{
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE in
    // Filter.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE in
    // Filter.
}

/*
 * wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE1
 */

void FilterDialog::OnChoice1Selected( wxCommandEvent& event )
{
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE1 in
    // Filter.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_CHOICE1 in
    // Filter.
}

/*
 * wxEVT_COMMAND_LISTBOX_DOUBLECLICKED event handler for ID_CHECKLISTBOX1
 */

void FilterDialog::OnChecklistbox1DoubleClicked( wxCommandEvent& event )
{
     // wxEVT_COMMAND_LISTBOX_DOUBLECLICKED event handler for
    // ID_CHECKLISTBOX1 in Filter.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_LISTBOX_DOUBLECLICKED event handler for
    // ID_CHECKLISTBOX1 in Filter.
}

/*
 * wxEVT_COMMAND_LISTBOX_DOUBLECLICKED event handler for ID_CHECKLISTBOX
 */

void FilterDialog::OnChecklistboxDoubleClicked( wxCommandEvent& event )
{
     // wxEVT_COMMAND_LISTBOX_DOUBLECLICKED event handler for
    // ID_CHECKLISTBOX in Filter.
    // Before editing this code, remove the block markers.
    event.Skip( );
     // wxEVT_COMMAND_LISTBOX_DOUBLECLICKED event handler for
    // ID_CHECKLISTBOX in Filter.
}

/*
 * Should we show tooltips?
 */

bool FilterDialog::ShowToolTips( )
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap FilterDialog::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
     // FilterDialog bitmap retrieval
    wxUnusedVar( name );
    return wxNullBitmap;
     // FilterDialog bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon FilterDialog::GetIconResource( const wxString& name )
{
    // Icon retrieval
     // FilterDialog icon retrieval
    wxUnusedVar( name );
    return wxNullIcon;
     // FilterDialog icon retrieval
}
